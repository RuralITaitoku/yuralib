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
enum Panel {
    Left,
    Right,
}
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
    let mut rx:i32 = 0;
    let mut ry:i32 = 0;
    let mut lx:i32 = 0;
    let mut ly:i32 = 0;
    let mut panel:Panel = Panel::Left;
    loop {
        let _test_c = utils::readline(timeout);
        match _test_c {
            Ok(c) => {
                if c == 'h' {
                    panel = Panel::Right;
                    rx = rx - 1;
                    if rx < 0 {rx = 0};
                }
                if c == 'j' {
                    panel = Panel::Right;
                    ry = ry + 1;
                    if ry > height as i32 {ry = height as i32};
                }
                if c == 'k' {
                    panel = Panel::Right;
                    ry = ry - 1;
                    if ry < 0 {ry = 0};
                }
                if c == 'l' {
                    panel = Panel::Right;
                    rx = rx + 1;
                    if rx > width as i32 {rx = width as i32};
                }
                if c == 's' {
                    panel = Panel::Left;
                    lx = lx - 1;
                    if lx < 0 {lx = 0};
                }
                if c == 'f' {
                    panel = Panel::Left;
                    ly = ly + 1;
                    if ly > height as i32 {ly = height as i32};
                }
                if c == 'd' {
                    panel = Panel::Left;
                    ly = ly - 1;
                    if ly < 0 {ly = 0};
                }
                if c == 'g' {
                    panel = Panel::Left;
                    lx = lx + 1;
                    if lx > width as i32 {lx = width as i32};
                }
                execute! (
                    stdout(),
                    Clear(ClearType::All),
                    MoveTo(rx as u16, ry as u16),
                    Print("R"),
                    MoveTo(lx as u16, ly as u16),
                    Print("L")
                )?;
                match panel {
                    Panel::Left => {
                        execute! (
                            stdout(),
                            MoveTo(lx as u16, ly as u16),
                        )?;
                    },
                    Panel::Right => {
                        execute! (
                            stdout(),
                            MoveTo(rx as u16, ry as u16),
                        )?;
                    },
                }
                if c == 'q' {
                    println!("quit");
                    break Ok(());
                }
            },
            _ => {},
        }
    }
    // Ok(())
}
