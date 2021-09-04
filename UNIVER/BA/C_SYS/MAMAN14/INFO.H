#include "draughts.h"
#define MoveLenth 20
#define Delimiter '-'
typedef enum {HALT,HELP,SHIFT,SAVE,LOAD,NEW,MOVE} COMMAND_VALUE;
COMMAND_VALUE UserInput(char **command_line);
void ShowHelp(void);
int StringToMove(char *mv,struct POINT p[]);