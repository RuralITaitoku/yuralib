#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "rng.hpp"
#include "yuraterm.hpp"

std::string esc_home() {
    return "\e[H";
}
std::string esc_clean() {
    return "\e[2J";
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

    std::cout << esc_clean();
    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat[i].size(); ++j) {
            std::cout << esc_fg(1) << std::setw(4) << mat[i][j] << esc_end();
        }
        std::cout << std::endl;
    }
}
void debug(const std::vector< std::vector<int8_t> > &mat) {

    std::cout << esc_clean();
    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat[i].size(); ++j) {
            double v = mat[i][j];
            std::cout << esc_fg(1) << std::setw(4) << v << esc_end();
        }
        std::cout << std::endl;
    }
}
void debug(const std::vector< std::vector<double> > &mat
           , const std::vector< std::vector<int8_t> > &state) {
    std::cout << esc_clean();
    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat[i].size(); ++j) {
            int s = state[i][j];
            std::cout << esc_fg(s) << std::fixed << std::setprecision(1) << std::setw(5) << mat[i][j] << esc_end();
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
    std::vector< std::vector<double> > min(rows, std::vector<double>(cols, 0));
    std::vector< int > id_list;

    for (int i = rows; i--;) {
        for (int j = cols; j--;) {
            dijkstra[i][j] = rnd.next(0, 10);
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
        //int min_id = -1;
        int i = s_row - 1;
        if (i < 0) {
            i = 0;
        }
        for (;  (i <= s_row + 1) && (i <= rows); ++i) {
            int j = s_col - 1;
            if (j < 0) {
                j = 0;
            }
            for (; (j <= s_col + 1) && (j <= cols); ++j) {
                if (state[i][j] == 2) {
                    // 確定ノードに対しては、何もしない。
                    continue;
                }
                double k = 0.0;
                if ((i == s_row) || (j == s_col)) {
                    k = 1.0;
                } else  {
                    k = std::sqrt(2.0);
                }
                double cost = s_cost + k * dijkstra[i][j];
                if (state[i][j] == 0) {
                    // 未探索ノード
                    id_list.push_back(xy2id(i,j));
                    state[i][j] = 1;
                    min[i][j] = cost;
                } else { // if (state[i][j] == 1)
                    double pre_cost = min[i][j];
                    if (cost < pre_cost){
                        min[i][j] = cost;
                    }
                }
            }
        }
        // 最小を探す。
        double min_cost = std::numeric_limits<double>::max();
        int min_index = -1;
        for (int id_index = 0; id_index < id_list.size(); ++id_index) {
            uint32_t id = id_list[id_index];
            int row = id2rows(id);
            int col = id2cols(id);
            double cost = min[row][col];
            if (cost < min_cost) {
                min_cost = cost;
                s_row = row;
                s_col = col;
                min_index = id_index;
            }
        }
        if (min_index < 0) {
            break;
        }else {
            id_list.erase(id_list.begin() + min_index);
        }



        ch = getchar();
        if (ch == 'q') {
            break;
        }
        debug(dijkstra);
        ch = getchar();
        if (ch == 'q') {
            break;
        }
        debug(min, state);
        std::cout << "id_list.size = " << id_list.size() << std::endl;
        for (int idid : id_list) {
            std::cout << " (" << id2rows(idid) << "," << id2cols(idid) << ")";
        }
        std::cout << std::endl;
    }


}

