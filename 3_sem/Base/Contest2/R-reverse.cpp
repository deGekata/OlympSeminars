#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <algorithm>

std::unordered_set<std::string> used_f, used_second;
std::queue<std::string> process_f, process_s;
std::queue<std::string>* process_f_, *process_s_;
int size;
int ans = 0;

void bfs_proc() {  
    while (!process_f.empty() && !process_s.empty()) {
        if (process_f.size() > process_s.size()) {
            std::swap(process_f, process_s); std::swap(used_f, used_second);
        }

        for (uint64_t cur_size = process_f.size(); cur_size; cur_size--) {
            std::string cur_cond = process_f.front(); 
            process_f.pop();

            for (int lft = 0; lft + 1 < size; ++lft)
                for (int rht = lft + 1; rht < size; ++rht) {
                    std::string n_cond = cur_cond;
                    std::reverse(n_cond.begin() + lft, n_cond.begin() + rht + 1);
                    
                    if (used_second.contains(n_cond)) {
                        ans++;
                        return;
                    } else if (!used_f.contains(n_cond)) {
                        process_f.push(n_cond);
                        used_f.insert(n_cond);
                    }
                }
        }
        
        if (++ans >= size - 1) {
            ans --;
            return;
        }
    }
}

int32_t main() {
    std::cin >> size;

    std::string begin, end;
    int chr;
    for (uint16_t it = 0; it < size; it++) {
        std::cin >> chr;
        begin.push_back(uint8_t(chr - '0'));
    }

    for (uint16_t it = 0; it < size; it++) {
        std::cin >> chr;
        end.push_back(uint8_t(chr - '0'));
    }

    if (begin == end) {
        std::cout << 0;
        return 0;
    }

    process_f.push(begin);
    process_s.push(end);
    used_f.insert(begin);
    used_second.insert(end);
    bfs_proc();
    std::cout << ans;
}