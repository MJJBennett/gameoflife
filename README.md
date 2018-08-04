### An Implementation of Conway's Game of Life with SFML 

This is a simple implementation of [Conway's Game of Life](gp.forricide.me/conway) - a cell simulation, where cells (or tiles, squares, etc) 'reproduce' based on their current conditions and a set of rules.

![](https://media.giphy.com/media/2rAKWLKwdtnw3FwgrJ/giphy.gif)

##### Rules
- Any live cell with fewer than two live neighbors dies, as if by under population.
- Any live cell with two or three live neighbors lives on to the next generation.
- Any live cell with more than three live neighbors dies, as if by overpopulation.
- Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

##### Installation

This application was designed and written with some new features of C++17 in mind. Consequently, building it will require a recent C++ compiler.

In order to build the application, `git clone` or download this repository, as well as binaries for [SFML](https://sfml-dev.org/download). Place the folder containing SFML into ./lib/ and ensure the folder's name starts with "SFML". Then run `cd build/` and then `cmake ..` and `make`. The application, when successfully built, can be run with `./ConwayLife` (Unix) or `ConwayLife.exe` (Windows). 

##### Instructions

Set tiles to "alive" by clicking on them.

The simulation can be advanced by pressing the return key, and reset with `r`. Furthermore, the simulation can be advanced any `n` times by entering a number (say, `342`) with number keys and then pressing the return key.

The tile size can be adjusted incrementally by pressing `o` and `p`.

A variety of configuration options can be found and adjusted in `conway.config`.
