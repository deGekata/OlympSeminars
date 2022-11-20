#include <cstdint>
#include <iostream>

#include <algorithm>

#include <stack>
#include <vector>
#include <unordered_set>


class Graph {
public:
    size_t V_cnt; 
    /// edges cnt
    size_t E_cnt;
    std::vector<std::unordered_set<uint32_t>> adj_list;
    std::vector<uint32_t> ans;

    Graph(size_t vertex_cnt) : V_cnt(vertex_cnt){
        adj_list.resize(V_cnt);
    }

    Graph() = delete;

    void readAdjList() {
        for (uint32_t it = 0; it < V_cnt; it++) {
            for (uint32_t other = 0; other < V_cnt; other++) {
                uint8_t curChar = 0;
                std::cin >> curChar;

                if ((curChar == '0') && (it != other)) {
                    adj_list[it].insert(other);
                }
            }
        }
        return;
    }
        //euler path ))))))))))))))))))))))))))))))
    void dfs(uint32_t startVertex) {
            while(!adj_list[startVertex].empty()) {
            uint32_t curVertex = *adj_list[startVertex].begin();
            adj_list[startVertex].erase(curVertex);

            dfs(curVertex);
        }

        ans.push_back(startVertex + 1);
        return;
    }

    void printAns() {
        for (uint32_t it = uint32_t(ans.size() - 1); it > 0; it--) {
            std::cout << (ans[it]) << " " << (ans[it - 1]) << "\n";
        }
        return;
    }
};

int32_t main() {
    
    uint32_t v_cnt, start;
    std::cin >> v_cnt >> start;
    
    Graph gr(v_cnt);
    gr.readAdjList();
    gr.dfs(start - 1);

    gr.printAns();
}