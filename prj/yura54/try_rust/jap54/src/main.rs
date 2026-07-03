use crossterm::event::{self, Event, KeyCode};
use std::time::Duration;

fn main() -> std::io::Result<()> {
    println!("3秒以内に何かキーを押してください...");

    // 1. タイムアウト時間を設定 (例: 3秒)
    let timeout = Duration::from_secs(3);

    // 2. ターミナルを「生モード(Raw mode)」にする
    // これをしないと、エンターキーを押すまで入力がプログラムに渡りません
    crossterm::terminal::enable_raw_mode()?;

    // poll でイベントが来るのを待つ（タイムアウト付き）
    if event::poll(timeout)? {
        // イベントが存在する場合、それを読み込む
        if let Event::Key(key_event) = event::read()? {
            // キー離した時のイベントなどを除外（主にWindows対策）
            if key_event.kind == event::KeyEventKind::Press {
                // 生モードを一度解除して標準出力を見やすくする
                crossterm::terminal::disable_raw_mode()?;
                
                match key_event.code {
                    KeyCode::Char(c) => println!("\n入力された文字: {}", c),
                    KeyCode::Esc => println!("\nEscキーが押されました"),
                    _ => println!("\nその他のキーが押されました: {:?}", key_event.code),
                }
            } else {
                // プレス以外のイベントだった場合は生モードを解除
                crossterm::terminal::disable_raw_mode()?;
            }
        }
    } else {
        // タイムアウトした場合
        crossterm::terminal::disable_raw_mode()?;
        println!("\nタイムアウトしました！何も入力されませんでした。");
    }

    Ok(())
}
