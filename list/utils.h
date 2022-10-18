#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* useful macro for handling error codes */
#define DIE(assertion, call_description)  \
	do                                    \
	{                                     \
		if (assertion)                    \
		{                                 \
			fprintf(stderr, "(%s, %d): ", \
					__FILE__, __LINE__);  \
			perror(call_description);     \
			exit(EXIT_FAILURE);           \
		}                                 \
	} while (0)

#define LOG(fmt, ...) printf("[%lu] " fmt, pthread_self(), ##__VA_ARGS__)

#endif