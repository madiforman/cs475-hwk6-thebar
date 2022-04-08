/*
 * TheBar.c
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
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
	printBanner();
	/// init(); // initialize semaphores
	pthread_t b;
	// pthread_t c;
	num_threads = atoi(argv[1]);
	// sem_open("/wait_outside", O_CREAT, 0600, 0);
	//  sem_open("/mutex", O_CREAT, 0600, 1);
	sem_open("/bar_full", O_CREAT, 0600, 0);
	sem_open("/customer_outside", O_CREAT, 0600, 0);
	sem_open("/bartender_available", O_CREAT, 0600, 0);
	sem_open("/drink_ordered", O_CREAT, 0600, 0);
	sem_open("/drink_made", O_CREAT, 0600, 0);
	sem_open("/c_paid", O_CREAT, 0600, 0);

	int i = 0;

	int t_id[num_threads];

	pthread_create(&b, NULL, bartender, NULL);
	pthread_t *customers = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
	// printf("here\n");
	for (i = 0; i < num_threads; i++)
	{
		t_id[i] = i;
	}
	for (i = 0; i < num_threads; i++)
	{
		pthread_create(&customers[i], NULL, customer, (void *)&t_id[i]);
	}

	for (i = 0; i < num_threads; i++)
	{
		pthread_join(customers[i], NULL);
	}

	pthread_join(b, NULL);

	sem_unlink("/wait_outside");
	sem_unlink("/bartender_awake");
	sem_unlink("/drink_made");
	sem_unlink("/c_paid");

	sem_close(&drink_made);
	sem_close(&c_paid);
	// TODO - fire off customer thread

	// TODO - fire off bartender thread

	// TODO - wait for all threads to finish

	// cleanup(); // cleanup and destroy semaphores
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
	// sem_unlink("/customer_traveling");
	// sem_unlink("/customer_arrived");
	// sem_unlink("/bar_open");
	// sem_unlink("/drink_ordered");
	// sem_unlink("/drink_made");
	// sem_unlink("/customer_paid");
	// sem_unlink("/payment_confirmed");
	// sem_unlink("/customer_left");
	// // TODO - create semaphores
	// // customer_traveling = sem_open("/customer_traveling", O_CREAT, 0600, 0);
	// customer_arrived = sem_open("/customer_arrived", O_CREAT, 0600, 0);
	// bar_open = sem_open("/bar_open", O_CREAT, 0600, 0);
	// drink_ordered = sem_open("/drink_ordered", O_CREAT, 0600, 0);
	// drink_made = sem_open("/drink_made", O_CREAT, 0600, 0);
	// customer_paid = sem_open("/customer_paid", O_CREAT, 0600, 0);
	// payment_confirmed = sem_open("/payment_confirmed", O_CREAT, 0600, 0);
	// customer_left = sem_open("/customer_left", O_CREAT, 0600, 0);
}

/**
 * Cleanup and destroy semaphores
 */
void cleanup()
{
	// TODO - close semaphores
	// sem_close(customer_traveling);
	// sem_close(customer_arrived);
	// sem_close(bar_open);
	// sem_close(drink_ordered);
	// sem_close(drink_made);
	// sem_close(customer_paid);
	// sem_close(payment_confirmed);
	// sem_close(customer_left);
	// // TODO - delete semaphores
	// //	sem_unlink("/customer_traveling");
	// sem_unlink("/customer_arrived");
	// sem_unlink("/bar_open");
	// sem_unlink("/drink_ordered");
	// sem_unlink("/drink_made");
	// sem_unlink("/customer_paid");
	// sem_unlink("/payment_confirmed");
	// sem_unlink("/customer_left");
}
