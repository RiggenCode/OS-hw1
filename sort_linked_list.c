//
// Created by riggens on 2/12/26.
//
#include "sort_linked_list.h"


void print_list(elem_t *head) {

    elem_t *elem = head;

    while(elem != NULL) {

        printf("%d ", elem->value);

        elem = elem->next;

    }

    printf("\n");

}

void bubble_sort_copy_value(elem_t **head) {
    if (head == NULL || *head == NULL) return;

    int swapped;
    do {
        swapped = 0;
        elem_t* curr = *head;
        while (curr->next != NULL) {
            if (curr->value > curr->next->value) {
                int tmp = curr->value;
                curr->value = curr->next->value;
                curr->next->value = tmp;
                swapped = 1;
            }
            curr = curr->next;
        }
    } while (swapped);
    // implement me
}

void bubble_sort_copy_ref(elem_t **head) {
    if (head == NULL || *head == NULL) return;

    int swapped;
    do {
        swapped = 0;
        elem_t *curr = *head;
        while (curr && curr->next) {
            elem_t *a = curr;
            elem_t *b = curr->next;
            if (a->value > b->value) {
                elem_t *a_prev = a->prev;
                elem_t *b_next = b->next;

                if (a_prev) a_prev->next = b;
                else *head = b;
                b->prev = a->prev;

                b->next = a;
                a->prev = b;

                a->next = b_next;
                if (b_next) b_next->prev = a;
                swapped = 1;
            } else {
                curr = curr->next;
            }
        }
    } while (swapped);
    // implement me

}

elem_t *build_list(int num_elements) {

    srand(1234);

    elem_t *head = NULL;

    for (int i = 0; i < num_elements; i++) {

        elem_t *e = (elem_t *) malloc(sizeof(elem_t));

        e->value = random() % 100;

        e->next = NULL;

        e->prev = NULL;

        if (head == NULL) {

            head = e;

        } else {

            e->next = head;

            head->prev = e;

            head = e;

        }

    }

    return head;

}

int main() {

    elem_t *head = build_list(100);

    print_list(head);
    printf("==================================\n");

    bubble_sort_copy_value(&head);

    bubble_sort_copy_ref(&head);

    print_list(head);

}