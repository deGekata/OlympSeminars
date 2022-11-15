#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <algorithm>

struct my_pair {
    int16_t x;
    int16_t y;
};

int x_, y_;
#define shift(lft, rht) (((lft) * y_) + (rht))

class Graph_Adj {
public:
    std::vector<std::vector<int>> adj_list;
    std::vector<bool> unused;
    /// vertex cnt
    size_t V_cnt; 
    /// edges cnt
    size_t E_cnt; 
    Graph_Adj(size_t vertex_cnt) : V_cnt(vertex_cnt){
        // adj_list.resize(V_cnt);
        unused.resize(vertex_cnt*vertex_cnt);
        for (int y = 0; y < vertex_cnt; ++y) {
            for (int x = 0; x < vertex_cnt; ++x) {
                unused[shift(y, x)] = true;
            }
        }
    }

    void readAdjList(int x_, int y_) {

    } 

    void printAdjList() {
        for (size_t v_num = 0; v_num < V_cnt; ++v_num) {
            std::cout << "V" << v_num << ":";
            for (size_t it = 0; it < adj_list[v_num].size(); ++it) {
                std::cout << " " << adj_list[v_num][it];
            }
            std::cout << "\n";
        }
    }
};

#define WHITE 0
#define GEY   1
#define BLACK 2
#define printChessPos(x, y) std::cout << (char)('A' + (x)) << (y) << '\n'

int bfs_color(Graph_Adj& gr, int x0, int y0, int x1, int y1, std::vector<my_pair>& ans) {

    std::queue<my_pair> process;
    // int max_comp_size = 0;
    int comp_cnt = 0;
    int bar = gr.V_cnt;
    process.push({(int16_t)x0, (int16_t)y0});
    std::vector<std::vector<my_pair>> prev(gr.V_cnt, std::vector<my_pair>(gr.V_cnt));
    gr.unused[shift(y0, x0)] = false;
    while (process.size() > 0) {
        comp_cnt++;
        my_pair cur_vert = process.front();
        int16_t x = cur_vert.x;
        int16_t y = cur_vert.y;
        // std::cout << x << " " << y << " iter\n";
        process.pop();
        // if (shift(y + 2, x + 1) >= gr.V_cnt * gr.V_cnt) exit(0);
        if (y-1>=0 && x - 2 >= 0 && gr.unused[shift(y - 1, x - 2)]) {
                process.push((my_pair){x - 2, y - 1});
                prev[y-1][x-2] = {x, y};
                gr.unused[shift(y - 1, x - 2)] = false;

        }

        if (y+1<bar && x - 2 >= 0 && gr.unused[shift(y + 1, x - 2)]) {
                process.push((my_pair){x - 2, y + 1});
                prev[y+1][x-2] = {x, y};
                gr.unused[shift(y + 1, x - 2)] = false;
        }
        
        if (y-1>=0 && x + 2 < bar && gr.unused[shift(y - 1, x + 2)]) {
                process.push((my_pair){x + 2, y - 1});
                prev[y-1][x+2] = {x, y};
                gr.unused[shift(y - 1, x + 2)] = false;
        }

        if (y+1<bar && x + 2 < bar && gr.unused[shift(y + 1, x + 2)]) {
                process.push((my_pair){x + 2, y + 1});
                prev[y+1][x+2] = {x, y};
                gr.unused[shift(y + 1, x + 2)] = false;
        }
        //--------------------------------------------------
        
        if (y-2>=0 && x - 1 >= 0 && gr.unused[shift(y - 2, x - 1)]) {
                process.push((my_pair){x - 1, y - 2});
                prev[y-2][x-1] = {x, y};
                gr.unused[shift(y - 2, x - 1)] = false;
        }
        
        if (y-2>=0 && x + 1 < bar && gr.unused[shift(y - 2, x + 1)]) {
                process.push((my_pair){x + 1, y - 2});
                prev[y-2][x+1] = {x, y};
                gr.unused[shift(y - 2, x + 1)] = false;
        }
        
        if (y+2<bar && x - 1 >= 0 && gr.unused[shift(y + 2, x - 1)]) {
                process.push((my_pair){x - 1, y + 2});
                prev[y+2][x-1] = {x, y};
                gr.unused[shift(y + 2, x - 1)] = false;
        }
        
        if (y+2<bar && x + 1 < bar && gr.unused[shift(y + 2, x + 1)]) {
                process.push((my_pair){x + 1, y + 2});
                prev[y+2][x+1] = {x, y};
                gr.unused[shift(y + 2, x + 1)] = false;
        }
    }
    // for (auto it: gr.unused) {
    //     std::cout << it << "\n";
    // }
    int16_t cur_x = x1, cur_y = y1;
    
    for (; cur_x != x0 || cur_y != y0;) {
        ans.push_back(my_pair{cur_x, (int16_t)(cur_y + 1)});
        // printChessPos(cur_x, cur_y + 1);
        // std::cout << cur_x << " " << cur_y << "\n";

        my_pair tmp = prev[cur_y][cur_x];
        cur_x = tmp.x;
        cur_y = tmp.y;
    }
    std::cout << ans.size() << "\n";
    for (int it = ans.size() - 1; it >= 0; --it) {
        printChessPos(ans[it].x, ans[it].y);
    }
    // std::cout << prev[y1][x1].x << "  " << prev[y1][x1].y << "\n";
    return comp_cnt;
}



int main() {
    int size;
    char tmp_sym;
    int x0, y0;
    int x1, y1;
    int  tmp_num;
    std::cin >> size;
    std::cin >> tmp_sym >> y0;
    x0 = tmp_sym - 'A';
    std::cin >> tmp_sym >> y1;
    x1 = tmp_sym - 'A';
    x_ = y_ = size;
    // std::cout << '"' <<  tmp_sym << '"' << tmp_num;
    // printChessPos(x0, y0);
    // printChessPos(x1, y1);
    y0--, y1--;
    // std::cin >> y >> x;
    // std::unordered_map<int, int> components;
    // std::vector<std::unordered_map<int, int>> components;
    Graph_Adj gr(size);
    // gr.readAdjList(x, y);
    // gr.printAdjList();
    std::vector<my_pair> ans;
    bfs_color(gr, x0, y0, x1, y1, ans);
    // for (int it = 0; it < v_num; ++it) {
    //     std::cout << components[it]<< " ";
    // }
    std::cout << "\n";
    return 0;
}