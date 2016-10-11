#include "forth.h"
#include "string.h"

char *dictionary[MAXDICT];

#define MAXWORDLEN 31

struct word {
    struct word *next;
    char length;  // 0x80 bit is set if immediate
    char name[MAXWORDLEN];
    cell code_field;
};

int match(struct word *p, char *adr, cell len)
{
    char *this_adr = p->name;

    if ((p->length & MAXWORDLEN) != len) {
	return 0;
    }
    while (len--) {
	if (*this_adr++ != *adr++) {
	    return 0;
	}
    }
    return 1;
}

struct word *last = NULL;

cell lastacf(void)
{
    return (cell)&last->code_field;
}

cell find(char *name_adr, cell name_len, cell *xt)
{
    struct word *p;
    for (p=last; p; p=p->next) {
	if (match(p, name_adr, name_len)) {
	    *xt = (cell)&p->code_field;
	    return (p->length & 0x80) ? 1 : -1;
	}
    }
    return 0;
}

void header(char *name_adr, cell name_len, cell word_type)
{
    name_len &= MAXWORDLEN;
    align();

    struct word *new_word = (struct word *)here;
    allot(sizeof(struct word));
    new_word->next = last;
    last = new_word;

    new_word->length = name_len;
    char *p = new_word->name;
    while(name_len--) {
	*p++ = *name_adr++;
    }

    new_word->code_field = word_type;
}

void cheader(char *name, void (*action_adr)(void))
{
    header(name, strlen(name), (cell)action_adr);
}


void immediate(void)
{
    last->length |= 0x80;
}
