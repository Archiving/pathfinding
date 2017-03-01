#include "menu.h"
#include <conio.h>

int main(int argc, char** argv) {
	ui::printInfo(VERSION, AUTHOR);
	//Dynamic memory allocation for the dimensions of 2d grid
	int dim;
	std::cout << "Enter the dimensions of your grid: ";
	std::cin >> dim;
	std::cout << std::endl;
	//Grid dimensions restrictions
	if (dim <= 0) {
		std::cerr << "Cannot have a grid size that is zero, smaller than 1, larger than 250 (visibility issues) or negative! Setting dim to 10...";
		dim = 10;
	}

	//Size of the grid on the screen
	float gridSize = 2.0f;

	//This should allocate space to point** grid.
	display(argc, argv, dim, gridSize);
	std::cout << "Instructions:\n";
	std::cout << "\t'W' to move up in grid space\n\t'S' to move down in grid space\n\t'A' to move left in grid space\n\t'D' to move right in grid space\n\t'SPACE' to change 'blocked' value of current cell\n\tPress 'G' to set the goal/unset the goal\n\tPress 'R' to set the initial robot position/unset it\n\tRight Click for Menu (Clear blocked cells, show all blocked cells, print author and version)\n";
	std::cout << "\tRED cells are BLOCKED while the green cell is your cursor.\n";
	std::cout << "\tGOLD cells are the goal for the robot and BLUE cells are the robot's starting position.";
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION); //Make it so it returns to glutMainLoop so we can delete pointers and such
	glutMainLoop(); //Enter the main loop

	//std::cout << "This part of the program has been reached! PogChamp!" << std::endl;
	
	//Delete the grid pointer
	delete[] grid;
	//Ask for a char from the console before termination
	_getch();
	return 0;
}