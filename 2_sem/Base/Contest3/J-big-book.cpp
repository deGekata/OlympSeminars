#include <inttypes.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

void* safe_calloc(size_t _Count, size_t _Size) {
    // printf("_count %zu _size %zu\n", _Count, _Size);
    void* ret_ptr = calloc(_Count, _Size);
    // printf("loool");
    assert(ret_ptr && "Not enough memory to allocate data");
    return ret_ptr;
}

void safe_realloc(void** _Block, size_t _Size) {
    void* ret_ptr = realloc(*_Block, _Size);
    assert(ret_ptr && "Not enough memory to reallocate data");
    *_Block = ret_ptr;
}

void safe_free(void* ptr) {
    if(ptr != NULL) {
        free(ptr);
    }
    return;
}

uint64_t strHashCode(char* str) {
    uint64_t hash = 123456;
    while (*str) {
        hash = ((hash << 7) + hash) ^ *(str++);
    }

    return hash;
}


uint64_t asciiHashCode(char* str) {
    // uint64_t hash = 1234;
    // printf("%d\n", str[0]);
    return str[0];
}

uint64_t strlenHashCode(char* str) {
    uint64_t hash = 1234;
    
    return hash + strlen(str); 
}

uint64_t sumHashCode(char* str) {
    uint64_t hash = 0;
    while (*str) {
        hash += *(str++);
    }

    return hash;
}

uint64_t rollHashCode(char* str) {
    uint64_t hash = str[0];
    while (*str) {
        hash = ((hash >> 1) | (hash << 63)) ^ *(str++);
    }

    return hash;
}

uint64_t constOneHashCode(char* str) {
    return 1;
}

typedef char* HKey;
typedef char* HValue;


typedef struct Entry {
    HKey key;
    HValue value;
} Entry;


void EntryCtor(Entry* ptr, HKey key, HValue value); //fffffffffff
// void EntryCtor(Entry* ptr, Entry* ref); //fffffffffff

void EntryLinkCtor(Entry* ptr, Entry* ref);

void EntryDtor(Entry* ptr);

// Entry* EntryCopy

size_t const Base_list_size = 8; 
size_t const Base_realloc_coeff = 2;

typedef int List_type;

typedef struct ListNode {
    Entry elem;
    int next, prev;
} ListNode;

typedef struct LinkedList {
    size_t size, capacity;
    int head, tail, free_tail;
    int is_sorted;
    ListNode* data;
} LinkedList;


void ctor_list(LinkedList* list);

void dtor_list(LinkedList* list);

void dtor_links_list(LinkedList* list);

void push_back_list(LinkedList* list, HKey key, HValue value);

void insert_list(LinkedList* list, int ind, HKey key, HValue value);

void erase_list(LinkedList* list, int ind);

void erase_link_list(LinkedList* list, int ind);

void sort_list(LinkedList* list);

int find_item_list_entr(LinkedList* list, Entry* val);

int find_item_list(LinkedList* list, HKey val);

// void get_item_by_ind(LinkedList* list, int ind);
Entry get_item_by_ind(LinkedList* list, int ind);

void realloc_list(LinkedList* list);

void printlist(LinkedList* list);

void add_free_elem(LinkedList* list, int ind);

int pop_free_elem(LinkedList* list);

int listCreateGraph(LinkedList* list);

#define Max_out_file_len 50
const size_t Max_out_file_len_ = 50;
#define Max_cmd_len 150
const size_t Max_cmd_len_  = 150;

const char* Img_dump_dir = "./dump/";

const char* Next_link_color = "blue";
const char* Prev_link_color = "red";
const char* Free_link_color = "orange";

#define CMP_EQ(a, b) (strcmp((a), (b)) == 0)

void EntryCtor(Entry* ptr, HKey key, HValue value) {
    char* ptr_ = (char*)0x280000002a;
    ptr->key = (char*) malloc(strlen(key) + 1);
    ptr->value = (char*) malloc(strlen(value) + 1);
    if (ptr->key == ptr_ || ptr->value == ptr_) {
        exit(-1);
    }
    strcpy(ptr->key, key);
    strcpy(ptr->value, value);
    return;
}

