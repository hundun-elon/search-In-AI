# search-In-AI

An AI agent designed to solve the 15-puzzle using search algorithms.

## Overview

Imagine we have to implement three search algorithms to find solutions to the 15-puzzle, a classic sliding tile puzzle that consists of a 4×4 grid with alphabets tiles and one empty space. The objective is to arrange the tiles in alphabetical order by sliding them into the empty space.

The implemented search algorithms are:

1. **Breadth-First Search (BFS)** – A brute-force approach that explores all possible moves level by level.
2. **A\* Search with Misplaced Tiles Heuristic** – Uses the number of misplaced tiles as the heuristic function to guide the search.
3. **A\* Search with Tile Distance Heuristic** – Uses the sum of Manhattan distances of all tiles from their goal positions as the heuristic.

## Credits

This problem was a search lab created by [Prof. Steven James](https://www.wits.ac.za/people/academic-a-z-listing/j/stevenjameswitsacza/).

## Usage

To run the AI agent, execute the corresponding script for the desired algorithm:
be sure to read the pdf so that you know the original problem statement.

```bash
g++ -o `filename.cpp` filename
```
