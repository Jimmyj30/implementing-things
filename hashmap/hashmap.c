#include <stdio.h>
#include <string.h>

// ***** hashmap entry *****
struct Entry {
    int key;
    int value;
} typedef Entry;


// ***** linked list node *****
struct Node {
    Entry* entry;
    struct Node* next;
} typedef Node;


// ***** struct for hashmap *****
struct Hashmap {
    // 1-D array of pointers to "entry".
    Node** buckets;
    int size;
    int capacity;
} typedef Hashmap;


void print_LL(Node* node){
    Node* p_traverse = node;
    while (node != NULL){
        printf("%d:%d", p_traverse->entry->key, p_traverse->entry->value);
        p_traverse = p_traverse->next;
    }
}


void print_hashmap(Hashmap* hashmap){
    for(int i=0; i < hashmap->capacity; ++i){
        if (hashmap->buckets[i] != NULL){
            print("at bucket %d", i);
            print_LL(hashmap->buckets[i]);
        }
    }
}


int main(void) {
    printf("Hello, World!\n");
    return 0;
}
