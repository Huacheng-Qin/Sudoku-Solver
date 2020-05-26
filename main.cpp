#include <iostream>
#include "Solver.hpp"

int main() {
    Solver solver;

    std::string input;
    std::cin >> input;

    solver.InitializeBoard(input);
    solver.Output();
    solver.Start();
    solver.Output();

	int x;
	std::cin >> x;
    return 0;
} // main