#define HOR_LINE		     0xCD
#define VER_LINE		     0xBA
#define TOP_LEFT_CORNER 	     0xC9
#define TOP_RIGHT_CORNER	     0xBB
#define DOWN_LEFT_CORNER	     0xC8
#define DOWN_RIGHT_CORNER	     0xBC
#define COLUMN_NUMBER		     80
#define FILLER_1		     42
#define FILLER_0		     32
#define MONOCHROME		     (0xb000)
#define BGN_SCR 		     (MK_FP(MONOCHROME,0))
#define END_SCR 		     (MK_FP(MONOCHROME,4000))
#define PLACE(X,Y)		     (2*((Y-1)*COLUMN_NUMBER+(X-1)))
#define ATR			     7
#define ATR_REVERSE		     112
#define LEFT_COL		     15
#define TOP_LINE		     10
#define VER_SIZE		     3
#define HOR_SIZE		     20
#define MSG_LINE		     11
#define HELP_LINE		     25
#define MSG_COL 		     17
#define MATRICE_0		     "зддддддбддддбддддбддддбддддбдддд©"
#define MATRICE_1		     "Ё DAY  Ё    Ё    Ё    Ё    Ё    Ё"
#define MATRICE_2		     "цдддддд╢SUN ЁMON ЁTUE ЁWED ЁTHU Ё"
#define MATRICE_3		     "ЁLESSONЁ    Ё    Ё    Ё    Ё    Ё"
#define MATRICE_4		     "цддддддеддддеддддеддддеддддедддд╢"
#define MATRICE_5		     "Ё  1   Ё    Ё    Ё    Ё    Ё    Ё"
#define MATRICE_6		     "цддддддеддддеддддеддддеддддедддд╢"
#define MATRICE_7		     "Ё  2   Ё    Ё    Ё    Ё    Ё    Ё"
#define MATRICE_8		     "цддддддеддддеддддеддддеддддедддд╢"
#define MATRICE_9		     "Ё  3   Ё    Ё    Ё    Ё    Ё    Ё"
#define MATRICE_10		     "цддддддеддддеддддеддддеддддедддд╢"
#define MATRICE_11		     "Ё  4   Ё    Ё    Ё    Ё    Ё    Ё"
#define MATRICE_12		     "юддддддаддддаддддаддддаддддадддды"
#define MATRICE_13		     '\0'
#define WIDE			     33
#define HEIGHT			     (2*TIME_UNITS+5)
#define START_HOR_STEP		     9
#define START_VER_STEP		     5
#define HOR_STEP		     5
#define VER_STEP		     2
#define MARKER			     'ш'
#define DELET			     83
#define PgUp			     73
#define PgDn			     81
#define RIGHT			     77
#define DOWN			     80
#define LEFT			     75
#define UP			     72
#define ENTER			     13
#define ESC			     27
#define LEFT_CORNER_COLUMN	     3
#define LEFT_CORNER_LINE	     1
#define RIGHT_CORNER_COLUMN	     68
#define RIGHT_CORNER_LINE	     11
#define LIST_LEFT_COL		     5
#define LIST_TOP_LINE		     4
#define LIST_RIGHT_COL		     70
#define LIST_BOTTOM_LINE	     14
#define MATRICE_START_COL	     5
#define MATRICE_START_LINE	     8
#define MATRICE_END_COL 	     MATRICE_START_COL + WIDE - 1
#define MATRICE_END_LINE	     MATRICE_START_LINE + HEIGHT - 1
#define START_COL		     MATRICE_START_COL+START_HOR_STEP
#define START_LINE		     MATRICE_START_LINE+START_VER_STEP
#define LAST_COL		     START_COL + (DAY_UNITS-1) * HOR_STEP
#define LAST_LINE		     START_LINE+(TIME_UNITS-1)*VER_STEP
#define COLUMN_INSIDE		     20
#define LINE_INSIDE		     5
#define DIF_COL 		     15
#define DIF_LINE		     1
#define SCR_BOT 		     25
#define   BACKSPACE		     8
#define   NUMERIC		     1
#define   COLOMN		     80
#define   YES_ESC		     1
#define   NO_ESC		     0
#define   MAX_COURSES		     10
#define   MAX_TEACHERS		     10
#define   MAX_GROUPS		     15
#define   NAME_LEN		     20
#define   MAX_UNITS		     12
#define   TIME_UNITS		     4
#define   DAY_UNITS		     5
#define   LIST_X1		     30
#define   LIST_X2		     77
#define   LIST_Y1		     6
#define   LIST_Y2		     23
#define   SIZE_OF_PAGE		     15
#define   INSERT		     82
#define   F1			     59
#define   CODE_LEN		     2
#define   NUN_NUMERIC		     0
#define   DIF_LINE_LIST              3
#define   LIST_LINE                  55
#define   DIF_COL_UNIT               10
#define   NUMBER_OF_ELEMENTS         4
#define   MAX_ROOM                   12
#define   END_UNIT                   {999,999,999,999}
#define   HIGH_VALUE                 999
