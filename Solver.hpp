#include "Board.hpp"

#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

class Solver {
    public:
        Solver();
        ~Solver();

        // This class takes a string input
        // The string requires the following format:
        // xyz-xyz-xyz-...
        // x is the row, y is the column, and z is the number in the cell
        // Each of x y and z are exclusively 1-9
        // Any non-number characters can be used in place of the '-'
        void InitializeBoard(std::string input);
        void Start();
        void Output();

    private:
        // Algorithm 1
        // Check each cell, if cell only has 1 possibility, set cell to that number
        bool StatesAlg1();
        // Algorithm 2
        // Check each row/column/box, if only one cell can hold a number, set cell to that number
        bool StatesAlg2();
        void SetNegativeStates();
        bool CheckSolved();

        Board* m_boardPtr;
        bool m_contradiction;
        bool m_guess;
};

#endif
