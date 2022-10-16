#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMP_TYPE(lft, rht) strcmp((lft), (rht))

// #define debug

#ifdef debug
    #define dprintf(...) printf(__VA_ARGS__)
#else
    #define dprintf(...)
#endif

typedef struct AVLTreeNode {
    struct AVLTreeNode* left;
    struct AVLTreeNode* right;
    struct AVLTreeNode* parent;
    char* key;
    char* value;
    int height;
    
} AVLTreeNode;

void AVLTreeNodeCtor(AVLTreeNode* node, char* _key, char* value, int _height, AVLTreeNode* _left, AVLTreeNode* _right, AVLTreeNode* _prev);
AVLTreeNode* AVLTreePush(AVLTreeNode* root, char* key, char* value);
AVLTreeNode* AVLTreePop(AVLTreeNode* root, char* key, AVLTreeNode** ret_val);
void AVLTreeClear(AVLTreeNode** root);
void AVLTreeNodeDtor(AVLTreeNode** root);
int  AVLTreeHeight_of(AVLTreeNode* node);
int  AVLTreeDiff_of(AVLTreeNode* node);
void AVLTreeFix_height(AVLTreeNode* node);

AVLTreeNode* min_way(AVLTreeNode* vertex);
AVLTreeNode* replace_min(AVLTreeNode* vertex);
AVLTreeNode* min_way(AVLTreeNode* vertex);
AVLTreeNode* find(AVLTreeNode* root, char* key);
AVLTreeNode* _insert(AVLTreeNode* root, char* key, char* value);
AVLTreeNode* _pop(AVLTreeNode* vertex, char* key);
AVLTreeNode* rotate_left(AVLTreeNode* vertex);
AVLTreeNode* rotate_right(AVLTreeNode* vertex);
AVLTreeNode* balance(AVLTreeNode* vertex);   



void AVLTreeNodeCtor(AVLTreeNode* node, char* _key, char* _value, int _height, AVLTreeNode* _left, AVLTreeNode* _right, AVLTreeNode* _prev) {
    node->key    = _key;
    node->value  = _value;
    node->height = _height;
    node->left   = _left;
    node->right  = _right;
    node->parent = _prev;
}

void AVLTreeNodeDtor(AVLTreeNode** root)  {
    if (root != NULL ) {
        free((*root)->key);
        free((*root)->value);
        free(*root);
        *root = NULL;
    }
}

void AVLTreeClear(AVLTreeNode** root) {
    if (*root == NULL) return;

    if ((*root)->left) {
        AVLTreeClear(&(*root)->left);
        (*root)->left = NULL;
    }

    if ((*root)->right) {
        AVLTreeClear(&(*root)->right);
        (*root)->right = NULL;
    }

    if ((*root)->left == NULL && (*root)->right == NULL) {
        AVLTreeNodeDtor(root);
    }
}

AVLTreeNode* AVLTreePush(AVLTreeNode* root, char* key, char* value) {
    char* n_key = (char*) malloc(strlen(key) + 1);
    char* n_value = (char*) malloc(strlen(value) + 1);
    strcpy(n_key, key);
    strcpy(n_value, value);

    return _insert(root, n_key, n_value);
    
}

AVLTreeNode* AVLTreePop(AVLTreeNode* root, char* key, AVLTreeNode** res) {
    *res = find(root, key);
    if ((*res) == NULL) return root;
    return _pop(root, key);
}

AVLTreeNode* find(AVLTreeNode* root, char* key) {
    if (root == NULL) {
        return NULL;
    }
    
    int cmp_res = CMP_TYPE(root->key, key);

    if (cmp_res == 0) {
        return root;
    }

    if (cmp_res < 0) {
        return find(root->right, key);
    } else {
        return find(root->left, key);
    }
    
    return NULL;
}


int AVLTreeHeight_of(AVLTreeNode* node) {
    return node == NULL ? 0 : node->height;
}

int  AVLTreeDiff_of(AVLTreeNode* node) {
    return AVLTreeHeight_of(node->right) - AVLTreeHeight_of(node->left);
}

void AVLTreeFix_height(AVLTreeNode* node) {
    int l_h = AVLTreeHeight_of(node->left);
    int r_h = AVLTreeHeight_of(node->right);
    node->height = (l_h > r_h ? l_h : r_h) + 1;
    return;
}

AVLTreeNode* min_way(AVLTreeNode* vertex) {
    return vertex->left == NULL ? vertex : min_way(vertex->left);
}

AVLTreeNode* replace_min(AVLTreeNode* vertex) {
    if (vertex->left == NULL) {
        return vertex->right;
    }

    vertex->left = replace_min(vertex->left);
    return balance(vertex);
}


AVLTreeNode* _insert(AVLTreeNode* root, char* key, char* value) {
    if (root == NULL) {
        
        AVLTreeNode* ret_val = (AVLTreeNode*) calloc(1, sizeof(AVLTreeNode));
        AVLTreeNodeCtor(ret_val, key, value, 1, NULL, NULL, NULL);
        return ret_val;
    }
    int cmp_res = CMP_TYPE(key, root->key);
    if (cmp_res < 0) {
        root->left =  _insert(root->left, key, value);
    } else if (cmp_res > 0) {
        root->right = _insert(root->right, key, value);
    } else {
        free(root->key);
        free(root->value);
        root->key = key;
        root->value = value;
        return root;
    }

    return balance(root);
    //return NULL;
}

