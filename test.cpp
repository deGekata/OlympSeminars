#include <iostream>
#include <algorithm>

#define int long long
const int INF = 1e18;

struct node {
    int priority;
    int size;
    int num;
    node* left, * right;

    node(int num_) {
        priority = ((rand() << 16) + rand());
        left = nullptr;
        right = nullptr;
        num = num_;
        size = 1;
    }
};

int size(node* v) {
    if (v == nullptr)
        return 0;
    else
        return v->size;
}

void up(node* v) {
    if (v == nullptr)
        return;
    v->size = size(v->left) + size(v->right) + 1;
}

node* merge(node* l, node* r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;

    if (l->priority > r->priority) {
        l->right = merge(l->right, r);
        up(l);
        return l;
    }
    else {
        r->left = merge(l, r->left);
        up(r);
        return r;
    }
}

std::pair<node*, node*> split(node* root, int k) {
    if (root == nullptr) {
        return { nullptr, nullptr };
    }
    int nw = size(root->left);
    if (nw < k) {
        std::pair<node*, node*> p = split(root->right, k - nw - 1);
        root->right = p.first;
        up(root);
        return { root, p.second };
    }
    else {
        std::pair<node*, node*> p = split(root->left, k);
        root->left = p.second;
        up(root);
        return { p.first, root };
    }

}

node* insert(node* root, int pos, node* v) {
    if (root == nullptr)
        return v;
    std::pair<node*, node*> p1 = split(root, pos);
    return merge(merge(p1.first, v), p1.second);
}

node* erase(node* root, int key) {
    if (root == nullptr) {
        return nullptr;
    }
    std::pair<node*, node*> p1 = split(root, key);
    std::pair<node*, node*> p2 = split(p1.second, 1);
    root = merge(p1.first, p2.second);
    return root;
}

int find_by_id(node* root, int id) {
    if (root == nullptr) {
        return -INF;
    }
    if (id < size(root->left))
        return find_by_id(root->left, id);
    else if (size(root->left) == id)
        return root->num;
    else
        return find_by_id(root->right, id - size(root->left) - 1);
}

signed main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    node* dekart = nullptr;
    int n, lol;
    std::cin >> n >> lol;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        ans += x * x;
        dekart = insert(dekart, i, new node(x));
    }
    std::cout << ans << '\n';
    int q;
    std::cin >> q;
    int nw = n;
    while (q--) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int ind;
            std::cin >> ind;
            --ind;
            if (ind == 0) {
                int x = find_by_id(dekart, 0);
                int y = find_by_id(dekart, 1);
                ans += 2 * x * y;
                dekart = erase(dekart, 0);
                dekart = erase(dekart, 0);
                dekart = insert(dekart, 0, new node(x + y));
                --nw;
            }
            else if (ind + 1 == nw) {
                int x = find_by_id(dekart, ind);
                int y = find_by_id(dekart, ind - 1);
                ans += 2 * x * y;
                dekart = erase(dekart, ind);
                dekart = erase(dekart, ind - 1);
                dekart = insert(dekart, ind - 1, new node(x + y));
                --nw;
            }
            else {
                int y = find_by_id(dekart, ind);
                int x = find_by_id(dekart, ind - 1);
                int z = find_by_id(dekart, ind + 1);
                int num1 = y / 2;
                int num2 = y - num1;
                ans += 2 * num1 * x + num1 * num1 + 2 * num2 * z + num2 * num2 - y * y;
                dekart = erase(dekart, ind - 1);
                dekart = erase(dekart, ind - 1);
                dekart = erase(dekart, ind - 1);
                dekart = insert(dekart, ind - 1, new node(x + num1));
                dekart = insert(dekart, ind, new node(z + num2));
                --nw;
            }
        }
        else {
            int ind;
            std::cin >> ind;
            --ind;
            int x = find_by_id(dekart, ind);
            int num1 = x / 2;
            int num2 = x - num1;
            ans -= 2 * num1 * num2;
            dekart = erase(dekart, ind);
            dekart = insert(dekart, ind, new node(num1));
            dekart = insert(dekart, ind + 1, new node(num2));
            ++nw;
        }
        std::cout << ans << '\n';
    }
}