#include <gtest/gtest.h>
#include <vector>




// テストケースの例
TEST(DijkstraTest, Addition) {
    int dim = 7;
    double big = 1.0e+10;
    std::vector< std::vector<double> > dijkstra = {
        {0,2,8,4,-1,-1,-1},
        {2,0,-1,-1,3,-1,-1},
        {8,-1,0,-1,2,3,-1},
        {4,-1,-1,0,-1,8,-1},
        {-1,3,2,-1,0,-1,9},
        {-1,-1,3,8,-1,0,3},
        {-1,-1,-1,-1,9,3,0}
    };
    int n_point=dim;/* 地点の数 */
    int sp = 0;/* 出発地の地点番号 */
    int dp =6;/* 目的地の地点番号 */
    double result;

    double s_dist = big;/* 出発地から目的地までの最短距離 */
    // 最短経路
    std::vector<int> s_route(dim, -1);

    // 計算用
    std::vector<double> p_disp(dim, big);
    std::vector<bool> f_fixed(dim, false);
    int sPoint,newDist;

    // 最初のノードには、0を設定
    p_disp[sp] = 0.0;

    for(;;) {
        int i = 0;


    }

    EXPECT_EQ(result, 13);
}


