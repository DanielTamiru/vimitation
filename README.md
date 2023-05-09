# vimitation
Built a Vim-like text editor in C++14 with additional features by following a detailed UML diagram I created in the planning phases of the project. I used SOLID OOP principles and implemented design patterns, like MVC, Strategy, and Template method, to maximize the cohesion and minimize the coupling of the program.


### Getting Started
Simply run `make` and the Makefile should handle the building of the executable called `vimitation` by default. 

### Features

Vimitation supports side scrolling in addition the following subset of vim commands:


Ctrl 
u
d
b
f
g

insertion
i
I
a
A
o
O
R

Movement
h
l
k
j
0
^
$
b
w
F
f

? search

deletion
d
dd
x
X
J

Colon
