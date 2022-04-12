/*
 * globals.h
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

int num_threads; // number of customer threads
int now_serving; // customer's ID who is being served

void random_sleep(int min, int max);
// TODO - declare some semaphores
sem_t *bar_full;
sem_t *customer_outside;
sem_t *bartender_available;
sem_t *drink_ordered;
sem_t *drink_made;
sem_t *c_paid;
// extern int finished;
#endif /* GLOBALS_H_ */
