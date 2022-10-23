#include <iostream>
#include <vector>
#include <algorithm>


int binsearch(std::vector<int>& vec, int elem) {
    int lhs = -1, rhs = vec.size();

    while(rhs - 1 > lhs) {
        int mid = (rhs + lhs) / 2;
        if (vec[mid] < elem) 
            lhs = mid;
        else
            rhs = mid;
    }

    return rhs;
}


int main() {
    int N;
    std::cin >> N;

    std::vector<int> nums(N + 1);
    std::vector<int> cache(N + 1, INT32_MAX);
    std::vector<int> prev(N + 1);
    std::vector<int> mx_pos(N + 1);
    mx_pos[0] = -1;

    for (int it = 0; it < nums.size(); ++it) {
        std::cin >> nums[it];
    }


    cache[0] = INT32_MIN;
    int mx_len = 0;

    for (int cur_elem = 0; cur_elem < N; ++cur_elem) {
        
        int ins_pos = binsearch(cache, nums[cur_elem]);

        if ((cache[ins_pos - 1] < nums[cur_elem]) && ((nums[cur_elem]) < cache[ins_pos])) {
                cache[ins_pos] = nums[cur_elem];
                prev[cur_elem] = mx_pos[ins_pos - 1];
                mx_pos[ins_pos] =  cur_elem;
                mx_len = std::max(mx_len, ins_pos);
            }

    }
// 5 10 6 12 3 24 7 8
    // int mx_size = cache[0];
    // int pos = 0;

    // for (int it = 0; it < N; ++it) {
    //     if (cache[it] > mx_size) {
    //         mx_size = cache[it];
    //         pos = it;
    //         // std::cout << pos << " pos\n";
    //     }
    // }1

    std::vector<int> ans;
    int cur_pos = mx_pos[mx_len];
    while (cur_pos != -1) {
        ans.push_back(cur_pos);
        cur_pos = prev[cur_pos];
    }

    std::reverse(ans.begin(), ans.end());
    std::cout << ans.size() << " ";
    for (int it = 0; it < ans.size(); ++it) {
        std::cout << ans[it] << ' ';
    }
    


    return 0;
}