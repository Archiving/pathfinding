#include "menu.h"
float gridSize;
float dim;

point** grid;

//Note that size is the dimensions of the grid where gridSize is the size of the grid on the screen (e.x. a 2.0f grid with a dimension of 20x20 would be display(...., 20, 2.0f);
void display(int argc, char** argv, float g_dim, float grid_Sz) {
	//Assign grid, sz and grid_Sz`
	dim = g_dim;
	gridSize = grid_Sz;
	grid = new point*[dim];
	for (int i = 0; i < dim; i++) grid[i] = new point[dim];
	//Populate with values
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			grid[i][j].x = i;
			grid[i][j].y = j;
			grid[i][j].blocked = false;
		}
	}
	/* Open the file for writing the contents of grid[][]
	* Writing by position and the text coresponds to wheter the coordinate in the grid[][] is blocked or not (if there is an obstacle) */
	ui::saveGrid(grid, dim);

	//Initialize the GLUT library and negotiate a session with the window system
	glutInit(&argc, argv);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(VWIDTH, VHEIGHT);
	glutCreateWindow("Pathfinding Creator");
	//Method callbacks
	glutIdleFunc(render_callback);
	glutDisplayFunc(render_callback);
	glutKeyboardFunc(key_callback);
	glutReshapeFunc(resize);
	glutCreateMenu(menu_callback);
	glutAddMenuEntry("Print All Blocked Cells", 1);
	glutAddMenuEntry("Clear All Blocked Cells", 2);
	glutAddMenuEntry("Print Version and Author", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//Start a point that the player is in at the top left corner of the grid (0,0)
point position;

bool every(point** arr, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (arr[i][j].blocked) return false;
		}
	}
	return true;
}

float cursorX = 0;
float cursorY = 0;

//Key input callback
void key_callback(unsigned char key, int x, int y) {
	//Constant ASCII codes
	const int ESC = 27;
	const int SPACE = 32;
	const int A = 97;
	const int D = 100;
	const int S = 115;
	const int W = 119;
	const int C = 99;
	const int ZERO = 48;
	const int ONE = 49;

	switch (key) {
	case ESC:
		exit(0);
		break;
	case A:
		position.x -= 1;
		if (position.x < 0) {
			position.x = dim - 1;
			cursorX = (dim) * ((gridSize * 2) / dim);
		}
		printf("You moved to: (%d, %d)\n", position.x, position.y);
		cursorX -= (gridSize * 2) / dim;
		break;
	case D:
		position.x += 1;
		if (position.x > dim - 1) {
			position.x = 0;
			cursorX = -((gridSize * 2) / dim);
		}
		printf("You moved to: (%d, %d)\n", position.x, position.y);
		cursorX += (gridSize * 2) / dim;
		glutPostRedisplay();
		break;
	case S:
		position.y += 1;
		if (position.y > dim - 1) {
			position.y = 0;
			cursorY = (gridSize * 2 / dim);
		}
		printf("You moved to (%d, %d)\n", position.x, position.y);
		cursorY -= (gridSize * 2) / dim;
		break;
	case W:
		position.y -= 1;
		if (position.y < 0) {
			position.y = dim - 1;
			cursorY = -(gridSize * 2);
		}
		printf("You moved to (%d, %d)\n", position.x, position.y);
		cursorY += (gridSize * 2) / dim;
		break;
	case SPACE:
		grid[position.x][position.y].blocked = grid[position.x][position.y].blocked ? false : true;
		printf("You changed the position (%d, %d) to being %s\n", position.x, position.y, (grid[position.x][position.y].blocked) ? "blocked" : "unblocked");

		ui::saveGrid(grid, dim);
		break;
	case ONE:
		printf("You are @ position: (%d, %d)\n", position.x, position.y);
		break;
	}
}

