/* --------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Standard.cpp
Purpose: Lab6
Project: Clash of Block
Author:Eunjin Hong
Creation date: 05.29.2020
-----------------------------------------------------------------
*/

#include "Weighted.h"
#include "Image_Anims.h"
#include "Cell.h"


void Weighted::MakeBoard(std::string levelData) {
	board = new Board(); 
	board->Load(levelData); 
	for (int x = 0; x < board->GetSize().x; x++) {
		for (int y = 0; y < board->GetSize().y; y++) {
			if (board->GetCell({ x,y })->GetImage() == Images::RedX) {
				target = board->GetCell({ x,y });
			}
		}
	}
}

bool Weighted::Visit()
{
	if (toVisit.IsEmpty() == true)
	{
		return true;
	}

	Cell *visitedCell = toVisit.Pop();
	board->GetCell(visitedCell->GetXYIndex())->SetToImage(Images::Green);
	if (visitedCell == selected) {
		while (toVisit.IsEmpty() == false) {
			toVisit.Pop();
		}
		Cell* curr = visitedCell;
		while (curr != target) {
			board->GetCell(curr->GetXYIndex())->SetToImage(Images::Blue);
			curr = curr->GetNext();
		}
		board->GetCell(curr->GetXYIndex())->SetToImage(Images::Blue);
		return true;
	}
	
	TryToAdd({ visitedCell->GetXYIndex().x , visitedCell->GetXYIndex().y + 1 }, visitedCell->GetGCost() + 10, visitedCell);
	TryToAdd({ visitedCell->GetXYIndex().x + 1, visitedCell->GetXYIndex().y }, visitedCell->GetGCost() + 10, visitedCell);
	TryToAdd({ visitedCell->GetXYIndex().x, visitedCell->GetXYIndex().y - 1 }, visitedCell->GetGCost() + 10, visitedCell);
	TryToAdd({ visitedCell->GetXYIndex().x - 1, visitedCell->GetXYIndex().y }, visitedCell->GetGCost() + 10, visitedCell);

	TryToAdd({ visitedCell->GetXYIndex().x + 1, visitedCell->GetXYIndex().y + 1 }, visitedCell->GetGCost() + 14, visitedCell);
	TryToAdd({ visitedCell->GetXYIndex().x + 1, visitedCell->GetXYIndex().y - 1 }, visitedCell->GetGCost() + 14, visitedCell);
	TryToAdd({ visitedCell->GetXYIndex().x - 1, visitedCell->GetXYIndex().y - 1 }, visitedCell->GetGCost() + 14, visitedCell);
	TryToAdd({ visitedCell->GetXYIndex().x - 1, visitedCell->GetXYIndex().y + 1 }, visitedCell->GetGCost() + 14, visitedCell);

	return false;
}

void Weighted::PlayerSelected(Vector2DInt cellLocation) //start the breadth first search filling process
{
	selected = board->GetCell(cellLocation);
	selected->SetToImage(Images::BlueX);

	target->SetGCost(0, board->GetCell(cellLocation), selected);
	toVisit.Push(target);
}

bool Weighted::TryToAdd(Vector2DInt cellPos, unsigned int newGCost, Cell *fromCell)
{
	if ((board->GetCell(cellPos) == nullptr) || (board->GetCell(cellPos)->GetImage() != Images::None && board->GetCell(cellPos)->GetImage() != Images::BlueX))
	{
		return false;
	}
	Cell* toAddCell = board->GetCell(cellPos);

	if (toVisit.Find(toAddCell) == toVisit.end()) {
		toAddCell->SetGCost(newGCost, fromCell, selected);
		toVisit.Push(toAddCell);
	}
	else {
		if (toAddCell->GetGCost() > newGCost) {
			toAddCell->SetGCost(newGCost, fromCell, selected);
			toVisit.HeapifyUp(toVisit.Find(toAddCell));
		}
	}
	return true;
}


bool Weighted::Compare(Cell* const& cellA, Cell* const& cellB) {
	if (cellA->GetFCost() == cellB->GetFCost()) {
		return cellA->GetHCost() < cellB->GetHCost();
	}
	else {
		return cellA->GetFCost() < cellB->GetFCost();
	}
}