1 (Welcome to LPA PROLOG Professional)
This demonstration shows some of the
things that can be done using the
programming language LPA PROLOG
Professional.

Throughout the demo, windows like this
will tell you things. When you want to
move on, just press any key. One special
key, ESCAPE, always returns to the main
options menu that you will see in a
moment.@

2 (What is "PROLOG?")
PROLOG is a very high level programming
language, first implemented 20 years
ago, and now used worldwide, throughout
the field of Artificial Intelligence.

The name stands for PROgramming in
LOGic, which is what PROLOG is all
about. We use logic every day. Facts and
rules fill instruction books, legal
documents, or text books. PROLOG allows
you to computerise such logic.@

3 (What is LPA PROLOG "Professional?")
LPA PROLOG Professional is a fully
fledged version of the PROLOG language,
greatly extended to make good use of
desktop computers such as the IBM PC and
its compatibles.

Features like formatted I/O, a powerful
window manager, random access files,
full DOS command and directory handling,
and much more, make it live up to its
name as the Professional's PROLOG.@

4 ("PROLOG's" Edinburgh Syntax)
Although there are several different
PROLOG dialects, one in particular has
emerged as a world-wide standard. Called
"Edinburgh Syntax", it was developed for
the early PROLOG compiler written in
Edinburgh for the DEC10 computer.

Naturally, PROLOG Professional 3.8 is a
fully fledged Edinburgh Syntax system,
closely emulating Quintus PROLOG, the
leading PROLOG compiler for UNIX.@

5 (LPA PROLOG Professional "3.8")
This is a demonstration of LPA's
advanced version of what is probably the
most powerful computer language ever
conceived. The examples in this demo can
only hint at the full capabilities of
PROLOG Professional.

Remember, though, that this demo is
written 100% in LPA PROLOG Professional.
So you are not just seeing, but also
using this remarkable product!@

1000 (End of Demonstration)
You have chosen to finish with this demo
and return to DOS. If you don't want to
exit from the demo, then press ESCAPE
right now!

You can always run this demo again if
you want to, by typing the DOS command
DEMO1; also try other demos, 2 3 & 4.

Thank you for your interest and
attention!@

101 (The Window Management System)
A highlight of LPA PROLOG Professional
is its built-in window manager. This is
a fast, compact screen handler which
enables all input and output to be
routed through user-definable windows.

Each window is like an individual, named
screen. In fact, this text is displayed
in just such a window.@

102 (Colours and Video Attributes)
If your computer has a colour screen,
then you can set up windows with their
own colour combinations.

Even with monochrome monitors, you can
use bold, reverse and underscore video
(that last one works only on true IBM
mono screens; if it did not work, then
you're lucky: you probably have access
to 64 grey scale combinations instead!).
@

103 (Unlimited Numbers of Windows)
(Well almost!) Your programs can create
up to 255 windows, subject to memory
limitations. Their size, position and
colour attributes are all programmable.

Windows can overlap each other, stacking
up on the screen just like paper on a
desk. When an application tries to write
to a window, it is brought to the top of
the stack, again just like a piece of
paper.@

104 (Moving Windows Around)
Once created, windows can be recoloured,
hidden and moved around the screen
quickly and easily. These facilities
allow displayed data to be highlighted,
rearranged, or just placed out of the
way for a moment.

They also allow the screen to be tidied
up automatically, as seems to be
necessary here!@

105 (Virtual Terminal Support)
The window system defines a simple
"virtual terminal" which allows the
screen to be manipulated either though
the output of control characters or by
using the special window primitives.

An important advantage of using the LPA
virtual terminal is that screen-handling
code written on one type of machine will
usually run on others, even if the
machines themselves are not compatible.@

106 (Uses of Windows)
Windows can be used for tabulating
output, printing debugging messages,
status reports, or for showing one part
of a program while another is being
worked on.

