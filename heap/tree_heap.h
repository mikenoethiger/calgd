

/* 
 * A max-heap is a priority queue, which means it's a queue
 * that always returns the element with the highest priority.
 *
 * Max-Heap conditions:
 * 1. Its structure is an almost complete binary tree
 * 2. For all heap_elements h:
 *      h->key >= h->left->key  AND
 *      h->key >= h->right->key
 */

typedef struct heap_element {
    int key;
    struct heap_element *parent;
    struct heap_element *left;
    struct heap_element *right;
} HeapElement;

typedef struct heap {
    size_t size;
    HeapElement *max_element;
    HeapElement *last_element;    
} Heap;

Heap *heap_create();
void heap_destroy(Heap *heap);

/* 
 * Get the max element of the heap (based on key), 
 * without removing the element.
 * O(1)
 *
 * returns max element or 0 if the heap is empty.
 */
int heap_get_max(Heap *heap);

/*
 * Get and remove the max element of the heap (based on key).
 *
 * returns max element or 0 if the heap is empty.
 */
int heap_remove_max(Heap *heap);

/*
 * Insert a new element to the heap.
 *
 * returns the added HeapElement.
 */
const HeapElement *heap_insert(Heap *heap, int key);

void heap_update_priority(Heap *heap, HeapElement *heap_element, int new_key);

void heap_print(Heap* heap);
