use std::time::Duration;

mod utils;

fn main() -> std::io::Result<()> {
    println!("3秒以内に何かキーを押してください...");

    // 1. タイムアウト時間を設定 (例: 3秒)
    let timeout = Duration::from_secs(3);
    loop {
        let _test_c = utils::readline(timeout);
        match _test_c {
            Ok(c) => {
                println!("\n入力された文字: {}", c);
                if c == 'q' {
                    break Ok(());
                }
            },
            _ => {},
        }
    }
    // Ok(())
}