The window manager takes the pain out of
user interface programming, and enables
systems with highly polished front ends
to be developed in a very short time.@

107 (The Window Manager)
This part of the demonstration has shown
some of the features of the built-in
windows in LPA PROLOG Professional. As
you have seen, they are very fast,
colourful, and have many uses.

The window manager is entirely contained
within PROLOG, so you do not need other
special software to use them. It is easy
to make your own applications look truly
professional!@

201 (Input and Output Facilities)
The input/output (I/O) subsystem of a
programming language is one of its most
important components. Without good I/O,
it is not possible to convert even the
cleverest of computational algorithms
into a useful software program.

LPA PROLOG Professional supports I/O in
all key areas, with screen windows,
serial and random files, formatted I/O,
printer and comms support.@

202 (Screen and Window Handling)
The first I/O interface seen by the user
is the screen/keyboard terminal. Most
people judge the friendliness and
professionalism of a piece of software
by its screen handling.

Menus, flashcards, forms, and much more,
are possible thanks to Professional's
window system. For a full demo of window
system, choose option 1 from the main
options menu.@

203 (Disk Files and Data Processing)
While screen I/O is the most apparent,
up-front component of a piece of
software, the handling of disk files is
equally important. These are of course
necessary to store programs and data,
but LPA PROLOG does not stop there.

Random access files, formatted records
and other features enable traditional
data processing to be combined with
PROLOG's intelligent logic.@

204 (Device Directed Input and Output)
It is often desirable for software to
control peripherals and hardware, for
example when printing out the contents
of a database, or reading keys typed at
the keyboard directly.

All of LPA PROLOG Professional's I/O
primitives can be used in conjunction
with a set of special files, or
channels, that give access to parallel,
serial and raw keyboard ports.@

205 (String and Term Conversions)
A special, and very powerful feature
uses PROLOG's string type as the I/O
device. Characters are "written" into a
standard PROLOG string so that list
processing can be performed on the very
text of PROLOG terms; likewise, the
resulting "text" can be "read" back in.

Two types of string are supported in
this way; choose option 5 from the main
options menu for further information.@

206 (Serial and Random Access Files)
Up to 8 disk files can be simultaneously
open for read/write access. Files are
treated as serial character devices, but
can also be accessed randomly using the
powerful SEEK primitive.

Indices for files can be created and
loaded into memory for speedy access to
data which is then on disk until needed.
These demos use this technique to store
and retrieve text such as this.@

207 (String Searching and End of File)
A useful primitive is provided to search
sequentially for a given character
string. Using FIND, you can implement
text file manipulation programs easily.

Another primitive, EOF, tests whether
the read/write pointer is at the end of
a file.

Together with SEEK, these primitives
provide highly flexible file handling.@

208 (Term Input and Output)
The basic form of input and output in
any PROLOG system is called term I/O.
The word "term" means "PROLOG data
item", and includes simple objects like
numbers, strings and variables, as well
as compound ones like lists and tuples.

Any PROLOG term can be output to a file
or device without worry using WRITE;
likewise, READ can always read the terms
back in again from files.@

209 (Formatted Input and Output)
LPA PROLOG Professional goes well beyond
term I/O with a complete formatted I/O
specification. Left/right aligned fixed
point numbers, quoted, unquoted and
arbitrary radix formats are defined.

Using the formatted I/O it is easy to
create tables, fixed record database
files and suchlike. It is also easy to
read and process formatted files from
other applications.@

210 (Fast and Flexible)
All Professional's I/O routines work
with explicitly named files. Windows are
just likes files displayed on the
screen. Likewise the serial, parallel,
editor and raw terminal devices are
simply addressed by their file names.

Every I/O call simply names the file,
window or device it is writing to or
reading from: there is no need for
reassigning standard I/O channels.@

301 (Disk and DOS Handling from PROLOG)
LPA PROLOG Professional is designed to
handle all types of programming, and not
just Expert Systems implementation.
Handling files, directories and DOS
commands is an important component of
many applications.

