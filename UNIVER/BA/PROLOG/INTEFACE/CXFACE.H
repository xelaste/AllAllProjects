/*
** File:	cxface.h - header file for C interface to 
**		PROLOG Professional 1.5
** Version:	1.5a
** Created:	Paul Parker, LPA, 18-Dec-1986
**
** Description:
**	Contains the type definitions associated with the C interface.
**	Also contains the external declarations of the functions 
**	provided by the C interface.
**
*/

typedef	char	BYTE;
typedef	BYTE	CELL[ 3];		/* a cell is 3 bytes long */
typedef	BYTE	far	*CELLPO;	/* points at a cell in the PROLOG heap */
typedef	char	BOOL;

typedef	double	real;		/* for compatability with sigma-PROLOG */

#define	TRUE	1
#define	FALSE	0


#define	OK	1		/* for compatability with sigma-PROLOG */
#define	FAIL	0		/* for compatability with sigma-PROLOG */

/* error codes used to raise LPA PROLOG Professional 3.0 errors */

#define	E_ARITHOV	0	/* Arithmetic Overflow		*/
#define	E_ARITHUF	1	/* Arithmetic Underflow		*/
#define	E_PRDNDEF	2	/* Predicate Not Defined	*/
#define	E_CTRLERR	3	/* Control Error		*/
#define	E_PRDNPRT	4	/* Predicate Name Protected	*/
#define	E_FILERR	5 	/* File Handling Error		*/
#define	E_TOOMANYFLS	6	/* Too Many Files Open		*/
#define	E_FILNOTFND	7	/* File Not Found		*/
#define	E_PATHNFND	8	/* Path Not Found		*/
#define	E_FILACCS	9	/* File Access Denied		*/
#define	E_DISKFULL	10	/* Disk or Directory Full	*/
#define	E_BREAK		11	/* Break			*/
#define	E_MODERR	12	/* Module Handling Error	*/
#define	E_GRAPHERR	13	/* Graphics Error		*/
#define	E_SYNERR	14	/* Syntax Error			*/
#define	E_EOFREAD	15	/* End Of File On Input		*/
#define	E_WINERR	16	/* Window Handling Error	*/
#define	E_DEVNSAME	17	/* Devices Not Same		*/
#define	E_NOMEM		18	/* Not Enough Memory		*/
#define	E_VARTAB	19	/* Variable Table Overflow	*/
#define	E_CONBUF	20	/* Console Buffer Overflow	*/
#define	E_NUMERR	21	/* Number Table Overflow	*/
#define	E_FNCERR	22	/* Function Not Defined		*/
#define	E_OPRERR	23	/* Operator Not Defined		*/
#define	E_ARITHERR	24	/* Arithmetic Error		*/
#define	E_FXDFRMERR	25	/* Fixed Format Error		*/
#define	E_CONTOOBIG	26	/* Constant Name Too Long	*/
#define	E_LOADERR	27	/* Object Format Error		*/
#define	E_BADSIG	28	/* Invalid File Signature	*/
#define	E_LABOVF	29	/* Label Table Overflow		*/
#define	E_EXROVF	30	/* External Table Overflow	*/
#define	E_CODOVF	31	/* Compiled Code Too Large	*/
#define	E_METAERR	32	/* Invalid Meta Variable	*/
#define	E_ISALLERR	33	/* ISALL Buffer Overflow	*/
#define	E_REGOVF	34	/* Too Many Arguments		*/
#define	E_BADCLS	35	/* Invalid Clause Structure	*/
#define	E_BADEMS	36	/* Expanded Memory System Error	*/
#define	E_ARRAY		37	/* Array Handling Error		*/
#define	E_NUMSPC	38	/* Not Enough Number Space	*/
#define	E_TXTSPC	39	/* Not Enough Text Space	*/

/*
**		define tags of different types of PROLOG cells
*/
#define	VARTAG	 0   	/* unbound variables */
#define	INTTAG	 4   	/* integer */
#define	REALTAG	 6   	/* real number */
#define	CONTAG	 8   	/* constant */
#define	NILTAG	10   	/* nil list */
#define	LISTTAG	12   	/* list  */
#define	TPLTAG	14   	/* n-tuple */

/*
**  define all external functions
*/

/*
**		term access functions
*/
extern	CELLPO	get_arg();
extern	BYTE	get_tag();


extern	int	get_int_val();
extern	double	get_real_val();

extern	char	*get_con_text();
extern	char	*get_con_len();

extern	CELLPO	get_list_head();
extern	CELLPO	get_list_tail();

extern	CELLPO	get_tpl_nth();
extern	int	get_tpl_len();

/*
** 	term construction functions
*/
extern	CELLPO	put_int_val();

extern	CELLPO	put_real_val();

extern	CELLPO	put_con_text();

extern	CELLPO	put_nil();
extern	CELLPO	put_list();

extern	CELLPO	put_tpl();

extern	CELLPO	put_copy_cell();

/*
** 	Error Handler
*/
extern	void	errtrap();

/*
**	C primitive definition function
*/
extern	int	def_cprim();


