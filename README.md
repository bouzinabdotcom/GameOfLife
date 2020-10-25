# Conway's Game Of Life

The **Game of Life**, also known simply as **Life**, is a cellular automaton devised by the British mathematician  John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves. It is Turing complete and can simulate a universal constructor or any other Turing machine.
The game is based on a grid of living and dead cells and life is based on 3 simple rules:
1.  Survivals. Every cell with two or three neighboring cells survives for the next generation.
2.  Deaths. Each cell with four or more neighbors dies (is removed) from overpopulation. Every cell with one neighbor or none dies from isolation.
3.  Births. Each empty cell adjacent to exactly three neighbors--no more, no fewer--is a birth cell. A cell is placed on it at the next move.

# Compile

Clone project:

    $ git clone https://github.com/bouzinabdotcom/GameOfLife

Go to directory:

    $ cd GameOfLife
Make:

    $ make


## Game of Life (.gol) File Format

To use this tool you will need a text file with the pattern you wish to start with.
Examples of that file is provided (examples/***.gol). The ".gol" extension is optional.

This tool makes a square grid with n*n cells. 
In your .gol file you need to specify the n at the start of the file. then in the next lines specify the pattern using 0 for a dead cell and 1 for one that is alive.

**Example:** Glider   
_ # _  
_ _ #  
\# # #  

**.gol format:** 
 
3  
010  
001  
111  

## How to use

To get 1 solution for the puzzle: 

    $ ./game-of-life -f examples/glider.gof

There are a number of options to play with:

 - Size:

    $ ./game-of-life -s b|d|h -f examples/glider.gof

	Use "-s" to specify a size for the grid as follows:

	- b (big): 50x50
	- d (double): 100x100
	- h (huge): 200x200

	If you don't use this option the default size if 25x25.

 - Time: 

    $ ./game-of-life -t f|fr|s|sr -f examples/glider.gof

	Use "-t" to specify the time it takes for the next generation to evolve.
	

	 - f (fast): 50 millisecond (20 gen/s)
	 - fr (faster): 1 millisecond (1000 gen/s)
	 - s (slow): 600 millisecond (1.67 gen/s)
	 - sr (slower): 1000 millisecond (1 gen/s)

	If you don't use the "-t" option the default time is 150 millisecond (6.67 gen/s)

 - x coordinate:
 
	Example:
	
    $ ./game-of-life -x 9 -f examples/glider.gof

	This puts the glider 9 cells to the right.

- y coordinate:
 
	Example:
	
    $ ./game-of-life -y 9 -f examples/glider.gof

	This puts the glider 9 cells to the bottom.

The (x, y) coordinates belong to the first cell of the pattern on the top left side.



## Issues

The code is still buggy and I still need to figure out how to simulate an infinite plain within a finite one.
Please feel free to fork and make a pull request if you know how.
Have fun :)