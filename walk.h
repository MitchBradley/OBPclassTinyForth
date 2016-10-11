#define COLON -1
#define CONSTANT -2
#define VARIABLE -3
#define FINISHED -4

extern cell *ip;

void unnest(void);
void walk(cell *new_ip);