void EntryLinkCtor(Entry* ptr, Entry* ref) {
    ptr->key = ref->key;
    ptr->value = ref->value;
}

void EntryDtor(Entry* ptr) {
    safe_free(ptr->key);
    safe_free(ptr->value);
    return;
}

void ctor_list(LinkedList* list) {
    assert(list && "list must not be NULL");
    
    if (list->data != NULL) {
        free(list->data);
    }
    
    list->data = (ListNode*) safe_calloc(Base_list_size, sizeof(ListNode));

    list->size = 0;
    list->capacity = Base_list_size;
    list->head = list->tail = 0;
    list->free_tail = 1;
    

    for (size_t it = 1; it < list->capacity - 1; ++it) {
        list->data[it].next = (int)(it + 1);
        list->data[it].prev = -1;
    }
    list->data[list->capacity - 1].prev = -1;

    list->data[list->capacity - 1].next = 0;

    list->is_sorted = 0;

    return;
}

void dtor_list(LinkedList* list) {
    assert(list && "list must not be NULL");
    if (list->capacity == 0) return;
    // printf("%d line\n", __LINE__);
    // for (size_t it = 0; it < list->capacity; ++it) {
    //     if (list->data[it].elem.key == (char*)0xbf000000c1 ||list->data[it].elem.value == (char*)0xbf000000c1) {
    //         printf("wtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtfwtf");
    //     }
    // }
    for (size_t it = 0; it < list->capacity; ++it) {
        // printf("")
        safe_free(list->data[it].elem.key);
        safe_free(list->data[it].elem.value);
    }

    // printf("%d line\n", __LINE__);
    safe_free(list->data);
    list->head = list->tail = list->free_tail = -1;
    list->size = list->capacity = (size_t)(0);
    list->is_sorted = 0;
    // printf("%d line\n", __LINE__);

    return;
}

void dtor_links_list(LinkedList* list) {
    assert(list && "list must not be NULL");
   
    for (size_t it = 0; it < list->capacity; ++it) {
        list->data[it].elem.key = NULL;
        list->data[it].elem.value = NULL;
    }

    // printf("%d line\n", __LINE__);
    safe_free(list->data);
    list->head = list->tail = list->free_tail = -1;
    list->size = list->capacity = (size_t)(0);
    list->is_sorted = 0;
    // printf("%d line\n", __LINE__);

    return;
}

void push_back_list(LinkedList* list, HKey key, HValue value) {
    insert_list(list, list->tail, key, value);
}

void insert_list(LinkedList* list, int ind, HKey key, HValue value) {
    assert(list && "List must not be NULL");
    assert(0 <= ind && (size_t)(ind) < list->capacity && "index out of range");
    assert(list->data[ind].prev != -1 && "item should be inserted after existing item");
    
    int n_elem_pos = pop_free_elem(list);
    
    // EntryLinkCtor(&list->data[n_elem_pos].elem, val);
    list->data[n_elem_pos].elem.key = key;
    list->data[n_elem_pos].elem.value = value;

    list->data[list->data[ind].next].prev = n_elem_pos;
    list->data[n_elem_pos].prev = ind;
    list->data[n_elem_pos].next = list->data[ind].next;
    list->data[ind].next = n_elem_pos;

    ++list->size;

    return;
} 

void erase_list(LinkedList* list, int ind) {
    assert(list && "List must not be NULL");
    assert(0 < ind && (size_t)(ind) < list->capacity && "index out of range");
    assert(list->data[ind].prev != -1 && "item must exist");

    safe_free(list->data[ind].elem.key);
    safe_free(list->data[ind].elem.value);
    list->data[ind].elem.key = NULL;
    list->data[ind].elem.value = NULL;
    
    list->data[ list->data[ind].prev ].next = list->data[ind].next;
    list->data[ list->data[ind].next ].prev = list->data[ind].prev;

    add_free_elem(list, ind);

    --list->size;
    
    return;
}

