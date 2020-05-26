#include "Board.hpp"

Cell::Cell(Cell* node) {
    m_state = 0;
    for (int i = 0; i < 9; i++) {
        m_negativeState[i] = true;
    }
    m_stateRadar = false;
    p_nextNode = node;
} // Cell c'tor

Cell::~Cell() {
    // d'tor
}

int Cell::GetState() {
    return m_state;
}

void Cell::SetState(int num) {
    m_state = num + 1;
}

bool Cell::IsNegative(int num) {
    return m_negativeState[num];
}

void Cell::SetNegative(int num) {
    m_negativeState[num] = false;
}

bool Cell::GetStateRadar() {
    return m_stateRadar;
}

void Cell::SetStateRadar() {
    m_stateRadar = true;
}

Cell* Cell::GetNextNode() {
	return p_nextNode;
}

Board::Board() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            // Link Cells based on their 3x3 boxes
            if (row % 3 == 0 && col % 3 == 0) {
                m_cells[row][col] = new Cell(nullptr);
            } else if (row % 3 != 0 && col % 3 == 0) {
                m_cells[row][col] = new Cell(m_cells[row - 1][col + 2]);
            } else {
                m_cells[row][col] = new Cell(m_cells[row][col - 1]);
            }
        } // col
    } // row
    p_saveState = nullptr;
} // Board c'tor

Board::Board(const Board& copy) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            // Link Cells based on their 3x3 boxes
            if (row % 3 == 0 && col % 3 == 0) {
                m_cells[row][col] = new Cell(nullptr);
            } else if (row % 3 != 0 && col % 3 == 0) {
                m_cells[row][col] = new Cell(m_cells[row - 1][col + 2]);
            } else {
                m_cells[row][col] = new Cell(m_cells[row][col - 1]);
            }

            // Copy Cell values
            if (copy.m_cells[row][col]->GetState() != 0) {
                m_cells[row][col]->SetState(copy.m_cells[row][col]->GetState() - 1);
                m_cells[row][col]->SetStateRadar();
            } else {
                for (int num = 0; num < 9; num++) {
                    if (!copy.m_cells[row][col]->IsNegative(num)) {
                        m_cells[row][col]->SetNegative(num);
                    }
                } // num
            } // if state
        } // col
    } // row
    p_saveState = nullptr;
} // Board copy c'tor

Board::~Board() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (m_cells[row][col] != nullptr) {
                delete m_cells[row][col];
                m_cells[row][col] = nullptr;
            }
        } // col
    } // row
} // Board d'tor

int Board::GetCellState(int row, int col) {
    return m_cells[row][col]->GetState();
}

void Board::SetCellState(int row, int col, int num) {
    m_cells[row][col]->SetState(num);
}

bool Board::GetCellNegativeState(int row, int col, int num) {
    return m_cells[row][col]->IsNegative(num);
}

void Board::SetCellNegativeState(int row, int col, int num) {
    m_cells[row][col]->SetNegative(num);
}

void Board::SetConnectionNegativeState(int row, int col, int num) {
    for (int i = 0; i < 9; i++) {
        m_cells[row][i]->SetNegative(num);
        m_cells[i][col]->SetNegative(num);
    }

    Cell* current = m_cells[row + (2 - row % 3)][col + (2 - col % 3)];

    while (current != nullptr) {
        current->SetNegative(num);
		current = current->GetNextNode();
    }
} // Board SetConnectionNegativeState()

bool Board::GetCellRadar(int row, int col) {
    return m_cells[row][col]->GetStateRadar();
}

void Board::SetCellRadar(int row, int col) {
    return m_cells[row][col]->SetStateRadar();
}

Cell* Board::GetCellNode(int row, int col) {
    return m_cells[row][col];
}