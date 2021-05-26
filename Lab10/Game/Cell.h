/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: cell.h
Purpose: header file for cell
Project: AStar (CS280 Programming Final)
Author:
Creation date:
-----------------------------------------------------------------*/
#pragma once

#include "..\Engine\BasicDataTypes.h"

class Sprite;
enum class Images;

class Cell {
public:
	friend std::ostream& operator<<(std::ostream& out, Cell*& cell);

	Cell(Vector2DInt xyIndex, char type, Vector2DInt screenPosition);
	virtual ~Cell();
	[[nodiscard]] Vector2DInt GetPosition() const noexcept;
	[[nodiscard]] Vector2DInt GetXYIndex() const noexcept;
	void Draw();
	void SetToImage(Images image);
	Images GetImage();
	void SetpNext(Cell* nextPointer);
	Cell* GetpNext();
	unsigned int GetGCost();
	unsigned int GetFCost();
	unsigned int GetHCost();
	// You may add additional functions

private:
	Vector2DInt xyIndex;
	Vector2DInt screenPosition;
	Sprite* sprite;
	unsigned gCost;
	unsigned hCost;
	Cell* pNext;
	// You may add member variables
};