Professional's disk and DOS primitives
provide the necessary backup support for
the disk I/O subsystems to allow fully
professional systems to be written.@

302 (File Manipulation)
As you would expect, files can be
created, renamed, moved between
directories and deleted easily from
within PROLOG. Full DOS path names are
supported for all file operations.

PROLOG automatically backs up any files
created, but existing files can also be
opened for database updates and similar
applications. Up to 8 files can be open
in read/write mode at any one time.@

303 (Drive and Directory Manipulation)
As well as files, PROLOG can create and
remove DOS directories, or just move
between them. It is also easy to switch
between disk drives. Because full DOS
path names are supported, drive and
directory switching is an added
convenience rather than a requirement.

PROLOG programs can also enquire which
drive and directory are selected at any
given time.@

304 (Directory and File Data)
A special directory primitive returns a
PROLOG list of all files matching a
given "wildcard" specification. So it is
easy for programs to load all files of
type .DEC or to delete .BAK files, etc.

Another primitive returns all data
stored by DOS about a given file, such
as its time, date, type, size etc.
Sophisticated DOS tools can therefore be
written in PROLOG.@

305 (DOS Command Execution)
Any DOS command can be run from within a
PROLOG program using the EXEC primitive.
A command file name (even COMMAND.COM)
and a command line is all your program
needs to specify. When the command
terminates, its error code is returned
to your program.

Editors, other languages or just about
anything can be run in this way - memory
permitting, that is.@

306 (Environment Variables)
The DOS command, SET, enables special
strings, or environment variables, to be
installed in memory. Some, like PATH and
COMSPEC, have special meanings in DOS.
Others can be defined for applications.

Professional uses environment variables
for default configuration and start-up
commands; in addition, a primitive is
provided so that your own applications
can access these system strings.@

307 (Complete System Control)
In short, there is virtually nothing LPA
PROLOG Professional cannot do in terms
of DOS management. In fact, we at LPA
use PROLOG to write many of our own day
to day DOS tools.

The well designed DOS interface allows
your applications to offer the same
sophistication as LPA's own products,
with all the benefits to your users that
this entails.@

401 (List Processing Primitives)
Like the other great AI language, Lisp,
PROLOG excels at list processing. LPA
PROLOG Professional takes this further
than other PROLOGs not only because
programs and data all consist of lists,
but also because of a range of special
list processing primitives.

Sorting, concatenation and sublist
indexing allow lists to be used with
ease and high efficiency.@

402 (Sorting and Ordering)
Most data processing applications need
to sort information at one time or
another. Professional's SORT primitive
uses a very fast sort algorithm to order
the elements of lists. On a typical
PC/AT, 1000 random numbers can be sorted
in well under 1 second!

The algorithm used is a logarithmic
merge sort, and its performance is
unaffected by the pre-ordering of data.@

403 (Specifying the Sort Key)
A unique feature of Professional's SORT
is that lists of lists (of lists ...)
can be sorted according to a "key". The
key is an index that identifies a
sublist rather like an array address.
This field is then used by the sort
algorithm to order the overall list.

You could sort the same address data on
name, or town, or post code, or name-
and-town, or whatever.@

404 (Indexed List Record Retrieval)
A PROLOG list is a data object that can
contain any combination of names,
numbers, other lists or unknown entries.
So lists are ideal for storing data such
as names and addresses, or whatever.

Recursive programs can easily process
list-based "records", but for speed, LPA
PROLOG Professional includes a fast list
access function called MEM for
retrieving entries from lists.@

405 (Append and List Concatenation)
A classic PROLOG program is "append",
which defines the concatenation of two
lists to give a third.

As beautiful as it is, append is highly
inefficient. But you may be surprised to
discover that most PROLOGs still use
this rather academic example as part of
their runtime system. Not PROLOG
Professional, with its special CONCAT
primitive!@

