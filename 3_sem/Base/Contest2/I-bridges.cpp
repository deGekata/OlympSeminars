#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <algorithm>

const uint8_t WHITE = 0;
const uint8_t GREY = 1;
const uint8_t BLACK = 2;




class Graph_Adj {
public:
    std::vector<std::map<int, int>> adj_list;
    std::vector<uint8_t> colors;
    std::vector<int> ret;
    std::vector<int> tin;
    /// vertex cnt
    size_t V_cnt; 
    /// edges cnt
    size_t E_cnt;
    int time = 0; 

    Graph_Adj(size_t vertex_cnt, size_t edges_cnt) : V_cnt(vertex_cnt), E_cnt(edges_cnt) {
        adj_list.resize(V_cnt);
        ret.resize(V_cnt, INT32_MAX);
        tin.resize(V_cnt, 0);
        colors.resize(V_cnt, WHITE);

    }

    void readAdjList() {
        for (size_t it = 0; it < E_cnt; ++it) {
            int v1, v2;
            std::cin >> v1 >> v2;
            adj_list[v1 - 1].insert({v2 - 1, it + 1});
            adj_list[v2 - 1].insert({v1 - 1, it + 1});
        }
    } 

    void printAdjList() {
        for (size_t v_num = 0; v_num < V_cnt; ++v_num) {
            std::cout << "V" << v_num << ":";
            for (size_t it = 0; it < adj_list[v_num].size(); ++it) {
                // std::cout << " " << adj_list[v_num][it].first;
            }
            std::cout << "\n";
        }
    }

    void dfs(int vertex, int root, std::vector<std::pair<int, int>>& ans) {
        colors[vertex] = GREY;
        tin[vertex] = time++;
        // ret[vertex] = time;

        for (auto& nei: adj_list[vertex]) {
            if (nei.first == root) continue;

            if (colors[nei.first] == WHITE) {
                dfs(nei.first, vertex, ans);
                ret[vertex] = std::min(ret[nei.first], ret[vertex]);

                if (ret[nei.first] > tin[vertex] ) {
                    ans.push_back({vertex, nei.first});
                    // std::cout << nei << " " << vertex << "\n";
                }

            } else {
                ret[vertex] = std::min(tin[nei.first], ret[vertex]);
            }
        }
        colors[vertex] = BLACK;
    }


};

int main() {
    int v_num, e_num;
    std::cin >> v_num >> e_num;
    // std::vector<std::unordered_map<int, int>> components;
    Graph_Adj gr(v_num, e_num);
    gr.readAdjList();
    // std::cout << "lol";
    std::vector<std::pair<int, int>> buff;
    for (int it = 0; it < v_num; ++it) {
        if (gr.colors[it] == WHITE) {
            gr.dfs(it, INT32_MAX, buff);
        }
    }

    std::set<int> ans;

    for(auto it: buff) {
        ans.insert(gr.adj_list[it.first][it.second]);
    }

    std::cout << ans.size() << "\n";
    for (auto it: ans) {
        std::cout << it << " ";
    }
    std::cout << "\n";
    
   
    return 0;
}