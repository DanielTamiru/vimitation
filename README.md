# vimitation
Built a Vim-like text editor in C++14 with additional features by following a detailed [UML diagram](https://github.com/DanielTamiru/vimitation/files/11434058/uml.pdf) I created in the planning phases of the project. I used SOLID OOP principles and implemented design patterns, like MVC, Strategy, and Template method, to maximize the cohesion and minimize the coupling of the program.

### [Demo](https://drive.google.com/file/d/1ty2_FUfGNJ1Cf_RB2QA4ysVysVSJ-3eZ/view?usp=share_link)
<img width="1074" alt="image" src="https://github.com/DanielTamiru/vimitation/assets/46784904/905ec645-65d8-40c2-89d2-a6ea198a68b7">


### Getting Started
Simply run `make` and the Makefile should build an executable called `vimitation`. 

### Features

Vimitation supports side scrolling in addition to the following subset of vim commands:

**Insertion**
- `i` - insert before the cursor
- `I` - insert at the beginning of the line
- `a` - insert (append) after the cursor
- `A` - insert (append) at the end of the line
- `o` - append (open) a new line below the current line
- `O` - append (open) a new line above the current
- `R` - replace mode - replace more than one character, until ESC is pressed 

**Movement**
- `h` - move cursor left
- `j` - move cursor down
- `k` - move cursor up
- `l` - move cursor right
- `0` - jump to the start of the line
- `^` - jump to the first non-blank character of the line
- `$` - jump to the end of the line
- `b` - jump backwards to the start of a word
- `w` - jump forwards to the start of a word
- `F` - jump to next occurrence of character x
- `f` - jump to the previous occurrence of character
- `Ctrl` + `b` - move back one full screen
- `Ctrl` + `f` - move forward one full screen
- `Ctrl` + d` - move forward 1/2 a screen
- `Ctrl + u` - move back 1/2 a scree


**Search**
- `?` - search for pattern
- `/` - search backward for pattern

**Edit**
- `d` - delete marked text (text moved over in subsequent movement operation)
- `dd` - delete (cut) a line
- `J` - join line below to the current one with one space in between

**Colon Commands**
- `:w` - write (save) the file, but don't exit
- `:wq` - write (save) and quit
- `:q` - quit (fails if there are unsaved changes)
- `:q!` - quit and throw away unsaved changes
- `:[line #]` - jump to line number

**Other**
- `Ctrl` +  `g` - Show file name

