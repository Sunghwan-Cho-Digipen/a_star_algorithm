/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: board.cpp
Purpose: Source file for Board
Project: AStar (CS280 Programming Final)
Author: Kevin Wright / Sunghwan Cho
Creation date: 05/26/21
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"

#include "Board.h"
#include "Cell.h"
#include "Image_Anims.h"


Board::Board() : cellSize({ 64,64 }) {}

void Board::Load(std::string fileName)
{
	if (fileName.substr(fileName.find_last_of('.')) != ".dat") 
	{
		throw std::runtime_error("Bad Filetype.  " + fileName + " not a sprite info file (.dat)");
	}
	std::ifstream inFile(fileName);
	if (inFile.is_open() == false) 
	{
		throw std::runtime_error("Failed to load " + fileName);
	}

	Vector2DInt center = Engine::GetWindow().GetSize() / 2;
	inFile >> boardWidth;
	inFile >> boardHeight;

	/* screenPosition is the xy position for where the cell is located on the screen.  
	This is the bottom left cell. position.  Use cellSize to find the other cell screen positions*/

	Vector2DInt screenPosition = { center.x - cellSize.x * (boardWidth - 1) / 2,
									center.y - cellSize.y * (boardHeight - 1) / 2 };
	// Dynamically create a 2D contiguous array (lab 3) of size boardWidth & boardHeight
	board = reinterpret_cast<Cell**>(malloc(sizeof(Cell*) * boardHeight + sizeof(Cell) * boardWidth * boardHeight));
	void* row_start_ptr = reinterpret_cast<char*>(board) + sizeof(Cell*) * boardHeight;

	char type = 0;
	for (int y = 0; y < boardHeight; ++y)
	{
		board[y] = reinterpret_cast<Cell*>(reinterpret_cast<char*>(row_start_ptr) + sizeof(Cell) * boardWidth * y);
		for (int x = 0; x < boardWidth; ++x)
		{
			inFile >> type;
			new (&board[y][x]) Cell({ x,y }, type, { screenPosition.x + cellSize.x * x ,screenPosition.y + cellSize.y * y });
		}
	}
}

Board::~Board()
{
	free(board);
}

void Board::Draw()
{
	for (int y = 0; y < boardHeight; y++) 
	{
		for (int x = 0; x < boardWidth; x++) 
		{
			board[y][x].Draw();
		}
	}
}

bool Board::IsMousePosOnBoard(Vector2DInt mousePos)
{
	if (mousePos.x < GetCell({ 0, 0 })->GetPosition().x - cellSize.x/2) 
	{
		return false;
	}
	if (mousePos.y < GetCell({ 0, 0 })->GetPosition().y - cellSize.y/2) 
	{
		return false;
	}
	if (mousePos.x > GetCell({ boardWidth - 1, boardHeight - 1 })->GetPosition().x + cellSize.x / 2) 
	{
		return false;
	}
	if (mousePos.y > GetCell({ boardWidth - 1, boardHeight - 1 })->GetPosition().y + cellSize.y / 2) 
	{
		return false;
	}
	return true;
}

Vector2DInt Board::MousePosToCellLoction(Vector2DInt mousePos)
{
	if (IsMousePosOnBoard(mousePos) == false) 
	{
		Engine::GetLogger().LogError("Mouse pos was in an invalid location");
	}

	Vector2DInt temp = GetCell({ 0, 0 })->GetPosition() - cellSize/2;
	Vector2DInt boardClickLocation = mousePos - temp;

	return { boardClickLocation.x / cellSize.x, boardClickLocation.y / cellSize.y };
}

Cell* Board::GetCell(Vector2DInt location)
{
	if (location.x < 0 || location.x >= boardWidth) 
	{
		return nullptr;
	}
	if (location.y < 0 || location.y >= boardHeight) 
	{
		return nullptr;
	}
	return &board[location.y][location.x];
}
