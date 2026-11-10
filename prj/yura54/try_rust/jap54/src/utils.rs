use crossterm::event::{self, Event, KeyCode};
use std::time::Duration;
use std::io::Error;
pub fn readline(timeout : Duration) -> std::io::Result<char> {
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
                    KeyCode::Char(c) => {
                        return Ok(c);
                    },
                    KeyCode::Esc => {
                        println!("\nEscキーが押されました");
                    },
                    _ => {
                        println!("\nその他のキーが押されました: {:?}", key_event.code);
                    },
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

    Err(Error::other("タイムアウトエラー"))
}

pub fn draw_line<F>(mut x0: i32, mut y0: i32, x1: i32, y1: i32, mut put: F)
where
    F: FnMut(i32, i32),
{
    let dx = (x1 - x0).abs();
    let dy = -(y1 - y0).abs();
    
    let sx = if x0 < x1 { 1 } else { -1 };
    let sy = if y0 < y1 { 1 } else { -1 };
    
    let mut err = dx + dy;

    loop {
        put(x0, y0); // ドットを描画

        if x0 == x1 && y0 == y1 {
            break;
        }

        let e2 = 2 * err;

        if e2 >= dy {
            err += dy;
            x0 += sx;
        }

        if e2 <= dx {
            err += dx;
            y0 += sy;
        }
    }
}