AVLTreeNode* _pop(AVLTreeNode* vertex, char* key) {
    if (vertex == NULL) {
        return NULL;
    }
    int cmp_res = CMP_TYPE(key, vertex->key);
    if (cmp_res < 0) {
        dprintf("Left\n");
        vertex->left = _pop(vertex->left, key);
    } else if (cmp_res > 0) {
        dprintf("Right\n");
        vertex->right = _pop(vertex->right, key);

    } else {
        dprintf("min: %s | %s\n", vertex->key, vertex->value);
        AVLTreeNode* left = vertex->left;
        AVLTreeNode* right = vertex->right;
        // free(vertex);
        if (right == NULL) {
            dprintf("true");
            vertex->left = NULL;
            return left;
        }
        AVLTreeNode* min = min_way(right);
        min->right = replace_min(right);
        min->left = left;
        return balance(min);
    }
    
    return balance(vertex);
}

AVLTreeNode* rotate_left(AVLTreeNode* vertex) {
    AVLTreeNode* p = vertex->right;
    vertex->right = p->left;
    p->left = vertex;
    AVLTreeFix_height(vertex);
    AVLTreeFix_height(p);
    return p;
}

AVLTreeNode* rotate_right(AVLTreeNode* vertex) {
    AVLTreeNode* q = vertex->left;
    vertex->left = q->right;
    q->right= vertex;
    AVLTreeFix_height(vertex);
    AVLTreeFix_height(q);
    return q;
}

AVLTreeNode* balance(AVLTreeNode* vertex) {
    AVLTreeFix_height(vertex);

    if (AVLTreeDiff_of(vertex) == 2) {
        if (AVLTreeDiff_of(vertex->right) < 0) {
            vertex->right = rotate_right(vertex->right);
        }
        return rotate_left(vertex);
    }

    if (AVLTreeDiff_of(vertex) == -2) {
        if (AVLTreeDiff_of(vertex->left) > 0) {
            vertex->left = rotate_left(vertex->left);
        }
        return rotate_right(vertex);
    }
    
    return vertex;
}
#ifdef debug
#include <stack>
void ghoul_graph_base(AVLTreeNode* tree) {
    
    static int dump_number = 0;
    dump_number = 0;
    char filename[150] = {};
    sprintf(filename, "./Dump/LIST_DMP_№%d.dot", dump_number);

    FILE* file = fopen(filename, "w");


    printf("%p file ptr\n", file);
    fprintf(file,   "digraph G{"
                    "   ");

    std::stack<AVLTreeNode*> stack;
    stack.push(tree);

    AVLTreeNode* cur_node = NULL;
    while (stack.size() > 0) {
        printf("lol\n");
        cur_node = stack.top();
        stack.pop();
        if (cur_node == NULL) break;
        fprintf(file, "N%p[label=\"key:'%s' \n value:'%s' \"];\n", cur_node, cur_node->key, cur_node->value);

        if (cur_node->left != NULL) {
            fprintf(file, "N%p->N%p[label=\"l\"];\n", cur_node, cur_node->left);
            stack.push(cur_node->left);
        }

        if (cur_node->right != NULL) {
            fprintf(file, "N%p->N%p[label=\"r\"];\n", cur_node, cur_node->right);
            stack.push(cur_node->right);
        }
         
    }
    
    fprintf(file, "}");
    fclose(file);

    char command[1000] = {};
    sprintf(command, "dot ./Dump/LIST_DMP_№%d.dot -T png -o ./Dump/LIST_DMP_№%d.png", dump_number, dump_number);
    system(command);

    ++dump_number;
}
#endif


int main() {
    AVLTreeNode* root = NULL;
    // AVLTreePush(&root, 5, 2);
    char buff[30];
    char buff2[30];
    // int cnt = 10;

    while ((scanf("%25s", buff)) != EOF
        // && cnt != 0
    ) {
        // cnt--;
        
        if (strcmp(buff, "insert") == 0) {
            scanf("%25s", buff);
            scanf("%25s", buff2);
            root = AVLTreePush(root, buff, buff2);
            #ifdef debug
                ghoul_graph_base(root);
            #endif
        } else if (strcmp(buff, "find") == 0) {
            scanf("%25s", buff);
            AVLTreeNode* ret_val = find(root, buff);
            if (ret_val == NULL) {
                printf("MISSING\n");
            } else {
                printf("%s\n", ret_val->value);
            }
            #ifdef debug
                ghoul_graph_base(root);
            #endif
        } else if (strcmp(buff, "erase") == 0) {
            scanf("%25s", buff);
            AVLTreeNode* ret_val;
            root = AVLTreePop(root, buff, &ret_val);
            if (ret_val != NULL) AVLTreeNodeDtor(&ret_val);
            #ifdef debug
                ghoul_graph_base(root);
            #endif
        } else if (strcmp(buff, "end") == 0) {
            break;
        }
    }

    AVLTreeClear(&root);
    #ifdef debug
        ghoul_graph_base(root);
    #endif
    return 0;
}