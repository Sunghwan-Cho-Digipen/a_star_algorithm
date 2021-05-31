/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: cell.h
Purpose: header file for cell
Project: AStar (CS280 Programming Final)
Author: Kevin Wright / Sunghwan Cho
Creation date: 05/26/21
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
	void SetPNext(Cell* nextPointer);
	Cell* GetPNext();
	[[nodiscard]] unsigned int GetGCost() const noexcept;
	void SetGCost(unsigned cost) noexcept;
	[[nodiscard]] unsigned int GetHCost() const noexcept;
	void SetHCost(unsigned cost) noexcept;
	[[nodiscard]] unsigned int GetFCost() const noexcept;

	static unsigned ComputeGCost(Cell* currentCell, Cell* startCell);
	static unsigned ComputeHCost(Cell* currentCell, Cell* endCell);

	void SetCostBetweenIndex(Cell* startCell, Cell* endCell);
	
private:
	Vector2DInt xyIndex;
	Vector2DInt screenPosition;
	Sprite* sprite;
	unsigned gCost;
	unsigned hCost;
	Cell* pNext;

	static constexpr unsigned DIAGONAL_COST = 14;
	static constexpr unsigned STRAIGHT_COST = 10;
};