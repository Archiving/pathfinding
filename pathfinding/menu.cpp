#include "menu.h"

namespace ui {

	void saveGrid(point** grid, int dim) {
		std::ofstream gridFile;
		gridFile.open("gridFile.txt", std::ios::out | std::ios::trunc);

		gridFile << "{ ";
		for (int i = 0; i < dim; i++) {
			gridFile << "{ ";
			for (int j = 0; j < dim; j++) {
				//std::cout << "The j, i coord is: (" << j << ", " << i << ")" << std::endl;
				if (j != 9) {
					if (grid[j][i].blocked || grid[j][i].isGoal || grid[j][i].isRobotPos) {
						if (grid[j][i].blocked) {
							gridFile << "1" << ", ";
						}
						else if (grid[j][i].isGoal) {
							gridFile << "2" << ", ";
						}
						else if (grid[j][i].isRobotPos) {
							gridFile << "99" << ", ";
						}
					}
					else {
						gridFile << "0" << ", ";
					}
				}
				else {
					if (grid[j][i].blocked || grid[j][i].isGoal || grid[j][i].isRobotPos) {
						if (grid[j][i].blocked) {
							gridFile << "1";
						}
						else if (grid[j][i].isGoal) {
							gridFile << "2";
						}
						else if (grid[j][i].isRobotPos) {
							std::cout << "Found a robot position!" << std::endl;
							gridFile << "99";
						}
					}
					else {
						gridFile << "0";
					}
				}
				//gridFile << "(" << grid[j][i].x << ", " << grid[j][i].y << ") ";
			}
			//Create a new line after every row
			gridFile << "}";
			gridFile << std::endl;
		}
		gridFile << "}; ";
		gridFile.close();

	}

	void printInfo(int version, std::string author) {
		printf("\n\t===============\n");
		printf("\tPATHFINDING CREATOR v%d\n", version);
		printf("\tby %s\n", author);
		printf("\t===============\n");
	}
}