void erase_link_list(LinkedList* list, int ind) {
    assert(list && "List must not be NULL");
    assert(0 < ind && (size_t)(ind) < list->capacity && "index out of range");
    assert(list->data[ind].prev != -1 && "item must exist");
    list->data[ind].elem.key = NULL;
    list->data[ind].elem.value = NULL;

    list->data[ list->data[ind].prev ].next = list->data[ind].next;
    list->data[ list->data[ind].next ].prev = list->data[ind].prev;

    add_free_elem(list, ind);

    --list->size;
    
    return;
}

void sort_list(LinkedList* list) {
    assert(list);

    ListNode* buff = (ListNode*) safe_calloc(list->capacity, sizeof(ListNode));

    int item_ind = list->data[0].next;
    int offset = 1;
    
    while (item_ind != 0) {
        buff[offset].elem = list->data[item_ind].elem;
        buff[offset].prev = offset - 1;
        buff[offset].next = offset + 1;

        item_ind = list->data[item_ind].next;
        offset += 1;
    }

    buff[offset - 1].next = 0;
    buff[0].next = list->size > 0;
    buff[0].prev = offset - 1;
    
    if (list->size < (list->capacity - 1)) {
        item_ind = list->free_tail;
        list->free_tail = offset;

        while (item_ind != 0) {
            buff[offset].next = offset + 1;
            buff[offset].prev = -1;
            ++offset;
            item_ind = list->data[item_ind].next;
        }

        buff[list->capacity - 1].next = 0;
    }

    ListNode* temp = list->data;
    list->data = buff;
    free(temp);

    list->is_sorted = 1;

    return;
}

int find_item_list_entr(LinkedList* list, Entry* val) {
    int cur_ind = list->head;
    while (cur_ind != 0) {
        if (CMP_EQ(list->data[cur_ind].elem.key, val->key)) {
            return cur_ind;
        }
        cur_ind = list->data[cur_ind].next;
    }
    return cur_ind;
}

int find_item_list(LinkedList* list, HKey val) {
    int cur_ind = list->data[list->head].next;
    int size = list->size;
    while (size != 0) {
        if (CMP_EQ(list->data[cur_ind].elem.key, val)) {
            return cur_ind;
        }
        size--;
        cur_ind = list->data[cur_ind].next;
    }
    return cur_ind;
}

Entry get_item_by_ind(LinkedList* list, int ind) {
    assert(list && "List must not be NULL");
    assert(1 <= ind && (size_t)(ind) < list->size && "Index out of range");

    if (list->is_sorted) {
        return list->data[ind].elem;
    }

    int cur_ind = 0;

    for(int it = 0; it < ind; ++it) {
        cur_ind =  list->data[cur_ind].next;
    }

    return list->data[cur_ind].elem;
}

void realloc_list(LinkedList* list) {
    assert(list && "list ptr must not be null");

    safe_realloc((void**)&list->data, (list->capacity * Base_realloc_coeff)*sizeof(ListNode) );

    size_t prev_capacity = list->capacity;
    list->capacity = list->capacity * 2;
    for (size_t it = prev_capacity; it < list->capacity; ++it) {
        add_free_elem(list, (int)(it));
    }    

    return;
}

void printlist(LinkedList* list) {
    printf("%lu   data: next:   :prev----------------", list->size);
    // printf("\n");
    for(size_t it = 0; it < list->capacity; ++it) {
        printf("\t%lu \t%s \n", it, list->data[it].elem.key);
    }
    printf("\n");
    // printf("\n");
    // printf(" tail :%d  head: %d  free_tail %d \n\n", list->tail, list->head, list->free_tail);

}


