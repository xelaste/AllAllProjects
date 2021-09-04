/*---------------------------------------------------------------------*/
/*                               TRIANGLE.H                            */
/*---------------------------------------------------------------------*/
#define Id_Length 20    /*lenth of figure ID */
#define NumberOfTypes 3
typedef enum {POINT,ARC,TRIANGLE,END,OTHER} kind;
/*------------------------------------------*/
typedef char ID[Id_Length] ;
typedef struct Flist *Fptr; /*Figure type and pointer to figure */
typedef struct Point
{
double X;
double Y;
double Z;
};
/*------------------------------------------*/
typedef struct Arc
{
Fptr P1;
Fptr P2;
};
/*------------------------------------------*/
typedef struct Triangle
{
Fptr A1;
Fptr A2;
Fptr A3;
};
/*------------------------------------------*/
typedef struct Flist /* table entry */
{
ID Fid;
kind Fkind;          /* kind of figure */
int mark;            /* help field     */
union
 {
 struct Point    P;
 struct Arc      A;
 struct Triangle T;
 } Figure;
Fptr next;          /* pointer to the next entry in chain */
};
/*---------------------------------------------------------------------*/