void menu_callback(int id) {
	switch (id)
	{
	//Print all blocked cells
	case 1:
		if (every(grid, dim)) std::cout << ("No cells are blocked!\n");
		for (int x = 0; x < dim; x++) {
			for (int y = 0; y < dim; y++) {
				if (grid[x][y].blocked) printf("The cell @ (%d, %d) is blocked.\n", grid[x][y].x, grid[x][y].y);
			}
		}
		break;

	//Clear all blocked cells
	case 2:
		if (every(grid, dim)) {
			std::cout << "No cells are blocked!\n";
			break;
		}
		printf("Clearing all cells that are blocked...\n");
		printf("You changed the following positions: \n");

		for (int x = 0; x < dim; x++) {
			for (int y = 0; y < dim; y++) {
				if (grid[x][y].blocked) {
					grid[x][y].blocked = false;
					printf("\t(%d, %d)\n", x, y);
				}
			}
		}
		ui::saveGrid(grid, dim);
		break;

	//Print version number, author
	case 3:
		ui::printInfo(VERSION, AUTHOR);
		break;
	}
}


//Render callback for drawing graphics on window
void render_callback() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Because the grid is always a perfect square of dimensions x by x
	float bound = gridSize;
	float boundo = -gridSize;
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);

	//Draw outer linear lines for the grid in case of skipping
	glVertex3f(boundo, bound, -5.0f);
	glVertex3f(bound, bound, -5.0f);

	glVertex3f(bound, bound, -5.0f);
	glVertex3f(bound, boundo, -5.0f);

	/* Loop through -bound -> bound, increment each line by bound*2/totalGridSize
	 * (since the total dimension, x, gets split into two bounds, -bound and bound, meaning we must double the bound since the size is effectively halved) */

	for (float i = boundo; i <= bound; i += (bound * 2) / (dim)) {
		//Draw the grid lines
		glVertex3f(i, bound, -5.0f);
		glVertex3f(i, boundo, -5.0f);

		glVertex3f(boundo, i, -5.0f);
		glVertex3f(bound, i, -5.0f);
	}
	glEnd();

	//Draw the cursor
	glColor3f(.0f, 0.9f, 0.4f);
	glBegin(GL_POLYGON);
	//top left
	glVertex3f(-bound + 0.01f + cursorX, bound - 0.01f + cursorY, -5.0f);
	//top right
	glVertex3f(-bound + (bound * 2) / dim - 0.01f + cursorX, bound - 0.01f + cursorY, -5.0f);
	//bottom right
	glVertex3f(-bound + (bound * 2) / dim - 0.01f + cursorX, bound - ((bound * 2) / dim) + 0.01f + cursorY, -5.0f);
	//bottom left
	glVertex3f(-bound + 0.01f + cursorX, bound - ((bound * 2) / dim) + 0.01f + cursorY, -5.0f);
	glEnd();

	//Draw any blocked cells *NOTE* the square order vertex matters!
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			if (grid[j][i].blocked) {
				glColor3f(1, 0, 0);
				glBegin(GL_POLYGON);
				//top left
				glVertex3f(-bound + j*((bound * 2) / dim) + 0.01f,
							bound - i*((bound*2)/dim) - 0.01f,
							-5.0f);

				//top right
				glVertex3f(-bound + (j + 1)*((bound * 2) / dim) - 0.01f,
							bound - i*((bound * 2) / dim) - 0.01f,
							-5.0f);

				//bottom right
				glVertex3f(-bound + (j + 1)*((bound * 2) / dim) - 0.01f, bound - (i + 1)*((bound * 2) / dim) + 0.01f, -5.0f);

				//bottom left
				glVertex3f(-bound + j*((bound * 2) / dim) + 0.01f,
							bound - (i+1)*((bound * 2) / dim) + 0.01f,
							-5.0f);

				glEnd();
			}
		}
	}


	//Flush the buffer, swaps buffers for current window
	glutSwapBuffers();
}

void resize(int w, int h) {
	//Prevent a divide by zero, when window is too short (you cant make a window of zero width).
	if (h == 0) h = 1;
	float ratio = 1.0* w / h;

	//Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	//Reset Matrix
	glLoadIdentity();

	//Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	//Set the correct perspective.
	gluPerspective(45, ratio, 1, 1000);

	//Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}