406 (Length of a List)
Another useful primitive is provided to
return the length of a list. Again, this
can be done by recursive programming,
but such a program is never very
efficient.

With MEM, SORT, CONCAT and LENGTH your
list processing in PROLOG Professional
need never hold up your applications
programs.@

407 (Professional List Processing)
As you have seen, the sheer speed of the
list processing primitives puts LPA
PROLOG Professional way ahead of the
rest in terms of practical efficiency.

Of course, its conventional list
processing is also very fast: the
compiler attains over 13,000 lips on
some 8MHz 80286 based computers as
measured by the n-rev 100 benchmark
(this reverses lists using append).@

501 (Prolog Data Types)
Like all real PROLOGs, Professional has
no Pascal-style data declarations, and
programs can be written with whatever
mix of numbers, names, lists and
variables that the logic requires.

Of course, there are different types of
data (numbers and lists are different!),
but the point is that you do not need to
worry about which data will occur where
in advance of writing a program.@

502 (Simple and Compound Terms)
A simple term is any single PROLOG data
object, like a number or a name, which
cannot be broken down into smaller
parts. A compound term is a structure
which can contain other terms, which
themselves can be simple or compound.

There is no limitation (other than free
memory) to the depth and complexity of
terms. Your programs create whatever
terms they need, when they need them.@

503 (Types of Simple Term)
There are two main types of simple term:
numbers (either integer or floating
point) or names (text strings which name
programs, files, windows, modules or
nothing at all).

Your programs do not need to distinguish
between integers and floating point
numbers, since conversion between them
is automatic. Where possible, any number
is stored in its compact, integer form.@

504 (Types of Compound Term)
There are two types of compound term.
Lists are the most common, can be of
undefined length, and are very easy to
process with recursive programming
techniques. Tuples (constructed terms),
on the other hand, have a fixed length
since they are stored as arrays.

Normally programs use lists for holding
data, but tuples are useful where
compactness is important.@

505 (Unknown Terms)
A special type of term in PROLOG is the
unknown term, or variable. This is
unlike the variables of other
programming languages, since it behaves
more as a local place-holder for some
term that is, as yet, unknown.

Professional has no type declarations,
since it is essential for true logic
programming that unknown terms genuinely
are unknown!@

506 (String Data Types)
In addition to text names, LPA PROLOG
Professional has two types of "string",
though these are not special data types,
but lists of characters or numbers.
Being lists, string processing is very
easy in PROLOG.

The first type uses individual one-
character names in the list; the second
uses numbers representing ASCII codes.
You use whichever suits you best.@

507 (String Handling Primitives)
A set of useful primitives has been
provided to give great control over any
PROLOG term. They convert the term into
a string that contains the "text" of the
term, or convert back to the term from
this "text".

You can easily write programs which edit
the text of programs stored, or
transform input from the user, or
convert numbers into text names, etc.@

508 (Formatted String Handling)
The most powerful string primitive uses
the same specification as the formatted
I/O system (see option 2), and lets you
format strings from terms, and "read"
terms back out of formatted strings.

All type conversions, such as hex to
decimal, number to name, list to name,
etc, are possible using this primitive.
It is also very useful for processing
binary files read in as strings.@

509 (Ground and Hollow Terms)
Just occasionally it is a nuisance to
have to process terms that contain
unknowns, because they can assume any
value during pattern matching. LPA
PROLOG Professional can convert between
such "hollow" terms and "ground" terms.

In a ground term, unknown variables are
replaced by text names. This is a great
help if ever you need to write a tracer,
compiler or other such program.@

510 (Data Types and Conversion)
As you can see, LPA PROLOG Professional
has a rich collection of data types, and
all the flexibility of using them of a
true logic programming language.

Because of the special extensions to the
normal PROLOG data types (ground terms
and tuples), Professional gives you
greater control over your data when you
need it, but without ever imposing
Pascal-style data type restrictions.@

