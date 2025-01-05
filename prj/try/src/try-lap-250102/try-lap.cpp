#include <opencv2/opencv.hpp>
#include "task.hpp"



using namespace cv;

#define DP(x) std::cout << __FILE__ << ":" << __LINE__ <<":" << x  << std::endl;
#define DPM(x) std::cout << __FILE__ << ":" << __LINE__ << std::endl << x  << std::endl;


double lap(cv::Mat& cost, cv::Mat& rowsol, cv::Mat& colsol, cv::Mat& u, cv::Mat& v) {

    int dim = cost.rows;
    
    std::vector<int> free_unassigned;
    std::vector<int> collist(dim);
    std::vector<double> d(dim);
    std::vector<int> pred(dim);
    cv::Mat matches = cv::Mat(dim, 1, CV_32SC1);

    // init how many times a row will be assigned in the column reduction.
    matches = 0;

    DP("");

    // COLUMN REDUCTION
    // 列ごとにループ
    for (int j = dim; j--;) {  // reverse order gives better results.
        // find minimum cost over rows.min = assigncost[0][j];
        // 列の最小コストとその行数を探す。
        double min = cost.at<double>(0, j);
        int index_min = 0;
        for (int i = 1; i < dim; i++) {
            if (cost.at<double>(i, j) < min) {
                min = cost.at<double>(i, j);
                index_min = i;
            }
        }
        v.at<double>(0, j) = min;
        int match = matches.at<int>(index_min, 0);
        if (++match == 1) {
            // 最初のマッチング
            rowsol.at<int>(index_min, 0) = j; // 最小値の列を入れる。
            colsol.at<int>(0, j) = index_min; // 最小値の行を入れる。
        } else if (min < v.at<double>(0, rowsol.at<int>(index_min, 0))) {
            // ２回目以降のマッチングではより値が小さい列と行を入れる。
            int j1 = rowsol.at<int>(index_min, 0); // 書き換え前の最小値の列を退避
            rowsol.at<int>(index_min, 0) = j; // 最小値の列を入れる。
            colsol.at<int>(0, j) = index_min; // 最小値の行を入れる。
            colsol.at<int>(0, j1) = -1; // 未割当に戻す。
        } else {
            colsol.at<int>(0, j) = -1; // 未割当。
        }
        matches.at<int>(index_min, 0) = match;
    }

    DP("");

    // REDUCTION TRANSFER
    // 削減　移行
    for (int i = 0; i < dim; i++) {
        int match = matches.at<int>(i, 0);
        if (match == 0) {
            // 未割付け行
            free_unassigned.push_back(i);
        } else if (match == 1)  { // transfer reduction from rows that are assigned once.
            // 割付付け行
            // 一度割り当てられた行からの転送削減。
            int j1 = rowsol.at<int>(i, 0);
            double min = std::numeric_limits<double>::max();
            for (int j = 0; j < dim; j++) {
                if (j != j1) {
                    // 最小コスト行以外から
                    // コストから列の最小コストを引く。
                    double d_cost = cost.at<double>(i, j) - v.at<double>(0, j); 
                    if (d_cost < min) { 
                        min = d_cost;
                    }
                }
            }
            // 列の最小コストを最小の値で減算
            v.at<double>(0, j1) = v.at<double>(0, j1) - min;
        }
    }

    DP("");

    // AUGMENTING ROW REDUCTION
    // さらに行の削減
    int loopcnt = 0; // do ループを 2 回実行します。
    do {
        loopcnt++;
        // scan all free rows.
        // すべての空き行をスキャンします。
        // in some cases, a free row may be replaced with another one to be scanned next.
        // 場合によっては、空き行が次にスキャンされる別の行に置き換えられることがあります。
        int k = 0;
        int pre_free_size = free_unassigned.size();
        int free_size = 0;
        // 行削減を拡張した後もまだ空いている行のリストの開始。 
        while(k < pre_free_size) {
            int i = free_unassigned[k];
            k++;
            // find minimum and second minimum reduced cost over columns.
            // 未割り付け行の列全体で 最小値(j1列:umin1)と 2 番目の最小値(j2列:umin2)の削減コストを見つけます。
            double umin1 = cost.at<double>(i, 0) - v.at<double>(0, 0);
            int j1 = 0;
            int j2 = 0;
            double umin2 = std::numeric_limits<double>::max();
            for (int j = 1; j < dim; j++) {
                double h = cost.at<double>(i, j) - v.at<double>(0, j);
                if (h < umin2) {
                    if (h < umin1) {
                        umin2 = umin1;
                        umin1 = h;
                        j2 = j1;
                        j1 = j;
                    } else {
                        umin2 = h;
                        j2 = j;
                    }
                }
            }
            int i0 = colsol.at<int>(0, j1); // 未割り付け行の最小値の列での最小値の行
            if (umin1 < umin2) {
                // change the reduction of the minimum column to increase the minimum
                // reduced cost in the row to the subminimum.
                // 最小列の削減を変更して、最小値を増やします
                // 行の削減コストを最小値未満にします。
                v.at<double>(0, j1) = v.at<double>(0, j1) - (umin2 - umin1);
            } else if (-1 < i0) {
                // swap columns j1 and j2, as j2 may be unassigned.
                // j2 は未割り当ての可能性があるため、列 j1 と j2 を交換します。
                j1 = j2;
                i0 = colsol.at<int>(0, j2);
            }
            //       (re-)assign i to j1, possibly de-assigning an i0.
            // i を j1 に (再) 割り当て、i0 の割り当てを解除する可能性があります。
            rowsol.at<int>(i, 0) = j1;
            colsol.at<int>(0, j1) = i;
            
            if (i0 > -1) {
                // j1の行は割り当て済み？
                if (umin1 < umin2) {
                    k --;
                    free_unassigned[k] = i0; // 未割り付け行を差し替え。
                } else {
                    free_unassigned.push_back(i0);
                }
            }
        }
    } while (loopcnt < 2);
    DP("");
    // AUGMENT SOLUTION for each free row.
    // 空き行ごとにソリューションを拡張します。
    for (int f = 0; f < free_unassigned.size(); f++) {
        // start row of augmenting path.
        // 拡張パスの開始行。
        int freerow = free_unassigned[f];  // start row of augmenting path.

        // Dijkstra shortest path algorithm.
        // runs until unassigned column added to shortest path tree.
        // ダイクストラ最短経路アルゴリズム。
        // 未割り当ての列が最短経路ツリーに追加されるまで実行されます。
        for (int j = dim; j--;) {
            d[j] = cost.at<double>(freerow, j) - v.at<double>(0, j);
            pred[j] = freerow;
            collist[j] = j;  // init column list.
        }
        // columns in 0..low-1 are ready, now none.
        // 0..low-1 の列は準備完了ですが、現在はありません。
        int low = 0;
        // columns in low..up-1 are to be scanned for current minimum, now none.
        // low..up-1 の列は現在の最小値を探すためにスキャンされますが、今は存在しません。
        // columns in up..dim-1 are to be considered later to find new minimum,
        // up..dim-1 の列は後で新しい最小値を探すために考慮されます。
        // at this stage the list simply contains all columns        
        // この段階では、リストにはすべての列が含まれているだけです
        int up = 0;

        bool unassigned = false;
        double min;            
        int last;
        int endofpath;
        DP("");
        do {
            if (up == low) { // 最小値を求めてスキャンする列はありません。
                int last = low - 1;
                // scan columns for up..dim-1 to find all indices for which new minimum occurs.
                // up..dim-1 の列をスキャンして、新しい最小値が発生するすべてのインデックスを検索します。
                // store these indices between low..up-1 (increasing up).
                // これらのインデックスを low..up-1 の間 (上に向かって増加) に格納します。
                int up_col = collist[up];
                up++;
                min = d[up_col];
                for (int k = up; k < dim;k++) {
                    int j = collist[k];
                    double h = d[j];
                    if (h <= min) {
                        up = low;
                        min = h;
                    }
                    collist[k] = collist[up];
                    collist[up] = j;
                    up++;
                }
                // check if any of the minimum columns happens to be unassigned.
                // 最小列のいずれかが割り当てられていないかどうかを確認します。
                // if so, we have an augmenting path right away.
                // そうであれば、すぐに拡張パスが得られます。
                for (int k = low; k < up; k++) {
                    int j = colsol.at<int>(0, collist[k]);
                    if (j < 0) {
                        endofpath = collist[k];
                        unassigned = true;
                        break;
                    }
                }
            }
            if (!unassigned) {
                // update 'distances' between freerow and all unscanned columns, via next scanned
                // column.
                // 次のスキャンされた列を介して、フリー行とすべての未スキャン列間の「距離」を更新します。
                int j1 = collist[low];
                low ++;
                int i = colsol.at<int>(0, j1);
                double h = cost.at<double>(i, j1) - v.at<double>(0, j1) - min;
                for (int k = up; k < dim; k++) {
                    int j = collist[k];
                    double v2 = cost.at<double>(i, j) - v.at<double>(0, j) - h;
                    if (v2 < d[j]) {
                        pred[j] = i;
                        if (v2 == min) {  // new column found at same minimum value
                            // 同じ最小値で新しい列が見つかりました
                            if (colsol.at<int>(0, j) < 0) {
                                // if unassigned, shortest augmenting path is complete.
                                // 割り当てられていない場合は、最短の拡張パスが完了します。
                                endofpath = j;
                                unassigned = true;
                                break;
                            } else {

                                // else add to list to be scanned right away.
                                // そうでない場合は、すぐにスキャンされるリストに追加します。
                                collist[k] = collist[up];
                                collist[up] = j;
                                up++;
                            }
                        }
                        d[j] = v2;
                    }
                }
            }
        } while (!unassigned);

        // update column prices.
        // 列の価格を更新します。
        for (int k = last + 1; k--;) {
            int j1 = collist[k];
            v.at<double>(0, j1) = v.at<double>(0,j1) + d[j1] - min;
        }

        // reset row and column assignments along the alternating path.
        // 交互パスに沿って行と列の割り当てをリセットします。
        for(;;) {
            int i = pred[endofpath];
            colsol.at<int>(0, endofpath) = i;
            int j1 = endofpath;
            endofpath = rowsol.at<int>(i, 0);
            if (i == freerow) {
                break;
            }
        }

    }


    return 0.0;
}

