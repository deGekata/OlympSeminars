#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <algorithm>

struct my_pair {
    int16_t x, y;
};


#define shift(lft, rht) (((lft) << 16) | (rht))

class Graph_Adj {
public:
    // std::vector<std::vector<int>> adj_list;
    std::vector<bool> unused;
    size_t cnt_unused = 0;
    // std::unordered_set<int> unused;
    std::queue<my_pair> process;
    size_t V_cnt; 
    size_t E_cnt; 
    Graph_Adj(size_t vertex_cnt) : V_cnt(vertex_cnt) {
        // adj_list.resize(V_cnt);
    }

    void readAdjList(int x_, int y_) {
        unused.resize(shift(y_, x_), false);
        // std::cout << x_ << "  x " << y_ << "  y \n";
        for (int y = 0; y < y_; ++y) {
            for (int x = 0; x < x_; ++x) {
                // unused.insert(shift(y, x));
                unused[shift(y, x)] = true;
                cnt_unused++;
                // std::cout << shift(y, x) << " inserted \n";
            }
        }

        for (int it = 0; it < E_cnt; ++it) {
            int x, y;
            std::cin >> x >> y;
            // unused.erase(shift(y, x));
            unused[shift(y, x)] = false;
            process.push({(int16_t)x, (int16_t)y});
            cnt_unused--;
            
        }
        
    } 

    void printAdjList() {
        for (size_t v_num = 0; v_num < V_cnt; ++v_num) {
            std::cout << "V" << v_num << ":";
            // for (size_t it = 0; it < adj_list[v_num].size(); ++it) {
            //     std::cout << " " << adj_list[v_num][it];
            // }
            std::cout << "\n";
        }
    }
};

#define WHITE 0
#define GEY   1
#define BLACK 2

int bfs_color(Graph_Adj& gr, int x_, int y_) {
    int comp_cnt = 0;
    std::queue<my_pair> buff;
    std::queue<my_pair>* real_queue = &gr.process;
    std::queue<my_pair>* swap_queue = &buff;

    // while (gr.unused.size() > 0) {
    while (gr.cnt_unused > 0) {

        while (real_queue->size() > 0) {
            my_pair cur_vert = real_queue->front();
            int x = cur_vert.x;
            int y = cur_vert.y;
            // components.insert({cur_vert, comp_cnt});
            // std::cout << "is processing " << x << " " << y << "\n"; 
            real_queue->pop();

            {
                // if (y > 0 && gr.unused.contains(shift(y - 1, x))) {
                if (y > 0 && gr.unused[shift(y - 1, x)]) {
                    swap_queue->push({(int16_t)x, (int16_t)(y - 1)});
                    gr.unused[shift(y - 1, x)] = false;
                    gr.cnt_unused--;
                    // gr.unused.erase(shift(y - 1, x));
                }

                if (x > 0 && gr.unused[shift(y, x - 1)]) {
                    swap_queue->push({(int16_t)(x - 1), (int16_t)y});
                    // gr.unused.erase(shift(y, x - 1));
                    gr.unused[shift(y, x - 1)] = false;
                    gr.cnt_unused--;
                }

                if (y < (y_ - 1) && gr.unused[shift(y + 1, x)]) {
                    swap_queue->push({(int16_t)x, (int16_t)(y + 1)});
                    // gr.unused.erase(shift(y + 1, x));
                    gr.unused[shift(y + 1, x)] = false;
                    gr.cnt_unused--;
                }

                if (x < (x_ - 1) && gr.unused[shift(y, x + 1)]) {
                    swap_queue->push({(int16_t)(x + 1), (int16_t)y});
                    // gr.unused.erase(shift(y, x + 1));
                    gr.unused[shift(y, x + 1)] = false;
                    gr.cnt_unused--;
                }

            }
        }
        // std::cout << "new epoch\n";
        std::swap(real_queue, swap_queue);
        comp_cnt++;
    }

    return comp_cnt;
}


int main() {
    int x, y, e_cnt;
    std::cin >> x >> y >> e_cnt;
    Graph_Adj gr(x * y);
    gr.E_cnt = e_cnt;
    gr.readAdjList(x, y);
    std::cout << bfs_color(gr, x, y) << "\n";
    return 0;
}