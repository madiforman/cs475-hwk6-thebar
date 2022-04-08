/*
 * customer.h
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

void *customer(void *args);
void custTravelToBar(int custID);
void custArriveAtBar(int custID);
void custPlaceOrder(int custID);
void custBrowseArt(int custID);
void custAtRegister(int custID);
void custLeaveBar(int custID);

#endif /* CUSTOMER_H_ */
