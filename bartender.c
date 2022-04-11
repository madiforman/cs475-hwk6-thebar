/*
 * bartender.c
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "bartender.h"

/**
 * Code for bartender thread.
 * Do not touch.
 */
void *bartender(void *args)
{
	int i;
	for (i = 0; i < num_threads; i++)
	{
		waitForCustomer();
		makeDrink();
		receivePayment();
	}
	return NULL;
}
/**
 * @brief used in customer and bartender .c files to make threads sleep for random amount of time between min and max microseconds
 *
 * @param min minimum sleep time
 * @param max maximum sleep time
 */
void random_sleep(int min, int max)
{
	int i = min + rand() % (max + 1 - min);
	usleep(i);
}
/**
 * Waits in a closet until a customer enters.
 */
void waitForCustomer()
{
	sem_wait(&customer_outside);
	printf("\t\t\t\t\t\t\t\t\t\t\t| Bartender\n");
	// sleep(1);
	sem_post(&bar_full);

	sem_post(&bartender_available);
}

/**
 * When a customer places an order it takes the Bartender
 * a random amount of time between 5 ms and 1000 ms to make the drink.
 */
void makeDrink()
{
	sem_wait(&drink_ordered);
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\tBartender\n");
	random_sleep(5, 1000);
}

/**
 * Gets payment from the correct customer
 */
void receivePayment()
{
	sem_post(&drink_made);
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\tBartender\n");

	sem_wait(&c_paid);
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\t\t\tBartender\n");
}
