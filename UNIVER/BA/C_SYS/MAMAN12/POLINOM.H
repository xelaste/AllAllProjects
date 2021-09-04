/*                        POLINOM.H                                       */
/*------------------------------------------------------------------------*/
#define MAX_DEGREE 15
typedef double POLINOM[MAX_DEGREE+1];
typedef enum {A,B,C,D,E,F} INDEX;
void init_polinoms(void);
int LEN (char *L);
void LEFT (char *str,int s);
int  read_pol  (char *Buffer,char Name);
void print_pol(char Name);
int Call_Operand(char P,char Q,char R,
	 int (*operand)(POLINOM P,POLINOM Q,POLINOM R));
int add_pol(POLINOM P,POLINOM Q,POLINOM R);
int  mul_pol(POLINOM P,POLINOM Q,POLINOM R);
int sub_pol(POLINOM P,POLINOM Q,POLINOM R);
int diff_pol(POLINOM P,POLINOM R,POLINOM DUMMY);
