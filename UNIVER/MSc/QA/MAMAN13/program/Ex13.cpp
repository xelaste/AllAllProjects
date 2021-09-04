#include <stdio.h> 

void procedure_1 (int x, int y);
void procedure_2();
void procedure_3(int param);
void procedure_4(int n);
void procedure_5();
void procedure_6(int n);

void put_into_queue(int element);
int get_from_queue();
int empty_queue();
int queue_length = 0;

main()
{
     int num ;
     char key ;
   
     scanf("%d", &num);

     if (num < 10) 
           procedure_1 (num, queue_length);
     else
           procedure_2 ();
     
     if (num  > 100)
           procedure_3 (queue_length);
     else 
           procedure_4 (num);

     scanf("%c", &key);
     switch (key)
         {
          case 'P':
              put_into_queue(num);
              queue_length++ ;
              break;
          case 'G':
              if ( !empty_queue() )
                 {
                 num = get_from_queue();
                 queue_length-- ;
                 }
              break;
           default:
              break;
         }
}
 
void procedure_1 (int x, int y)
{
     printf ("in p1\n");
     if (x > 100)
         {
         procedure_3(x);
         return;
         }
     if (x == y)
         procedure_4(2*x);
     procedure_5();
     printf ("out p1\n");
}


void procedure_2()
{
    printf ("in p2\n");
    /* some actions here; no further function calls */
    printf ("out p2\n");
}

void procedure_3(int param)
{
     printf ("in p3\n");
     param-- ;
     procedure_5 ();
     printf ("out p3\n");
}

void procedure_4(int n)
{
    printf ("in p4\n");
    if (empty_queue())
        procedure_4 (n+1);
    else
        procedure_6(n-1);
    if (n == 10)
        procedure_2();
   printf ("out p4\n");        
}


void procedure_5()
{
     printf ("in p5\n");
    /* some actions here; no further function calls */
     printf ("out p5\n");
}


void procedure_6(int n)
{
    printf ("in p6\n");
    if (n == 0)
       printf ("DONE\n");
   else 
       procedure_4 (n/2);
  printf ("out p6\n");       
}


 
void put_into_queue (int element)
{
/* Adds element at the queue's tail.
    Queue is a global variable */
      printf ("in piq\n");
      printf ("out piq\n");
}


int get_from_queue()
{int top_element;

/* Removes the first element from the queue and assigns it to top_element. 
    Queue is a global variable */
      printf ("in gfq\n");
      printf ("out gfq\n");

return top_element;

}


int empty_queue ()
{
      printf ("in eq\n");


if (queue_length == 0)
{
   printf ("out eq\n");
   return 1;
}
else {
   printf ("out eq\n");  
   return 0;
}
}
