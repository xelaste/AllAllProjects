/*
** File:	user.c - source file for user defined C primitives for use
**		with LPA PROLOG Professional 1.5
** Version:	2.0
** Created:	Paul Parker, LPA, 02-Mar-1987
**
** Description:
**		User defined C primitives should be defined here.
**		All primitives must be declared by calling to def_cprim
**		from the function c_start_up. This function should be at the 
**		end of the file.
**
*/

#include	"cxface.h"	/* include C interface type definitions and 
		   		function declarations */

/*
** Insert any user required #include directives here.
*/

/*
** INSERT USER PRIMITIVES HERE.
**
** A primitive should have single argument which is an integer. 
** This value is the number of arguments with which the C 
** primitive has been called.
**
** A primitive should return a value of type BOOL, which is 
** either the value TRUE or the value FALSE.
*/


/*
**
** routine:	c_start_up - C function executed during the initialisation
**		of the PROLOG Kernel
** created:	Paul Parker, LPA, 02-Mar-1987
**
** The names of user defined primitives should be declared by a call to 
** the function def_cprim in this function:
**
** For example:
** 	def_cprim( "convert", cp_convert)
**
*/
c_start_up()
{
	/* put definitions here */
}

