#include <iostream>
#include "Solver.hpp"
#include "Board.hpp"

Solver::Solver() {
    m_boardPtr = new Board;
    m_contradiction = false;
    m_guess = false;
}

Solver::~Solver() {
    while (m_boardPtr != nullptr) {
        Board* holder = m_boardPtr;
        m_boardPtr = m_boardPtr->p_saveState;
        delete holder;
    }
}

void Solver::InitializeBoard(std::string input) {
    while (!input.empty()) {
        while ((input.front() < 49 || input.front() > 57) && !input.empty()) {
            input.erase(0, 1);
        }

        int row = int(input.front()) - 49;
        input.erase(0, 1);
        int col = int(input.front()) - 49;
        input.erase(0, 1);
        int num = int(input.front()) - 49;
        input.erase(0, 1);

        m_boardPtr->SetCellState(row, col, num);
    } // input not empty
} // Input()

void Solver::Start() {
    while (!CheckSolved()) {
        bool stuck;

        if (m_contradiction) {
            Board* boardHolder = m_boardPtr;
            m_boardPtr = m_boardPtr->p_saveState;
            delete boardHolder;
            m_contradiction = false;
        } // contradiction

        if (!StatesAlg1()) {
            if (!StatesAlg2()) {
                Board* boardHolder = new Board(*m_boardPtr);
                boardHolder->p_saveState = m_boardPtr;
                m_boardPtr = boardHolder;
                m_guess = true;
            } // Algorithm 2
        } // Algorithm 1
    } // solve loop
} // Start()

bool Solver::StatesAlg1() {
    bool changeFlag = false;

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (m_boardPtr->GetCellState(row, col) == 0) {
                int counter = 0;
                int holder = 0;

                for (int num = 0; num < 9; num++) {
                        if (m_boardPtr->GetCellNegativeState(row, col, num)) {
                            counter++;
                            holder = num;
                        }
                } // num

                if (counter == 0) {
                    m_contradiction = true;
                } else if (counter == 1) {
                    m_boardPtr->SetCellState(row, col, holder);
                    m_boardPtr->SetConnectionNegativeState(row, col, holder);
                    m_boardPtr->SetCellRadar(row, col);
                    changeFlag = true;
                } else if (m_guess && counter == 2) {
                    m_boardPtr->SetCellState(row, col, holder);
                    m_boardPtr->SetConnectionNegativeState(row, col, holder);
                    m_boardPtr->SetCellRadar(row, col);
                    m_boardPtr->p_saveState->SetCellNegativeState(row, col, holder);
                    m_guess = false;
                    changeFlag = true;
                } // counter result
            } // if undefined state
        } // col
    } // row

    return changeFlag;
} // StatesAlg1()

bool Solver::StatesAlg2() {
    bool changeFlag = false;

	for (int num = 0; num < 9; num++) {
        // Check 3x3 boxes
		for (int row = 2; row < 9; row += 3) {
			for (int col = 2; col < 9; col += 3) {
				Cell* current = m_boardPtr->GetCellNode(row, col);
				Cell* holder = nullptr;
				int counter = 0;

				while (current != nullptr) {
					if (current->GetState() == 0 && current->IsNegative(num)) {
						counter++;
						holder = current;
					}
					current = current->GetNextNode();
				} // node

				if (counter == 1) {
					holder->SetState(num);
					changeFlag = true;
				}
			} // col
		} // row
        SetNegativeStates();

        // Check rows
        for (int row = 0; row < 9; row++) {
            int counter = 0;
            int holder = 0;

            for (int col = 0; col < 9; col++) {
                if (m_boardPtr->GetCellState(row, col) == 0 && m_boardPtr->GetCellNegativeState(row, col, num)) {
                    counter++;
                    holder = col;
                }
            } // col

            if (counter == 1) {
                m_boardPtr->SetCellState(row, holder, num);
                m_boardPtr->SetConnectionNegativeState(row, holder, num);
                m_boardPtr->SetCellRadar(row, holder);
                changeFlag = true;
            }
        } // row
        
        // Check columns
        for (int col = 0; col < 9; col++) {
            int counter = 0;
            int holder = 0;

            for (int row = 0; row < 9; row++) {
                if (m_boardPtr->GetCellState(row, col) == 0 && m_boardPtr->GetCellNegativeState(row, col, num)) {
                    counter++;
                    holder = row;
                }
            } // col

            if (counter == 1) {
                m_boardPtr->SetCellState(holder, col, num);
                m_boardPtr->SetConnectionNegativeState(holder, col, num);
                m_boardPtr->SetCellRadar(holder, col);
                changeFlag = true;
            }
        } // col
	} // num

    return changeFlag;
} // StatesAlg2()

void Solver::SetNegativeStates() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (m_boardPtr->GetCellState(row, col) != 0 && !m_boardPtr->GetCellRadar(row, col)) {
                m_boardPtr->SetConnectionNegativeState(row, col, m_boardPtr->GetCellState(row, col) - 1);
                m_boardPtr->SetCellRadar(row, col);
            } // unset cell
        } // col
    } // row
} // SetNegativeStates()

void Solver::Output() {
    std::cout << "-------------------------------------" << std::endl;
    for (int row = 0; row < 9; row++) {
        std::cout << "| ";
        for (int col = 0; col < 9; col++) {
			if (m_boardPtr->GetCellState(row, col) == 0) {
				std::cout << " ";
			} else {
				std::cout << m_boardPtr->GetCellState(row, col);
			}
            std::cout << " | ";
        } // col
        std::cout << std::endl;
		std::cout << "-------------------------------------" << std::endl;
    } // row
} // Output

bool Solver::CheckSolved() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (m_boardPtr->GetCellState(row, col) == 0) {
                return false;
            }
        } // col
    } // row

    return true;
} // CheckSolved()
