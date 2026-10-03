use std::time::Duration;
use crossterm::{
    cursor::MoveTo,
    style::Print,
    terminal,
    terminal::{Clear, ClearType},
    execute,
};
use std::io::stdout;

mod utils;

fn main() -> std::io::Result<()> {
    println!("3秒以内に何かキーを押してください...");

    let (width, height) = terminal::size()?;

    println!("幅: {}, 高さ: {}", width, height);
    // 1. タイムアウト時間を設定 (例: 3秒)
    let timeout = Duration::from_secs(1);
    let mut x = 0;
    let mut y = 0;

    loop {
        let _test_c = utils::readline(timeout);
        match _test_c {
            Ok(c) => {
                if c == 'h' {
                    x = if x <= 1 { 1 } else { x - 1 };
                }
                if c == 'j' {
                    y = if y >= height { height } else { y + 1 };
                }
                if c == 'k' {
                    y = if y <= 1 { 1 } else { y - 1 };
                }
                if c == 'l' {
                    x = if x >= width { width } else { x + 1 };
                }
                execute! (
                    stdout(),
                    Clear(ClearType::All),
                    MoveTo(x, y),
                    Print("test x:{x} y:{y}")
                )?;
                println!("\n入力された文字: {c}  x:{x} y:{y}");
                if c == 'q' {
                    break Ok(());
                }
            },
            _ => {},
        }
    }
    // Ok(())
}
