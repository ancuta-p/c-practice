#include <stdio.h>
#include "th_list.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void mutex_lock(pthread_mutex_t *mutex)
{
  int rc = 0;
  rc = pthread_mutex_lock(mutex);
  DIE(rc != 0, "pthread_mutex_lock");
}

void mutex_unlock(pthread_mutex_t *mutex)
{
  int rc = 0;
  rc = pthread_mutex_unlock(mutex);
  DIE(rc != 0, "pthread_mutex_unlock");
}

void th_add_node(NODE **list, const int val)
{
  mutex_lock(&mutex);
  add_node(list, val);
  LOG(ADD, val);
  mutex_unlock(&mutex);
}

void th_delete_node(NODE **list, const int val)
{
  mutex_lock(&mutex);
  delete_node(list, val);
  LOG(DELETE, val);
  mutex_unlock(&mutex);
}

void th_print_list(const NODE *list)
{
  mutex_lock(&mutex);
  LOG();
  print_list(list);
  LOG(PRINT);
  mutex_unlock(&mutex);
}

void th_sort_list(NODE **list)
{
  mutex_lock(&mutex);
  sort_list(list);
  LOG(SORT);
  mutex_unlock(&mutex);
}