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
#include "Title.h"
#include "../Engine/TransformMatrix.h"

void Title::Load() {
}

void Title::Update(double dt) {
}

void Title::Unload() {
}

void Title::Draw() {
	Engine::GetWindow().Clear(0xFFFFFFFF);

	Engine::DrawText()
	texture.Draw(TranslateMatrix({ (Engine::GetWindow().GetSize() - texture.GetSize()) / 2.0 }));
}