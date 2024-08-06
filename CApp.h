#pragma once

#ifndef CAPP_H
#define CAPP_H

#include <SDL.h>
#include "qbImage.hpp"
#include "scene.hpp"
#include "camera.hpp"

class CApp
{
public:
	CApp();

	int OnExecute();
	bool OnInit();
	void OnEvent(SDL_Event* event);
	void OnLoop();
	void OnRender();
	void OnExit();

private:
	void PrintVector(const qbVector<double>& inputVector);

private:
	// An instance of the qbImage class
	qbImage m_image;

	// An instance of the scene class.
	qbRT::Scene m_scene;

	// SDL
	bool isRunning;
	SDL_Window *pWindow;
	SDL_Renderer *pRenderer;
};


#endif