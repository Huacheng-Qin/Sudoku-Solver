#ifndef SUDOKU_SOLVER_COMPONENTS_H
#define SUDOKU_SOLVER_COMPONENTS_H

class Cell {
    public:
        Cell(Cell* node);
        ~Cell();

        int GetState();
        void SetState(int num);
        bool IsNegative(int num);
        void SetNegative(int num);
        bool GetStateRadar();
        void SetStateRadar();
        Cell* GetNextNode();

    private:
        int m_state;
        bool m_negativeState[9];
        bool m_stateRadar;
        Cell* p_nextNode;
};

class Board {
    public:
        Board();
        Board(const Board& copy);
        ~Board();

        int GetCellState(int row, int col);
        void SetCellState(int row, int col, int num);
        bool GetCellNegativeState(int row, int col, int num);
        void SetCellNegativeState(int row, int col, int num);
        void SetConnectionNegativeState(int row, int col, int num);
        bool GetCellRadar(int row, int col);
        void SetCellRadar(int row, int col);
        Cell* GetCellNode(int row, int col);

        Board* p_saveState;

    private:
        Cell* m_cells[9][9];
};

#endif
