#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "rng.hpp"
#include "yuraterm.hpp"

std::string esc_home() {
    return "\e[H";
}
std::string esc_end() {
    return "\e[0m";
}
std::string esc_fg(int color) {
    std::string result = "\e[3";
    result += std::to_string(color);
    result += "m";
    return result;
}
std::string esc_bg(int color) {
    std::string result = "\e[4";
    result += std::to_string(color);
    result += "m";
    return result;
}


void debug(const std::vector< std::vector<double> > &mat) {

    std::cout << esc_home();
    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat[i].size(); ++j) {
            std::cout << esc_fg(1) << std::setw(4) << mat[i][j] << esc_end();
        }
        std::cout << std::endl;
    }
}

inline uint32_t xy2id(int x, int y) {
    return (x << 16) + y;
}
inline int id2rows(uint32_t id) {
    return (id >> 16);
}
inline int id2cols(uint32_t id) {
    return id & 0xffff;
}


TEST(DijkstraTest, 01) {
    int rows = 40;
    int cols = 30;
    // コンストラクタ
    LinearCongruentialGenerator rnd(0);

    std::vector< std::vector<double> > dijkstra(rows, std::vector<double>(cols));
    std::vector< std::vector<int8_t> > state(rows, std::vector<int8_t>(cols, 0));
    std::vector< std::vector<int> > from_id(rows, std::vector<int>(cols, -1));
    std::vector< std::vector<double> > min(rows, std::vector<double>(cols, std::numeric_limits<double>::max()));
    std::vector< int > id_list;

    for (int i = rows; i--;) {
        for (int j = cols; j--;) {
            dijkstra[i][j] = rnd.next(0, 100);
        }
    }
    int s_col = 1;
    int s_row = 1;
    // 繰り返し
    char ch;

    yuraterm yura;

    uint32_t min_id = xy2id(s_row, s_col);
    from_id[s_row][s_col] = min_id;
    min[s_row][s_col] = 0.0;
    int lhand = 0;
    int rhand = lhand;
    for (;;) {
        // 最小から繋がるノードを探してそのノードに距離を設定する。
        state[s_row][s_col] = 2;
        double s_cost = min[s_row][s_col];
        double k = 0.0;
        int min_id = -1;
        int i = s_row - 1;
        if (i < 0) {
            i = 0;
        }
        double min_cost = std::numeric_limits<double>::max();
        for (;  (i <= s_row + 1) && (i <= rows); ++i) {
            int j = s_col - 1;
            if (s_col < 0) {
                s_col = 0;
            }
            for (; j <= s_col + 1; ++j) {
                if (state[i][j] == 2) {
                    continue;
                }
                id_list.push_back(xy2id(i,j));
                if ((i == s_row) || (j == s_col)) {
                    k = 1.0;
                } else  {
                    k = std::sqrt(2.0);
                }
                double pre_cost = min[i][j];
                double cost = s_cost + k * dijkstra[i][j];
                if (cost < pre_cost){
                    min[i][j] = cost;
                }


            }
        }

        // 最小を探す。

        ch = getchar();
        if (ch == 'q') {
            break;
        }
    }


    debug(dijkstra);
}

