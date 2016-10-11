#include "forth.h"
#include "stdio.h"
#include "stdlib.h"

static void plus(void)
{
    push(pop() + pop());
}
static void minus(void)
{
    cell n = pop();
    push(pop() - n);
}
static void times(void)
{
    push(pop() * pop());
}

static void divide(void)
{
    cell n = pop();
    push(pop() / n);
}

static void print(void)
{
    cell n = pop();
    printf(base == 10 ? "%d " : "%x ", n);
}

static void drop(void)
{
    (void)pop();
}

static void bye(void)
{
    exit(0);
}

cell unnester;

static void semicolon(void)
{
    compile(unnester);
    state = 0;
}

static void colon(void)
{
    char *p;
    cell len;
    len = parse_word(&p);
    if (len == 0) {
	ctype(": needs an argument\n");
	return;
    }
    if (len > 31) {
	type(p, len);
	ctype(" is too long\n");
	return;
    }
    header(p, len, COLON);
    state = 1;
}

static void doliteral(void)
{
    push(*ip++);
}

cell dolit;

void literal(cell n)
{
    compile(dolit);
    compile(n);
}

void init_dictionary(void)
{
    here = origin;
    cheader("exit", unnest);
    unnester = lastacf();
    cheader("(literal)", doliteral);
    dolit = lastacf();
    cheader(";", semicolon); immediate();
    cheader("+", plus);
    cheader("-", minus);
    cheader("*", times);
    cheader("/", divide);
    cheader(".", print);
    cheader("drop", drop);
    cheader("dup", dup);
    cheader("depth", depth);
    cheader("bye", bye);
    cheader(":", colon);
}
