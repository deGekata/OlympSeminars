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
    /// vertex cnt
    size_t V_cnt; 
    /// edges cnt
    size_t E_cnt; 
    int cycle_begin = -1;
    std::vector<int> used;

    Graph_Adj(size_t vertex_cnt, size_t edges_cnt) : V_cnt(vertex_cnt), E_cnt(edges_cnt) {
        adj_list.resize(V_cnt);
        used.resize(V_cnt, 0);
    }

    void readAdjList() {
        for (size_t it = 0; it < E_cnt; ++it) {
            int v1, v2;
            std::cin >> v1 >> v2;
            adj_list[v1].push_back(v2);
            adj_list[v2].push_back(v1);
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

    bool dfs_color(std::vector<int>& ans, int cur_vert) {
        
            
        return 1;
    }
};





int main() {
    std::vector<int> ans;
    int v_num, e_num;
    std::cin >> v_num >> e_num;

    Graph_Adj gr(v_num, e_num);
    gr.readAdjList();
    dfs_cycle(gr, ans);

    return 0;
}