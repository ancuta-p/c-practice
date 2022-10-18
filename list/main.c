#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "list.h"
#include "th_list.h"
#include "utils.h"

#define NUM_THREADS 3

typedef void *(*func_task)(void *);

int signal = 0;
pthread_mutex_t mutex_signal = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_signal = PTHREAD_COND_INITIALIZER;

// pthread_mutex_t mutex_list = PTHREAD_MUTEX_INITIALIZER;

static void wait_for_signal()
{
    int rc = 0;
    rc = pthread_mutex_lock(&mutex_signal);
    DIE(rc != 0, "pthread_mutex_lock");

    while (signal == 0)
    {
        rc = pthread_cond_wait(&cond_signal, &mutex_signal);
        DIE(rc != 0, "pthread_cond_wait");
    }

    rc = pthread_mutex_unlock(&mutex_signal);
    DIE(rc != 0, "pthread_mutex_unlock");
}

static void set_signal()
{
    int rc = 0;
    rc = pthread_mutex_lock(&mutex_signal);
    DIE(rc != 0, "pthread_mutex_lock");

    signal = 1;
    rc = pthread_cond_broadcast(&cond_signal);
    DIE(rc != 0, "pthread_cond_broadcast");
    
    rc = pthread_mutex_unlock(&mutex_signal);
    DIE(rc != 0, "pthread_mutex_unlock");
}

void *task_1(void *args)
{
    wait_for_signal();

    NODE **list = (NODE **)args;

    th_add_node(list, 2);
    th_add_node(list, 4);
    //sleep(0.5);
    th_add_node(list, 10);
    th_delete_node(list, 2);
    th_sort_list(list);
    th_delete_node(list, 10);
    th_delete_node(list, 5);

    return NULL;
}

void *task_2(void *args)
{
    wait_for_signal();

    NODE **list = (NODE **)args;

    th_add_node(list, 11);
    th_add_node(list, 1);
    th_delete_node(list, 11);
    th_add_node(list, 8);
    //sleep(0.5);
    th_print_list(list);

    return NULL;
}

void *task_3(void *args)
{
    NODE **list = (NODE **)args;

    th_add_node(list, 30);
    th_add_node(list, 25);
    th_add_node(list, 100);
    th_sort_list(list);
    th_print_list(list);
    //sleep(0.5);
    th_delete_node(list, 100);

    return NULL;
}

int main()
{
    LOG("program starting...\n");
    pthread_t thread[NUM_THREADS] = {0};
    func_task task[NUM_THREADS] = {task_1, task_2, task_3};
    NODE *list = NULL;
    int rc = 0;

    // create threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        rc = pthread_create(&thread[i], NULL, task[i], &list);
        DIE(rc == -1, "pthread_create");
    }

    // start exec threads
    LOG("finished threads creation\n");
    set_signal();

    // join threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(thread[i], NULL);
        DIE(rc == -1, "pthread_join");
    }

    LOG();
    print_list(list);
    flush_list(&list);
    LOG(FLUSH);

    return 0;
}
