/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AStar.cpp
Purpose: AStar logic for assignment 5 
Project: AStar (CS280 Programming Final)
Author: Sunghwan Cho
Creation date: 05/26/21
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

	neighbors.emplace_back(Vector2DInt{ 0, 1 });				//up
	neighbors.emplace_back(Vector2DInt{ 1, 1 });				//right up
	neighbors.emplace_back(Vector2DInt{ 1, 0 });				//right
	neighbors.emplace_back(Vector2DInt{ 1, -1 });				//right down
	neighbors.emplace_back(Vector2DInt{ 0, -1 });				//down
	neighbors.emplace_back(Vector2DInt{ -1, -1 });				//left down
	neighbors.emplace_back(Vector2DInt{ -1, 0 });				//left
	neighbors.emplace_back(Vector2DInt{ -1, 1 });				//left up
}

void AStar::PlayerSelected(Vector2DInt cellLocation)
{
	selected = board->GetCell(cellLocation);
	selected->SetToImage(Images::BlueX);
	
	beginSearch->SetCostBetweenIndex(beginSearch, selected);
	toVisit.Push(beginSearch);
}

bool AStar::Visit()
{
	std::cout << "Heap:" << toVisit << std::endl;
	if (toVisit.IsEmpty() == false)
	{
		Cell* currentCell = toVisit.Pop();

		if(currentCell->GetXYIndex() == selected->GetXYIndex())
		{
			SetPath(currentCell);
			return true;
		}
		
		SetVisit(currentCell);
		TryToAddNeighbors(currentCell);

		return false;
	}

	return true;
}

bool AStar::Compare(Cell* const& cellA, Cell* const& cellB)
{
	return cellA->GetFCost() == cellB->GetFCost() ? cellA->GetHCost() < cellB->GetHCost() : cellA->GetFCost() < cellB->GetFCost();
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

void AStar::SetVisit(Cell* current)
{
	current->SetToImage(Images::Green);
}

void AStar::SetPath(Cell* destination)
{
	Cell* path = destination;
	while (path != nullptr)
	{
		path->SetToImage(Images::Blue);
		path = path->GetPNext();
	}
}

bool AStar::HasAlreadyVisited(Cell* current)
{
	return current->GetImage() == Images::Green;
}

void AStar::TryToAddNeighbors(Cell* current)
{
	for(Vector2DInt pos : neighbors)
	{
		TryToAdd(current, pos);
	}
}

void AStar::TryToAdd(Cell* parent, const Vector2DInt& neighbor)
{
	Cell* currentCell = board->GetCell(parent->GetXYIndex() + neighbor);
	if (currentCell == nullptr)
	{
		return;
	}

	if (currentCell->GetImage() == Images::Black || HasAlreadyVisited(currentCell) == true)
	{
		return;
	}

	auto iter = toVisit.Find(currentCell);
	if (iter != toVisit.end())
	{
		const unsigned GCost = (*iter)->GetGCost();
		const unsigned HCost = (*iter)->GetHCost();
		const unsigned FCost = GCost + HCost;

		const unsigned CurrentGCost = Cell::ComputeGCost(currentCell, parent);
		const unsigned CurrentHCost = Cell::ComputeHCost(currentCell, selected);
		const unsigned CurrentFCost = CurrentGCost + CurrentHCost;

		if (FCost == CurrentFCost)
		{
			if (CurrentHCost < HCost)
			{
				(*iter)->SetGCost(CurrentGCost);
				(*iter)->SetHCost(CurrentHCost);
				(*iter)->SetPNext(parent);
				toVisit.Update(iter);
			}
			return;
		}

		if (FCost > CurrentFCost)
		{
			(*iter)->SetGCost(CurrentGCost);
			(*iter)->SetHCost(CurrentHCost);
			(*iter)->SetPNext(parent);
			toVisit.Update(iter);
		}

		return;
	}

	currentCell->SetCostBetweenIndex(parent, selected);
	currentCell->SetPNext(parent);
	toVisit.Push(currentCell);
}