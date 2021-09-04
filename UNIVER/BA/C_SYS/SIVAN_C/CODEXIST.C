 /*************************************************************************/
#include "const.h"
#include "msg.h"
/*#include "struct.h"*/
/*-------------------------------------------*/
struct entry *code_exists(int Code, struct entry *pentry, int listlen);
void help_line(char *str);
int acceptcode(void);
/*-------------------------------------------*/
struct entry *code_exists(int Code, struct entry *pentry, int listlen)
{
int i=0;
char *str = NO_RECORD;

while(i <= listlen)
	{
	if(pentry -> code == Code)
		return(pentry);
	else
		{
		pentry++;
		i++;
		}
	}
if(i > listlen)
	{
	help_line(str);
	return(0);
	}
}
/**********************************************************************/