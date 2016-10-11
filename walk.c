#include "forth.h"

cell *ip;

void unnest()
{
    ip = (cell *)rpop();
}

void walk(cell *new_ip)
{
    ip = new_ip;
    while(1) {
	cell *xt = (cell *)*ip++;
	cell token = *xt;
	switch (token) {
	case COLON:
	    rpush((cell)ip);
	    ip = xt+1;
	    break;
	case CONSTANT:
	case VARIABLE:
	    push(*(xt+1));
	    break;
	case FINISHED:
	    return;
	default:
	    ((void (*)(void))token)();
	    break;
	}
    }
}
