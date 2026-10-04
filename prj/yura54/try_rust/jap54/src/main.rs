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
    // println!("3秒以内に何かキーを押してください...");

    let (width, height) = terminal::size()?;

    println!("幅: {}, 高さ: {}", width, height);
    let put = | x:i32, y:i32 | {
        let _ = execute! (
            stdout(),
            MoveTo(x as u16, y as u16),
            Print("X")
        );
    };
    utils::draw_line(0, 0, 10, 10, put);

    // 1. タイムアウト時間を設定 (例: 3秒)
    let timeout = Duration::from_secs(3);
    let mut x:i32 = 0;
    let mut y:i32 = 0;
    loop {
        let _test_c = utils::readline(timeout);
        match _test_c {
            Ok(c) => {
                if c == 'h' {
                    x = x - 1;
                    if x < 0 {x = 0};
                }
                if c == 'j' {
                    y = y + 1;
                    if y > height as i32 {y = height as i32};
                }
                if c == 'k' {
                    y = y - 1;
                    if y < 0 {y = 0};
                }
                if c == 'l' {
                    x = x + 1;
                    if x > width as i32 {x = width as i32};
                }
                execute! (
                    stdout(),
                    Clear(ClearType::All),
                    MoveTo(x as u16, y as u16),
                    Print("x:{x} y:{y}")
                )?;
                // println!("\n入力された文字: {c}  x:{x} y:{y}");
                if c == 'q' {
                    break Ok(());
                }
            },
            _ => {},
        }
    }
    // Ok(())
}
