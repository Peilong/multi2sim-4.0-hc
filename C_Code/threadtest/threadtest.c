#include <stdio.h>
#include <pthread.h>

void *childfn(void *ptr) 
{
	printf("child says hello\n");
	return NULL;
}


int main() 
{
	pthread_t child;
	pthread_create(&child, NULL, childfn, NULL);
	printf("parent says hello\n");
	pthread_join(child, NULL);
	return 0;
}

