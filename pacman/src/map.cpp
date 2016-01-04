#include "map.h"

Map::Map(int height, int width) 
		:
			_height(height),
			_width (width)
		{

	/* Memory allocation */
	map = new Tile*[height];
	for(int i = 0; i < height; i++) {
		map[i] = new Tile[width];
	}

	/* Map initialization */
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			map[i][j] = Tile(
				DefaultMap::type    [i][j],
				DefaultMap::eatable [i][j] == '1'
			);
		}
	}
}

Map::~Map() {
	/* Memory deallocation */
	for(int i = 0; i < height; i++) {
		delete map[i];
	}
	delete map;
}

bool Map::valid(int i, int j) {
	return map[i][j].walkable;
/*
		   i >= 0 && i < height
		&& j >= 0 && j < width
		&& map[i][j].walkable;
*/
}

bool Map::eat(int i, int j) {
	bool ate = map[i][j].eat();

	return ate;
}