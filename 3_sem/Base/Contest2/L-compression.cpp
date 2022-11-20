#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <algorithm>


const int BLACK =  2;
const int GREY  =  1;
const int WHITE = -1;

class Graph_Adj {
public:
    std::vector<std::vector<int>> adj_list;
    std::vector<std::vector<int>> adj_listT;
    /// vertex cnt
    size_t V_cnt; 
    /// edges cnt
    size_t E_cnt; 
    int cycle_begin = INT32_MAX;
    int cycle_end   = INT32_MAX;
    std::vector<int> used;
    std::vector<int> usedRev;
    std::vector<int> tout;
    std::vector<int> toutRev;
    // std::vector<int> prev;

    Graph_Adj(size_t vertex_cnt, size_t edges_cnt) : V_cnt(vertex_cnt), E_cnt(edges_cnt) {
        adj_list.resize(V_cnt);
        adj_listT.resize(V_cnt);
        used.resize(V_cnt, WHITE);
        usedRev.resize(V_cnt, WHITE);
        // prev.resize(V_cnt, -1);
    }

    void readAdjList() {
        for (size_t it = 0; it < E_cnt; ++it) {
            int v1, v2;
            std::cin >> v1 >> v2;
            adj_list[v1 - 1].push_back(v2 - 1);
            adj_listT[v2 - 1].push_back(v1 - 1);
            // adj_list[v2].push_back(v1);
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

    void dfs_color(int cur_vert, int color) {
        used[cur_vert] = color;
        //reverse color optimisation
        for (auto next_vertex : adj_list[cur_vert]) {
            if (used[next_vertex] == WHITE)
                dfs_color(next_vertex, color);
        }
        tout.push_back(cur_vert);
        return;
    }

    void dfs_colorRev(int cur_vert, int color) {
        usedRev[cur_vert] = color;
        //reverse color optimisation
        for (auto next_vertex : adj_listT[cur_vert]) {
            if (usedRev[next_vertex] == WHITE)
                dfs_colorRev(next_vertex, color);
        }
        toutRev.push_back(cur_vert);
        return;
    }
};





int main() {
    std::vector<int> ans;
    int v_num, e_num;
    std::cin >> v_num >> e_num;

    Graph_Adj gr(v_num, e_num);
    gr.readAdjList();


    int compColor = 0;
    for (int it = 0; it < v_num; ++it)
        if (gr.used[it] == WHITE)
            gr.dfs_color(it, compColor);
        

    gr.used.assign(gr.used.size(), WHITE);

    for (int it = v_num - 1; it >= 0; --it) {
        int top_vert = gr.tout[it];
        if (gr.usedRev[top_vert] == WHITE) {
            gr.dfs_colorRev(top_vert, compColor++);
        }
    }

    std::set<std::pair<int, int>> comp;
    for (int it = 0; it < v_num; ++it) {
        for (auto con: gr.adj_list[it]) 
            if (gr.usedRev[it] != gr.usedRev[con]) 
                comp.insert({gr.usedRev[it], gr.usedRev[con]});
    }
    std::cout << comp.size() << "\n";
    // gr.printAdjList();
    // for (int it = 0; it < v_num; ++it) {
    //     gr.dfs_color(it);
    // }

    // // std::cout << gr.cycle_begin << " " << gr.cycle_end;

    // if (gr.cycle_begin == INT32_MAX) {
    //     std::cout << "NO";
    //     return 0;
    // }
    

    // std::cout << "YES\n";
    // for (int iter = gr.cycle_end; iter != gr.cycle_begin; iter = gr.prev[iter]) {
    //     ans.push_back(iter + 1);
    // }
    // ans.push_back(gr.cycle_begin + 1);


    // for (int v = ans.size() - 1; v >= 0; --v) {
    //     std::cout << ans[v] << " ";
    // }

    

    return 0;
}