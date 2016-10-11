#include "forth.h"

char origin[MAXDICT];

char *here;

void align()
{
    while ((cell)here & (sizeof(cell)-1)) {
	++here;
    }
}

void allot(cell nbytes)
{
    here += nbytes;
}

cell unused(void)
{
    return &origin[MAXDICT] - here;
}

void compile(cell xt)
{
    *(cell *)here = xt;
    here += sizeof(cell);
}
