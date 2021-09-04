/**************************************************************************/
#include "const.h"
#include "msg.h"
/*#include "struct.h"*/
/*----------------------------------------------------------------*/
void addlistentry(struct entry *pentry, int *listlen);
struct entry *code_exists(int code, struct entry *pentry, int listlen);
/*--------------------------------------------------------------*/
/*main()
{
struct entry *pentry = courses;
int *listlen = MAX_COURSES;
addlistentry(pentry, listlen);
printf("%s",  *pentry_current);
} */
/*--------------------------------------------------------------*/
void addlistentry(struct entry *pentry, int *listlen)
{
int Code,  was_esc;
struct entry *pentry_end, *pentry_current;

Code = acceptcode();
pentry_current = code_exists(Code, pentry, *listlen);
pentry_end = pentry + *listlen -1;

while(pentry_end != pentry_current)
	 {
	 *pentry_end = *(pentry_end - 1);
	  pentry_end--;
	 }
do
    was_esc = acceptlistentry(pentry_current);
while(was_esc!= NO_ESC);
(*listlen)++;
}
/*************************************************************************/