601 (The Clause Database)
PROLOG programs consist of collections
of rules and facts, collectively known
as clauses. Except when they have been
optimised, clauses can be extracted from
programs, printed or modified, and added
back into programs - all in PROLOG.

This mechanism allows programs to modify
each other or even themselves, and is
absolutely essential when writing expert
systems or compilers.@

602 (Incremental Compilation)
As just mentioned, clauses that have
been compiled with the optimising
compiler cannot be retrieved. This is
because the optimisation process looses
information about the clause in the
interests of efficiency.

However, fast incremental compilation is
used in the Professional Compiler to
fully support all dynamic clause
database applications.@

603 (Asserting New Clauses)
The built-in assertion mechanism allows
any clause to be added, at any time, by
any program. Facts and rules alike can
be stored in this way. In the Compiler,
these rules are actually compiled on the
fly!

A unique and useful feature of LPA
PROLOG Professional is that new clauses
can be added anywhere into a relation,
not just at the beginning or the end.@

604 (Deleting Clauses)
Clauses can be deleted one at a time in
two ways, either by matching a pattern
you give, or simply by name and number.

The pattern match mechanism allows you
to specify as much or as little as you
like of the clause being deleted; the
unspecified bits of your pattern are
"filled out". The Compiler actually
decompiles clauses before deleting them
to do this!@

605 (Killing Relations)
A quicker, "wholesale" way of removing
parts of a program is to "kill" a
relation. All clauses for the named
relation(s) are deleted immediately.

The same mechanism can be used for
removing whole modules from a system,
and together with PROLOG's loading
primitives and programmable error
handler provides an easy method of
writing overlay systems.@

606 (Clause Retrieval)
While the main purpose of clauses is to
be part of a program, it is often
necessary for programs to handle clauses
themselves. If you write an expert
system, compiler or other such program
then you will need to do this.

Several primitives are provided to
retrieve clauses, with easy backtracking
or efficient direct access. You can even
use the clause indexing mechanism.@

607 (The Structure of Clauses)
Clauses in LPA PROLOG Professional are
logically stored as lists of lists, with
the head and each goal on the body being
a list with the predicate name first,
and any arguments following on.

This structure is very easy to split up
and manipulate for meta-level
applications (using ordinary list
processing), and provides full upwards
compatibility with LPA's micro-PROLOG.@

608 (Dynamic Programs)
All AI languages should allow programs
to modify themselves, and LPA PROLOG
Professional makes sure you can do this.
We have seen that clauses are easily
added, retrieved and retracted, and that
they have a simple structure which is
easy to process.

Professional's clause database handling
is probably the most flexible of any
PROLOG system available.@

701 (Floating Point Arithmetic)
LPA PROLOG Professional uses a mixture
of 16-bit integer and 8-byte double
precision floating point numbers.
Whenever possible, numbers are stored as
integers, because they are more compact;
moreover, conversion between the number
types occurs automatically whenever
possible.

A full range of trig, log and other
maths functions is built in.@

702 (Dynamic Range)
The 8-byte, IEEE double precision format
used for floating point numbers provides
a massive dynamic numerical range to
please the astronomers and engineers:

  +/- 2.2E-308 ... +/- 1.7E+308

The mantissa has more than 15 digits of
accuracy, and integer precision can be
guaranteed over the range 1E+/-15 to
please the financial wizards!@

703 (The Expression Handler)
A very fast arithmetical expression
evaluator is built into Professional. It
employs standard operator precedences
for addition, multiplication, etc., and
also supports all the floating point
functions.

The evaluation primitive can easily
handle expressions of considerable
complexity, with many levels of
parentheses possible.@

704 (The Calculator Functions)
Plus, minus, times, divide are naturally
available, as are non-integer
exponentiation and module. These six
mathematical functions are treated as
binary operators, and their precedence
is handled correctly. So expressions
like:

  (3.14159 * 2 ^ 21.9 / (22 / 7))

