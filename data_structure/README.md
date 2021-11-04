# Solution to Assignment2
## Program1 : Rats in the maze
---
Solution to program1 : Rats in the maze.
### Description
---
This is a solution to the mazing problem using stack, the program will find a path for the given mazes and print them out.
### Usage
---
First, enter the number of mazes you want to find a path out, then you will need to type in the size and the content of the maze one by one, just like the example input in the following.  
If you enter the data properly, you are good to go.The program will ouput the path map in n x n size.
```
/* sample input */
2
4
1100
1101
0100
1111
5
10000
11101
00111
10001
00001

/* sample output */
1000 
1100 
0100 
0111

10000 
11100 
00111 
00001 
00001
```
## Program2 : Infix to Postfix
---
Solution to program2 : Infix to Postfix.
### Description
---
If the given infix expression is valid, it will print 1 with a postfix expression after it, Otherwise, it will only print 0 as a sign of invalid expression.
### Usage
---
Start with the number of infix expressions, then type them in one afte another.
```
/* sample input */
5
(1+2)-(4+1*8)
(5+5)-8/4
((8+9)
8+9-(6/3)
1*2/3*(5+6))

/* sample output */
1 12+418*+-
1 55+84/-
0
1 89+63/-
0
```
## Program3 : Push and Pop
---
Solution to program3 : Push and Pop.
### Description
---
This is a program using stack and backtracing to solve multiple anagram problems.  
The order of pop and push can be seen as the rearrangements of characters. The program will accept a pair of string as a single data. If the second string can't be reconstruct from first string, it will print a empty string with the brackets. Otherwise, it will output the sequence of order of push and pop in 'i'(in) and 'o'(out) form with the brackets.  
If a single data have multilple sequences, then it will print them out in alphabetical order.
### Usage
---
Similarly, enter the number of data first(a pair of strings is a single data), then type all the data in.
```
/* sample input */
3
toyz
tozy
asiagodton
bygliang
bahama
bahama

/* sample output */
[
i o i o i i o o
]
[
]
[
i o i i i o o i i o o o
i o i i i o o o i o i o
i o i o i o i i i o o o
i o i o i o i o i o i o
]
```
