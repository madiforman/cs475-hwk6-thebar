/*
 * customer.c
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
#include "customer.h"

int random_time(int min, int max)
{
	return min + rand() % (max + 1 - min);
}

/**
 * This is what the thread will call.
 * Do not touch.
 */
int random_intc(int min, int max)
{
	int s = min + rand() % (max + 1 - min);
	return s;
}
void *customer(void *args)
{
	int custID = *(int *)args;
	custTravelToBar(custID);
	custArriveAtBar(custID);
	custPlaceOrder(custID);
	custBrowseArt(custID);
	custAtRegister(custID);
	custLeaveBar(custID);

	// printf("Cust %d\t\t\t\t\t\t\t\t\t\t\t|\n", custID);

	// int t = random_intc(3, 5);
	// sleep(t);

	// sem_post(&customer_outside);
	// sem_wait(&bar_full);
	// printf("\t\tCust %d\t\t\t\t\t\t\t\t\t|\n", custID);

	// sem_wait(&bartender_available);
	// sleep(1);
	// sem_post(&drink_ordered);
	// printf("\t\t\t\tCust %d\t\t\t\t\t\t\t|\n", custID);

	// int art = random_intc(0, 3);
	// sleep(art);
	// printf("\t\t\t\t\t\tCust %d\t\t\t\t\t|\n", custID);
	// // sleep(art);

	// sem_wait(&drink_made);
	// printf("\t\t\t\t\t\t\t\tCust %d\t\t\t|\n", custID);
	//  sleep(1);
	// sem_post(&c_paid);
	// printf("\t\t\t\t\t\t\t\t\t\tCust %d\t|\n", custID);
	//  sleep(1);
	return NULL;
}

/**
 * Each customer takes a random amount of time between 20 ms and 5000 ms to travel to the bar.
 */
void custTravelToBar(int custID)
{
	printf("Cust %d\t\t\t\t\t\t\t\t\t\t\t|\n", custID);

	int t = random_intc(0, 3);
	sleep(t);
	sem_post(&customer_outside);
}

/**
 * If there is already another customer in the bar the current customer has
 * to wait until bar is empty before entering.
 */
void custArriveAtBar(int custID)
{
	sem_wait(&bar_full);
	printf("\t\tCust %d\t\t\t\t\t\t\t\t\t|\n", custID);

	sem_wait(&bartender_available);
}

/**
 * The customer in the bar places an order
 */
void custPlaceOrder(int custID)
{
	sem_post(&drink_ordered);
	printf("\t\t\t\tCust %d\t\t\t\t\t\t\t|\n", custID);
}

/**
 * The customer in the bar can browse the wall art for a random amount of time between 3ms and 4000ms.
 */
void custBrowseArt(int custID)
{
	int art = random_intc(0, 3);
	printf("\t\t\t\t\t\tCust %d\t\t\t\t\t|\n", custID);
	sleep(art);
}

/**
 * If their drink is not ready by the time they are done admiring the art they must wait
 * until the bartender has finished. When the bartender is finished, the customer pays.
 *
 */
void custAtRegister(int custID)
{
	sem_wait(&drink_made);
	printf("\t\t\t\t\t\t\t\tCust %d\t\t\t|\n", custID);
}

/**
 * The customer in the bar leaves the bar.
 */
void custLeaveBar(int custID)
{
	sem_post(&c_paid);
	printf("\t\t\t\t\t\t\t\t\t\tCust %d\t|\n", custID);
}
