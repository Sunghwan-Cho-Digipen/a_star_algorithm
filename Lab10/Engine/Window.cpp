/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Window.cpp
Purpose: Source file for Window
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/

#include "doodle/window.hpp"        // doodle stuff
#include "doodle/drawing.hpp"
#include "Engine.h"
#include "Window.h"

void Window::Init(std::string windowName) {
	doodle::create_window(windowName);
	doodle::set_frame_of_reference(doodle::FrameOfReference::RightHanded_OriginBottomLeft);
	doodle::set_image_mode(doodle::RectMode::Corner);
}

void Window::Resize(int newWidth, int newHeight) {
	screenSize.x = newWidth; 
	screenSize.y = newHeight; 
}

Vector2DInt Window::GetSize() {
	return screenSize; 
}

void Window::Clear(Color color) {
	doodle::clear_background(doodle::HexColor { color }); 
}

void Window::Update() {
	doodle::update_window(); 
}

void on_window_resized(int new_width, int new_height) {
	Engine::GetWindow().Resize(new_width, new_height);
}
