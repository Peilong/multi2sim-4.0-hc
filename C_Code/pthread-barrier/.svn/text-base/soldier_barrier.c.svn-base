#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
//#include <sync.h>
#include <sched.h>
#include <unistd.h>

pthread_barrier_t barrier;

void *soldier1(void *arg) {

	printf("Soldier1:::::::::: Adjusting angle \n");

	int i = 0;

	for (i = 0; i < 20; i++) {

		//delay(45);
	}
	printf("Soldier1:::::::::: angle ready!\n");
	pthread_barrier_wait(&barrier);
	printf("Soldier1:::::::::: Fire! \n");
}

void *soldier2(void *arg) {

	printf("Soldier2:::::::::: Adjusting direction \n");

	int i = 0;

	for (i = 0; i < 20; i++) {

		//delay(55);
	}
	printf("Soldier2:::::::::: direction ready!\n");
	pthread_barrier_wait(&barrier);
	printf("Soldier2::::::::::  Fire! \n");
}

void *soldier3(void *arg) {

	printf("Soldier3:::::::::: Filling bullet \n");

	int i = 0;

	for (i = 0; i < 20; i++) {

		//delay(76);
	}
	printf("Soldier3:::::::::: bullet ready!\n");
	pthread_barrier_wait(&barrier);
	printf("Soldier3::::::::::  Fire! \n");

}

int main(int argc, char *argv[]) 
{
	pthread_t threads[3];
	printf("Entering Barrier Test\n");

	printf("creating the barrier\n");
	pthread_barrier_init(&barrier, NULL, 3);

	printf("creating the threads\n");
	pthread_create(&threads[0], NULL, soldier1, NULL );
	pthread_create(&threads[1], NULL, soldier2, NULL );
	pthread_create(&threads[2], NULL, soldier3, NULL );

	int i = 0;

	for (i = 0; i < 10; i++) {

		printf("timer in main thread:%d\n", i);
		//delay(200);
	}
	
	pthread_join (threads[0],NULL);
	pthread_join (threads[1],NULL);
	pthread_join (threads[2],NULL);
	printf("end of main thread\n");
	pthread_barrier_destroy(&barrier);

	return 1;
}


