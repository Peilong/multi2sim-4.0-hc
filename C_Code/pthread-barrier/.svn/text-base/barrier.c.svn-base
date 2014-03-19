/*
 * Example of POSIX barriers.
 * Link with `-lpthread'.
 * Based on test code from glibc.
 *
 * Copyright (C) 2010, Marek Polacek <mmpolacek@gmail.com>
 */

#include <err.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NTHREADS 20
#define ROUNDS 20

static pthread_barrier_t barriers[NTHREADS];
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static int counters[NTHREADS];
static int serial[NTHREADS];

static void *worker(void *arg)
{
	void *result = NULL;
	int nr = (long int)arg;
	int i;

	for (i = 0; i < ROUNDS; i++) {
		int j;
		int retval;

		if (!nr) {
			memset(counters, 0, sizeof(counters));
			memset(serial, 0, sizeof(serial));
		}

		retval = pthread_barrier_wait(&barriers[NTHREADS - 1]);
		if (retval != 0 && retval != PTHREAD_BARRIER_SERIAL_THREAD) {
			warnx("thread %d failed to wait for all the others",
			      nr);
			result = (void *)1;
		}

		for (j = nr; j < NTHREADS; j++) {
			/* Increment the counter for this round */
			pthread_mutex_lock(&lock);
			++counters[j];
			pthread_mutex_unlock(&lock);

			/* Wait for the rest */
			retval = pthread_barrier_wait(&barriers[j]);

			/* Test the result */
			if (!nr && counters[j] != j + 1) {
				warnx
				    ("barrier in round %d released but count is %d",
				     j, counters[j]);
				result = (void *)1;
			}

			if (retval) {
				if (retval != PTHREAD_BARRIER_SERIAL_THREAD) {
					warnx
					    ("thread %d in round %d has nonzero return value != PTHREAD_BARRIER_SERIAL_THREAD",
					     nr, j);
					result = (void *)1;
				} else {
					pthread_mutex_lock(&lock);
					++serial[j];
					pthread_mutex_unlock(&lock);
				}
			}

			/* Wait for the rest again */
			retval = pthread_barrier_wait(&barriers[j]);

			/* Now we can check whether exactly one thread was serializing */
			if (!nr && serial[j] != 1) {
				warnx
				    ("not exactly one serial thread in round %d",
				     j);
				result = (void *)1;
			}
		}
	}

	return result;
}

int main(void)
{
	pthread_t threads[NTHREADS];
	int i;
	void *res;
	int result = 0;

	/* Initialized the barrier variables */
	for (i = 0; i < NTHREADS; i++)
		if (pthread_barrier_init(&barriers[i], NULL, i + 1))
			errx(EXIT_FAILURE, "failed to initialize barrier %d",
			     i);

	/* Start the threads */
	for (i = 0; i < NTHREADS; i++)
		if (pthread_create
		    (&threads[i], NULL, worker, (void *)(long int)i))
			errx(EXIT_FAILURE, "failed to start thread %d", i);

	/* And wait for them */
	for (i = 0; i < NTHREADS; i++)
		if (pthread_join(threads[i], &res) || res != NULL) {
			warnx("thread %d returned a failure", i);
			result = 1;
		} else
			printf("joined threads %d\n", i);

	if (!result)
		puts("all OK");

	return result;
}
