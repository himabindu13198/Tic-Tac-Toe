# Tic-Tac-Toe
Built the game of Tic Tac Toe on OpenGL without using any built in functions for rasterization
This implementation does not use any built in functions of
OpenGL for the drawing of various components of the game like
the lines and circles.
For these purposes (drawing the ‘X’, ‘O’ and the game lines),
Bresenham’s line drawing and circle drawing algorithms are used.
The game is a 2 player game and announces either a winner or a
draw after each match.
System requirements :
Our system is a Linux 14.02 OS. For systems with other OS, we
need a C++ compiler that can compile tic.cpp.
We also need OpenGL and it’s dependencies installed beforehand.
To compile the code : g++ tic.cpp -lGL -lGLU -lglut -lm
To run: ./a.out
