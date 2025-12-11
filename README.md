# NAMING-DLL
from sudoku to canonical name and reverse
handling canonical names for puzzles

This DLL is created to give to users the basics functions to handle names of sudoku puzzles.

=================== about canonical names, definition and printable form of the name

In any process working with plenty of sudokus, the same issue appears: Is this sudoku a morph of a previous one. Cleaning the redundancy is important

to save processing time
to build the final result

to avoid redundancy, the classical way is to use a "canonical morph of the entry". For a solution grid, the most common canonical morph is the min lexical form of the solution grid.

For a puzzle, we use here the puzzle morphed to the canonical solution grid. As the solution grid can have auto morphs, an additional condition is to use the min lexical morph of the puzzle for these auto morphs of the solution grid.

Having the ED (essentially different) puzzle, next point is "how do you show it to have a short record.

We know that we have 5 472 730 538 ED solution grids. This is the start to define a short canonical name. Having the solution grid reduced to this number, the puzzle can be defined by the given cells, a 81 bits field. 

Next point is "how can we print this sequence of 81 binary values.

The hexadecimal print is well known to show a 4 bits sequence. The print uses 16 characters, 0-9 plus a-f or A-F. The print will be shorter if we use more printable characters.

If we stick to the 128 first ascii values, the maximum that we can do is to use 64 characters for a 6 bits sub field. This is what is done here with the following sequence 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz{}

These 64 printable characters are here in increasing ascii value, giving room to the use of many programs as the “sort” program. Then, the 81 bits field can be printed as 14 characters 6x13= 78 bits, the last characters with 3 bits used. This is the first possible name for a puzzle

10 characters for the rank of the solution grid 14 characters for the bit field, plus one separator to have the file easy to process.

This "relatively short" name has a big interest; the solution grid rank is explicitly given.

If a very short name is wanted, we can switch easily to the second name, a 19 bytes name. The solution grid rank uses 33 bits the bit field 81 bits This is a total of 114 bits = 19x6 These 114 bits are printed in the same way. Note: such names in a file sorted are compressed very efficiently by the .zip process.

=========================== DLLs used in the process 

The naming process uses several big DLLs as

back force solver
grid morphing to minlex
virtual catalog of min lexical solution grids. ....

The corresponding DLLs must be in a directory seen by the program.
The repository contains all needed DLLs, the sources are in the corrresponding repositories.

=================================================================================== naming DLL

This DLL has a very limited number of entries with a double target

The user has only to know the properties of the DLL itself
The user code to process files is very simple.

A small progam is added to do the main file transformations used in my datbases. 
This program uses the file u09names_user.h where the content of the DLL appears as comment.

The DLL requires (needed in called DLLs) a computer using a 64 bits intel set of instructions 

The code of the DLL is given to explain how it works.
================================================== main uses of the repository

A============================= DLL

to work with the DLL the user has to download 
all DLLs 
sk9names.lib 
u09names_user.h to use it in a C or C++ program.

If the coding is not C or C++ the user must have similar calling possibilities in his code.

B=========================== small .exe

If the user is working under windows, he can use directly the small program sku06D_names.exe
The coding of the command line is available in the file sku06D_names_readme.txt
Again, all DLLs are needed.

here again, the source is available compiled using virtual studio

All functions of this program are processing a text file containing sudoku or names 
and create an output with ED sudokus and/or names

