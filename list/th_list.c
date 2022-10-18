#include <stdio.h>
#include "th_list.h"
#include "utils.h"

pthread_mutex_t mutex_list = PTHREAD_MUTEX_INITIALIZER;

void th_add_node(NODE **list, int val)
{
  int rc = 0;
  rc = pthread_mutex_lock(&mutex_list);
  DIE(rc != 0, "pthread_mutex_lock");

  add_node(list, val);
  LOG(ADD, val);

  rc = pthread_mutex_unlock(&mutex_list);
  DIE(rc != 0, "pthread_mutex_unlock");
}

void th_delete_node(NODE **list, int val)
{
  int rc = 0;
  rc = pthread_mutex_lock(&mutex_list);
  DIE(rc != 0, "pthread_mutex_lock");

  rc = delete_node(list, val);
  LOG(DELETE, val);

  rc = pthread_mutex_unlock(&mutex_list);
  DIE(rc != 0, "pthread_mutex_unlock");
}

void th_print_list(NODE **list)
{
  int rc = 0;
  rc = pthread_mutex_lock(&mutex_list);
  DIE(rc != 0, "pthread_mutex_lock");

  LOG();
  print_list(*list);
  LOG(PRINT);

  rc = pthread_mutex_unlock(&mutex_list);
  DIE(rc != 0, "pthread_mutex_unlock");
}

void th_sort_list(NODE **list)
{
  int rc = 0;
  rc = pthread_mutex_lock(&mutex_list);
  DIE(rc != 0, "pthread_mutex_lock");

  sort_list(list);
  LOG(SORT);
  
  rc = pthread_mutex_unlock(&mutex_list);
  DIE(rc != 0, "pthread_mutex_unlock");
}