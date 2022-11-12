#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

bool is_match(const std::string& sample, const std::string& pattern) {
    std::vector<std::set<uint32_t>> db(pattern.length() + 1);
    db[0].insert(0);


    for (uint32_t pattern_ind = 0; pattern_ind < pattern.length(); ++pattern_ind) {

        for (auto& sample_ind: db[pattern_ind]) {

            switch (pattern[pattern_ind]) {
                /*case */
                case '*':{
                    for (uint32_t n_sample_ind = sample_ind; n_sample_ind < (sample.length() + 1); ++n_sample_ind) {
                        db[pattern_ind + 1].insert(n_sample_ind);
                    }
                    continue;
                    break;
                }

                case '?':{
                    if (sample_ind < sample.length()) {
                        db[pattern_ind + 1].insert(sample_ind + 1);
                    }
                    /* code */
                    continue;
                    break;
                }

                default: {
                    break;
                }
            }
            if (sample_ind < sample.length() && sample[sample_ind] == pattern[pattern_ind]) {
                        db[pattern_ind + 1].insert(sample_ind + 1);
            }
        }
    }


    if (!db[pattern.length()].empty() && db[pattern.length()].find(sample.length()) != db[pattern.length()].end()) {
        return 1;
    }
    else {
        return 0;
    }
    
}


int main() {
    std::string sample = "", pattern = "";
    std::cin >> sample >> pattern;
    // std::string lol = "abc", kek = "a*c";
    // std::cout << is_match(lol, kek);


    std::cout << (is_match(sample, pattern) ? "YES" : "NO");
    return 0;
}