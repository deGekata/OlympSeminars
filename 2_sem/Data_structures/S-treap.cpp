#include <iostream>
#include <string>

struct node {
    int priority;
    int size;
    int num;
    std::string name;
    node* left, * right;

    node(int num_, std::string name_) {
        priority = ((rand() << 16) + rand());
        left = nullptr;
        right = nullptr;
        num = num_;
        name = name_;
        size = 1;
    }
};


void erase_tree(node* root) {
    if (root == nullptr) return;

    if (root->right != nullptr) {
        erase_tree(root->right);
        delete root->right;
    }

    if (root->left != nullptr) {
        erase_tree(root->left);
        delete root->left;
    }

    return;
}


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
    // if (p1.second != nullptr) delete p1.second;
    if (p2.first != nullptr) {
        erase_tree(p2.first);
        delete p2.first;
    } 

    root = merge(p1.first, p2.second);
    return root;
}

node* find_by_id(node* root, int id) {
    if (root == nullptr) {
        return nullptr;
    }
    if (id < size(root->left))
        return find_by_id(root->left, id);
    else if (size(root->left) == id)
        return root;
    else
        return find_by_id(root->right, id - size(root->left) - 1);
}



int main()
{
    node* dekart = nullptr;
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        std::string name;
        int val;
        std::cin >> name >> val;
        dekart = insert(dekart, i, new node(val, name));
    }
    for (int i = 0; i < m; ++i) {
        int mod, index;
        std::cin >> mod >> index;
        --index;
        if (mod == 0) {
            int val;
            std::string name;
            std::cin >> name >> val;
            dekart = insert(dekart, index, new node(val, name));
        } else if (mod == 1) {
            dekart = erase(dekart, index);
        } else if (mod == 2) {
            node* employee = find_by_id(dekart, index);
            std::cout << employee->name << ' ' << employee->num << '\n';
        }
    }

    erase_tree(dekart);
    delete dekart;
}
