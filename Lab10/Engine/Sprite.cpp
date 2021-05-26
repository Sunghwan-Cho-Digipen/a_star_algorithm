/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.cpp
Purpose: source file for Sprite Module
Project: CS230
Author: Kevin Wright
Creation date: 3/21/2020
-----------------------------------------------------------------*/

#include "Sprite.h"
#include "Engine.h"
#include "TransformMatrix.h"
#include "Texture.h"

Sprite::Sprite(std::string spriteInfoFile) { Load(spriteInfoFile); }
Sprite::~Sprite() {
	for (Animation *animation : animations) {
		delete animation;
	}
	animations.clear();
}

void Sprite::Load(std::string spriteInfoFile) {
	animations.clear();
	hotSpots.clear();
	
	if (spriteInfoFile.substr(spriteInfoFile.find_last_of('.')) != ".spt") {
		throw std::runtime_error("Bad Filetype.  " + spriteInfoFile + " not a sprite info file (.spt)");
	}
	std::ifstream inFile(spriteInfoFile);

	if (inFile.is_open() == false) {
		throw std::runtime_error("Failed to load " + spriteInfoFile);
	}

	std::string text;
	inFile >> text;
	texture.Load(text);
	frameSize = texture.GetSize();

	inFile >> text;
	while (inFile.eof() == false) {
		if (text == "FrameSize") {
			inFile >> frameSize.x;
			inFile >> frameSize.y;
		} else if (text == "Frame") {
			int frameLocationX, frameLocationY;
			inFile >> frameLocationX;
			inFile >> frameLocationY;
			frameTexel.push_back({ frameLocationX, frameLocationY });
		} else if (text == "HotSpot") {
			int hotSpotX, hotSpotY;
			inFile >> hotSpotX;
			inFile >> hotSpotY;
			hotSpots.push_back({ hotSpotX, hotSpotY });
		} else if (text == "Anim") {
			inFile >> text;
			animations.push_back(new Animation(text));
		} else {
			Engine::GetLogger().LogError("Unknown spt command " + text);
		}
		inFile >> text;
	}
	if (frameTexel.empty() == true) {
		frameTexel.push_back({ 0,0 });
	}
	if (animations.empty() == true) {
		animations.push_back(new Animation());
		PlayAnimation(0);
	}
}

void Sprite::AddHotSpot(Vector2DInt position) {
	hotSpots.push_back(position);
}

Vector2DInt Sprite::GetHotSpot(int index) {
	if (index >= static_cast<int>(hotSpots.size())) {
		Engine::GetLogger().LogError("Invalid hotspot index");
		return hotSpots[0];
	}
	return hotSpots[index];
}

void Sprite::PlayAnimation(int anim) {
	if (anim >= static_cast<int>(animations.size())) {
		Engine::GetLogger().LogError("Animation " + std::to_string(anim) + " not found");
		currAnim = 0;
	} else {
		currAnim = anim;
		animations[currAnim]->Reset();
	}
}

int Sprite::GetAnimation() {
	return currAnim;
}

bool Sprite::IsAnimationDone() {
	return animations[currAnim]->IsAnimationDone();
}

void Sprite::Update(double dt) {
	animations[currAnim]->Update(dt);
}

Vector2DInt Sprite::GetFrameSize() const {
	return frameSize;
}

Vector2DInt Sprite::GetFrameTexel(int frameNum) const {
	if (frameNum >= static_cast<int>(frameTexel.size())) {
		Engine::GetLogger().LogError("Bad frame request: " + std::to_string(frameNum));
		return { 0, 0 };
	} else {
		return frameTexel[frameNum];
	}
}

void Sprite::Draw(TransformMatrix displayMatrix) {
	texture.Draw(displayMatrix * TranslateMatrix(-hotSpots[0]), GetFrameTexel(animations[currAnim]->GetDisplayFrame()), GetFrameSize());
}