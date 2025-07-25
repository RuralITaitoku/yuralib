#include "yura_pipe.hpp"

int yura_pipe::exec(const std::string& cmd) {

    std::cout << "コマンド：" << cmd << std::endl;
    std::system(cmd.c_str());
    return 1;
}





int test_pipe() {
    FILE* pipe = nullptr; // ファイルポインタの初期化
    char buffer[128];     // コマンドの出力を格納するバッファ
    std::string result = ""; // コマンドの出力を連結する文字列

    // 実行したいコマンド
    // 例: Linux/macOS では "ls -l"、Windows では "dir"
    // 環境に合わせて変更してください。
#ifdef _WIN32
    const char* command = "dir";
#else
    const char* command = "ls -l";
#endif

    // popen を使ってコマンドを実行し、パイプを開く
    // "r" は読み込みモード (コマンドの出力を読み取る)
    pipe = popen(command, "r");

    // popen が失敗した場合のチェック
    if (!pipe) {
        std::cerr << "popen() に失敗しました！" << std::endl;
        return 1;
    }

    // パイプから出力を読み取り、result に追加していく
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    // コマンドの出力を表示
    std::cout << "コマンドの出力:\n" << result << std::endl;

    // pclose を使ってパイプを閉じる
    int status = pclose(pipe);

    // pclose の戻り値をチェック (コマンドの終了ステータス)
    if (status == -1) {
        std::cerr << "pclose() に失敗しました！" << std::endl;
        return 1;
    } else {
        if (status != 0) {
            std::cerr << "コマンドがエラーで終了しました。ステータス: " << status << std::endl;
            return 1;
        }
    }

    return 0;
}