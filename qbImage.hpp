#ifndef QBIMAGE_H
#define QBIMAGE_H

#include <string>
#include <vector>
#include <SDL.h>

class qbImage
{

public:

	// The constructor.
	qbImage();

	// The destructor.
	~qbImage();

	// Function to initialize
	void Initialize(const int xSize, const int ySize, SDL_Renderer* pRenderer);

	// Function to set the color of a pixel.
	void SetPixel(const int x, const int y, const double red, const double green, const double blue);

	// Function to return the image for display.
	void Display();

	// Functions to return the dimensions of the image.
	int GetXSize();
	int GetYSize();

private:
	Uint32 ConvertColor(const double red, const double green, const double blue);
	void InitTexture();
	void ComputeMaxValues();

private:
	// Arrays to store the image data. 
	std::vector<std::vector<double>> m_rChannel;
	std::vector<std::vector<double>> m_gChannel;
	std::vector<std::vector<double>> m_bChannel;

	// Store the dimensions of the image. 
	int m_xSize, m_ySize;

	// Store the maximum values.
	double m_maxRed, m_maxGreen, m_maxBlue, m_overallMax;

	// SDL
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;


};

#endif


