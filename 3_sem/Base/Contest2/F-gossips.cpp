#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <algorithm>

class Graph_Adj {
public:
    std::vector<std::vector<int>> adj_list;
    std::unordered_set<int> unused;
    /// vertex cnt
    size_t V_cnt; 
    /// edges cnt
    size_t E_cnt; 
    Graph_Adj(size_t vertex_cnt) : V_cnt(vertex_cnt){
        adj_list.resize(V_cnt);
    }

    void readAdjList(int x_, int y_) {
        std::vector<std::vector<bool>> matrix(y_, std::vector<bool>(x_));
        char tmp = '-';
        for (int y = 0; y < y_; ++y) {
            for (int x = 0; x < x_; ++x) {
                std::cin >> tmp;
                switch (tmp) {
                    case '+':
                        matrix[y][x] = true;
                        unused.insert(y*y_ + x);
                        break;
                    case '-':
                        matrix[y][x] = false;
                        break;
                    default:
                        break;
                }
            }
        }

        // for (int y = 0; y < y_; ++y) {
        //     for (int x = 0; x < x_; ++x) {
        //         std::cout << matrix[y][x];
        //     }
        // }
        // std::cout << "\n";

        for (int y = 0; y < y_; ++y) {
            for (int x = 0; x < x_; ++x) {
                switch (matrix[y][x]) {
                    case true: {
                        if (y > 0 && matrix[y - 1][x]) {
                            // std::cout << x << " " << y << " 0\n";
                            adj_list[y * y_ + x].push_back((y - 1) * y_ + x);
                        }

                        if (x > 0 && matrix[y][x - 1]) {
                            // std::cout << x << " " << y << " 1\n";
                            adj_list[y * y_ + x].push_back(y * y_ + x - 1);
                        }

                        if (y < (y_ - 1) && matrix[y + 1][x]) {
                            // std::cout << x << " " << y << " 2\n";
                            adj_list[y * y_ + x].push_back((y + 1) * y_ + x);
                        }

                        if (x < (x_ - 1) && matrix[y][x + 1]) {
                            // std::cout << x << " " << y << " 3\n";
                            adj_list[y * y_ + x].push_back(y * y_ + x + 1);
                        }
                    }
                        break;
                    default:
                        break;
                }
            }
        }
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

int bfs_color(Graph_Adj& gr) {
    
    // for (int it = 0; it < gr.adj_list.size(); ++it) {
    //     unused.insert(it);
    // }

    std::queue<int> process;
    // int max_comp_size = 0;
    int comp_cnt = 0;

    while (gr.unused.size() > 0) {
        // components.push_back(std::vector<int>());
        int comp_vert = *gr.unused.begin();
        process.push(comp_vert);
        // components.insert({comp_vert, comp_cnt});
        gr.unused.erase(gr.unused.begin());
        bool has_comp = false;
        while (process.size() > 0) {
            has_comp = true;
            int cur_vert = process.front();
            // components.insert({cur_vert, comp_cnt});
            process.pop();
            for (int it = 0; it < gr.adj_list[cur_vert].size(); ++it) {
                if (gr.unused.find(gr.adj_list[cur_vert][it]) != gr.unused.end()) {
                    process.push(gr.adj_list[cur_vert][it]);
                    gr.unused.erase(gr.unused.find(gr.adj_list[cur_vert][it]));
                }
            }
        }
        if (has_comp) comp_cnt++;
        // if (cur_comp_size > max_comp_size) max_comp_size = cur_comp_size;
        // comp_cnt++;
    }

    return comp_cnt;
}


int main() {
    int x, y;
    std::cin >> y >> x;
    std::unordered_map<int, int> components;
    // std::vector<std::unordered_map<int, int>> components;
    Graph_Adj gr(x * y);
    gr.readAdjList(x, y);
    // gr.printAdjList();
    std::cout << bfs_color(gr) << "\n";
    // for (int it = 0; it < v_num; ++it) {
    //     std::cout << components[it]<< " ";
    // }
    return 0;
}