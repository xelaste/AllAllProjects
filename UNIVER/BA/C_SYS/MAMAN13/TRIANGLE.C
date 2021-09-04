/*------------------------------------------------------------------------*/
/*                                TRIANGLE.C                              */
/*------------------------------------------------------------------------*/
/*This program reads input file into database if there is wrong data      */
/* (same names for different entities) it stops.After that if all right   */
/* printing list pair of triangles with common arcs and list triangles    */
/* without share apexes and begin online process till getting command     */
/* HALT.In on line mode program get point definition and name of existing */
/* Triangle and three news and will insert into database triangles created*/
/* by P and apexes of existing triangle and delete the existing triangle  */
/* from data base                                                         */
/* DATA BASE is based on hash table principle.There is a HashTab array    */
/* of pointers to stored figure and every of them is head of list figures */
/* Place in the table calculate function Hash from ID of entity           */
/* Every kind of Figure have his own hashtable (another line in           */
/*   2-dimensional hash table                                             */
#include <stdio.h>
#include <string.h>
#include <alloc.h>
#include "triangle.h" /* file of definitons */
#define  HASHSIZE  101
#define DELIMITER    ';'
#define TERMINATOR   "HALT" /*command for terminating program */
#define INPUTFILE    "TRIANGLE.INP"
#define OUTPUTFILE   "TRIANGLE.OUT"
#define NEW_ARC_NAME "AN"
Fptr hashtab[NumberOfTypes][HASHSIZE];/*table for storing etitirs*/
char *IMAGES[NumberOfTypes+2]={"POINT","ARC","TRIANGLE","END","OTHER"};
/*------------------------------------------------------------------*/
void Ucase(char *L)
/*function for transform any letter in input string to Uppercase */
/*char *L input string                                           */
{
int i;
for (i=0;L[i];i++)
	if ((L[i]>='a')&&(L[i]<='z')) L[i]+='A'-'a';
}
/*-----------------------------------------------------------------*/
char *itoa(int N)
/*transform integer N to string s */
{
char *s;
int i,L,n=1,sign;
if((sign=N)<0) N*=(-1);
for (L=0;N>=n;n*=10,L++);/*compute number of digits*/
if (sign<=0) L++;
s=malloc(L+1);
s[L]='\0';
for(i=L-1;i>=0;i--)
   {
   s[i]=N%10+'0';
   N/=10;
   }
if(sign<0) s[0]='-';
return s;
}
/*-----------------------------------------------------------------*/
void InitString(char *S,int l)
/* Function for deleting existng string to lenth l  */
/* S string,l - lenth of string for delete          */
{
int i;
for (i=0;i<l;S[i]=0,i++);
}
/*-------------------------------------------------------------------*/
void DeleteDelimiters(char *S)
/* Function for deleting DELIMITERS in the input string  */
/* S string                                              */
{
int i;
for (i=0;S[i]!=0;i++)
		S[i]=((S[i]==DELIMITER)?' ':S[i]);
}
/*---------------------------------------------------------------*/
char *IMAGE(kind k)
/* transform enum k to his string image */
{
return IMAGES[k];
}
/*-----------------------------------------------------------------*/
kind VALUE(char *S)
/* transform string S to his enum value */
{
kind k;
for (k=POINT;strcmp(S,IMAGES[k])!=0&&k<OTHER;k++);
return k;
}
/*--------------------------------------------------------------------*/
unsigned hash(char *s)
/*form hash value for string s */
{
unsigned long hashval;
for (hashval=0;*s!='\0';s++)
	  hashval=*s+7*hashval;
return hashval % HASHSIZE;
}
/*-----------------------------------------------------------------*/
/* lookup: look for s in hashtab */
Fptr lookup (char *s,kind k)
{
Fptr fp;
for (fp=hashtab[k][hash(s)];fp!=NULL;fp=fp->next)
	 if(strcmp(s,fp->Fid)==0) return fp;/*found */
return NULL;
}
/*-----------------------------------------------------------------*/
int insert(Fptr F)
/* insert figure F in hashtab */
{
unsigned hashval;
if (lookup(F->Fid,F->Fkind)==NULL)
	{
	hashval=hash(F->Fid);
	F->next=hashtab[F->Fkind][hashval];
	hashtab[F->Fkind][hashval]=F;
	return 1;
	}
	else
	{
	 printf("%s %s exists already !!!\n",IMAGE(F->Fkind),F->Fid);
	 return 0;
	}
}
/*-----------------------------------------------------------------*/
int ReadPoint (char *s)
/* read point data from input string s */
{
Fptr F;
int Num;
double x,y,z;
if((F=(Fptr) malloc(sizeof(struct Flist)))==NULL)
  {
  printf("Not enough memory\n");
  return 0;
  }
F->Fkind=POINT;
F->next=NULL;
F->mark=0;
Num=sscanf(s,"%s%lf%lf%lf",F->Fid,&x,&y,&z);
if
 (Num!=4)
	{
	printf("Invalid point parameters - point %s\n",F->Fid);
	free(F);
	return 0;
	}
F->Figure.P.X=x;F->Figure.P.Y=y;F->Figure.P.Z=z;
if (insert(F)) return 1;
	else
	{
	free(F);
	return 0;
	}
}
/*-------------------------------------------------------------------*/
int ReadArc   (char *s)
/* read new arc from input line s */
{
Fptr F;
int Num;
ID P1,P2;
if((F=(Fptr) malloc(sizeof(struct Flist)))==NULL)
  {
  printf("Not enough memory\n");
  return 0;
  }
F->Fkind=ARC;
F->next=NULL;
F->mark=0;
Num=sscanf(s,"%s%s%s",F->Fid,P1,P2);
if (Num!=3)
	{
	printf("Invalid arc parameters - arc %s\n",F->Fid);
	free(F);
	return 0;
	}
if(((F->Figure.A.P1=lookup(P1,POINT))!=NULL)&&
   ((F->Figure.A.P2=lookup(P2,POINT))!=NULL))
   if (insert(F)) return 1;
      else
      {
      free(F);
      return 0;
      }
   else
   {
   printf("Invalid Points in ARC parameters - ARC %s\n",F->Fid);
   free(F);
   return 0;
   }
}
/*------------------------------------------------------------------*/
int IsTriangle(Fptr F)
/* check if arcs of inputed triangle F create a triangle */
{
Fptr p11=F->Figure.T.A1->Figure.A.P1,/*first arc points*/
     p12=F->Figure.T.A1->Figure.A.P2,

     p21=F->Figure.T.A2->Figure.A.P1,/*second arc points*/
     p22=F->Figure.T.A2->Figure.A.P2,

     p31=F->Figure.T.A3->Figure.A.P1,/*third arc points*/
     p32=F->Figure.T.A3->Figure.A.P2;

if (p11==p21&&p12!=p22)
   if((p12==p31&&p22==p32)||(p12==p32&&p22==p31)) return 1;

if (p11==p22&&p12!=p21)
   if((p12==p31&&p21==p32)||(p12==p32&&p21==p31)) return 1;

if (p12==p22&&p11!=p21)
   if((p11==p31&&p21==p32)||(p11==p32&&p21==p31)) return 1;

if (p12==p21&&p11!=p22)
   if((p11==p31&&p22==p32)||(p11==p32&&p22==p31)) return 1;
printf("The Arcs do not create triangle - triangle %s\n",F->Fid);
return 0;
}
/*------------------------------------------------------------------*/
int ReadTriangle (char *s)
/*read new triangles from input string s */
{
Fptr F;
int Num;
ID A1,A2,A3;
if((F=(Fptr) malloc(sizeof(struct Flist)))==NULL)
  {
  printf("Not enough memory\n");
  return 0;
  }
F->Fkind=TRIANGLE;
F->next=NULL;
F->mark=0;
Num=sscanf(s,"%s%s%s%s",F->Fid,A1,A2,A3);
if (Num!=4)
	{
	printf("Invalid triangle parameters - triangle %s\n",F->Fid);
	free(F);
	return 0;
	}
if(((F->Figure.T.A1=lookup(A1,ARC))!=NULL)&&/*do all arcs exist?*/
  ((F->Figure.T.A2=lookup(A2,ARC))!=NULL)&&
  ((F->Figure.T.A3=lookup(A3,ARC))!=NULL))
  if (IsTriangle(F)&&insert(F)) return 1;
  else {
       free(F);
       return 0;
       }
else
  {
   printf("Invalid Arcs in triangle parameters - triangle %s\n",F->Fid);
   free(F);
   return 0;
  }
}
/*-----------------------------------------------------------------*/
int get_line (char *s,kind *k)
/* process of input line s and send it to match function depends on k*/
{
kind Line_Kind;
Ucase(s);
if ((Line_Kind=VALUE(s))==OTHER)
	{
	DeleteDelimiters(s);
	switch (*k)
		{
		case POINT   : return ReadPoint    (s);
		case ARC     : return ReadArc      (s);
		case TRIANGLE: return ReadTriangle (s);
		default      : break;
		}
	}
	else *k=Line_Kind;
return 1;
}
/*-----------------------------------------------------------------*/
int InputData (void)
/* read input file */
{
FILE *fin;
int i=0,OK=1;
kind k;
char ch,
	  line[80]; /*input line*/
InitString(line,80);
if ((fin=fopen(INPUTFILE,"rt"))==NULL)
  {
  printf("Can not open input file\n");
  return 0;
  }
while (((ch=getc(fin))!=EOF)&&OK)
 {
 if (ch=='\n')
	 {
	 line[i]='\0';
	 i=0;
	 OK=get_line(line,&k);
	 InitString(line,strlen(line));
	 printf("%s\n",line);
	 }
 else
	 {
	 line[i]=ch;
	 i++;
	 }
 }
fclose(fin);
return OK;
}
/*-----------------------------------------------------------------*/
int OutputData(void)
/*write database to output file */
{
FILE *fout;
Fptr F;
int i;
kind k;
if ((fout=fopen(OUTPUTFILE,"wt"))==NULL)
  {
  printf("Can not open output file\n");
  return 0;
  }
for(k=POINT;k<NumberOfTypes;k++)
 {
  fprintf(fout,"%s\n",IMAGE(k));
  for (i=0;i<HASHSIZE;i++)
  {
  for(F=hashtab[k][i];F!=NULL;F=F->next)
  switch (k)
      {
      case POINT   :fprintf(fout,"%-20s  %11lf ; %11lf ; %11lf ;\n",
		    F->Fid,F->Figure.P.X,F->Figure.P.Y,F->Figure.P.Z);
		    break;
      case ARC     :fprintf(fout,"%-20s  %-20s ; %-20s ;\n",
		    F->Fid,F->Figure.A.P1->Fid,F->Figure.A.P2->Fid);
		    break;
      case TRIANGLE:fprintf(fout,"%-20s  %-20s ; %-20s ; %-20s ;\n",
					   F->Fid,
					   F->Figure.T.A1->Fid,
					   F->Figure.T.A2->Fid,
					   F->Figure.T.A3->Fid);
		     break;
     default       :break;
     }
		  }
  fprintf(fout,"%s\n",IMAGE(END));
  }
fclose(fout);
return 1;
}
/*-----------------------------------------------------------------*/
void PrintTriangle(Fptr T)
/* print triangle T and his arcs */
{
printf(" %s %s %s %s ",T->Fid,T->Figure.T.A1->Fid,T->Figure.T.A2->Fid,
						  T->Figure.T.A3->Fid);
}
/*-----------------------------------------------------------------*/
int Find_Common_Arc(Fptr A,Fptr Arcs[3])
/* lookup for arc a in table of arcs Arcs */
{
int i;
for(i=0;i<3;i++)
   if (A==Arcs[i]) return 1;
return 0;
}
/*-----------------------------------------------------------------*/
void Find_Triangle_With_Common_Arc(Fptr T,int HashValue)
/* look for all triangles having common arcs with T and print them */
{
int i;
Fptr Tp=T->next,A[3];
A[0]=T->Figure.T.A1;
A[1]=T->Figure.T.A2;
A[2]=T->Figure.T.A3;
for(i=HashValue;i<HASHSIZE;i++)
   {
   if (i>HashValue) Tp=hashtab[TRIANGLE][i];
   while (Tp!=NULL)
	 {
	 if(Find_Common_Arc(Tp->Figure.T.A1,A)||
	    Find_Common_Arc(Tp->Figure.T.A2,A)||
	    Find_Common_Arc(Tp->Figure.T.A3,A))
	    {
	    PrintTriangle(T);
	    PrintTriangle(Tp);
	    printf("\n");
	    }
	  Tp=Tp->next;
	  }
   }
}
/*-----------------------------------------------------------------*/
void PrintCommonArcs(void)
/*print all pairs of triangles having common arcs */
{
int i;
printf("List triangles with common arcs\n");
for(i=0;i<HASHSIZE;i++)
   if (hashtab[TRIANGLE][i]!=NULL)
      Find_Triangle_With_Common_Arc(hashtab[TRIANGLE][i],i);
}
/*-----------------------------------------------------------------*/
void Apex2array(Fptr F,Fptr P[3])
/* put point-apexes of triangle F to array P*/
{
P[0]=F->Figure.T.A1->Figure.A.P1;
P[1]=F->Figure.T.A1->Figure.A.P2;
if(F->Figure.T.A2->Figure.A.P1!=F->Figure.T.A1->Figure.A.P1 &&
   F->Figure.T.A2->Figure.A.P1!=F->Figure.T.A1->Figure.A.P2)
   P[2]=F->Figure.T.A2->Figure.A.P1;
   else
   P[2]=F->Figure.T.A2->Figure.A.P2;
}
/*-----------------------------------------------------------------*/
void PrinTriangleApex(Fptr F)
/* print triangle F with his apexes */
{
Fptr P[3];
Apex2array(F,P);
printf(" %s %s %s %s \n",F->Fid,P[0]->Fid,P[1]->Fid,P[2]->Fid);
}
/*-----------------------------------------------------------------*/
int CheckApex(Fptr P,Fptr F)
/* check if triangle F have apex P */
{
if ((P==F->Figure.T.A1->Figure.A.P1)||(P==F->Figure.T.A1->Figure.A.P2)
   ||(P==F->Figure.T.A2->Figure.A.P1)||(P==F->Figure.T.A2->Figure.A.P2))
   return 1;
   else
   return 0;
}
/*-----------------------------------------------------------------*/
int ExistApex(Fptr F)
/* check if exist triangle sharing apex with triangle F */
{
int i,j;
Fptr P[4],Fp;
P[0]=F->Figure.T.A1->Figure.A.P1;
P[1]=F->Figure.T.A1->Figure.A.P2;
P[2]=F->Figure.T.A2->Figure.A.P1;
P[3]=F->Figure.T.A2->Figure.A.P2;
for(i=0;i<HASHSIZE;i++)
   {
   Fp=hashtab[TRIANGLE][i];
    while(Fp!=NULL)
	 {
	 if (Fp!=F)
	    for(j=0;j<=3;j++)
	       if(CheckApex(P[j],Fp))
		 {
		  Fp->mark=1;
		  F->mark =1;
		  return 1;
		 }
	 Fp=Fp->next;
	 }
   }
return 0;
}
/*-----------------------------------------------------------------*/
void PrintListAloneTriangle(void)
/*print all triangles do not share theirs apexes */
{
int i;
printf("List triangles do not share apexes\n");
for(i=0;i<HASHSIZE;i++)
   if (hashtab[TRIANGLE][i]!=NULL)
    if(!(hashtab[TRIANGLE][i]->mark))
       if(!(ExistApex(hashtab[TRIANGLE][i])))
	 PrinTriangleApex(hashtab[TRIANGLE][i]);
}
/*-----------------------------------------------------------------*/
Fptr addarc(Fptr P1,Fptr P2,ID Aid)
/* add new arc Aid from P1 to P2  to data base */
{
Fptr F;
F=(Fptr)malloc(sizeof(struct Flist));
strcpy(F->Fid,Aid);
F->Fkind=ARC;
F->next=NULL;
F->mark=0;
F->Figure.A.P1=P1;
F->Figure.A.P2=P2;
insert(F);
return F;
}
/*-----------------------------------------------------------------*/
Fptr base(Fptr P1,Fptr P2,Fptr T)
/* find arc of triangle T that points P1,P2 are his ends */
{
if((P1==T->Figure.T.A1->Figure.A.P1&&P2==T->Figure.T.A1->Figure.A.P2)||
   (P2==T->Figure.T.A1->Figure.A.P1&&P1==T->Figure.T.A1->Figure.A.P2))
   return T->Figure.T.A1;
if((P1==T->Figure.T.A2->Figure.A.P1&&P2==T->Figure.T.A2->Figure.A.P2)||
   (P2==T->Figure.T.A2->Figure.A.P1&&P1==T->Figure.T.A2->Figure.A.P2))
   return T->Figure.T.A2;
if((P1==T->Figure.T.A3->Figure.A.P1&&P2==T->Figure.T.A3->Figure.A.P2)||
   (P2==T->Figure.T.A3->Figure.A.P1&&P1==T->Figure.T.A3->Figure.A.P2))
   return T->Figure.T.A3;
return NULL;
}
/*-----------------------------------------------------------------*/
void addtriangle(Fptr A1,Fptr A2,Fptr A3,ID Tid)
{
Fptr T;
T=(Fptr)malloc(sizeof(struct Flist));
strcpy(T->Fid,Tid);
T->Fkind=TRIANGLE;
T->next=NULL;
T->mark=0;
T->Figure.T.A1=A1;
T->Figure.T.A2=A2;
T->Figure.T.A3=A3;
insert(T);
}
/*-----------------------------------------------------------------*/
void kill (Fptr F)
/* deleting item F from data base */
{
Fptr Fp;
Fp=hashtab[F->Fkind][hash(F->Fid)];
if (Fp==F) hashtab[F->Fkind][hash(F->Fid)]=NULL;/*F is ahead of list */
   else
   while (Fp->next!=NULL&&Fp->next!=F) Fp=Fp->next;
if(Fp->next==F) Fp->next=F->next; /* delete from the list */
free (F);     /* Free memory   */
}
/*-----------------------------------------------------------------*/
void AddNewTriangles (ID Pid,double x,double y,double z,Fptr T,
		      ID Tid1,ID Tid2,ID Tid3,int N)
