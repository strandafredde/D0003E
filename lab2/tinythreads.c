#include <setjmp.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "tinythreads.h"
#include <stdio.h>

#define NULL            0
#define DISABLE()       cli()
#define ENABLE()        sei()
#define STACKSIZE       80
#define NTHREADS        4
#define SETSTACK(buf,a) *((unsigned int *)(buf)+8) = (unsigned int)(a) + STACKSIZE - 4; \
                        *((unsigned int *)(buf)+9) = (unsigned int)(a) + STACKSIZE - 4

struct thread_block {
    void (*function)(int);   // code to run
    int arg;                 // argument to the above
    thread next;             // for use in linked lists
    jmp_buf context;         // machine state
    char stack[STACKSIZE];   // execution stack space
};

struct thread_block threads[NTHREADS];

struct thread_block initp;

thread freeQ   = threads;
thread readyQ  = NULL;
thread current = &initp;

int initialized = 0;

static void initialize(void) {
    int i;
    for (i=0; i<NTHREADS-1; i++)
        threads[i].next = &threads[i+1];
    threads[NTHREADS-1].next = NULL;
	
	
	// Set the pull-up resistor for the joystick
	PORTB |= (1<<7);
	

	// Enable interrupts
	EIMSK |= (1<<PCIE1); // 7th bit enabled for PCIE1 (1<<7)
	PCMSK1 |= (1<<PCINT15); // 7th bit enabled for PCINT (1<<7)

	// 8Mh clock

	// Set OC1A to 1
	TCCR1A |= (1<<COM1A0) | (1<<COM1A1); 
	// Set the mode to CTC and prescaler to 1024
	TCCR1B |= (1<<WGM12) | (1<<CS10) | (1<<CS12); 
	//Activate "timer output"
	TIMSK1 |= (1<<OCIE1A); 
	
	
	OCR1A = 391; //8000000/1024 * 0.05 (391)
	
	// set timer to 0
	TCNT1 = 0;
    initialized = 1;
}

ISR(PCINT1_vect) { // Step 2
	// Check the status of PORTB bit 7 before calling yield()
	if (PORTB & (1<<7)) {
		yield();
	}
}

ISR(TIMER1_COMPA_vect) { // Step 2
	yield();
}
static void enqueue(thread p, thread *queue) {
    p->next = NULL;
    if (*queue == NULL) {
        *queue = p;
    } else {
        thread q = *queue;
        while (q->next)
            q = q->next;
        q->next = p;
    }
}

static thread dequeue(thread *queue) {
    thread p = *queue;
    if (*queue) {
        *queue = (*queue)->next;
    } else {
        // Empty queue, kernel panic!!!
        while (1) ;  // not much else to do...
    }
    return p;
}

static void dispatch(thread next) {
    if (setjmp(current->context) == 0) {
        current = next;
        longjmp(next->context,1);
    }
}

void spawn(void (* function)(int), int arg) {
    thread newp;

    DISABLE();
    if (!initialized) initialize();

    newp = dequeue(&freeQ);
    newp->function = function;
    newp->arg = arg;
    newp->next = NULL;
    if (setjmp(newp->context) == 1) {
        ENABLE();
        current->function(current->arg);
        DISABLE();
        enqueue(current, &freeQ);
        dispatch(dequeue(&readyQ));
    }
    SETSTACK(&newp->context, &newp->stack);

    enqueue(newp, &readyQ);
    ENABLE();
}

void yield(void) {
	
	DISABLE();
	enqueue(current,(&readyQ));
	dispatch(dequeue(&readyQ));
	ENABLE();
}

void lock(mutex *m) {
	DISABLE();
	if(m ->locked  == 0) {
		m ->locked  = 1;	
	}
	else {
		enqueue(current,&(m ->waitQ));
		dispatch(dequeue(&readyQ));
	}
	ENABLE();
}

void unlock(mutex *m) {
	DISABLE();
	if(m -> waitQ == NULL) {
		m ->locked  = 0;
	}
	else {
		enqueue(current, (&readyQ));
		dispatch(dequeue(&(m -> waitQ)));
	}
	
	ENABLE();
}
