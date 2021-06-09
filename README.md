# AHHH: a programming language for the dreadful
### Screaming into the Void but make it Turing Complete

AHHH is an esoteric programming language inspired by the all-consuming dread induced by programming. 

![SpoOoOoOoKy](https://www.fg-a.com/halloween/computer-ghost-black-white.jpg)

Programming languages can shape everything about an algorithm, from its speed, effiency, and modularity all the way down to its aesthetics. In that vein, I wanted to write a programming language that was an absolute bitch to use. Just the absolute worst. A miserable experience for everyone involved. I think - in that goal - I have succeeded. Good luck...

### Setup

To compile the interpreter, run:

    g++ -Wall interpret_ahhh.cpp -o AHHH

Then, to run files, just call the executable with:

    ./AHHH file.ahhh
   
If you aren't using linux you either:
1. already know how to compile c++ code on your machine, or
2. should probably use an IDE. Here's a pretty good [guide](https://www.cs.odu.edu/~zeil/cs250PreTest/latest/Public/installingACompiler/).

I've provided a number of demo files:
* fib.ahhh
  * Explicitly generates the first ~46 Fibonacci numbers. I stopped at 46 because any larger yields overflow, since I'm using c++ ints. I could fix that, but I won't.
* fib_inf.ahhh
  * Loops through infinitely many Fibonacci numbers. It overflows basically immediately, but the implimentation is kind of cool (and well documented).
* hello_world.ahhh
  * You know I had to do it to 'em.
* hello_world_expanded.ahhh
  * You know what it does, and now you know why. Same program, just with documentation.

The expanded hello world program is only 150 lines of code, but in condensed form is actually quite simple:

    AHHHHhhHHHhHHHHhHHHhHHhHHHhHHhhHHhhHHhhHHhhHHhhHHhhHHhhHHhhHhHhhHhhhhhhHHhhHHHhHHHHhHHHhHHhHhHHhhHhhhHhhHhHhHhHhHhHhHhhhhhhHhHhhHhhHHhhHHhhHHhhHhHhhHhhhhhhHhHhhhHhhHhhhhhhHhHhhhHhhHhhHHhhHHhhHHhhhhhhHHhhHHHhHHHHhHHHhHHhHhHhHHHhhHhhHHHhHHHHhHHHhhHHHhHhHHhHhHhHhHhHhHhHhHhhhhhhHHhhHHHhHHHHhHHHhHHhHHhhhhhhHHhhHHHhHHHHhHHHhHHhHHHhHhHhHHHhhHhhHHHhHHHHhHHHhhHHHHHhhHhhHHHhHHHhHHHhHhHHHhHhHHhHhHhhhhhhHhHhhHhhHHhhHHhhHhHhhHhhhhhhHhHhhhHhhHhhHHhhHHhhHHhhhhhhHhHhhHhHhHhHhHhHhhHhhHhhhhhhHhHhhHhHhHhHhHhHhHhHhHhHhHhHhHhHhHhHhHhhhhhhHHhhHHHhHHHHhHHHhHHhHHhhHHhhhhhh!

If there's a glaring problem you want me to know about or you otherwise feel strongly inclined, feel free to bug me at kyle.morgenstein@gmail.com or yell at me on Twitter [@KyleMorgenstein](https://twitter.com/KyleMorgenstein).

# Language Mechanics
The language is pretty simple and is heavily based on COW. There's 16 (+2) commands, which are all the capitalization permutations of hhhh to HHHH. The start key is AHHH. The AHHH language has a memory head (pointer) which can be moved along a tape of memory. There are also two registers that values can be read/written from. Anything that isn't a command is a comment. See fib_inf.ahhh or hello_world_expanded.ahhh for examples of comments/documentation.  

The commands are as follows:

Code | Command | Function
------------ | -------------| -------------
0 | hhhh | Searching in reverse, skip the first preceding command, and then jump back to matching HHHH command and begin execution from that HHHH command (end loop).
1 | hhhH | Move the pointer right one cell.
2 | hhHh | Move the pointer left one cell.
3 | hhHH | Print the current memory cell as an integer.
4 | hHhh | If Register 1 is empty, copy the current memory cell to the register. Otherwise, write the Register 1 value to the current memory cell.
5 | hHhH | If Register 2 is empty, copy the current memory cell to the register. Otherwise, write the Register 2 value to the current memory cell.
6 | hHHh | Add the current memory cell to the value of Register 1 and store the sum in Register 1. The memory cell is unchanged. 
7 | hHHH | Add the current memory cell to the value of Register 2 and store the sum in Register 2. The memory cell is unchanged. 
8 | Hhhh | If the current memory cell is nonzero, print the cell as an ASCII character. Otherwise, read in an ASCII character from the console.
9 | HhhH | Increment the current memory cell by one.
10 | HhHh | Decrement the current memory cell by one.
11 | HhHH | Read in an integer from the console and store it in the current memory cell (overwrites current cell).
12 | HHhh | Set the current memory cell to zero.
13 | HHhH | Double the value of the current memory cell and store it in the current memory cell.
14 | HHHh | Square the value of the current memory cell and store it in the current memory cell.
15 | HHHH | If the current memory cell is nonzero, continue to the next command. Otherwise, skip one command, and then skip ahead to the next matching hhhh command (begin loop).
16 | AHHH | Start program.
17 | hhh! | Print new line (useful after printing ASCII characters, which otherwise don't print a new line).

As you can see, this language sucks. You won't enjoy it. I think it's pretty [funny](https://www.youtube.com/watch?v=-50NdPawLVY), which is an accomplishment given the number of brain cells I've killed trying to get this to work. Hopefully you think it's at least passively amusing too. If not, idk, go scream about it or something.
