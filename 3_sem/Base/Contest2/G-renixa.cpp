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
    size_t V_cnt; 
    size_t E_cnt; 

    std::vector<int> used;
    std::vector<int> tout;
    std::vector<int> tin;
    int time = 0;
    // std::vector<int> prev;

    Graph_Adj(size_t vertex_cnt) : V_cnt(vertex_cnt) {
        adj_list.resize(V_cnt);
        used.resize(V_cnt, WHITE);
        tin.resize(V_cnt, 0);
        tout.resize(V_cnt, 0);
        // prev.resize(V_cnt, -1);
    }

    void readAdjList() {
        for (size_t it = 0; it < E_cnt; ++it) {
            int v1, v2;
            std::cin >> v1 >> v2;
            adj_list[v1 - 1].push_back(v2 - 1);
            // adj_listT[v2 - 1].push_back(v1 - 1);
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

    void dfs_color(int cur_vert) {
        used[cur_vert] = GREY;
        tin[cur_vert] = time++;
        //reverse color optimisation
        
        for (auto next_vertex : adj_list[cur_vert]) {
            if (used[next_vertex] == WHITE)
                dfs_color(next_vertex);
        }
        used[cur_vert] = BLACK;
        tout[cur_vert] = time++;
        //забыть время в дфс)) кринж))))))))
        return;
    }
};





int main() {
    int vSize = 0, wAmount = 0;

    std::cin >> vSize;
    std::cin >> wAmount;

    Graph_Adj gr(vSize);
    std::vector<std::string> words(wAmount);

    std::cin >> words[0];
    for (uint32_t wordNumber = 1; wordNumber < wAmount; wordNumber++) {
        std::cin >> words[wordNumber];

        for (uint32_t curChar = 0; curChar < std::min(words[wordNumber - 1].size(), words[wordNumber].size()); curChar++) {
            if (words[wordNumber - 1][curChar] != words[wordNumber][curChar]) {
                gr.adj_list[words[wordNumber - 1][curChar] - 'A'].push_back(words[wordNumber][curChar] - 'A');

                break;
            }
        }
    }

    for (uint8_t v = 0; v < vSize; v++) {
        if (gr.used[v] == WHITE) {
            gr.dfs_color(v);
        }
    }

    std::vector<int> copyTime(gr.tout);
    // std::copy(gr.tout.begin(), gr.tin.end(), copyTime);
    std::sort(copyTime.begin(), copyTime.end());


    for (uint8_t curV = 0; curV < vSize; curV++) {
        for (uint8_t curAnotherV = 0; curAnotherV < vSize; curAnotherV++) {
            if (gr.tout[curAnotherV] == copyTime[vSize - 1 - curV]) {
                std::cout << (char)('A' + curAnotherV);
            }
        }
    }
    std::cout << std::endl;

}