#include <stdlib.h>
#include "tree_heap.h"

/* 
 * Frees allocated memory of a HeapElement and all
 * its children. Does not go up in hierarchy.
 */
static void heap_element_destroy(HeapElement *el) {
    if (el->right) heap_element_destroy(el->right);
    if (el->left) heap_element_destroy(el->left);
    free(el);
}

static HeapElement *heap_element_create(int key) {
    HeapElement *el = malloc(sizeof(HeapElement));
    el->key = key;
    el->left = NULL;
    el->right = NULL;
    el->parent = NULL;
    return el;
}

/*
 * Returns a number (size_t), where the only bit set to 1
 * is the msb of input n. If n is (in binary representation):
 * 0000000000000000000000000000000000000000000000000000000010011100
 * then this function will return:
 * 0000000000000000000000000000000000000000000000000000000010000000
 */
static size_t get_msb(size_t n) {
    long n_bits = sizeof(size_t) * 8;
    size_t pivot = 1;
    pivot = pivot << (n_bits-1);
    size_t bit = 0;
    ssize_t i = n_bits-1;
    while (i >= 0 && bit != 1) {
        bit = (n & pivot) >> i;
        pivot = pivot >> 1;
        i--;
    }
    return (bit << (i+1));
}

static void print_bits(size_t n) {
    long n_bits = sizeof(size_t) * 8;
    size_t pivot = 1 << (n_bits-1);
    size_t bit;
    for (size_t i = 0; i < n_bits; i++) {
        bit = (n & pivot) >> (n_bits-1-i);
        printf("%zu", bit);
        pivot = pivot >> 1;
    }
    printf("\n");
}

/*
 * Returns parent of the nth element in the heap.
 * Since the heap is an almost binary tree, n iterates
 * from left to right, top to bottom on the heap.
 * The nth element must not exist, but the parent of the
 * nth element must.
 */
static HeapElement *heap_get_parent_of(Heap* heap, size_t nth_element) {
    size_t size = nth_element; 
    size_t pivot_bit = get_msb(nth_element);
    // skip msb
    pivot_bit = pivot_bit >> 1;
    HeapElement *pivot_element = heap->max_element;
    while (pivot_bit > 1) {
        if (pivot_bit & size) { 
            // bit is 1
            pivot_element = pivot_element->right;
        } else { 
            // bit is 0
            pivot_element = pivot_element->left;
        }
        pivot_bit = pivot_bit >> 1;
    }
    return pivot_element;
}

static void heap_element_swap(HeapElement *el1, HeapElement *el2) {
    int tmp = el1->key;
    el1->key = el2->key;
    el2->key = tmp;
}

/*
 * O(log n)
 * Moves a given HeapElement pivot up hierarchy until
 * the heap conditions are fulfilled again, which is:
 *  parent.key > parent.left.key AND parent.key > parent.right.key
 * The actual HeapElement is not move in heap tree, rather
 * its key will be swapped with the HeapElement at the corret
 * place.
 * returns a pointer to the correct HeapElement
 */
static const HeapElement *sift_up(HeapElement *heap_el) {
    int key = heap_el->key;
    HeapElement *target = heap_el;
    while (target->parent != NULL && key > target->parent->key) {
        heap_element_swap(target, target->parent);
        target = target->parent;
    }
    return target;
}

static int is_left_child_bigger(HeapElement *el) {
    return el->left != NULL && el->left->key > el->key;
}

static int is_right_child_bigger(HeapElement *el) {
    return el->right != NULL && el->right->key > el->key;
}

static int is_any_child_bigger(HeapElement *el) {
    return (is_right_child_bigger(el) || is_left_child_bigger(el)); 
}

/*
 * Returns bigger child of el (regarding its key)
 * or NULL if el has no children.
 */
static HeapElement *get_bigger_child(HeapElement *el) {
    if (el->left == NULL && el->right != NULL) return el->right;
    if (el->left != NULL && el->right == NULL) return el->left;
    if (el->left != NULL && el->right != NULL) return el->left->key >= el->right->key ? el->left : el->right;
    return NULL;
}

