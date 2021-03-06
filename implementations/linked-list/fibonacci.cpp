/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
using namespace std;


/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;

   WholeNumber a;
   WholeNumber b;
   WholeNumber temp;
   a = 0;
   b = 1;
   temp = 0;

   for (int i = 1; i <= number; i++)
   {
	   if (i == 1)
	   {
		   cout << "\t1\n";
		   continue;
	   }
	   temp = a + b;
	   a = b;
	   b = temp;
	   cout << "\t" << b << "\n";
   }


   //prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;
   WholeNumber aa;
   WholeNumber bb;
   WholeNumber temptemp;
   aa = 0;
   bb = 1;
   temptemp = 0;

   for (int i = 1; i <= number; i++)
   {
	   if (i == 1)
	   {
		   continue;
	   }
	   temptemp = aa + bb;
	   aa = bb;
	   bb = temptemp;
   }
   cout << "\t" << bb << endl;
}


