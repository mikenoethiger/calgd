/* Author: Mike Nöthiger
 *
 * This is the interface definition of a max-heap.
 *
 * A max-heap is a priority queue, i.e. the queue
 * always delivers the element with the highest priority
 * in the queue.
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

/*
 * Data structure for a tree heap.
 * 
 * size: Represents the amount of heap elements present in the tree.
 * max_element: A pointer to the max element (based on its key) is maintained.
 * The max element represents the root of the tree.
 * last_element: A pointer to the last inserted element is maintained.
 * Once a heap element is inserted into the tree, its place will never 
 * be changed unless it is removed again.
 * The only possible change in the tree structure is to swap keys of 
 * two heap elements.
 */
typedef struct heap {
    size_t size;
    HeapElement *max_element;
    HeapElement *last_element;    
} Heap;

/*
 * Initializes the heap datastructure and its memory.
 * The heap is initialized with a size of 0.
 */
Heap *heap_create();

/*
 * Destroys the heap data strucuture and its memory.
 */
void heap_destroy(Heap *heap);

/* 
 * Get the max element of the heap (based on key). 
 * Does not change the heap. 
 * O(1)
 *
 * returns key of max element or 0 if the heap is empty.
 */
int heap_get_max(Heap *heap);

/*
 * Removes the max element of the heap (based on key).
 *
 * returns key of removed element or 0 if the heap is empty.
 */
int heap_remove_max(Heap *heap);

/*
 * Inserts a new element to the heap.
 *
 * returns the added HeapElement.
 */
const HeapElement *heap_insert(Heap *heap, int key);

/*
 * Updates the priority of a heap element which
 * might lead to a internal reorder of the elements.
 */
void heap_update_priority(Heap *heap, HeapElement *heap_element, int new_key);

void heap_print(Heap* heap);
