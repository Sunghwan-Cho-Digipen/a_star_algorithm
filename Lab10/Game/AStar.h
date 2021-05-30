/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AStar.h
Purpose: Header for the AStar file
Project: AStar (CS280 Programming Final)
Author: Kevin Wright / Sunghwan Cho
Creation date: 05/26/21
-----------------------------------------------------------------*/

#pragma once

#include "../Engine/Heap.h"
#include "Level.h"
#include "Board.h"

class AStar : public Level {
public:
	AStar() : board(nullptr), toVisit(Compare) {}
	void MakeBoard(std::string levelData);
	void PlayerSelected(Vector2DInt cellLocation) override;
	bool Visit() override;
	Board* GetBoard() override { return board; }
	std::string GetName() override { return "AStar " + std::to_string(currLevel); }

	void Unload() override;
private:
	static bool Compare(Cell* const& a, Cell* const& b);
	// You may add additional functions
protected:
	Board* board;
	Heap<Cell*> toVisit;
	Cell* beginSearch;
	Cell* selected;
};

