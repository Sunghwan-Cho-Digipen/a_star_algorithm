/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Splash.cpp
Purpose: Source file for Splash
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"

#include "Screens.h"
#include "Splash.h"
#include "../Engine/TransformMatrix.h"

void Splash::Load() {
	std::string texturePath = "assets/DigiPen_BLACK_1024px.png";
	texture.Load(texturePath);
	timer = 0;
}

void Splash::Update(double dt) {
	timer += dt;
	if (timer >= DISPLAY_TIME) {
		Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::AStar));
	}
}

void Splash::Unload() {
}

void Splash::Draw() {
	Engine::GetWindow().Clear(0xFFFFFFFF);

	texture.Draw(TranslateMatrix({ (Engine::GetWindow().GetSize() - texture.GetSize()) / 2.0 }));
}