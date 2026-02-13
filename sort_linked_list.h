//
// Created by riggens on 2/12/26.
//

#ifndef HW1_SORT_LINKED_LIST_H
#define HW1_SORT_LINKED_LIST_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct elem {

    int value;

    struct elem *next;

    struct elem *prev;

} elem_t;

void print_list(elem_t *head);
void bubble_sort_copy_value(elem_t **head);
void bubble_sort_copy_ref(elem_t **head);
elem_t *build_list(int num_elements);
#endif //HW1_SORT_LINKED_LIST_H