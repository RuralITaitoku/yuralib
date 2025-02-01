#include <iostream>

#ifndef __UTF8LINES__
#define __UTF8LINES__

#define DP(x) std::cout << __FILE__ << ":" << __LINE__ << " " << x << std::endl

class utf8lines {
public:
    std::vector<char> line;


    void debug_print() {
        std::cout << "debug_print" << std::endl;
    }
    utf8lines& operator=(const std::string& str) {
        for (char ch : str) {
            line.push_back(ch);
        }
        return *this;
    }

    bool operator==(const utf8lines& other) const {
        return line == other.line;
    }
    bool operator==(const std::string& str) const {
        if (str.size() != line.size()) {
            return false;
        }
        for (int i = 0; i < str.size(); ++i) {
            char ch1 = line[i];
            char ch2 = str[i];
            if (ch1 != ch2) {
                return false;
            }
        }
        return true;
    }

    void put(int j, const std::string& str) {
        if (line.size() < (j + str.size())) {
            int last = j + str.size();
            for (int left = line.size(); left < last; ++left) {
                line.push_back(' ');
            }
        }
        int left = j;
        for (char ch : str) {
            line[left] = ch;
            left++;
        }
    }
    int get(std::string& str, int i, int size) {
        DP("get");
        for (int j = size; j--;) {
            DP("j=" << j);
            if (i < line.size()) {
                str += line[i++];
            }
        }
        return i;
    }

    int next(int index, std::string& str, int& dw) {
        unsigned char ch = line[index];
        str.clear();
        if (ch < 0x80) {
            dw++;
            index = get(str, index, 1);
        } else if (ch < 0xc0) {
            do {
                index ++;
                if (index >= line.size()) {
                    return index;
                }
                ch = line[index];
            } while((0x80 <= ch) && (ch < 0xc0));
            return index;
        } else if (ch < 0xe0) {
            dw+=2;
            index = get(str, index, 2);
        } else if (ch < 0xf7) {
            dw+=2;
            index = get(str, index, 4);
        } else if (ch < 0xfc) {
            dw+=2;
            index = get(str, index, 5);
        } else  {
            dw+=2;
            index = get(str, index, 6);
        }
        return index;
    }

    int prev(int index, std::string& str) {
        for(;;) {
            index--;
            unsigned char ch = line[index];
            if (ch < 0x80) {
                get(str, index, 1);
                return index;
            } else if (ch < 0xc0) {
            } else if (ch < 0xe0) {
                get(str, index, 2);
                return index;
            } else if (ch < 0xf7) {
                get(str, index, 4);
                return index;
            } else if (ch < 0xfc) {
                get(str, index, 5);
                return index;
            } else  {
                get(str, index, 6);
                return index;
            }
        }


    }

    void print(int rows=-1) {
        for (char ch: line) {
            std::cout << ch;
        };
        std::cout << std::endl;
    }

};

#endif


