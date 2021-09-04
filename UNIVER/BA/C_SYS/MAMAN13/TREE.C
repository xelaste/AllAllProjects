/*------------------------------------------------------------------------*/
/*                             TREE.C                                     */
/*------------------------------------------------------------------------*/
/*This programm get form standard input integer and string length of      */
/* equal to integer inputad before string,insert this string to a binary  */
/* tree and to list of string.When input is over programm will print      */
/*list of strings and after that print tree by inorder arrangment         */
/*------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <alloc.h>
typedef struct node /*type of tree node*/
{
char *item;
int len;
struct node *right;/*pointer to right subtree */
struct node *left; /*pointer to left subtree */
struct node *next; /*pointer to next node in the list */
};
typedef struct tree  /*type root of tree */
{
struct node *root;
struct node *last;/*pointer to last inserted item*/
int size ;
};
/*---------------------------------------------------*/
int insert (struct tree *the_tree,char *item,int len)
/*This function insert new string to the tree*/
/*the_tree - root of the tree                */
/*item new string                            */
/*len lenth of this string                   */
{
enum {LEFT,RIGHT,ROOT} branch=ROOT;/*pointer to direction*/
struct node *np,*prev;
np=the_tree->root;
while (np!=NULL)
	 {prev=np;
	 if (strcmp(item,np->item)>0)
		 {
		 np=np->right;
		 branch=RIGHT;
		 }
	 else
		 {
		 np=np->left;
		 branch=LEFT;
		 }
	 }
if ((np=(struct node *)malloc(sizeof(struct node)))!=NULL)
  {
   np->right=NULL;
   np->left=NULL;
   np->next=NULL;
   np->len=len;
   np->item=item;
   the_tree->size++;
   switch (branch)
	  {
	   case ROOT :the_tree->root=np;/*empty tree*/
		      the_tree->last=np;
		      break;
	   case LEFT :prev->left=np;
		      the_tree->last->next=np;
		      the_tree->last=np;
		      break;
	   case RIGHT:prev->right=np;
		      the_tree->last->next=np;
		      the_tree->last=np;
		      break;
		  } /*case */
  }
else return 0;/* memory problem */
return 1;
}
/*-----------------------------------------------------*/
void printtree (struct node *root)
{
/*function for print tree in inorder*/
/*root root of the subtree to be printed*/
 if (root!=NULL)
 {
  printtree(root->left);    /*print left subtree*/
  printf("%s\n",root->item);/*print root*/
  printtree(root->right);   /*print right subtree*/
 }
}
/*-----------------------------------------------------*/
void printlist(struct node *head)
/*Function for print list of strings in input order*/
/*head pointer to first string in the list         */
{
while (head!=NULL)
   {
   printf("%s\n",head->item);
   head=head->next;
   }
}
/*-----------------------------------------------------*/
void main ()
{
unsigned int len;
char *s,line[200];
struct tree my_tree={NULL,NULL,0};
printf("LEN  STRING\n");
while (scanf("%d%s",&len,&line)!=EOF)
      {
      s=(char *)malloc((len+1)*sizeof(char));
      sscanf(line,"%s",s);
      insert(&my_tree,s,len);
      }
printf("\nThe given list of strings\n");
printlist(my_tree.root);
printf("\nSorted list of strings\n");
printtree(my_tree.root);
}
/*-----------------------------------------------------------------------*/