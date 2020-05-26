# Sudoku-Solver
A program that takes user input and solves a Sudoku puzzle.

The solver is made up of three classes: Solver, Board, and Cell.
Both the Board and Cell class are used as part of the Solver class,
which will interact with the user.

The solver takes a string input, with the following format for initialization:
  xyz-xyz-xyz
Where x is the row, y is the column, and z is the number in the cell.
The rows and columns are counted from left to right, top to bottom.
All three variables are exclusively 1-9.
Any other non-number characters can be used in place for '-'

The solver uses two solving algorithms that I developed myself based on how I would
solve Sudoku in real life.

The solver also has a copy algorithm, which copies the current state of the board
and makes a guess when no definite decision could be made

The solver uses std::cout to print the solution on the console