can be written exactly as shown here.@

705 (Scientific Calculator Functions)
Sine, arcsine, cosine, arccosine,
tangent, arctangent: the three trigs and
their inverses are included; square
roots, natural and common logarithms
too. Most if not all of your numerical
calculations can be handled by the
built-in functions.

Hyperbolics are not included, but can
easily be implemented with the existing
functions.@

706 (Truncation and Rounding Functions)
Integer part, fractional part, floor,
sign and absolute value are all provided
in the expression handler.

These functions are used to truncate,
round and split numbers, say in removing
pence from currency values in pounds, or
rounding a value up to the nearest
quarter of a unit. They enable you to
control the 15+ digit accuracy of the
arithmetic.@

707 (Pseudo Random Numbers)
A well researched, high potency linear
congruential random number generator is
included with the expression handler. It
will produce a different sequence of
numbers every time you enter PROLOG,
since it is seeded at start-up from the
system time and date, and can be re-
randomised at any time.

For simulations, or cheating at games,
you can explicitly seed the generator.@

708 (Mathematical Applications)
Whether you wish to program multi-
dimensional graphics, compute non-
parametric statistics, simulate the
Stock Exchange, or just add up a few
numbers here and there, the arithmetic
package in LPA PROLOG Professional will
fit the bill.

Using its assembler coded expression
handler, Professional can cheerfully eat
its way though your numerical problems.@

801 (Error and Spypoint Handling)
LPA PROLOG Professional incorporates a
very powerful, totally programmable
error handler. Any execution error that
occurs can be intercepted by a PROLOG
relation that you can define.

Likewise, you can set "spypoints" on
individual relations, which cause
execution to jump to another special
PROLOG relation. This makes it easy to
implement special debuggers.@

802 (PROLOG Error Types)
There are two types of error in
Professional. The first, execution
errors, result from things like maths
overflow, attempts to delete a protected
file, etc. There are about 30 such
errors, and these are the ones that you
can intercept by a PROLOG program.

The other types of error result from
space running out. You can't intercept
these, but can define recovery actions.@

803 (Default Versus User Error Handling)
If you do not define an error handler,
then all errors print a diagnostic
message and stop program execution. You
then fix the error, and start over.

If you define the relation '?ERROR?',
any non-fatal error causes execution of
this relation, with the error number and
offending goal as arguments. You can do
anything you like to recover, including
trying the goal again.@

804 (Automatic Program Overlays)
One of the execution errors occurs when
a call is made to an undefined relation.
Most PROLOGs simply fail when this
happens, but Professional's error
handler gives far greater flexibility.

One very useful trick is to write an
error handler that loads the module
which contains the missing definition,
and then re-issues the goal. This method
provides a transparent overlay manager.@

805 (The Fatal Errors)
When one or more of the system workspace
segments (stacks, heap, etc) become
exhausted, the garbage collector is
invoked to try to reclaim some space.
Normally, the program can then continue.

In some cases, space really does run
out, and the program's execution is
aborted. All dynamic space can now be
reclaimed, and you can define how to
resume your program.@

806 (The Spypoint Mechanism)
LPA's sophisticated debugging aids make
use of the built-in spypoint mechanism.
A spypoint is a special flag that can be
set against any program you write; when
a call is made to that program, control
is transferred to the relation '?SPY?'.

You can define '?SPY?' yourself, if you
want to write a special purpose
debugger; otherwise you can simply use
one of LPA's own spypoint handlers.@

807 (A Programmable Timer)
Some versions of LPA PROLOG Professional
contain a programmable timer. When set,
it causes program execution to be
interrupted at some specified future
time. When the elapsed time expires, the
goal about to be called is replaced by a
call to the relation '?TIME?', which
again you can define.

