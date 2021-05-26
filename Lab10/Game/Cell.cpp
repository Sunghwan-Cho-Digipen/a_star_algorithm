/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: cell.cpp
Purpose: Source file for cell
Project: AStar (CS280 Programming Final)
Author:
Creation date:
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/TransformMatrix.h"

#include "Cell.h"
#include "Image_Anims.h"


Cell::Cell(Vector2DInt xyIndex, char type, Vector2DInt screenPosition) : xyIndex(xyIndex), screenPosition(screenPosition),
																	gCost(static_cast<unsigned int>(-1)), hCost(static_cast<unsigned int>(-1)), pNext(nullptr) //todo
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

unsigned Cell::GetGCost()
{
	return gCost;
}

unsigned Cell::GetFCost()
{
	return  gCost + hCost;
}

unsigned Cell::GetHCost()
{
	return hCost;
}

std::ostream& operator<<(std::ostream& out, Cell*& cell)
{
	out << std::endl << "{" << cell->xyIndex.x << ", " << cell->xyIndex.y << '}' << " = " << cell->GetFCost();
	return out;
}
