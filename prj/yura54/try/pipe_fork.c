#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int parent_to_child[2]; // 親から子へ (stdin用)
    int child_to_parent[2]; // 子から親へ (stdout用)

    if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // --- 子プロセス ---
        // 読み込み側: pipe[0], 書き込み側: pipe[1]
        
        dup2(parent_to_child[0], STDIN_FILENO);  // 標準入力をパイプに繋ぎ変える
        dup2(child_to_parent[1], STDOUT_FILENO); // 標準出力をパイプに繋ぎ変える

        // 不要なファイルディスクリプタを閉じる
        close(parent_to_child[0]);
        close(parent_to_child[1]);
        close(child_to_parent[0]);
        close(child_to_parent[1]);

        execlp("sort", "sort", NULL); // sortコマンド実行
        perror("execlp");
        exit(1);
    } else {
        // --- 親プロセス ---
        close(parent_to_child[0]); // 親は書き込むので読み取り側は不要
        close(child_to_parent[1]); // 親は読み取るので書き込み側は不要

        // 1. 子プロセスにデータを送る
        FILE *out = fdopen(parent_to_child[1], "w");
        fprintf(out, "orange\napple\nbanana\n");
        fclose(out); // ここで閉じることで子プロセスに EOF が伝わり、sortが動き出す

        // 2. 子プロセスからの結果を読み出す
        FILE *in = fdopen(child_to_parent[0], "r");
        char buf[100];
        while (fgets(buf, sizeof(buf), in)) {
            printf("Sorted: %s", buf);
        }
        fclose(in);

        waitpid(pid, NULL, 0); // 子プロセスの終了を待つ
    }

    return 0;
}
