/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: cell.cpp
Purpose: Source file for cell
Project: AStar (CS280 Programming Final)
Author: Kevin Wright / Sunghwan Cho
Creation date: 05/26/21
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/TransformMatrix.h"

#include "Cell.h"
#include "Image_Anims.h"


Cell::Cell(Vector2DInt xyIndex, char type, Vector2DInt screenPosition) : xyIndex(xyIndex), screenPosition(screenPosition),
																	gCost(static_cast<unsigned int>(-1)), hCost(static_cast<unsigned int>(-1)), pNext(nullptr)
{
	sprite = new Sprite("assets/Images.spt");
	switch (type)
	{
	case '0':
		sprite->PlayAnimation(static_cast<int>(Images::None));
		break;
	case 'F':
		sprite->PlayAnimation(static_cast<int>(Images::RedX));
		break;
	case 'W':
		sprite->PlayAnimation(static_cast<int>(Images::Black));
		break;
	}
}

Cell::~Cell()
{
	delete sprite;
}

Vector2DInt Cell::GetPosition() const noexcept
{
	return screenPosition;
	
}

Vector2DInt Cell::GetXYIndex() const noexcept
{
	return xyIndex;
}

void Cell::Draw()
{
	sprite->Draw(TranslateMatrix(screenPosition));

	if (gCost != static_cast<unsigned int>(-1)) 
	{
		// draw G cost replace the "" with a std::to_string( whatever your g cost is)
		Engine::Instance().DrawText(1, screenPosition + Vector2DInt{ -sprite->GetFrameSize().x / 2 + 5, 10 }, std::to_string(GetGCost()), SpriteFont::Justified::Left, 0x0000FFFF);
		// draw H cost replace the "" with a std::to_string( whatever your h cost is)
		Engine::Instance().DrawText(1, screenPosition + Vector2DInt{ sprite->GetFrameSize().x / 2 - 12, 10 }, std::to_string(GetHCost()), SpriteFont::Justified::Right, 0xFF0000FF);
		// draw F cost replace the "" with a std::to_string( whatever your f cost is)
		Engine::Instance().DrawText(0, screenPosition + Vector2DInt{ 0, -22 }, std::to_string(GetFCost()), SpriteFont::Justified::CenterX, 0x000000FF);
	}
}

void Cell::SetToImage(Images image)
{
	sprite->PlayAnimation(static_cast<int>(image));
}

Images Cell::GetImage()
{
	return static_cast<Images>(sprite->GetAnimation());
}

void Cell::SetPNext(Cell* nextPointer)
{
	pNext = nextPointer;
}

Cell* Cell::GetPNext()
{
	return pNext;
}

unsigned Cell::GetGCost() const noexcept
{
	return gCost;
}

void Cell::SetGCost(unsigned cost) noexcept
{
	gCost = cost;
}

void Cell::SetHCost(unsigned cost) noexcept
{
	hCost = cost;
}

unsigned Cell::GetFCost() const noexcept
{
	return  gCost + hCost;
}

unsigned Cell::ComputeGCost(Cell* currentCell, Cell* startCell)
{
	if(startCell == currentCell)
	{
		return 0;
	}

	const Vector2DInt StartCellIndex = startCell->GetXYIndex();
	const Vector2DInt CurrentCellIndex = currentCell->GetXYIndex();

	const int XOffset = std::abs(StartCellIndex.x - CurrentCellIndex.x);
	const int YOffset = std::abs(StartCellIndex.y - CurrentCellIndex.y);

	const int MinValue = std::min(XOffset, YOffset);
	const int MaxValue = std::max(XOffset, YOffset);

	return  DIAGONAL_COST * MinValue + STRAIGHT_COST * (MaxValue - MinValue) + startCell->GetGCost();
}

unsigned Cell::ComputeHCost(Cell* currentCell, Cell* endCell)
{
	if(endCell ==  currentCell)
	{
		return 0;
	}

	const Vector2DInt EndCellIndex = endCell->GetXYIndex();
	const Vector2DInt CurrentCellIndex = currentCell->GetXYIndex();

	const int XOffset = std::abs(EndCellIndex.x - CurrentCellIndex.x);
	const int YOffset = std::abs(EndCellIndex.y - CurrentCellIndex.y);

	const int MinValue = std::min(XOffset, YOffset);
	const int MaxValue = std::max(XOffset, YOffset);

	return  DIAGONAL_COST * MinValue + STRAIGHT_COST * (MaxValue - MinValue);
}

void Cell::SetCostBetweenIndex(Cell* startCell, Cell* endCell)
{
	gCost = ComputeGCost(this, startCell);
	hCost = ComputeHCost(this, endCell);
}

unsigned Cell::GetHCost() const noexcept
{
	return hCost;
}

std::ostream& operator<<(std::ostream& out, Cell*& cell)
{
	out << std::endl << "{" << cell->xyIndex.x << ", " << cell->xyIndex.y << '}' << " = " << cell->GetFCost();
	return out;
}
