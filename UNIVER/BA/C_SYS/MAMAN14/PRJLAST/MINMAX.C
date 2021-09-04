/*********/
/* DAMKA */             /* functions, dealing with minmax tree */
/*********/

#include "main.h"

void buildtree(pointer ptr, char depth)
/* recursively builds min-max tree of depth DEPTH_MIN_MAX */

{
    pointer p;

    if(depth < DEPTH_MIN_MAX-1)
       {
	p=ptr->son=generate(ptr->b->board,depth+1); /* generate next level */
	if(depth>1) free(ptr->b);  /* kill the board after */
	while(p!=NULL)
	   {
	   if(p->val!=50 && p->val!=-50) buildtree(p, depth+1);                   /* build minimax subtree */
	   p=p->next;
	   }
	}
}
/*******************************************************************/
pointer bestbranch(void)
/* finds the best move and realizes it. returns 1 if stale-mate situation
   occures, i.e. if all figures of computer have been blocked */
/* This version of the procedure is not recursive and searching depth has
   been bounded by four levels. */

{
    pointer best,           /* best move of the 1st level */
	    l1, l2, l3, l4, /* auxiliary variables for levels */
	    max, min, m;    /* hold maximum of 3rd and minimum of 4th levels */

    best=l1=head->son;
    if (l1==0)
       {
	stalemate=1;
	return head;        /* Empty tree? Stale mate situation. */
	}

    while(l1!=0)                /* 2nd level */
	 {
	 min=l2=l1->son;
	 while(l2!=0)           /* 3rd level */
	      {
	      max=l3=l2->son;
	      while(l3!=0)      /* 4th level */
		   {
		   m=l4=l3->son;
		   while(l4!=0) /* 5th level */
			{
			l4=l4->next;
			if (l4 && (l4->val < m->val)) m=l4;
			}
		   if(m) l3->val+=m->val;
		   if(!m && DEPTH_MIN_MAX>4) l3->val=50; /* terminal node */
		   l3=l3->next;
		   if (l3 && (l3->val > max->val)) max=l3;
		   }
	      if(max) l2->val+=max->val;
	      if(max->val==50) l2->val=50;
	      if(!max && DEPTH_MIN_MAX>3) l2->val=-50;  /* terminal node */
	      l2=l2->next;
	      if (l2 && (l2->val < min->val)) min=l2;
	      }
	 if(min) l1->val+=min->val;
	 if(min->val==-50) l1->val=-50;
	 if(!min && DEPTH_MIN_MAX>2) l1->val=50;        /* terminal node */
	 l1=l1->next;
	 if (l1 && (l1->val > best->val)) best=l1;
	 }
    fprintf(filep,"Computer's move is : %c%d-%c%d\n",best->b->move[0]+96,best->b->move[1],best->b->move[2]+96,best->b->move[3]);
    copy(best->b->board,head->b->board);                /* board modifying */
    return head;
}
/*******************************************************************/
pointer addnode(pointer first, boardt brd, char level)
/* node creating and adding to the chain of some level of minimax tree */

{
   pointer ptr=(pointer)malloc(sizeof(Tnode));      /* new node creating */
   if(level < DEPTH_MIN_MAX-1)
      {
      ptr->b=(Bblock*)malloc(sizeof(Bblock));       /* board block creating */
      copy(brd, ptr->b->board);
      }

   ptr->son=NULL;
   ptr->val=0;
   ptr->next=first;                         /* ptr is the first from now */
   first=ptr;
   return first;
}
/*******************************************************************/
pointer killtree(pointer head)
/* kills minimax tree - releases memory */
/* this vertion deals only with a tree of depth 4 - not the optional case */

{
    pointer l1=head->son, l2, l3, l4,        /* auxiliary var's */
	    aux1, aux2, aux3, aux4;

    while(l1!=NULL)
	 {                                   /* 2nd level */
	 l2=l1->son;
	 while(l2!=NULL)
	      {                              /* 3rd level */
	      l3=l2->son;
	      while(l3!=NULL)
		   {                         /* 4th level */
		   l4=l3->son;
		   while(l4!=NULL)
			{
			aux4=l4->next;       /* 5th level */
			free(l4);
			l4=aux4;
			}
		   aux3=l3->next;
		   free(l3);
		   l3=aux3;
		   }
	      aux2=l2->next;
	      free(l2);
	      l2=aux2;
	      }
	 aux1=l1->next;
	 free(l1->b);
	 free(l1);
	 l1=aux1;
	 }
    return head;
}
