#ifndef HEADER_H_
#define HEADER_H_

#define ADD "added %d\n"
#define DELETE "deleted %d\n"
#define PRINT "printed list\n"
#define SORT "sorted list\n"
#define FLUSH "flushed list\n"

typedef struct _NODE
{
	struct _NODE *next;
	void (*callback_print)(const struct _NODE *self);
	int val;
} NODE;

void add_node(NODE **, const int);
int delete_node(NODE **, const int);
void print_list(const NODE *);
void sort_list(NODE **);
void flush_list(NODE **);

#endif
