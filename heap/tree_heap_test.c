#include "../libs/ctest.h"
#include "tree_heap.c"

static int test_heap_create_empty() {
    Heap *heap = heap_create();
    assrt(heap != NULL);
    assrt(heap->size == 0);
    assrt(heap->max_element == NULL);
    assrt(heap->last_element == NULL);
    return 1;
}

static int test_heap_destroy_empty() {
    Heap *heap = heap_create();
    heap_destroy(heap);
    return 1;
}

static int test_heap_get_max_empty() {
    Heap *heap = heap_create();
    assrt(heap_get_max(heap) == 0);
    return 1;
}

static int test_heap_insert_empty() {
    int key = 3;
    Heap *heap = heap_create();
    const HeapElement *el = heap_insert(heap, key);
    assrt(el != NULL);
    assrt(el->parent == NULL);
    assrt(el->key == key);
    assrt(heap->max_element == el);
    assrt(heap->last_element == el);
    assrt(heap->size == 1);
    return 1;
}

static int test_heap_insert_sorted() {
    int key1 = 6;
    int key2 = 5;
    int key3 = 4;
    int key4 = 3;
    Heap *heap = heap_create();
    const HeapElement *e1 = heap_insert(heap, key1);
    const HeapElement *e2 = heap_insert(heap, key2);
    const HeapElement *e3 = heap_insert(heap, key3);
    const HeapElement *e4 = heap_insert(heap, key4);

    assrt(heap->size == 4);
    assrt(heap->max_element == e1);
    assrt(heap->max_element->left == e2);
    assrt(heap->max_element->right == e3);
    assrt(heap->max_element->left->left == e4);
    return 1;
}

static int test_heap_insert_unsorted() {
    int key1 = 3;
    int key2 = 4;
    int key3 = 5;
    int key4 = 6;
    Heap *heap = heap_create();
    const HeapElement *e1 = heap_insert(heap, key1);
    const HeapElement *e2 = heap_insert(heap, key2);
    const HeapElement *e3 = heap_insert(heap, key3);
    const HeapElement *e4 = heap_insert(heap, key4);

    assrt(heap->size == 4);
    assrt(heap->max_element->key == key4);
    assrt(heap->max_element->left->key == key3);
    assrt(heap->max_element->right->key == key2);
    assrt(heap->max_element->left->left->key == key1);
    return 1;
}

static int test_heap_remove_max_empty() {
    Heap *heap = heap_create();
    assrt(heap_remove_max(heap) == 0);
    return 1;
}

static int test_heap_order() {
    Heap *heap = heap_create();

    heap_insert(heap, 4);
    heap_insert(heap, 3);
    heap_insert(heap, 9);
    heap_insert(heap, 15);
    heap_insert(heap, 23);
    heap_insert(heap, 11);
    heap_insert(heap, 19);
    heap_insert(heap, 7);

    assrt(heap_remove_max(heap) == 23);
    assrt(heap_remove_max(heap) == 19);
    assrt(heap_remove_max(heap) == 15);
    assrt(heap_remove_max(heap) == 11);
    assrt(heap_remove_max(heap) == 9);
    assrt(heap_remove_max(heap) == 7);
    assrt(heap_remove_max(heap) == 4);
    assrt(heap_remove_max(heap) == 3);

    assrt(heap->size == 0);

    return 1;
}

static int playground_test() {
    return 1;
}

static void run_all_tests() {
    ctest_run(test_heap_create_empty);
    ctest_run(test_heap_destroy_empty);
    ctest_run(test_heap_get_max_empty);
    ctest_run(test_heap_insert_empty);
    ctest_run(test_heap_insert_sorted);
    ctest_run(test_heap_insert_unsorted);
    ctest_run(test_heap_remove_max_empty);
    ctest_run(test_heap_order);
}

int main(int argc, char **argv) {
    run_all_tests();
    //ctest_run(playground_test);
    ctest_print_result();
    return tests_failed;
}
