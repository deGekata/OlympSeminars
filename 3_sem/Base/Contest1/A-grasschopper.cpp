#include <vector>
#include <iostream>


int get_variants(std::vector<int>& vars, int pos) {
    if (pos < 0) return 0;

    return  vars[pos];
}


int main() {

    int steps, m_jump;
    std::cin >> steps >> m_jump;
    
    std::vector<int> cache(steps + 1, 0);

    cache[0] = 1;

    for (int it = 1; it <= steps; ++it) {
        for (int jump_size = 1; jump_size <= m_jump; ++jump_size)
            cache[it] += get_variants(cache, it - jump_size); 
    }

    std::cout << cache[steps];

    

    return 0;
}