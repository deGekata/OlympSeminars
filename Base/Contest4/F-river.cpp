    #include <stdio.h>
    #include <stdlib.h>

    #define int long long
    const long long INF = 1e18;

    struct node {
        long long priority;
        long long size;
        long long num;
        node* left, * right;
    };

    struct pr {
        node* first;
        node* second;
    };

    node* node_ctor(long long num) {
        node* nd = (node*) calloc(1, sizeof(node));
        nd->priority = ((rand() << 16) + rand());
        nd->left = nullptr;
        nd->right = nullptr;
        nd->num = num;
        nd->size = 1;
        return nd;
    }


    long long size(node* v) {
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



    pr split(node* root, long long k) {
        if (root == nullptr) {
            return { nullptr, nullptr };
        }
        long long nw = size(root->left);
        if (nw < k) {
            pr p = split(root->right, k - nw - 1);
            root->right = p.first;
            up(root);
            return { root, p.second };
        }
        else {
            pr p = split(root->left, k);
            root->left = p.second;
            up(root);
            return { p.first, root };
        }

    }

    node* insert(node* root, int pos, node* v) {
        if (root == nullptr)
            return v;
        pr p1 = split(root, pos);
        return merge(merge(p1.first, v), p1.second);
    }

    node* erase(node* root, int key) {
        if (root == nullptr) {
            return nullptr;
        }
        pr p1 = split(root, key);
        pr p2 = split(p1.second, 1);
        root = merge(p1.first, p2.second);
        return root;
    }

    long long find_by_id(node* root, long long id) {
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

        node* dekart = nullptr;
        long long n, lol;
        scanf("%lld %lld", &n, &lol);
        long long ans = 0;
        for (long long i = 0; i < n; ++i) {
            long long x;
            scanf("%lld", &x);
            ans += x * x;
            dekart = insert(dekart, i, node_ctor(x));
        }

        printf("%lld\n", ans);

        long long q;
        scanf("%lld", &q);
        long long nw = n;
        while (q--) {
            long long op;
            scanf("%lld", &op);
            if (op == 1) {
                long long ind;
                scanf("%lld", &ind);
                --ind;
                if (ind == 0) {
                    long long x = find_by_id(dekart, 0);
                    long long y = find_by_id(dekart, 1);
                    ans += 2 * x * y;
                    dekart = erase(dekart, 0);
                    dekart = erase(dekart, 0);
                    dekart = insert(dekart, 0, node_ctor(x + y));
                    --nw;
                } else if (ind + 1 == nw) {
                    long long x = find_by_id(dekart, ind);
                    long long y = find_by_id(dekart, ind - 1);
                    ans += 2 * x * y;
                    dekart = erase(dekart, ind);
                    dekart = erase(dekart, ind - 1);
                    dekart = insert(dekart, ind - 1, node_ctor(x + y));
                    --nw;
                } else {
                    long long y = find_by_id(dekart, ind);
                    long long x = find_by_id(dekart, ind - 1);
                    long long z = find_by_id(dekart, ind + 1);
                    long long num1 = y / 2;
                    long long num2 = y - num1;
                    ans += 2 * num1 * x + num1 * num1 + 2 * num2 * z + num2 * num2 - y * y;
                    dekart = erase(dekart, ind - 1);
                    dekart = erase(dekart, ind - 1);
                    dekart = erase(dekart, ind - 1);
                    dekart = insert(dekart, ind - 1, node_ctor(x + num1));
                    dekart = insert(dekart, ind, node_ctor(z + num2));
                    --nw;
                }
            } else {
                long long ind;
                scanf("%lld", &ind);
                --ind;
                long long x = find_by_id(dekart, ind);
                long long num1 = x / 2;
                long long num2 = x - num1;
                ans -= 2 * num1 * num2;
                dekart = erase(dekart, ind);
                dekart = insert(dekart, ind, node_ctor(num1));
                dekart = insert(dekart, ind + 1, node_ctor(num2));
                ++nw;
            }
            printf("%lld\n", ans);
        }

        return 0;
    }