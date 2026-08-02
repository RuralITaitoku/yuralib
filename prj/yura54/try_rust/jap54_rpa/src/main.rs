use std::process::Command;

fn send_key_to_windows(keys: &str) -> Result<(), Box<dyn std::error::Error>> {
    // PowerShellの WScript.Shell を利用してWindowsにキー入力を送る
    let script = format!(
        "$wshell = New-Object -ComObject wscript.shell; $wshell.SendKeys('{}')",
        keys
    );

    Command::new("powershell.exe")
        .args(["-NoProfile", "-Command", &script])
        .output()?;

    Ok(())
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    // 例: Windows側のアプリに "a" を送信
    send_key_to_windows("a")?;

    // 例: エンターキーを送る場合
    // send_key_to_windows("{ENTER}")?;

    Ok(())
}