You can use this mechanism to write time
based debuggers or profiling tools.@

808 (Total Exception Handling)
The error, spypoint and (where it is
available) timer mechanisms are very
powerful. Quite apart from being able to
handle errors with the full flexibility
of PROLOG, you can also create and
handle well defined exceptions during
development and testing.

Between them, these user-programmable
components of the system enable you to
write robust, user-proof software.@

900 (Installing GraFiX)
Before PROLOG can perform graphics,
GraFiX must be installed in memory. The
batch command DEMO1.BAT installs GraFiX
correctly for this demo: if you are
reading this message then you have run
the demo in some other way!

If you want to see some graphics, then
select menu option 0 to return to DOS,
and restart this demo with the command
DEMO1.@

901 (The GraFiX Interface)
A special built-in primitive is provided
which calls the "GraFiX" graphics kernel
by Brian D Steel. This allows lines,
rectangles, ellipses, filled areas,
bitmaps and text to be plotted in any of
the CGA, EGA and VGA graphics modes.

Support is also provided for input from
the Microsoft Mouse, and an optional
toolkit contains programs to plot
charts, graphs and turtle graphics.@

902 (Drawing Lines)
The most basic graphics function is line
drawing, and GraFiX allows you not only
to plot line segments, but also to
define the colour and style of lines.
Furthermore, lines can be drawn using
absolute or relative coordinates.

Press a key to see a simple line drawing
of a fennel plant. In this example, the
lines are all coloured appropriately
(graphics mode permitting).@ 

903 (Filling Areas)
Another graphics primitive allows GraFiX
to fill pre-defined areas. Any of the
graphics primitives may be used to draw
the fill outline: the cursor is then
placed within the enclosed area, and
filling commences, using a chosen colour
and/or fill texture.

The next demonstration shows randomly
placed LPA logos being drawn and then
filled with solid colours or textures.@

904 (Bitmap Manipulation)
A simple, but important requirement of a
graphics package is the ability to store
and retrieve pictures as bitmaps. These
may take the form of simple screen
dumps, or of scanned images or paint
files from other packages.

The GraFiX toolkit includes some utility
programs which can be used to save and
subsequently display part of, or the
whole of the screen.@

905 (Barchart Plotting)
One of the applications packages in the
GraFiX toolkit is a barchart plotter.
Given a chart title, set of labels and
data, it will scale and plot the
information on the screen.

Appropriate colours or textures are
selected automatically to suit the
graphics mode in use: these can be
overridden by you own choices for
personalised presentations.@

906 (Mathematical Plotting)
As well as bar charts, the GraFiX
toolkit allows you to plot single-
variable mathematical curves. As with
the barchart application, the axes are
scaled automatically to fit the
calculated values.

Colour is used where available, and
several line styles and text styles are
employed according to the graphics
resolution.@

907 (Turtle Graphics)
Popular with educationalists, Turtle
graphics are largely responsible for the
popularity of the LOGO programming
language in schools, especially in the
USA.

Another application program in the
GraFiX toolkit uses PROLOG's powerful
arithmetic handling to implement Turtle
graphics. This demo shows random spirals
created in this way.@

908 (Availability of GraFiX)
The GraFiX kernel, by Brian D Steel, is
distributed free with the IBM version of
PROLOG Professional. It is a memory-
resident utility which provides all the
functions needed to write fast,
colourful graphics programs in PROLOG.

An optional package, the GraFiX toolkit,
is available separately from LPA. This
includes bitmap, charting, plotting and
turtle graphics programs just shown.@

999 (Graphics Adapters)
In order to perform graphics, your
computer must be equipped with a
graphics adapter. The current GraFiX
kernel works with any of the following
adapters: CGA, EGA, VGA, or AT&T.

Your machine either contains MDA (which
cannot display graphics) or a dual-mode
adapter running in mono mode. In the
latter case, it may be possible for you
to reconfigure it to show graphics.@

