#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <algorithm>

const bool WHITE = 0;
const bool GREY  = 1;
std::string pattern = "123456789\b";
// std::string cur_cond = "";
// std::string n_cond = "";





void check_cond(std::string& cur_cond, std::string& n_cond,
std::unordered_map<std::string, bool>& colors,
std::unordered_map<std::string, uint32_t>& distances,
std::queue<std::string>& queue, uint32_t& min_dist) {
    // n_cond.push_back('\0');
    // cur_cond.push_back('\0');
    // std::cout << cur_cond << ',' << n_cond << "\n";
    if (colors.find(n_cond) == colors.end()) {
        queue.push(n_cond);
        
        uint32_t newDistance = 0;
        auto it = distances.find(cur_cond);
        if (it != distances.end()) {
            newDistance = it->second;
        }
        newDistance++;
 
        distances.insert({n_cond, newDistance});
 
        if (n_cond == pattern) {
            min_dist = std::min(min_dist, newDistance);
        }
 
        colors.insert({n_cond, GREY});
    }
}


#define OPT(offset) \
    std::swap(n_cond[cur_cond[9]], n_cond[cur_cond[9] + (offset)]);\
    n_cond[9] += (offset);\
    check_cond(cur_cond, n_cond, colors, distances, queue, min_dist);\
    n_cond[9] -= (offset);\
    std::swap(n_cond[cur_cond[9]], n_cond[cur_cond[9] + (offset)]);\


uint32_t bfs(std::unordered_map<std::string, bool>& colors,
    std::unordered_map<std::string, uint32_t>& distances,
    std::queue<std::string>& queue) {
    uint32_t min_dist = UINT32_MAX;
    while (!queue.empty()) {
        if (min_dist != UINT32_MAX) {
            break;
        }
        std::string cur_cond = queue.front();
        queue.pop();
        colors.insert({cur_cond, GREY});
        std::string n_cond = cur_cond;

        if (cur_cond[9] >= 3) {
            OPT(-3);
        }

        if (cur_cond[9] < 6) {
            OPT(3);
        }
        
        if ((cur_cond[9] % 3) > 0) {
            OPT(-1);
        }
        
        if ((cur_cond[9] % 3) < 2) {
            OPT(1);
        }
    }
    return min_dist;
}

int main() {
    std::string startState(10, 'a');
    for (uint8_t curChar = 0; curChar < 9; curChar++) {
        int32_t inChar = getchar();
        
        if (inChar == '\n') {
            curChar--;
            continue;
        }
        else if (inChar == ' ') {
            startState[curChar] = '9';
            startState[9] = curChar;
        }
        else {
            startState[curChar] = char(inChar);
        }
    }
    std::unordered_map<std::string, bool> colors;
    std::unordered_map<std::string, uint32_t> distances;
    std::queue<std::string> queue;
    queue.push(startState);

    uint32_t ans = bfs(colors, distances, queue);
    if(ans == UINT32_MAX) {
        std::cout << -1 << "\n";
    } else {
        std::cout << ans << "\n";
    }
    return 0;
}