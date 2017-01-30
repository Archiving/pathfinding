
//maybe place this somewhere in a grid class?
typedef struct point point;

//Point class
struct point {
	int x;
	int y;
	bool blocked = false;
};

class Grid {
public:
	point** grid;

	Grid(point** _grid) {
		grid = _grid;
	}

	point** get_grid() {
		return grid;
	}

	bool is_grid_blocked(int x, int y) {
		return grid[x][y].blocked;
	}
};
