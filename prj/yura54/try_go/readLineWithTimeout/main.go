package main

import (
	"bufio"
	"fmt"
    "log"
	"os"
	"time"
	"database/sql"
	_ "modernc.org/sqlite" // Pure Goドライバ
)

func readLineWithTimeout(timeout time.Duration) (string, error) {
	type result struct {
		text string
		err  error
	}
	ch := make(chan result, 1)

	// 1. バックグラウンドで1行読み込み
	go func() {
		scanner := bufio.NewScanner(os.Stdin)
		if scanner.Scan() {
			ch <- result{text: scanner.Text()}
		} else {
			ch <- result{err: scanner.Err()}
		}
	}()

	// 2. 入力完了とタイムアウトの監視
	select {
	case res := <-ch:
		return res.text, res.err
	case <-time.After(timeout):
		return "", fmt.Errorf("タイムアウトしました")
	}
}
type User struct {
	ID   int
	Name string
	Age  int
}
func testDb() {
    db, err := sql.Open("sqlite", "./example.db?_busy_timeout=5000&_journal_mode=WAL")
    if err != nil {
        log.Fatal(err)
    }
    // 接続数を1に制限して書き込み衝突を完全に防止（必要に応じて）
    db.SetMaxOpenConns(1)
    defer db.Close()

    // 2. テーブルの作成
	createTableSQL := `CREATE TABLE IF NOT EXISTS users (
		id INTEGER PRIMARY KEY AUTOINCREMENT,
		name TEXT NOT NULL,
		age INTEGER
	);`
	_, err = db.Exec(createTableSQL)
	if err != nil {
		log.Fatalf("テーブル作成エラー: %v", err)
	}

    // 3. データの挿入（プリペアドステートメントの使用）
	insertSQL := `INSERT INTO users(name, age) VALUES(?, ?)`
	stmt, err := db.Prepare(insertSQL)
	if err != nil {
		log.Fatal(err)
	}
	defer stmt.Close()

	res, err := stmt.Exec("Alice", 25)
	if err != nil {
		log.Fatal(err)
	}
	lastID, _ := res.LastInsertId()
	fmt.Printf("追加したユーザーのID: %d\n", lastID)
    // 4. データの取得
	rows, err := db.Query("SELECT id, name, age FROM users")
	if err != nil {
		log.Fatal(err)
	}
	defer rows.Close()

	fmt.Println("--- ユーザー一覧 ---")
	for rows.Next() {
		var u User
		if err := rows.Scan(&u.ID, &u.Name, &u.Age); err != nil {
			log.Fatal(err)
		}
		fmt.Printf("ID: %d, Name: %s, Age: %d\n", u.ID, u.Name, u.Age)
	}
}
func main() {
	timeout := 1 * time.Second
	fmt.Print("1秒以内にテキストを入力してEnterを押してください: ")

    testDb()
    for {
        text, err := readLineWithTimeout(timeout)
        if err != nil {
            fmt.Printf("\nエラー: %v", err)
        } else {
            fmt.Printf("入力された文字列: %s\n", text)
            return
        }
    }
}
