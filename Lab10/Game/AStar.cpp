/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AStar.cpp
Purpose: AStar logic for assignment 5 
Project: AStar (CS280 Programming Final)
Author: 
Creation date: 
-----------------------------------------------------------------*/

#include "AStar.h"
#include "Image_Anims.h"
#include "Cell.h"


void AStar::MakeBoard(std::string levelData)
{
	board = new Board();	// Create the board class
	board->Load(levelData);	// load the data file and initialize the 2D array

	// Find the target cell (the other end of our search path)
	for (int x = 0; x < board->GetSize().x; x++) 
	{
		for (int y = 0; y < board->GetSize().y; y++) 
		{
			if (board->GetCell({ x,y })->GetImage() == Images::RedX) 
			{
				beginSearch = board->GetCell({ x,y });
			}
		}
	}
}

void AStar::PlayerSelected(Vector2DInt cellLocation)
{
	selected = board->GetCell(cellLocation);
	selected->SetToImage(Images::BlueX);
	//todo
	// Do stuff here for the selected locations
}

bool AStar::Visit()
{
	// Do stuff here for each step of our AStar algorithm
	//todo
}

bool AStar::Compare(Cell* const& cellA, Cell* const& cellB)
{
	//todo
	// compare 2 cells (return the less than value)
	// The heap is already set up to use this function for our heap compare
	//return cellA->GetFCost() < cellB->GetFCost() ? true : cellA->GetHCost() < cellB->GetHCost() ? true : false ;
	
}

void AStar::Unload()
{
	delete board;
	while (toVisit.IsEmpty() == false) 
	{
		toVisit.Pop();
	}
	beginSearch = nullptr;
	selected = nullptr;

	Level::Unload();
}