void add_free_elem(LinkedList* list, int ind) {
    assert(list && "List must not be NULL");
    assert(0 < ind && (size_t)(ind) < list->capacity && "index out of range");

    // list->data[ind].elem = 0;
    list->data[ind].prev = -1;

    if (list->free_tail == 0) {
        list->data[ind].next = 0; 
    } else {
        list->data[ind].next = list->free_tail;
    }
    list->data[ind].elem.key = list->data[ind].elem.value = 0;
    list->free_tail = ind;

    return;
}

int pop_free_elem(LinkedList* list) {
    assert(list && "List must not be NULL");
    
    if (list->free_tail == 0) {
        realloc_list(list);
    }

    int n_elem_pos = list->free_tail;
    list->free_tail = list->data[n_elem_pos].next;
    return n_elem_pos;
}




int listCreateGraph(LinkedList* list) {
    
    static int nDump = 0;

    char filename[Max_out_file_len] = {};
    sprintf(filename, "%sLIST_DUMP_%d.dot", Img_dump_dir, nDump);

    FILE* file = fopen(filename, "w");

    fprintf(file,   "digraph G{\n");
    fprintf(file,   "   rankdir=LR;\n");
    fprintf(file,   "   splines=ortho;\n");
    fprintf(file,   "   nodesep=1;\n");
    fprintf(file,   "   F[shape=\"circle\", color=\"blue\", label=\"Free\"];\n");

    // printf("%d line\n", __LINE__);
    for(size_t node = 0; node < list->capacity; ++node){
        fprintf(file, "   L%lu[shape=\"record\", label=\" %lu | {<lp%lu> %s | <ln%lu> %s} | {<lp%lu> %d | <ln%lu> %d}\"];\n", node, node, node, list->data[node].elem.key, node, list->data[node].elem.value, node, list->data[node].next, node, list->data[node].prev);
    }
    // printf("%d line\n", __LINE__);

    for(size_t node = 0; node < list->capacity - 1; ++node){
        fprintf(file, "L%lu->L%lu[color=\"black\", weight=1000, style=\"invis\"];\n", node, node+1);
    }
    // printf("%d line\n", __LINE__);

    for(size_t node = 0; node < list->capacity; ++node){
        fprintf(file, "L%lu->L%d[color=\"%s\", constraint=false];\n", node,list->data[node].next, ((list->data[node].prev == -1) ? Free_link_color : Next_link_color ));
        if(list->data[node].prev != -1){
            fprintf(file, "L%lu->L%d[color=\"%s\", constraint=false];\n", node, list->data[node].prev, Prev_link_color);
        }
    }
    // printf("%d line\n", __LINE__);

    fprintf(file, "F->L%d[color=\"%s\"];", list->free_tail, Free_link_color);

    // printf("%d line\n", __LINE__);

    fprintf(file, "}");
    fclose(file);
    // printf("%d line\n", __LINE__);

    char command[Max_cmd_len] = {};
    // printf("%d line\n", __LINE__);

    sprintf(command, "dot %sLIST_DUMP_%d.dot -T png -o %sLIST_DUMP_%d.png", Img_dump_dir, nDump, Img_dump_dir, nDump);
    // printf("%d line\n", __LINE__);

    system(command);
    // printf("%d line\n", __LINE__);

    return nDump++;
}



typedef struct hashFunction {
    uint64_t (*func)(char*);
    char* name;
} hashFunction;

#define HASHCODE(a) strHashCode((a))
#define NO_RE_HASH 0

static const float hashmap_max_load = 0.7f;
#if NO_RE_HASH == 0
    static const size_t hashmap_base_size = 1000;
#else
    static const size_t hashmap_base_size = 4289;
#endif

static const size_t hashmap_extent_coef = 2;



// static hashFunction allowed_functions[6] = {
//     {strHashCode, "strHashCode"},
//     {asciiHashCode, "asciiHashCode"},
//     {strlenHashCode, "strlenHashCode"},
//     {sumHashCode, "sumHashCode"},
//     {rollHashCode, "rollHashCode"},
//     {constOneHashCode, "constOneHashCode"},
// };


