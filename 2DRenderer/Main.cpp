#include "Renderer.h"
#include "Framebuffer.h"
#include "Image.h"

#include <iostream>
#include <SDL.h>

int main(int, char**)
{
	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);

	std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(), renderer->width, renderer->height);
	
	std::unique_ptr<Image> image = std::make_unique<Image>();
	image->Load("../resources/cat.bmp");
	image->Flip();

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		framebuffer->Clear({ 0, 0, 0, 0 });

		for (int i = 0; i < 100; i++)
		{
			framebuffer->DrawPoint(rand() % framebuffer->width, rand() % framebuffer->height, {0, 255, 0, 0});
		}
		for (int i = 0; i < 20; i++)
		{
			framebuffer->DrawRect(rand() % framebuffer->width, rand() % framebuffer->height, 20, 20, { 0, 0, 255, 0 });
		}
		for (int i = 0; i < 20; i++)
		{
			framebuffer->DrawLine(framebuffer->width >> 1, framebuffer->height >> 1, rand() % framebuffer->width, rand() % framebuffer->height, { 255, 255, 255, 0 });
		}

		for (int i = 0; i < 10; i++)
		{
			framebuffer->DrawQuadraticCurve(
				rand() % framebuffer->width, rand() % framebuffer->height, 
				rand() % framebuffer->width, rand() % framebuffer->height, 
				rand() % framebuffer->width, rand() % framebuffer->height, 30, { 255, 255, 0, 255 });
		}
		for (int i = 0; i < 10; i++)
		{
			framebuffer->DrawCubicCurve(
				rand() % framebuffer->width, rand() % framebuffer->height,
				rand() % framebuffer->width, rand() % framebuffer->height,
				rand() % framebuffer->width, rand() % framebuffer->height, 
				rand() % framebuffer->width, rand() % framebuffer->height,
				30, { 0, 255, 255, 255 });
		}

		//framebuffer->DrawSimpleCurve(200, 200, 300, 100, 3, { 255, 255, 255, 255 });
		//framebuffer->DrawQuadraticCurve(200, 200, 300, 100, 400, 200, 15, { 255, 255, 255, 255 });
		//framebuffer->DrawCubicCurve(200, 200, 300, 100, 400, 100, 500, 200, 15, { 255, 255, 255, 255 });

		framebuffer->DrawImage(30, 30, image.get());

		framebuffer->Update();

		renderer->CopyBuffer(framebuffer.get());
		renderer->Present();
	}

	SDL_Quit();

	return 0;
}
