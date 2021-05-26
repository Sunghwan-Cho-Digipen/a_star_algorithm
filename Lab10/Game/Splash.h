/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Splash.h
Purpose: Header file for Splash
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/

#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Texture.h"

class Splash : public GameState {
public:
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Splash"; }
private:
	double timer;
	const int DISPLAY_TIME = 3;
	Texture texture;
};

