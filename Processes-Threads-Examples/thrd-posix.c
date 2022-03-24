/**
 * A pthread program illustrating how to
 * create a simple thread and some of the pthread API
 * This program implements the summation function where
 * the summation operation is run as a separate thread.
 *
 * Most Unix/Linux/OS X users
 * gcc thrd.c -lpthread
 *
 * Solaris users must enter
 * gcc thrd.c -lpthreads
 *
 * Figure 4.9
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* this data is shared by the thread(s) */
int sum[3]; 
int n;
pthread_t tid[3]; /* the thread identifier */

void *runner(void *param); /* the thread */

int main(int argc, char *argv[])
{
	pthread_attr_t attr; /* set of attributes for the thread */

	if (argc != 2) {
		fprintf(stderr,"usage: a.out <integer value>\n");
		/*exit(1);*/
		return -1;
	}

	if (atoi(argv[1]) < 0) {
		fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
		/*exit(1);*/
		return -1;
	}

	n = atoi(argv[1]);

	/* get the default attributes */
	pthread_attr_init(&attr);

	/* create the thread */
	for(int i=0; i<3; i++){
	   pthread_create(&(tid[i]),&attr,runner,(void *)((long long)i));
	  
	}

	/* now wait for the thread to exit */
	for(int i=0; i<3; i++){
	   pthread_join(tid[i],NULL);
	}

	for(int i=0; i<3; i++){
	    printf("sum = %d\n",sum[i]);
	}
}

/**
 * The thread will begin control in this function
 */
void *runner(void *param) 
{
	int i = ((int)param);
	printf("%d param = %d\n", (int )tid[i], i);

	sum[i] = 0;

	for (int j = 1; j <= n; j++)
		sum[i] += j;


	pthread_exit(0);
}
