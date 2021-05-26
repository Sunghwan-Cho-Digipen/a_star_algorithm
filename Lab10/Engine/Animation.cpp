/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Animation.h
Purpose: Source file for Animation Module
Project: CS230
Author: Kevin Wright
Creation date: 3/15/2020
-----------------------------------------------------------------*/
#include <fstream>	// file input stuff

#include "Engine.h"	// Engine::
#include "Animation.h"

Animation::Animation() : Animation("assets/none.anm")  { }

Animation::Animation(std::string fileName) : animSequenceIndex(0) {
	std::ifstream inFile(fileName);
	std::string label;

	if (fileName.substr(fileName.find_last_of('.')) != ".anm") {
		throw std::runtime_error("Bad Filetype.  " + fileName + " not a sprite info file (.anm)");
	}
	if (inFile.is_open() == false) {
		throw std::runtime_error("Failed to load " + fileName);
	}

	while (inFile.eof() == false) {
		inFile >> label;
		if (label == "PlayFrame") {
			int frame;
			float targetTime;
			inFile >> frame;
			inFile >> targetTime;

			animation.push_back(new PlayFrame(frame, targetTime));
		} else if (label == "Loop") {
			int loopToIndex;
			inFile >> loopToIndex;
			animation.push_back(new Loop(loopToIndex));
		} else if (label == "End") {
			animation.push_back(new End());
		} else {
			Engine::GetLogger().LogError("Unknown command " + label + " in anm file " + fileName);
		}
	}
	Reset();
}

void Animation::Update(double dt) {
	currPlayFrameData->Update(dt);
	if (currPlayFrameData->IsFrameDone() == true) {
		currPlayFrameData->Reset();
		++animSequenceIndex;
		if (animation[animSequenceIndex]->GetType() == Command::PlayFrame) {
			currPlayFrameData = static_cast<PlayFrame*>(animation[animSequenceIndex]);
		} else if (animation[animSequenceIndex]->GetType() == Command::Loop) {
			Loop *loopData = static_cast<Loop*>(animation[animSequenceIndex]);
			animSequenceIndex = loopData->GetLoopToIndex();
			if (animation[animSequenceIndex]->GetType() == Command::PlayFrame) {
				currPlayFrameData = static_cast<PlayFrame*>(animation[animSequenceIndex]);
			} else {
				Engine::GetLogger().LogError("Loop does not go to PlayFrame");
				Reset();
			} 
		} else if (animation[animSequenceIndex]->GetType() == Command::End) {
			isAnimationDone = true;
			return;
		}
	}
}

Animation::~Animation() {
	for (CommandData *command : animation) {
		delete command;
	}
	animation.clear();
}

int Animation::GetDisplayFrame() {
	return currPlayFrameData->GetFrameNum();
}

void Animation::Reset() {
	animSequenceIndex = 0;
	currPlayFrameData = static_cast<PlayFrame*>(animation[animSequenceIndex]);
	isAnimationDone = false;
}

bool Animation::IsAnimationDone() {
	return isAnimationDone;
}

Animation::PlayFrame::PlayFrame(int frame, double targetTime) : frame(frame), targetTime(targetTime), timer(0) {}
void Animation::PlayFrame::Update(double dt) { timer += dt; }
bool Animation::PlayFrame::IsFrameDone() { return timer >= targetTime; }
void Animation::PlayFrame::Reset() { timer = 0; }
int Animation::PlayFrame::GetFrameNum() { return frame; }

Animation::Loop::Loop(int loopToIndex) : loopToIndex(loopToIndex) {}
int Animation::Loop::GetLoopToIndex() {return loopToIndex; }