typedef struct Hashmap {
    LinkedList* lists;
    size_t size, capacity;
    size_t remap_size;
    uint64_t (*hashFunc)(char*);

} Hashmap;

Hashmap* HashmapCreate(uint64_t (*newFunc)(char*));

Hashmap* HashmapCreateCap(size_t capacity, uint64_t (*newFunc)(char*));

void Hashmap_raw_put(Hashmap **_map_, HKey key, HValue value);

void Hashmap_insert(Hashmap **_map_, HKey key, HValue value);

Hashmap* Hashmap_rehashUp(Hashmap **_map_, HKey key, HValue value);

HValue get(Hashmap *map, HKey key);


Entry* Hashmap_remove(Hashmap *map, HKey key);

void destroyHashmap(Hashmap **_map_);

Hashmap* HashmapCreate(uint64_t (*newFunc)(char*)) {
    Hashmap* map = (Hashmap*) malloc(sizeof(Hashmap));
    map->capacity = hashmap_base_size;
    map->size = 0;
    map->lists = (LinkedList*) calloc(map->capacity, sizeof(LinkedList));
    map->remap_size = map->capacity * hashmap_max_load;
    map->hashFunc = newFunc;
    return map;
}

Hashmap* HashmapCreateCap(size_t capacity, uint64_t (*newFunc)(char*)) {
    Hashmap* map = (Hashmap*) malloc(sizeof(Hashmap));
    map->capacity = capacity;
    map->size = 0;
    map->lists = (LinkedList*) calloc(map->capacity, sizeof(LinkedList));
    map->remap_size = map->capacity * hashmap_max_load;
    map->hashFunc = newFunc;
    return map;
}

void Hashmap_raw_put(Hashmap **_map_, HKey key, HValue value) {
    Hashmap *map = *_map_;
    unsigned long long hash = map->hashFunc(key);
    size_t index = (hash % map->capacity);
 

    if (map->size < map->remap_size || NO_RE_HASH) {

        if (map->lists[index].capacity == 0) {
            ctor_list(&map->lists[index]);
            push_back_list(&map->lists[index], key, value);
            // listCreateGraph(&map->lists[index]);
        } else {
            int entry_pos = find_item_list(&map->lists[index], key);
            
            if (entry_pos == 0) {
                push_back_list(&map->lists[index], key, value);
            } else {
                // printf("wtf");
                // printf("%s | %s\n", map->lists[index].data[entry_pos].elem.key, key);
                free(map->lists[index].data[entry_pos].elem.value);
                free(map->lists[index].data[entry_pos].elem.key);
                map->lists[index].data[entry_pos].elem.value = value;
                map->lists[index].data[entry_pos].elem.key = key;
            }
        }

    } else {
        *_map_ = Hashmap_rehashUp(_map_, key, value);
    }

    (*_map_)->size++;
}


void Hashmap_insert(Hashmap **_map_, HKey key, HValue value) {
    // allowed_functions[0];
    // Entry *e = (Entry*) malloc(sizeof(Entry));
    // assert(e);
    // // char* ptr = (char*)0x280000002a;
    // if (key == ptr || value == ptr) {
    //     exit(-1);
    // }
    // EntryCtor(e, key, value);
    HKey n_key  = (char*) malloc(strlen(key) + 1);
    HKey n_value  = (char*) malloc(strlen(value) + 1);
    // ptr->value = (char*) malloc(strlen(value) + 1);
    strcpy(n_key, key);
    strcpy(n_value, value);
    // if ((int64_t)(e->key) == 0xbf000000c1 ||(int64_t)(e->value) == 0xbf000000c1) {
    //     printf("wtf");
    //     exit(0);
    // }
    Hashmap_raw_put(_map_, n_key, n_value);
    // free(e);
}


