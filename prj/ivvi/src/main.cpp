#include "task.hpp"
#include "ivvi.hpp"
#include <fstream>
#include <sstream>

/**
 * @brief テキストファイルを読み込む。
 * @param filename テキストファイル名
 * @return ファイルのテキスト
 */
std::string load(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    } else {
        // ファイルを開けなかった場合のエラー処理
        // ここでは空の文字列を返すが、例外を投げるなどの処理も考えられる
        return "";
    }
}
  
int main(int argc, char** argv) {

  ivvi iv;
  task_mng mng;
  std::map<std::string, std::string> circle;
  std::vector<std::string> args;
  for (int i = 0; i < argc; i++) {
    args.push_back(argv[i]);
  }

  mng.add_task(iv.screen);
  mng.add_task(iv);
  mng.setup();
  mng.loop(circle);

  return 0;
}
