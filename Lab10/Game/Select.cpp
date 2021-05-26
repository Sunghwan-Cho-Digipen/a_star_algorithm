/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Select.cpp
Purpose: Source file for Select
Project: CS230
Author: Kevin Wright
Creation date: 5/2/2020
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "../Engine/Texture.h"
#include "..\Engine\TransformMatrix.h"

#include "Screens.h"
#include "Select.h"


Select::Select() : quitKey(Input::ButtonType::Escape) {}

void Select::Load() {
	selectLevel1Image = new Texture("assets/AStar.png");
	selectLevel2Image = new Texture("assets/Weighted.png");

	level1ImagePos = { Engine::GetWindow().GetSize() / 2 - selectLevel1Image->GetSize() / 2 + Vector2DInt{0, 80}};
	level2ImagePos = { Engine::GetWindow().GetSize() / 2 - selectLevel2Image->GetSize() / 2 - Vector2DInt{0, 80} }; 
}

void Select::Update(double) {
	if (Engine::GetInput().IsKeyReleased(Input::ButtonType::LeftMB) == true) {
		Vector2DInt mousePos = Engine::GetInput().GetMousePos();
		if (mousePos.x >= level1ImagePos.x && mousePos.y >= level1ImagePos.y &&
					mousePos.x <= level1ImagePos.x + selectLevel1Image->GetSize().x &&
					mousePos.y <= level1ImagePos.y + selectLevel1Image->GetSize().y) {
			Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::AStar));
		}
		if (mousePos.x >= level2ImagePos.x && mousePos.y >= level2ImagePos.y &&
					mousePos.x <= level2ImagePos.x + selectLevel2Image->GetSize().x &&
					mousePos.y <= level2ImagePos.y + selectLevel2Image->GetSize().y) {
			Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::Weighted ));
		}
	}
	if (quitKey.IsKeyDown() == true) {
		Engine::GetGameStateManager().Shutdown();
	}
}

void Select::Unload() {
}

void Select::Draw() {
	Engine::GetWindow().Clear(0xFFFFFFFF);

	selectLevel1Image->Draw(TranslateMatrix(level1ImagePos));
	selectLevel2Image->Draw(TranslateMatrix(level2ImagePos));

}