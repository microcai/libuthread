/*
 * uthread.c
 *
 *  Created on: 2010-11-12
 *      Author: cai
 */

#include <ucontext.h>
#include <uthread.h>
#include <malloc.h>

typedef struct thread_context{
	ucontext_t	self;
	unsigned long stack[0]; //to make it align
}thread_context,*pthread_context;

struct thread_list{
	struct thread_list * next;
	pthread_context		thread;
};


static thread_context	first_one;

struct thread_list	head = {.next = NULL, .thread = & first_one};

// yes , point to current thread
static uthread_t 	current = (uthread_t) & first_one ;

// yes, if some thread exit , put it here ,
// the next thread will clean it for you
static pthread_context	clean_up;

static pthread_context	threads[100]; // max 100 thread allowed currently

static uthread_t uthread_sched_find_next();
static void uthread_startup(pthread_context tc,__uthread_func fn, void * param);
static void thread_list_append(pthread_context tc);
static pthread_context thread_list_removehead();
static void thread_list_remove(pthread_context ct);

/**
 * Get self? ... maybe a little bit hard, but ... not hard any way
 */
uthread_t uthread_self()
{
	return current;
}

uthread_t uthread_create(__uthread_func fn, size_t stack_size,void * param)
{
	pthread_context tc = malloc(sizeof(thread_context)+stack_size);

	getcontext(&tc->self);

	tc->self.uc_stack.ss_size = stack_size;
	tc->self.uc_stack.ss_sp = tc->stack;

	makecontext(&tc->self,(void (*) (void))uthread_startup,3,tc,fn,param);

	//append to tail
	thread_list_append(tc);

	return (uthread_t)tc;
}

/**
 * find uthid from global data struct, then switch to it
 */
void uthread_switchto(uthread_t uthid)
{
	uthread_t cur;
	cur = uthread_self();

	//起码你可以 return back了，呵呵
	((pthread_context)uthid)->self.uc_link = & ((pthread_context)cur)->self;

	current = uthid;
	swapcontext(&((pthread_context)cur)->self,&((pthread_context)uthid)->self);
	current = cur;

	if(clean_up)
	{
		//从列表中移走
		thread_list_remove(clean_up);
		free(clean_up);
		clean_up = NULL;
	}
}

/**
 * in fact , all schedule happens here
 */
void uthread_yield()
{
	uthread_t next;

	//to find the next runing thread, and do swapcontext
	next = uthread_sched_find_next();
	if(next) //有下一个线程才切换，否则直接返回
		uthread_switchto(next);
}

/**
 * This is the actual schedule function
 */
static uthread_t uthread_sched_find_next()
{
	pthread_context next;

	next = thread_list_removehead();
	if(next)
	{
		thread_list_append((pthread_context)current);
	}
		return (uthread_t)next;
}

/**
 * This is the real startup function
 */
static void uthread_startup(pthread_context tc,__uthread_func fn, void * param)
{
	//call user function
	fn(param);

	clean_up = tc;
}

static void thread_list_append(pthread_context tc)
{
	struct thread_list * p = &head;
	while(p->next)
	{
		p = p->next;
	}

	p->next = malloc(sizeof(struct thread_list));
	p = p->next;
	p->next = NULL;
	p->thread = tc;
}

static pthread_context thread_list_removehead()
{
	struct thread_list*	p;
	pthread_context head_tc;

	if(head.next)
	{
		head_tc = head.thread;

		head.thread = head.next->thread;

		p = head.next;

		head.next = p->next;

		free(p);
		return head_tc;
	}else
	{
		return NULL;
	}
}

static void thread_list_remove(pthread_context ct)
{
	struct thread_list * pp,* p = &head;
	if(ct==head.thread)
	{
		thread_list_removehead();
		return ;
	}
	while(p->next)
	{
		if(p->next->thread == ct)
		{
			pp = p->next;
			p->next = p->next->next;
			free(pp);
			return ;
		}
		p = p->next;
	}
}
