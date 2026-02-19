#include <iostream>
#include <string>
#include <cstdio>

// OSごとのコマンドを判定
#if defined(__APPLE__) || defined(__MACH__)
    // macOSの場合
    #define CLIP_COMMAND "pbcopy"
#elif defined(__linux__)
    // WSLを含むLinuxの場合（Windowsの実行ファイルを作法通りに呼ぶ）
    #define CLIP_COMMAND "powershell.exe -NoProfile -Command \"Set-Clipboard\""
#elif defined(_WIN32) || defined(_WIN64)
    // 純粋なWindows(MinGW/MSVCなど)の場合
    #define CLIP_COMMAND "clip"
#else
    #error "サポートされていないOSです"
#endif

void copyToClipboard(const std::string& text) {
    FILE* pipe = popen(CLIP_COMMAND, "w");
    if (!pipe) {
        std::perror("popen failed");
        return;
    }

    fwrite(text.c_str(), sizeof(char), text.size(), pipe);
    pclose(pipe);
}

int testClipboard() {
    std::string message = "OSを自動判別してコピーしました！";
    copyToClipboard(message);

    std::cout << "使用したコマンド: " << CLIP_COMMAND << std::endl;
    return 0;
}
