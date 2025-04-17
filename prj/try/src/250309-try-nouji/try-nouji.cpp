

#include "task.hpp"


#include <fstream>
#include <sstream>

std::string readFileToString(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        return filename; // ファイルが開けなかった場合は空文字列を返す
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}


//#include <vector>

std::vector<std::string> splitLines(const std::string& text) {
  std::vector<std::string> lines;
  std::stringstream ss(text);
  std::string line;

  while (std::getline(ss, line)) {
    lines.push_back(line);
  }

  return lines;
}

std::vector<std::string> splitString(const std::string& text) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = text.find(' ');
  
    while (end != std::string::npos) {
      tokens.push_back(text.substr(start, end - start));
      start = end + 1;
      end = text.find(' ', start);
    }
  
    tokens.push_back(text.substr(start)); // 最後のトークンを追加
  
    return tokens;
  }

int main(int argc, char **argv) {
    std::string file_name="test.txt";
    if (argc > 1) {
        file_name = argv[1];
    }
    std::cout << "file_name=" << file_name << std::endl;
    std::string content = readFileToString(file_name);
    std::cout << content << std::endl;

    auto lines = splitLines(content);
    int i = 0;
    for (const auto line: lines) {
        //std::cout << (i++) << " -- " << line << std::endl;
        auto tokens = splitString(line);
        for (auto t: tokens) {
            if (t == "江島北") {
                std::cout << " " << std::endl;
            }
            std::cout << t;
        }
        std::cout << std::endl;
    }
}
 