Hashmap* Hashmap_rehashUp(Hashmap **_map_, HKey key, HValue value) {
    Hashmap *newMap = HashmapCreateCap((size_t)(*_map_)->capacity * hashmap_extent_coef, (*_map_)->hashFunc);
 
    size_t i, size;
    Hashmap *map = (*_map_);
 
    size = (*_map_)->capacity;
    for (i = 0; i < size; i++) {
        if (!map->lists[i].capacity) {
            // printf("%d lol\n", i);
            continue;
        }
        // if (i == 97) {
        //     // listCreateGraph(&map->lists[i]);
        //     printf("abcd");
        // }

        int cur_ind = map->lists[i].data[map->lists[i].head].next;

        while (cur_ind) {
            Hashmap_raw_put(&newMap, map->lists[i].data[cur_ind].elem.key, map->lists[i].data[cur_ind].elem.value);
            cur_ind =map->lists[i].data[cur_ind].next;
        }
        // dtor_list(&map->lists[i]);
        dtor_links_list(&map->lists[i]);
    }
    free(map->lists);
    free(*_map_);
    *_map_ = newMap;
    Hashmap_raw_put(&newMap, key, value);
    return newMap;
}

HValue get(Hashmap *map, HKey key) {
    unsigned long long hash = map->hashFunc(key);
    size_t index = (hash % map->capacity);

    HValue retVal = NULL;
    if (map->lists[index].capacity != 0) {
        int find_ind =  find_item_list(&map->lists[index], key);
        if (find_ind) {
            retVal = map->lists[index].data[find_ind].elem.value;
        }
        
    }

    return retVal;
}


Entry* Hashmap_remove(Hashmap *map, HKey key) {
    unsigned long long hash = map->hashFunc(key);
    size_t index = (hash % map->capacity);
    Entry *content = NULL;
 
    if (map->lists[index].capacity != 0) {
        int find_ind =  find_item_list(&map->lists[index], key);
        if (find_ind) {
            content = (Entry*) malloc(sizeof(Entry));
            content->key = map->lists[index].data[find_ind].elem.key;
            content->value = map->lists[index].data[find_ind].elem.value;
            erase_link_list(&map->lists[index], find_ind);
        }
    }

    map->size--;
    return content;
}


void destroyHashmap(Hashmap **_map_) {
    Hashmap *map = *_map_;
    size_t i, size;

    size = map->capacity;
     
    for (i = 0; i < size; i++) {
        dtor_list(&map->lists[i]);
    }
     
    free(map->lists);
    free(*_map_);
    *_map_ = NULL;
}

#define DEBUG
// #undef DEBUG
const size_t insert_num_target = 100000;
const size_t rand_str_len = 15;

int main() {
    
    Hashmap* map = HashmapCreate(strHashCode);

    size_t oper_cnt = 0;
    scanf("%lu", &oper_cnt);

    char buff[4097];
    char buff2[4097];
    
    for (size_t it = 0; it < oper_cnt; ++it) {
        scanf("%s %s", buff, buff2);

         if (strcmp(buff, "ADD") == 0) {
            // root = AVLTreePush(root, buff, buff2);
            scanf("%s", buff);
            HValue get_res = get(map, buff2);
            if (get_res != NULL) {
                printf("ERROR\n");
            } else {
                Hashmap_insert(&map, buff2, buff);
            }
        } else if (strcmp(buff, "DELETE") == 0) {
            HValue get_res = get(map, buff2);
            if (get_res == NULL) {
                printf("ERROR\n");
            } else {
                Hashmap_remove(map, buff2);
            }
        } else if (strcmp(buff, "UPDATE") == 0) {
            scanf("%s", buff);
            HValue get_res = get(map, buff2);
            if (get_res == NULL) {
                printf("ERROR\n");
            } else {
                Hashmap_insert(&map, buff2, buff);
            }
        } else if (strcmp(buff, "PRINT") == 0) {

            HValue get_res = get(map, buff2);
            if (get_res == NULL) {
                printf("ERROR\n");
            } else {
                printf("%s %s\n", buff2, get_res);
            }
        }


    }

    destroyHashmap(&map);


    return 0;
} 