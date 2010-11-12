/*
 * main.c
 *
 *  Created on: 2010-11-12
 *      Author: cai
 */
#include <stdio.h>
#include <uthread.h>

void uthread_func(void * param)
{
	printf("thread %p is running\n",(void*)uthread_self());
}

int main()
{
	printf("create thread %p\n",(void*)uthread_create(uthread_func,16384,0));
	printf("create thread %p\n",(void*)uthread_create(uthread_func,16384,0));
	printf("create thread %p\n",(void*)uthread_create(uthread_func,16384,0));
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
	uthread_yield();
}