void pathfinding_body(int number, int base, int depth, cv::Mat& rowsol) {
    if (base <= 0) {
        return;
    }
    int next_number = number / base;
    // DP("depth=" << depth << ", " << (number % base));
    rowsol.at<int>(depth - 1, 0) = (number % base);
    pathfinding_body(next_number, base - 1, depth - 1, rowsol);
}

int factorial(int n) {
    int result = 1;
    for (;n > 0; n--) {
        result *= n;
    }
    return result;
}

void debug(cv::Mat &m) {

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            std::cout << std::setw(4) << m.at<int>(i, j) << std::endl;
        }
    }
}
void debug(cv::Mat& m, cv::Mat& rowsol) {

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            if (j == rowsol.at<int>(i, 0)) {
                std::cout << "\033[41m\033[37m" << std::setw(4) << m.at<double>(i, j) << "\033[0m";
            } else {
                std::cout << std::setw(4) << m.at<double>(i, j);
            }
        }
        std::cout << std::endl;
    }
}



int main() {

    DP("test");

    std::vector<double> data = 
            {
                1, 2, 3, 1,
                4, 5, 6, 1,
                7, 9, 1, 1,
                1, 1, 1, 1
            };
    cv::Mat cost = cv::Mat(4, 4, CV_64FC1, data.data());
    cv::Mat rowsol = cv::Mat(4, 1, CV_32SC1);
    cv::Mat u = cv::Mat(4, 1, CV_64FC1);
    cv::Mat colsol = cv::Mat(1, 4, CV_32SC1);
    cv::Mat v = cv::Mat(4, 1, CV_64FC1);
    
    // DP("f=" << f);
    colsol = -1;
    //DPM(colsol);
    double min = std::numeric_limits<double>::max();
    cv::Mat min_rowsol;
    for (int f = factorial(rowsol.rows); f--;) {
        int base = cost.cols;
        int depth = base;
        pathfinding_body(f, base, depth, rowsol);
        colsol = -1;
        for (int i = rowsol.rows - 1; i >= 0; i--) {
            int no = rowsol.at<int>(i, 0);
            int count = no;
            for (int j = 0; j < colsol.cols; j++) {
                int v = colsol.at<int>(0, j);
                if (v < 0) {
                    if (count == 0) {
                        colsol.at<int>(0, j) = i;
                        rowsol.at<int>(i, 0) = j; 
                        break;
                    }
                    count --;
                }
            }
        }
        double sum = 0.0;
        for (int i = 0; i < rowsol.rows; i++) {
            int j = rowsol.at<int>(i, 0);
            sum += cost.at<double>(i, j);
        }
        if (sum < min) {
            min = sum;
            min_rowsol = rowsol.clone();
        }
        DP("sum = " << sum);
        DPM(colsol);
        DPM(rowsol);
    }
    // DP("min = " << min);
    DPM(min_rowsol);
    debug(cost, min_rowsol);




    //lap(cost, rowsol, colsol, u, v);
    task_mng mng;

    task task1;
    task1.name = "test1";
    task task2;
    task2.name = "test2";

    mng.add_task(task1);
    mng.add_task(task2);
    mng.setup();
    mng.loop(); 


    return 0;
}

