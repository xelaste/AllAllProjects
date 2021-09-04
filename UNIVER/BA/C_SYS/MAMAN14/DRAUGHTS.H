/*--------------------------------------------------------------------------*/
/*                                DRAUGHTS.H                                */
/*--------------------------------------------------------------------------*/
#define  MAXINT        32000
#define  WIN           20000
#define  LOSS          -20000
#define  DEPTH         3
#define  MAXBDSIZE     8           /* maximum board size                   */
#define  MAXMOVES      40          /* maximum number of moves to consider  */
#define  MAXPLY        30          /* maximum depth of tree search         */
#define  WHITEMAN      1
#define  WHITEKING     2
#define  BLACKMAN      11
#define  BLACKKING     12
#define  CON(X,Y)      (X[Y.row][Y.col].Piece.Value)
#define  WHO(X,Y)      (X[Y.row][Y.col].Piece.Side)
#define  OPLAYER       ((player == white) ? black : white)
#define  WHAT(COLOR,PIECE) ((COLOR)*10 + PIECE)
#define IMAGE(OK,Piece,Color) IMAGE_LIST[Color][(OK)*(Piece+1)]
typedef enum {white,black,unknown} color;
typedef enum {empty,man,king} piecetype;
typedef enum {FALSE,TRUE} BOOL;
struct TRIP
{
int x1,y1,x2,y2;
};
typedef struct PIECE *PPiece;
struct POINT {
	     int col,row;
	     };
struct PIECE
	{
	 piecetype Value;
	 color     Side ;
	};
struct Square {int row,col;   /* Square on the board */
	     BOOL IsValid;
	     struct PIECE Piece;
	     };
struct MOVE
{
   struct POINT org, dest, capt;  /* origin, destination, capture squares*/
   piecetype Capture;             /* Has someone been captured?          */
   BOOL   Crown;                  /* the king is dead, long live the king*/
   int Value;                     /* value of this move */
};

struct BOARD
{
 int  SearchDepth;       /* user-selected depth of search       */
 int  IterFlag;          /* flag, TRUE for iterative deepening  */
 int  KillerFlag;        /* flag, TRUE for Killer move table    */
 int  BoardSize;         /* usually 8x8                         */
 color The_Winer;
 color Human,Computer;   /* which side are the players */
 int  Material[3];       /* value of each players material      */
 int  JumpAgain;         /* flag, TRUE if human must jump again */
 struct Square LastDest; /* destination square of humans last move*/
 int Man [3][3];         /* Array of Pieces */
 int SValue[MAXBDSIZE+1][MAXBDSIZE+1][3][3];   /* Square Values; */
 struct Square Board[MAXBDSIZE+2][MAXBDSIZE+2];/* What each square holds */
					       /* and its screen location */
 struct Square SavedBoard[MAXBDSIZE+2][MAXBDSIZE+2];/*Last position before*/
						    /*computers search began*/
 int NumBlackPieces; /* any black pieces left?  */
 int NumWhitePieces; /* any red pieces left?    */
};
/*--------------------------------------------------------------------*/
BOOL SaveToFile (struct BOARD B);
BOOL LoadFromFile(struct BOARD *B);
void NewGame (struct BOARD *B);
void showboard (struct Square Board[MAXBDSIZE+2][MAXBDSIZE+2]);
void ExChangeSide (struct BOARD *B);
BOOL ComputersTurn(struct BOARD *B);
BOOL UsersTurn(struct BOARD *B,struct POINT from,struct POINT to);