/* add triangles created by point Pid and apexes of T , delete T */
{
Fptr P,A1,A2,A3,TP[3];
ID ArcId;
P=(Fptr)malloc(sizeof(struct Flist));
strcpy(P->Fid,Pid);
P->Fkind=POINT;
P->mark=0;
P->next=NULL;
P->Figure.P.X=x;
P->Figure.P.Y=y;
P->Figure.P.Z=z;
insert(P);
Apex2array(T,TP);
A1=addarc(P,TP[0],strcat(strcpy(ArcId,NEW_ARC_NAME),itoa(N*10+1)));
A2=addarc(P,TP[1],strcat(strcpy(ArcId,NEW_ARC_NAME),itoa(N*10+2)));
A3=addarc(P,TP[2],strcat(strcpy(ArcId,NEW_ARC_NAME),itoa(N*10+3)));
addtriangle(base(TP[0],TP[1],T),A1,A2,Tid1);
addtriangle(base(TP[0],TP[2],T),A1,A3,Tid2);
addtriangle(base(TP[1],TP[2],T),A2,A3,Tid3);
kill(T);
}
/*-----------------------------------------------------------------*/
void OnLineMode(void)
/* on line dialog with end use input new points    */
{
char line[80];
int i,N=0,count=0;
ID Pid,Tid,Tid1,Tid2,Tid3;
double x,y,z;
Fptr T;
while (strcmp(Pid,TERMINATOR)!=0)
    {
    InitString(Pid,Id_Length);
    InitString(Tid,Id_Length);
    InitString(Tid1,Id_Length);
    InitString(Tid2,Id_Length);
    InitString(Tid3,Id_Length);
    InitString(line,80);
    printf("\\>");
    for(i=0;(i<80&&(line[i]=getchar())!='\n');i++);
    N=sscanf(line,"%s %lf%lf%lf %s%s%s%s",Pid,&x,&y,&z,Tid,Tid1,Tid2,Tid3);
    Ucase(Pid);
    if (strcmp(Pid,TERMINATOR)!=0)/* not stop the program*/
    if (N<7)                      /* valid number of parameters */
       printf("Invalid numbers of parameters\n");
       else if (lookup(Pid,POINT)!=NULL)
	       printf("Point %s exists\n",Pid);
	       else if(((T=lookup(Tid,TRIANGLE))!=NULL)&&
		       (lookup(Tid1,TRIANGLE)==NULL)&&
		       (lookup(Tid2,TRIANGLE)==NULL)&&
		       (lookup(Tid3,TRIANGLE)==NULL))
		       AddNewTriangles (Pid,x,y,z,T,Tid1,Tid2,Tid3,++count);
		    else
		    printf("Triangle %s exists or exists one of %s %s %s \n",
			   Tid,Tid1,Tid2,Tid3);
    }
}
/*-----------------------------------------------------------------*/
void main ()
{
int i,j;
for (i=0;i<NumberOfTypes;i++)
    for(j=0;j<HASHSIZE;hashtab[i][j]=NULL,j++);
if (InputData())
   {
    PrintCommonArcs();
    PrintListAloneTriangle();
    OnLineMode();
    OutputData();
   }
}