#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "utils.h"

#define RES_NOT_FOUND -1
#define RES_SUCCESS 0

static void print_node(const NODE *self)
{
    printf("%d ", self->val);
}

static NODE *init_node(const int val)
{
    NODE *node = NULL;
    node = (NODE *)malloc(sizeof(NODE));
    DIE(NULL == node, "malloc");

    node->next = NULL;
    node->callback_print = print_node;
    node->val = val;

    return node;
}

static int is_empty(const NODE *list)
{
    return NULL == list;
}

void add_node(NODE **list, const int val)
{
    NODE *node = init_node(val);

    // first element
    if (is_empty(*list))
    {
        *list = node;
        return;
    }

    NODE *it = *list;
    while (it->next != NULL)
        it = it->next;
    it->next = node;
}

int delete_node(NODE **list, const int val)
{
    if (is_empty(*list))
        return RES_NOT_FOUND;

    NODE *it = *list;
    NODE *prev = *list;

    // value on first position
    if ((*list)->val == val)
    {
        *list = (*list)->next;
        free(it);

        return RES_SUCCESS;
    }

    // search value
    while (it->next != NULL && it->val != val)
    {
        prev = it;
        it = it->next;
    }

    if (it->val != val)
        return RES_NOT_FOUND;

    // delete
    prev->next = it->next;
    free(it);
    it = NULL;

    return RES_SUCCESS;
}

void print_list(const NODE *list)
{
    if (is_empty(list))
    {
        printf("( )\n");
        return;
    }

    printf("( ");
    while (list != NULL)
    {
        list->callback_print(list);
        list = list->next;
    }
    printf(")\n");
}

void sort_list(NODE **list)
{
    if (is_empty(*list))
        return;

    NODE *it;
    NODE *next;

    for (it = *list; it->next != NULL; it = it->next)
    {
        for (next = it->next; next != NULL; next = next->next)
        {
            if (it->val > next->val)
            {
                // swap data
                int val = it->val;
                it->val = next->val;
                next->val = val;

                void (*callback)(const NODE *) = it->callback_print;
                it->callback_print = next->callback_print;
                next->callback_print = callback;
            }
        }
    }
}

void flush_list(NODE **list)
{
    NODE *node = *list;

    while (!is_empty(*list))
    {
        node = *list;
        *list = (*list)->next;
        free(node);
    }
}
