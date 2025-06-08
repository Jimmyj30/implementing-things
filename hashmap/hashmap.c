#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ***** hashmap entry *****
struct Entry {
    int key;
    int value;
} typedef Entry;


// ***** linked list node *****
struct Node {
    Entry entry;
    struct Node* next;
} typedef Node;


// ***** struct for hashmap *****
struct Hashmap {
    // 1-D array of pointers to a LL. First element of the 
    // LL is a sentinel node. "actual" nodes come after.
    Node** buckets;
    int size; // number of keys in the map
    int capacity; // size of buckets array
} typedef Hashmap;


void print_LL(Node* node){
    Node* p_traverse = node->next;
    while (p_traverse != NULL){
        printf("%d:%d\n", p_traverse->entry.key, p_traverse->entry.value);
        p_traverse = p_traverse->next;
    }
}

void print_hashmap(Hashmap* hashmap){
    for(int i=0; i < hashmap->capacity; ++i){
        printf("at bucket %d\n", i);
        print_LL(hashmap->buckets[i]);
    }
    printf("---\n");
}

Entry new_entry(int key, int value){
    Entry result;
    result.key = key;
    result.value = value;
    return result;
}

const int INITIAL_CAPACITY = 5;
const float MAX_LOAD_FACTOR = 3;
void resize(Hashmap* hashmap);

void init_buckets(Node** buckets, int capacity){
    for (int i=0; i < capacity; ++i){
        Node* sentinel = malloc(sizeof(Node));
        sentinel->entry = new_entry(0, 0);
        sentinel->next = NULL;
        buckets[i] = sentinel;
    }
}

void init_hashmap(Hashmap* hashmap){
    hashmap->size = 0;
    hashmap->capacity = INITIAL_CAPACITY;
    hashmap->buckets = malloc(INITIAL_CAPACITY * sizeof(Node*));
    init_buckets(hashmap->buckets, hashmap->capacity);
}

void delete_buckets(Node** buckets, int capacity){
    for (int i=0; i < capacity; ++i) {
        // delete sentinel and all nodes after it
        Node* p_traverse = buckets[i];
        while (p_traverse != NULL){
            Node* next = p_traverse->next;
            free(p_traverse);
            p_traverse = next;
        }
    }
    free(buckets);
}

// insert or update key-value pair
void insert(Hashmap* hashmap, int key, int val){
    double load = (double) hashmap->size / hashmap->capacity;
    if (load > MAX_LOAD_FACTOR) {
        resize(hashmap);
    }

    int idx = key % hashmap->capacity;
    Node* list = hashmap->buckets[idx];
    Node* p_traverse = list;
    while (
        p_traverse->next != NULL &&
        p_traverse->next->entry.key != key
    ) {
        p_traverse = p_traverse->next;
    }

    if (p_traverse->next == NULL){
        Node* new_node = malloc(sizeof(Node));
        new_node->entry = new_entry(key, val);
        new_node->next = NULL;
        p_traverse->next = new_node;
        hashmap->size++;
        return;
    }

    // p_traverse->next->entry is the desired [k, v] pair
    p_traverse->next->entry.value = val;
}

// get value for key, return 0 on success
int get(Hashmap* hashmap, int key, int* val){
    int idx = key % hashmap->capacity;
    Node* list = hashmap->buckets[idx];
    Node* p_traverse = list;
    while (
        p_traverse->next != NULL && 
        p_traverse->next->entry.key != key
    ) {
        p_traverse = p_traverse->next;
    }

    // key not found in map
    if (p_traverse->next == NULL){
        return 1;
    }

    *val = p_traverse->next->entry.value;
    return 0;  
}

// double capacity and rehash all entries
void resize(Hashmap* hashmap){
    int old_capacity = hashmap->capacity;
    Node** old_buckets = hashmap->buckets;

    hashmap->capacity = hashmap->capacity * 2;
    hashmap->size = 0;
    hashmap->buckets = malloc(hashmap->capacity * sizeof(Node*));
    init_buckets(hashmap->buckets, hashmap->capacity);

    // re-hash old elements and add to resized hashtable buckets
    for (int i=0; i < old_capacity; ++i) {
        // go through all elements of linked list.
        Node* p_traverse = old_buckets[i]->next;
        while (p_traverse != NULL){
            int key = p_traverse->entry.key;
            int val = p_traverse->entry.value;
            insert(hashmap, key, val);
            p_traverse = p_traverse->next;
        }
    }

    delete_buckets(old_buckets, old_capacity);
}

int main(void) {
    Hashmap map;
    init_hashmap(&map);

    insert(&map, 1, 1);
    print_hashmap(&map);

    insert(&map, 1, 2);
    print_hashmap(&map);

    insert(&map, 50, 3);
    print_hashmap(&map);

    int value;
    if(get(&map, 30, &value) == 0){
        printf("FOUND! value: %d\n", value);
    }
    if(get(&map, 50, &value) == 0){
        printf("FOUND! value: %d\n", value);
    }

    insert(&map, 50, value+1);
    insert(&map, 51, value+2);
    print_hashmap(&map);
    if(get(&map, 50, &value) == 0){
        printf("FOUND! value: %d\n", value);
    }

    for(int i=0; i < 20; ++i){
        insert(&map, i, i);
    }
    print_hashmap(&map);

    if(get(&map, 10, &value) == 0){
        printf("FOUND! value: %d\n", value);
    }

    return 0;
}
