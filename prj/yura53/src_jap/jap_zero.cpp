#include "jap_zero.hpp"
#include "ivvi.hpp"
#include "jap_csv.hpp"
#include <cstdlib>
#include <memory>
#include <fstream>

std::ofstream debug_log("japlog.txt");

template <typename T>
class TypeCheck;
#define DP(x) std::cout << __FILE__ << ":" << __LINE__ << " " << x << std::endl;

bool jap_zero::run(std::string &cmd, std::vector<std::string> &stack)
{
    if (cmd == "jap0" || cmd == "jf")
    {
    }
    return false;
}

void jap_zero::system(std::string &cmd)
{
    std::cout << "-----------------------" << std::endl;
    std::cout << yuraterm::fg(2) << cmd << yuraterm::end() << std::endl;
    auto result = std::system(cmd.c_str());
    if (result == 0)
    {
        std::cout << "正常終了" << std::endl;
        std::cout << "--------------------" << std::endl;
    }
    else
    {
        std::cout << "異常終了:" << result << std::endl;
    }
}

std::string jap_zero::escape(std::string &str)
{
    std::string result;

    for (size_t i = 0; i < str.size(); ++i)
    {
        auto ch = str[i];
        if (ch == '\\')
        {
            result += ch;
            i++;
        }
        else if (ch == '"')
        {
            result += '\\';
            result += ch;
        }
        else
        {
            result += ch;
        }
    }
    return result;
}
std::string getWeek(int i)
{
    std::vector<std::string> weeks = {"月", "火", "水", "木", "金", "土", "日"};
    return weeks[i % 7];
}

class save_csv_tsv : public jap {
public:
    virtual ~save_csv_tsv() {}
    std::string help() {
        std::string help;
        help += "-\n";
        help += "ファイル名\n";
        help += "save : スタックの先頭からをファイル名で保存\n";
        help += "-\n";
        help += "save_csv_to_tsv:\n";
        help += "-\n";
        help += "csv_to_tsv:\n";
        return help;
    }

    bool run(std::string &cmd, std::vector<std::string> &stack) {
        if (cmd == "save") {
            auto filename = stack.back();
            stack.pop_back();
            std::cout << "filename=" << filename << std::endl;
            std::ostringstream oss;
            for (auto line: stack) {
                oss << line << std::endl;
            }
            yura::save(filename, oss.str());
            return true;
        }
        if (cmd == "csv_to_tsv") {
            for (size_t i = 0; i < stack.size(); i++) {
                auto vec = yura::split(stack[i], ",");
                std::string result;
                for (auto a: vec) {
                    result += yura::trim(a);
                    result += "\t";
                }
                stack[i] = result;
            }
            return true;
        }
        if (cmd == "save_csv_to_tsv") {
            std::cout << "セーブな感じtsv" << std::endl;
            return true;
        }
        return false;
    }
};


std::vector<std::shared_ptr<jap>> jap_vec;
void jap_zero::main()
{
    std::string git_cmd("git pull");
    system(git_cmd);
    std::string line;
    std::vector<std::string> stack;
    std::cout << "-" << std::endl;
    jap_vec.push_back(std::make_shared<save_csv_tsv>());
    for (;;) {
        getline(std::cin, line);
        if (line == ".")
        {
            if (stack.size())
            {
                std::cout << stack.back() << std::endl;
                stack.pop_back();
            }
        }
        else if (line == "..")
        {
            std::cout << "-stack-" << stack.size() << std::endl;
            if (stack.size())
            {
                for (size_t i = 0; i < stack.size(); i++)
                {
                    std::cout << i << ":" << stack[i] << std::endl;
                }
            }
            std::cout << "-" << std::endl;
        }
        else if (line == "clear")
        {
            stack.clear();
        }
        else if (line == "drop")
        {
            if (stack.size())
            {
                stack.pop_back();
            }
        }
        else if (line == "s" || line == "status")
        {
            git_cmd = "git status";
            system(git_cmd);
        }
        else if (line == "d" || line == "diff")
        {
            git_cmd = "git diff";
            system(git_cmd);
        }
        else if (line == "a" || line == "add")
        {
            git_cmd = "git add .;git status";
            system(git_cmd);
        }
        else if (line == "b" || line == "branch")
        {
            git_cmd = "git branch -a -vv";
            system(git_cmd);
        }
        else if (line == "c" || line == "commit")
        {
            git_cmd = "git commit -m \"";
            auto msg = stack.back();
            git_cmd += escape(msg);
            git_cmd += '\"';
            system(git_cmd);
        }
        else if (line == "iv")
        {
            std::cout << "iv" << std::endl;
            ivvi edit;
            edit.run(line, stack);
        }
        else if (line == "today") {
            auto ymd = yura::today();
            stack.push_back(std::to_string(ymd));
        }
        else if (line == "td")
        {
            auto ymd = std::stoi(stack.back());
            stack.pop_back();
            for (int i = 0; i < 33; i++)
            {
                auto weekday = yura::weekday_string(ymd);
                std::string str = std::to_string(ymd / 10000) + "年" + std::to_string(ymd / 100 % 100) + "月" + std::to_string(ymd % 100) + "日(" + weekday + ")";
                stack.push_back(str);
                if (weekday == "月" || weekday == "土") {
                    debug_log << "---" << std::endl;
                }
                debug_log << "- [" << str << "]" << std::endl; 
                ymd = yura::add_days(ymd, 1);
            }
        }
        else if (line == "p" || line == "push")
        {
            git_cmd = "git push";
            system(git_cmd);
        }
        else if (line == "q")
        {
            std::cout << "jap終了" << std::endl;
            return;
        }
        else
        {
            bool run_jap = false;
            for (auto jap : jap_vec) {
                if (jap->run(line, stack) == true) {
                    run_jap = true;
                    break;
                }
            }
            if (run_jap == false) {
                stack.push_back(line);
            }
        }
    }
}

int main()
{
    std::cout << "jap" << std::endl;
    jap_zero jap0;

    jap0.main();
}
