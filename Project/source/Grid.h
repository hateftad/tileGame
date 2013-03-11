#ifndef GRID_H
#define GRID_H

#include "Tile.h"
#include "DrawableFactory.h"

class Grid
{
public:

	struct GridSpace
	{
		int widthCount;
		float startGridX;
		float startGridY;
		int aboveGridY;
		float tileWidth;
		int topOfGrid;

	};

	Grid(GridSpace gspace);
	~Grid();
	void Initialize(DrawableFactory* df);
	void Swap(int idx1, int idx2);
	bool CheckMatch(bool correct = false);
	bool CheckMatch( Tile* t1, Tile* t2 );
	bool CheckMatch( Tile* t1, Tile* t2, Tile* t3 );
	bool CheckMatch( Tile* t1, Tile* t2, Tile* t3, Tile* t4 );
	void Matched(const int pos1,const int pos2,const int pos3,const int pos4 = 0,const int pos5 = 0, bool horizontal = true);
	void TheMatchedOnes(const int pos1,const int pos2,const int pos3,const int pos4 = 0,const int pos5 = 0, bool horizontal = true);

	Tile* Get(int idx);
	std::vector<Tile*>* GetGrid();
	std::vector<Tile*>::iterator End();
	std::vector<Tile*>::iterator Begin();

protected:
private:
	std::vector<Tile*> m_grid;

	GridSpace m_gridSpace;
	void Swapper(int from, int to, int stopRow);

};




#endif