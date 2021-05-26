/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: board.h
Purpose: Source file for Board
Project: AStar (CS280 Programming Final)
Author: Kevin Wrigtht
Creation date: 6/12/2020
-----------------------------------------------------------------*/

#pragma once
#include <list>

#include "..\Engine\BasicDataTypes.h"

class Cell;

class Board {
public:
	Board();
	virtual ~Board();
	void Load(std::string fileName);
	void Draw();

	bool IsMousePosOnBoard(Vector2DInt mousePos);
	Vector2DInt MousePosToCellLoction(Vector2DInt mousePos);
	Cell* GetCell(Vector2DInt location);

	Vector2DInt GetSize() { return { boardWidth, boardHeight }; }
protected:
	std::list<Vector2DInt> aiStartCells;

private:
	
	Cell** board;
	int boardWidth;
	int boardHeight;
	const Vector2DInt cellSize;
};