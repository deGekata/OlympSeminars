#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

struct Node {
    Node* lft;
    Node* rht;
};

Node* Node_ctor() {
    Node* n_node = (Node*) calloc(1, sizeof(Node));
    return n_node;
}

Node* Node_dtor(Node* node) {
    if (node == NULL) {
        return NULL;
    }

    free(node);
    return NULL;
}

void Tree_insert(Node* head, unsigned int num, unsigned int digit_pos) {
    if (digit_pos == 32) {
        return;
    }
    
    uint8_t bit_val = ((num & (1 << (31 - digit_pos))) != 0);

    if (bit_val != 0) { 
        if (head->rht == NULL) {
            head->rht = Node_ctor();
        }
        Tree_insert(head->rht, num, digit_pos + 1);

    } else {
        if (head->lft == NULL) {
            head->lft = Node_ctor();
        }
        Tree_insert(head->lft, num, digit_pos + 1);

    }
}

Node* Tree_erase(Node* head, unsigned int num, unsigned int digit_pos) {
    if ((digit_pos == 32) || (head == NULL)) {
        return Node_dtor(head);
    }

    unsigned char curBit = ((num & (1 << (31 - digit_pos))) != 0);

    if (curBit) {
        head->rht = Tree_erase(head->rht, num, digit_pos + 1);
    } else {
        head->lft  = Tree_erase(head->lft, num, digit_pos + 1);
    }

    if (head->lft != NULL || head->rht != NULL  ) {
        return head;
    }
        
    return Node_dtor(head);
}

unsigned int xor_max(Node* node, unsigned int num, unsigned int digit_pos) {
    if (digit_pos == 32) {
        return 0;
    }
    
    uint8_t bit_val = ((num & (1 << (31 - digit_pos)))) != 0;

    if (bit_val) {
        if (node->lft) {
            return (0 + xor_max(node->lft, num, digit_pos + 1));
        }

        return ((1 << (31 - digit_pos)) + xor_max(node->rht, num, digit_pos + 1));

    } else {
        if (node->rht) {
            return (1 << (31 - digit_pos)) + xor_max(node->rht, num, digit_pos + 1);
        }

        return 0 + xor_max(node->lft, num, digit_pos + 1);

    }
    
    return -1;
}

Node* Tree_dtor(Node* head) {
    if (head->lft != NULL) {
        head->lft = Tree_dtor(head->lft);
    }

    if (head->rht != NULL) {
        head->rht = Tree_dtor(head->rht);
    }

    return Node_dtor(head);
}

int main() {
    Node* t_tree = Node_ctor();

    unsigned int cmd_cnt = 0;
    scanf("%u", &cmd_cnt);

    unsigned int operation_num  = 0, param = 0;
    
    for (unsigned int cur_command = 0; cur_command < cmd_cnt; cur_command++) {
        scanf("%u %u", &operation_num, &param);

        switch (operation_num) {
            case 1: 
                Tree_insert(t_tree, param, 0);
                break;

            case 2:
                Tree_erase(t_tree, param, 0);
                break;

            case 3:
                printf("%u\n", xor_max(t_tree, param, 0));
                break;
        }
    }
    

    t_tree = Tree_dtor(t_tree);

    return 0;
}