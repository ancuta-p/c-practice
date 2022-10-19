#ifndef TH_HEADER_H_
#define TH_HEADER_H_

#include "list.h"
#include "utils.h"

void th_add_node(NODE **, const int);
void th_delete_node(NODE **, const int);
void th_print_list(const NODE *);
void th_sort_list(NODE **);

void mutex_lock(pthread_mutex_t *);
void mutex_unlock(pthread_mutex_t *);

#endif