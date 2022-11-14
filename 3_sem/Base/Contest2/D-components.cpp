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
    Graph_Adj(size_t vertex_cnt, size_t edges_cnt) : V_cnt(vertex_cnt), E_cnt(edges_cnt) {
        adj_list.resize(V_cnt);
    }

    void readAdjList() {
        for (size_t it = 0; it < E_cnt; ++it) {
            int v1, v2;
            std::cin >> v1 >> v2;
            adj_list[v1 - 1].push_back(v2 - 1);
            adj_list[v2 - 1].push_back(v1 - 1);
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

int bfs_color(Graph_Adj& gr, std::unordered_map<int, int>& components) {
    std::unordered_set<int> unused;
    for (int it = 0; it < gr.adj_list.size(); ++it) {
        unused.insert(it);
    }

    std::queue<int> process;
    
    int comp_cnt = 1;

    while (unused.size() > 0) {
        // components.push_back(std::vector<int>());
        int comp_vert = *unused.begin();
        process.push(comp_vert);
        // components.insert({comp_vert, comp_cnt});
        unused.erase(unused.begin());
        while (process.size() > 0) {
            int cur_vert = process.front();
            components.insert({cur_vert, comp_cnt});
            process.pop();
            for (int it = 0; it < gr.adj_list[cur_vert].size(); ++it) {
                if (unused.find(gr.adj_list[cur_vert][it]) != unused.end()) {
                    process.push(gr.adj_list[cur_vert][it]);
                    unused.erase(unused.find(gr.adj_list[cur_vert][it]));
                }
            }
        }
        comp_cnt++;
    }

    return comp_cnt - 1;
}


int main() {
    int v_num, e_num;
    std::cin >> v_num >> e_num;
    std::unordered_map<int, int> components;
    // std::vector<std::unordered_map<int, int>> components;
    Graph_Adj gr(v_num, e_num);
    gr.readAdjList();
    std::cout << bfs_color(gr, components) << "\n";
    for (int it = 0; it < v_num; ++it) {
        std::cout << components[it]<< " ";
    }
    return 0;
}