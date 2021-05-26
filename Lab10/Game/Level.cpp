/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level.cpp
Purpose: Source file for Level
Project: CS230
Author: Kevin Wright
Creation date: 4/30/2020
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "../Engine/TransformMatrix.h"
#include "..\Engine\Sprite.h"

#include "Level.h"
#include "Board.h"
#include "Screens.h"
#include "Cell.h"
#include "Image_Anims.h"

Level::Level() : quitKey(Input::ButtonType::Escape), reloadKey(Input::ButtonType::R), state(State::PickStart), mode(Modes::Step), currLevel(0),
					modeText(nullptr), resetText(nullptr), startingSpotText(nullptr), nextLevelText(nullptr), stepText(nullptr) {
	modePos = Vector2DInt{ 50, Engine::GetWindow().GetSize().y / 2 + 40 };
	resetPos = { 1150, Engine::GetWindow().GetSize().y / 2 + 40 };
	startingSpotPos = { 1120, Engine::GetWindow().GetSize().y / 2 - 80 };
	stepPos = { 25, Engine::GetWindow().GetSize().y / 2 - 80 };
	nextLevelPos = { 1130, Engine::GetWindow().GetSize().y / 2 - 120 };
}

void Level::Load() {
	MakeBoard(levels[currLevel]);
	state = State::PickStart;

	modeText = new Sprite("assets/mode.spt");
	modeText->PlayAnimation(static_cast<int>(mode));
	resetText = new Texture("assets/reset.png");
	startingSpotText = new Texture("assets/startingSpot.png");
	nextLevelText = new Texture("assets/nextLevel.png");
	stepText = new Texture("assets/step.png");
}

void Level::Update(double ) {
	if (quitKey.IsKeyDown() == true) {
		Engine::GetGameStateManager().Shutdown();
	}
	if (reloadKey.IsKeyDown() == true) {
		Engine::GetGameStateManager().ReloadState();
	}

	bool isMouseDown = Engine::GetInput().IsKeyReleased(Input::ButtonType::LeftMB);
	Vector2DInt mousePos = Engine::GetInput().GetMousePos();

	if (isMouseDown) {
		if (mousePos.x >= modePos.x && mousePos.y >= modePos.y
				&& mousePos.x <= modePos.x + modeText->GetFrameSize().x
				&& mousePos.y <= mousePos.y + modeText->GetFrameSize().y) {
			if (static_cast<Modes>(modeText->GetAnimation()) == Modes::Play) {
				mode = Modes::Step;
				if (state == State::Filling) {
					state = State::Filling_Step;
				}
			} else {
				mode = Modes::Play;
				if (state == State::Filling_Step) {
					state = State::Filling;
				}
			}
			modeText->PlayAnimation(static_cast<int>(mode));
		}
	}

	switch (state) {
	case State::PickStart:
		if (isMouseDown == true){
			Vector2DInt cellLocation = GetBoard()->MousePosToCellLoction(mousePos);
			Cell* selectedCell = GetBoard()->GetCell(cellLocation);
			if (selectedCell != nullptr && selectedCell->GetImage() == Images::None) {
				PlayerSelected(cellLocation);
				state = mode == Modes::Play ? State::Filling : State::Filling_Step;
			}
		}
		break;
	case State::Filling:
		if (Visit() == true) {
			state = State::Done;
		}
		break;
	case State::Filling_Step:
		if (isMouseDown == true) {
			if (Visit() == true) {
				state = State::Done;
			}
		}
		break;
	case State::Done:
		if (isMouseDown == true) {
			if (++currLevel >= static_cast<int>(levels.size())) {
				Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::AStar));
				currLevel = 0;
			}
			Engine::GetGameStateManager().ReloadState();
		}
		break;
	}
}

void Level::Unload() {
	delete resetText;
	delete startingSpotText;
	delete nextLevelText;
	delete stepText;
}

void Level::Draw() {
	Engine::GetWindow().Clear(0x808080FF);

	GetBoard()->Draw();

	resetText->Draw(TranslateMatrix(resetPos));
	if (state == State::PickStart) {
		startingSpotText->Draw(TranslateMatrix(startingSpotPos));
	}
	if (state == State::Filling_Step) {
		stepText->Draw(TranslateMatrix(stepPos));
	}
	if (state == State::Done) {
		nextLevelText->Draw(TranslateMatrix(nextLevelPos));
	}
	modeText->Draw(TranslateMatrix(modePos)); 
}
