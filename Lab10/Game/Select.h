/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Select.h
Purpose: Header file for Select
Project: CS230
Author: Kevin Wright
Creation date: 5/2/2020
-----------------------------------------------------------------*/

#pragma once
#include "..\Engine\GameState.h"

class Texture;

class Select : public GameState {
public:
	Select();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Title"; }
private:
	Texture* selectLevel1Image;
	Texture* selectLevel2Image;
	Vector2DInt level1ImagePos;
	Vector2DInt level2ImagePos;
	Input::InputKey quitKey;
};