static const HeapElement *sift_down(HeapElement *heap_el) {
    int key = heap_el->key;
    HeapElement *pivot_element = heap_el;
    HeapElement *bigger_child = get_bigger_child(pivot_element);
    while (bigger_child != NULL && bigger_child->key > key) {
        heap_element_swap(pivot_element, bigger_child);
        pivot_element = bigger_child;
        bigger_child = get_bigger_child(pivot_element);
    }
    return pivot_element;
}

Heap *heap_create() {
    Heap *heap = malloc(sizeof(Heap));
    heap->max_element = NULL;
    heap->last_element = NULL;
    heap->size = 0;
    return heap;
}

void heap_destroy(Heap *heap) {
    if (heap->size != 0) {
        heap_element_destroy(heap->max_element);
    }
    free(heap);
}

int heap_get_max(Heap *heap) {
    if (heap->size == 0) return 0;
    return heap->max_element->key;
}

const HeapElement *heap_insert(Heap *heap, int key) {
    if (heap->size == 0) {
        HeapElement *el = heap_element_create(key);
        heap->max_element = el;
        heap->last_element = el;
        heap->size++;
        return el;
    }

    // 1. Increment heap->size
    // 2. Put element at next free place:
    //    Treat heap->size as a bitnumber b
    //    Let MSB(b) be the most significant bit of b
    //    Let LSB(b) be the least significatn bit of b
    //    pivot_element = heap->max_element 
    //    find the path starting at pivot_element:
    //    for MSB-1 to LSB+1
    //      if (bit = 0) turn left 
    //      if (bit = 1) turn right
    //    if (LSB = 0) insert el at pivot_element->left
    //    if (LSB = 1) insert el at pivot_element->right
    // 3. Call sift_up(el)
    
    HeapElement *el = heap_element_create(key);
    heap->last_element = el;
    heap->size++;
    size_t size = heap->size;
    size_t pivot_bit = get_msb(heap->size);
    // skip msb
    pivot_bit = pivot_bit >> 1;
    HeapElement *pivot_element = heap_get_parent_of(heap, size);
    if (1 & size) {
        pivot_element->right = el;
    } else {
        pivot_element->left = el;
    }
    el->parent = pivot_element;
    const HeapElement *output = sift_up(el);

    return el;
}

int heap_remove_max(Heap *heap) {
    if (heap->size == 0) return 0; 
    if (heap->size == 1) {
        int key = heap->max_element->key;
        heap->size--;
        heap_element_destroy(heap->max_element);
        heap->max_element = NULL;
        heap->last_element = NULL;
        return key;
    }

    int max = heap->max_element->key;
    heap_element_swap(heap->max_element, heap->last_element);

    // remove last_element from tree and free memory space
    if (heap->last_element->parent->left == heap->last_element) {
        heap->last_element->parent->left = NULL;
    } else {
        heap->last_element->parent->right = NULL;
    }
    heap_element_destroy(heap->last_element);
    heap->size--;

    // update last_element
    HeapElement *new_parent = heap_get_parent_of(heap, heap->size);
    if (1 & heap->size) {
        // LSB(size) = 1
        heap->last_element = new_parent->right;
    } else {
        // LSB(size) = 0
        heap->last_element = new_parent->left;
    }

    // place the current (possibly wrong) root to its right place
    sift_down(heap->max_element);

    return max;
}

static void print_n(char *c, int n) {
    for (int i = 0; i < n; i++) printf("%s", c);
}

static void heap_element_print(HeapElement *el, int level) {
    if (level != 0) printf("\n");
    print_n("-", level*3);
    printf("%d", el->key);
    if (el->left) {
        heap_element_print(el->left, level+1);
        if (el->right) {
            heap_element_print(el->right, level+1);
        }
    }
}

void heap_print(Heap* heap) {
    heap_element_print(heap->max_element, 0);
    printf("\n");
}
