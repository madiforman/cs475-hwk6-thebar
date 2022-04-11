/*
 ============================================================================
 Name        : The Bar.C
 Author      : Madison Sanchez-Forman
 Version     : 4.11.22
 Description : Uses semaphores to synchranize threads in a "bartender" and
 "customer" scenario. Only one customer allowed in bar at a time.
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "customer.h"
#include "bartender.h"

void printBanner();
void init();
void cleanup();

int main(int argc, char **argv)
{
	if (argc != 2) /*if user didnt enter number of customers (threads)*/
	{
		printf("Usage: ./thebar <num threads>\n");
		return 0;
	}
	num_threads = atoi(argv[1]);
	int i = 0, t_id[num_threads]; /*holds numbers to repersent which customer is running*/
	srand(time(0));				  /*seed random at time 0 for different random numbers everytime program runs*/
	printBanner();
	init();		 /*initialize semaphores*/
	pthread_t b; /*bartender thread*/

	pthread_t *customers = (pthread_t *)malloc(num_threads * sizeof(pthread_t)); /*customer threads*/
	for (i = 0; i < num_threads; i++)
	{
		t_id[i] = i;
	}
	// TODO - fire off customer thread(s)
	for (i = 0; i < num_threads; i++)
	{
		pthread_create(&customers[i], NULL, customer, (void *)&t_id[i]);
	}
	// TODO - fire off bartender thread
	pthread_create(&b, NULL, bartender, NULL);

	// TODO - wait for all threads to finish
	for (i = 0; i < num_threads; i++)
	{
		pthread_join(customers[i], NULL);
	}

	pthread_join(b, NULL);

	cleanup(); /*cleanup and destroy semaphores*/
	return 0;
}

/**
 * Prints the activity banner.
 * Do not touch.
 */
void printBanner()
{
	printf("Customer:\t\t\t\t\t\t\t\t\t\t| Employee:\n");
	printf("Traveling\tArrived\t\tOrdering\tBrowsing\tAt Register\tLeaving");
	printf("\t| Waiting\tMixing Drinks\tAt Register\tPayment Recv\n");
	printf("----------------------------------------------------------------------------------------+");
	printf("-----------------------------------------------------------\n");
}

/**
 * Create and initialize semaphores
 */
void init()
{
	// TODO - unlink semaphores
	sem_unlink("/bar_full");
	sem_unlink("/customer_outside");
	sem_unlink("/bartender_available");
	sem_unlink("/drink_ordered");
	sem_unlink("/drink_made");
	sem_unlink("/c_paid");
	// // TODO - create semaphores
	sem_open("/bar_full", O_CREAT, 0600, 0);
	sem_open("/customer_outside", O_CREAT, 0600, 0);
	sem_open("/bartender_available", O_CREAT, 0600, 0);
	sem_open("/drink_ordered", O_CREAT, 0600, 0);
	sem_open("/drink_made", O_CREAT, 0600, 0);
	sem_open("/c_paid", O_CREAT, 0600, 0);
}

/**
 * Cleanup and destroy semaphores
 */
void cleanup()
{
	// TODO - close semaphores
	sem_close(&bar_full);
	sem_close(&customer_outside);
	sem_close(&bartender_available);
	sem_close(&drink_ordered);
	sem_close(&drink_made);
	sem_close(&c_paid);
	// TODO - delete semaphores
	sem_unlink("/bar_full");
	sem_unlink("/customer_outside");
	sem_unlink("/bartender_available");
	sem_unlink("/drink_ordered");
	sem_unlink("/drink_made");
	sem_unlink("/c_paid");
}
