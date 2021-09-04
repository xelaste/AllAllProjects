#include "const.h"
#include "msg.h"
/*----------------------------------------------------------------------*/
void  window (int x1, int x2, int y1, int y2, char *title, char *Line)
{
 frame(x1,y1,x2,y2);
 fprint_msg((x1 + DIF_COL), (y1 + DIF_LINE),  title, ATR);
 help_line(Line);
}
