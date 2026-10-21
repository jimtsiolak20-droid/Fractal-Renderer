#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "lodepng.h"

#include "SdlInitializer.h"
#include "ErrorHandler.h"
#include "MyWindow.h"
#include "MyRenderer.h"
#include "Keymouse.h"
#include "FontText.h"
#include "GameUtilities.h"
#include "Drawable.h"

#include <string>
#include <thread>
#include <vector>

bool MenuScreen(unsigned char& fractal, unsigned char& colouring, unsigned char& colour_mode, MyRenderer* renderer, Keymouse& events)
{
	using GameUtils::SimpleRectClickButton;
	double textsize = 1.0 * 1.0 / renderer->GetWindow()->GetEqualizer();

	int scrollingmandelbrotpos = 2500 * 4;
	Spritesheet scrollingmandelbrot = Spritesheet("..\\textures\\scrolling_mandelbrot.png", renderer, 1111, 1078);

	FontText menufont = FontText("..\\fonts\\GreatVibes_Regular.ttf", renderer, 45);
	
	SDL_Texture* titletext = menufont.RenderText("Red Fractal", { 200, 0, 0, 255 });
	SDL_Texture* versiontext = menufont.RenderText("v1.1.0", { 200, 0, 0, 255 });
	SDL_Texture* mandelbrottext = menufont.RenderText("Mandelbrot Set", { 200, 0, 0, 255 });
	SDL_Texture* burningshiptext = menufont.RenderText("Burning Ship", { 200, 0, 0, 255 });
	SDL_Texture* tricorntext = menufont.RenderText("Tricorn", { 200, 0, 0, 255 });
	SDL_Texture* multibrot3text = menufont.RenderText("Multibrot Order 3", { 200, 0, 0, 255 });
	SDL_Texture* normalcolouringtext = menufont.RenderText("Normal Colouring", { 200, 0, 0, 255 });
	SDL_Texture* candycolouringtext = menufont.RenderText("Candy Colouring", { 200, 0, 0, 255 });
	SDL_Texture* darkcolouringtext = menufont.RenderText("Dark Colouring", { 200, 0, 0, 255 });
	SDL_Texture* saturatedcolouringtext = menufont.RenderText("Saturated Colouring", { 200, 0, 0, 255 });
	SDL_Texture* fragmentedcolouringtext = menufont.RenderText("Fragmented Colouring", { 200, 0, 0, 255 });
	SDL_Texture* controlstext0 = menufont.RenderText("   Mouse                       Navigate menu", { 200, 0, 0, 255 });
	SDL_Texture* controlstext1 = menufont.RenderText("Arrow keys / wasd           Move camera", { 200, 0, 0, 255 });
	SDL_Texture* controlstext2 = menufont.RenderText("    Z                            Zoom in", { 200, 0, 0, 255 });
	SDL_Texture* controlstext3 = menufont.RenderText("    X                           Zoom out", { 200, 0, 0, 255 });
	SDL_Texture* controlstext4 = menufont.RenderText("    P                           Snapshot", { 200, 0, 0, 255 });
	SDL_Texture* controlstext5 = menufont.RenderText("  Escape                       Main menu", { 200, 0, 0, 255 });

	SimpleRectClickButton explorebutton(&menufont, &events, renderer);
	explorebutton.SetText("Explore", { 200, 0, 0, 255 }, textsize);
	explorebutton.SetPosition(960, 400);
	explorebutton.SetDimensions(700, 100);
	explorebutton.SetButtonColours({ 255, 190, 190, 255 }, { 255, 150, 150, 255 });

	SimpleRectClickButton controlsbutton(&menufont, &events, renderer);
	controlsbutton.SetText("Controls", { 200, 0, 0, 255 }, textsize);
	controlsbutton.SetPosition(960, 650);
	controlsbutton.SetDimensions(700, 100);
	controlsbutton.SetButtonColours({ 255, 190, 190, 255 },{ 255, 150, 150, 255 });

	SimpleRectClickButton creditsbutton(&menufont, &events, renderer);
	creditsbutton.SetText("Astonut Entertainment", { 200, 0, 0, 255 }, textsize);
	creditsbutton.SetPosition(960, 800);
	creditsbutton.SetDimensions(700, 100);
	creditsbutton.SetButtonColours({ 255, 190, 190, 255 }, { 255, 150, 150, 255 });

	SimpleRectClickButton quitbutton(&menufont, &events, renderer);
	quitbutton.SetText("Quit", { 200, 0, 0, 255 }, textsize);
	quitbutton.SetPosition(960, 950);
	quitbutton.SetDimensions(700, 100);
	quitbutton.SetButtonColours({ 255, 190, 190, 255 }, { 255, 150, 150, 255 });

	SimpleRectClickButton backbutton(&menufont, &events, renderer);
	backbutton.SetText("Back", { 200, 0, 0, 255 }, textsize);
	backbutton.SetPosition(960, 950);
	backbutton.SetDimensions(700, 100);
	backbutton.SetButtonColours({ 255, 190, 190, 255 }, { 255, 150, 150, 255 });

	SimpleRectClickButton fractalleftbutton(&menufont, &events, renderer);
	fractalleftbutton.SetText("<<", { 200, 0, 0, 255 }, textsize);
	fractalleftbutton.SetPosition(260, 525);
	fractalleftbutton.SetDimensions(90, 50);
	fractalleftbutton.SetButtonColours({ 255, 190, 190, 255 }, { 255, 150, 150, 255 });

	SimpleRectClickButton fractalrightbutton(&menufont, &events, renderer);
	fractalrightbutton.SetText(">>", { 200, 0, 0, 255 }, textsize);
	fractalrightbutton.SetPosition(860, 525);
	fractalrightbutton.SetDimensions(90, 50);
	fractalrightbutton.SetButtonColours({ 255, 190, 190, 255 }, { 255, 150, 150, 255 });

	SimpleRectClickButton colourleftbutton(&menufont, &events, renderer);
	colourleftbutton.SetText("<<", { 200, 0, 0, 255 }, textsize);
	colourleftbutton.SetPosition(1060, 525);
	colourleftbutton.SetDimensions(90, 50);
	colourleftbutton.SetButtonColours({ 255, 190, 190, 255 }, { 255, 150, 150, 255 });

	SimpleRectClickButton colourrightbutton(&menufont, &events, renderer);
	colourrightbutton.SetText(">>", { 200, 0, 0, 255 }, textsize);
	colourrightbutton.SetPosition(1660, 525);
	colourrightbutton.SetDimensions(90, 50);
	colourrightbutton.SetButtonColours({ 255, 190, 190, 255 }, { 255, 150, 150, 255 });

	SimpleRectClickButton eastereggbutton(&menufont, &events, renderer);
	eastereggbutton.SetText("", { 200, 0, 0, 255 }, textsize);
	eastereggbutton.SetPosition(0, 1080);
	eastereggbutton.SetDimensions(40, 40);
	eastereggbutton.SetButtonColours({ 255, 190, 190, 255 }, { 255, 150, 150, 255 });

	static unsigned char fractalstate = 1;
	static unsigned char colouringstate = 1;

	char menustate = 1;
	while (menustate > 0)
	{
		events.Process();

		switch (menustate)
		{
		case 1:
		{
			explorebutton.Update();
			controlsbutton.Update();
			creditsbutton.Update();
			quitbutton.Update();
			fractalleftbutton.Update();
			fractalrightbutton.Update();
			colourleftbutton.Update();
			colourrightbutton.Update();
			eastereggbutton.Update();

			if (fractalleftbutton.GetState() == 2 && fractalstate > 1)
			{
				fractalstate -= 1;
			}

			if (fractalrightbutton.GetState() == 2 && fractalstate < 4)
			{
				fractalstate += 1;
			}

			if (colourleftbutton.GetState() == 2 && colouringstate > 1)
			{
				colouringstate -= 1;
			}

			if (colourrightbutton.GetState() == 2 && colouringstate < 5)
			{
				colouringstate += 1;
			}

			if (explorebutton.GetState() == 2)
			{
				menustate = 0;
			}

			if (controlsbutton.GetState() == 2)
			{
				menustate = 2;
			}

			if (creditsbutton.GetState() == 2)
			{
				if (system(NULL))
				{
					system(std::string("start https://astronut-entertainment.itch.io/").c_str());
				}
			}

			if (quitbutton.GetState() == 2 || events.QuitEvent())
			{
				menustate = -1;
			}

			if (eastereggbutton.GetState() == 2)
			{
				if (system(NULL))
				{
					system(std::string("start https://www.youtube.com/watch?v=dQw4w9WgXcQ").c_str());
				}
			}

			renderer->DrawRect(0, 0, 1920, 1080, { 255, 255, 255, 255 }, false);
			
			scrollingmandelbrot.Draw(0, 0, scrollingmandelbrotpos / 4, 540, 2, true);
			scrollingmandelbrotpos--;
			
			renderer->DrawRect(0, 0, 1920, 1080, { 255, 255, 255, 180 }, false);

			renderer->DrawTexture(titletext, 960, 180, textsize * 3, true);
			renderer->DrawTexture(versiontext, 1500, 300, textsize, true);

			switch (fractalstate)
			{
			case 1:
				renderer->DrawTexture(mandelbrottext, 560, 525, textsize, true);
				break;
			case 2:
				renderer->DrawTexture(burningshiptext, 560, 525, textsize, true);
				break;
			case 3:
				renderer->DrawTexture(tricorntext, 560, 525, textsize, true);
				break;
			case 4:
				renderer->DrawTexture(multibrot3text, 560, 525, textsize, true);
				break;
			}

			switch (colouringstate)
			{
			case 1:
				renderer->DrawTexture(normalcolouringtext, 1360, 525, textsize, true);
				break;
			case 2:
				renderer->DrawTexture(candycolouringtext, 1360, 525, textsize, true);
				break;
			case 3:
				renderer->DrawTexture(darkcolouringtext, 1360, 525, textsize, true);
				break;
			case 4:
				renderer->DrawTexture(saturatedcolouringtext, 1360, 525, textsize, true);
				break;
			case 5:
				renderer->DrawTexture(fragmentedcolouringtext, 1360, 525, textsize, true);
				break;
			}
			
			explorebutton.Render();
			controlsbutton.Render();
			creditsbutton.Render();
			quitbutton.Render();
			eastereggbutton.Render();
			
			if (fractalstate > 1)
			{
				fractalleftbutton.Render();
			}
			
			if (fractalstate < 4)
			{
				fractalrightbutton.Render();
			}

			if (colouringstate > 1)
			{
				colourleftbutton.Render();
			}
			
			if (colouringstate < 5)
			{
				colourrightbutton.Render();
			}
			
			break;
		}
		case 2:
		{
			backbutton.Update();

			if (backbutton.GetState() == 2)
			{
				menustate = 1;
			}

			renderer->DrawRect(0, 0, 1920, 1080, { 255, 255, 255, 255 }, false);

			scrollingmandelbrot.Draw(0, 0, scrollingmandelbrotpos / 4, 540, 2, true);
			scrollingmandelbrotpos--;

			renderer->DrawRect(0, 0, 1920, 1080, { 255, 255, 255, 180 }, false);

			renderer->DrawTexture(controlstext0, 500, 100, textsize, false);
			renderer->DrawTexture(controlstext1, 500, 300, textsize, false);
			renderer->DrawTexture(controlstext2, 500, 400, textsize, false);
			renderer->DrawTexture(controlstext3, 500, 500, textsize, false);
			renderer->DrawTexture(controlstext4, 500, 600, textsize, false);
			renderer->DrawTexture(controlstext5, 500, 700, textsize, false);

			
			backbutton.Render();

			break;
		}
		default:
		{
			break;
		}
		}
		
		renderer->Present();
		renderer->Clear();
		SDL_Delay(20);
	}

	SDL_DestroyTexture(titletext);
	SDL_DestroyTexture(versiontext);
	SDL_DestroyTexture(mandelbrottext);
	SDL_DestroyTexture(burningshiptext);
	SDL_DestroyTexture(tricorntext);
	SDL_DestroyTexture(multibrot3text);
	SDL_DestroyTexture(normalcolouringtext);
	SDL_DestroyTexture(candycolouringtext);
	SDL_DestroyTexture(darkcolouringtext);
	SDL_DestroyTexture(saturatedcolouringtext);
	SDL_DestroyTexture(fragmentedcolouringtext);
	SDL_DestroyTexture(controlstext0);
	SDL_DestroyTexture(controlstext1);
	SDL_DestroyTexture(controlstext2);
	SDL_DestroyTexture(controlstext3);
	SDL_DestroyTexture(controlstext4);
	SDL_DestroyTexture(controlstext5);

	fractal = fractalstate;
	colouring = colouringstate;

	if (menustate == -1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int MandelbrotSet(const long double& x0, const long double& y0, const int& max_iterations)
{
	long double x = 0;
	long double y = 0;
	int iterations = 0;
	while (x * x + y * y <= 4 && iterations < max_iterations)
	{
		long double xtemp = x * x - y * y + x0;
		y = 2 * x * y + y0;
		x = xtemp;
		iterations++;
	}

	return iterations;
}

int BurningShip(const long double& x0, const long double& y0, const int& max_iterations)
{
	long double x = 0;
	long double y = 0;
	int iterations = 0;
	while (x * x + y * y <= 4 && iterations < max_iterations)
	{
		long double xtemp = x * x - y * y + x0;
		y = abs(2 * x * y) - y0;
		x = xtemp;
		iterations++;
	}

	return iterations;
}

int Tricorn(const long double& x0, const long double& y0, const int& max_iterations)
{
	long double x = 0;
	long double y = 0;
	int iterations = 0;
	while (x * x + y * y <= 4 && iterations < max_iterations)
	{
		long double xtemp = x * x - y * y + x0;
		y = -2 * x * y + y0;
		x = xtemp; 
		iterations++;
	}

	return iterations;
}

int Multibrot3(const long double& x0, const long double& y0, const int& max_iterations)
{
	long double x = 0;
	long double y = 0;
	int iterations = 0;
	while (x * x + y * y <= 4 && iterations < max_iterations)
	{
		long double xtemp = x * x * x - 3 * x * y * y + x0;
		y = 3 * x * x * y - y * y * y + y0;
		x = xtemp;
		iterations++;
	}

	return iterations;
}

void ColourNormal(const int& iterations, unsigned char& greenandblue, unsigned char& red)
{
	if (iterations <= 255)
	{
		red = 255;
		greenandblue = 255 - iterations;
	}
	else
	{
		greenandblue = 0;
		red = 510 - iterations;
	}
}

void ColourCandy(const int& iterations, unsigned char& greenandblue, unsigned char& red)
{
	if (iterations % 2 == 1)
	{
		red = 255;
		greenandblue = 200;
	}
	else
	{
		red = 200;
		greenandblue = 0;
	}
}

void ColourDark(const int& iterations, unsigned char& greenandblue, unsigned char& red)
{
	if (iterations <= 255)
	{
		red = iterations;
		greenandblue = iterations / 2;
	}
	else
	{
		red = 255;
		greenandblue = iterations / 2;
	}
}

void ColourSaturated(const int& iterations, unsigned char& greenandblue, unsigned char& red)
{
	if (iterations % 3 == 0)
	{
		red = 0;
		greenandblue = 0;
	}
	else if (iterations % 3 == 1)
	{
		red = 255;
		greenandblue = 255;
	}
	else
	{
		red = 255;
		greenandblue = 0;
	}
}

void ColourFragmented(const int& iterations, unsigned char& greenandblue, unsigned char& red)
{
	if (iterations % 2 == 0)
	{
		red = 255 - iterations / 2;
		greenandblue = 0;
	}
	else
	{
		red = 255;
		greenandblue = 255 - (iterations - 1) / 2;
	}
}

void Snapshot(const char* filepath, const unsigned char& fractal, const unsigned char& colouring, const long double& fractalX, const long double& fractalY, const long double& fractalScale)
{
	int max_iterations = 510;
	double pixel_size = 0.25;
	
	std::vector<unsigned char> image(7680 * 4320 * 4, 0);

	for (int y = 0; y < 4320; y++)
	{
		for (int x = 0; x < 7680; x++)
		{
			long double realx = fractalX - (fractalScale / 2.0L) + ((long double)x) * ((long double)pixel_size * fractalScale / 1920.0L);
			long double realy = fractalY + (fractalScale * 540.0L / 1920.0L) - ((long double)y * ((long double)pixel_size * fractalScale / 1920.0L));

			int iterations = 0;
			switch (fractal)
			{
			case 1:
				iterations = MandelbrotSet(realx, realy, max_iterations);
				break;
			case 2:
				iterations = BurningShip(realx, realy, max_iterations);
				break;
			case 3:
				iterations = Tricorn(realx, realy, max_iterations);
				break;
			case 4:
				iterations = Multibrot3(realx, realy, max_iterations);
				break;
			}

			unsigned char greenandblue = 255;
			unsigned char red = 255;
			switch (colouring)
			{
			case 1:
				ColourNormal(iterations, greenandblue, red);
				break;
			case 2:
				ColourCandy(iterations, greenandblue, red);
				break;
			case 3:
				ColourDark(iterations, greenandblue, red);
				break;
			case 4:
				ColourSaturated(iterations, greenandblue, red);
				break;
			case 5:
				ColourFragmented(iterations, greenandblue, red);
				break;
			}

			image.at((size_t)y * 7680 * 4 + (size_t)x * 4 + 0) = red;
			image.at((size_t)y * 7680 * 4 + (size_t)x * 4 + 1) = greenandblue;
			image.at((size_t)y * 7680 * 4 + (size_t)x * 4 + 2) = red;
			image.at((size_t)y * 7680 * 4 + (size_t)x * 4 + 3) = 255;
		}
	}

	lodepng::encode(filepath, image, 7680, 4320);
}

void DrawFractalMultithreaded(MyRenderer* renderer, const unsigned char& fractal, const unsigned char& colouring, const long double& fractalX, const long double& fractalY, const long double& fractalScale)
{
	int max_iterations = 510;
	int pixel_size = 1;

	int(*fractal_func)(const long double&, const long double&, const int&) = nullptr;
	void(*colour_func)(const int&, unsigned char&, unsigned char&) = nullptr;

	switch (fractal)
	{
	case 1:
		fractal_func = MandelbrotSet;
		break;
	case 2:
		fractal_func = BurningShip;
		break;
	case 3:
		fractal_func = Tricorn;
		break;
	case 4:
		fractal_func = Multibrot3;
		break;
	}

	switch (colouring)
	{
	case 1:
		colour_func = ColourNormal;
		break;
	case 2:
		colour_func = ColourCandy;
		break;
	case 3:
		colour_func = ColourDark;
		break;
	case 4:
		colour_func = ColourSaturated;
		break;
	case 5:
		colour_func = ColourFragmented;
		break;
	}

	unsigned short int* pixeldata0 = new unsigned short int[259200];
	unsigned short int* pixeldata1 = new unsigned short int[259200];
	unsigned short int* pixeldata2 = new unsigned short int[259200];
	unsigned short int* pixeldata3 = new unsigned short int[259200];
	unsigned short int* pixeldata4 = new unsigned short int[259200];
	unsigned short int* pixeldata5 = new unsigned short int[259200];
	unsigned short int* pixeldata6 = new unsigned short int[259200];
	unsigned short int* pixeldata7 = new unsigned short int[259200]; 

	std::thread thread0([&]() {
		for (int y = 0; y < 135; y++)
		{
			for (int x = 0; x < 1920; x++)
			{
				long double realx = fractalX - (fractalScale / 2.0L) + ((long double)x) * ((long double)pixel_size * fractalScale / 1920.0L);
				long double realy = fractalY + (fractalScale * 540.0L / 1920.0L) - ((long double)(y + (long double)0 * 135) * ((long double)pixel_size * fractalScale / 1920.0L));

				pixeldata0[x + y * 1920] = (unsigned short int)fractal_func(realx, realy, max_iterations);
			}
		}
		});

	std::thread thread1([&]() {
		for (int y = 0; y < 135; y++)
		{
			for (int x = 0; x < 1920; x++)
			{
				long double realx = fractalX - (fractalScale / 2.0L) + ((long double)x) * ((long double)pixel_size * fractalScale / 1920.0L);
				long double realy = fractalY + (fractalScale * 540.0L / 1920.0L) - ((long double)(y + (long double)1 * 135) * ((long double)pixel_size * fractalScale / 1920.0L));

				pixeldata1[x + y * 1920] = (unsigned short int)fractal_func(realx, realy, max_iterations);
			}
		}
		});

	std::thread thread2([&]() {
		for (int y = 0; y < 135; y++)
		{
			for (int x = 0; x < 1920; x++)
			{
				long double realx = fractalX - (fractalScale / 2.0L) + ((long double)x) * ((long double)pixel_size * fractalScale / 1920.0L);
				long double realy = fractalY + (fractalScale * 540.0L / 1920.0L) - ((long double)(y + (long double)2 * 135) * ((long double)pixel_size * fractalScale / 1920.0L));

				pixeldata2[x + y * 1920] = (unsigned short int)fractal_func(realx, realy, max_iterations);
			}
		}
		});

	std::thread thread3([&]() {
		for (int y = 0; y < 135; y++)
		{
			for (int x = 0; x < 1920; x++)
			{
				long double realx = fractalX - (fractalScale / 2.0L) + ((long double)x) * ((long double)pixel_size * fractalScale / 1920.0L);
				long double realy = fractalY + (fractalScale * 540.0L / 1920.0L) - ((long double)(y + (long double)3 * 135) * ((long double)pixel_size * fractalScale / 1920.0L));

				pixeldata3[x + y * 1920] = (unsigned short int)fractal_func(realx, realy, max_iterations);
			}
		}
		});

	std::thread thread4([&]() {
		for (int y = 0; y < 135; y++)
		{
			for (int x = 0; x < 1920; x++)
			{
				long double realx = fractalX - (fractalScale / 2.0L) + ((long double)x) * ((long double)pixel_size * fractalScale / 1920.0L);
				long double realy = fractalY + (fractalScale * 540.0L / 1920.0L) - ((long double)(y + (long double)4 * 135) * ((long double)pixel_size * fractalScale / 1920.0L));

				pixeldata4[x + y * 1920] = (unsigned short int)fractal_func(realx, realy, max_iterations);
			}
		}
		});

	std::thread thread5([&]() {
		for (int y = 0; y < 135; y++)
		{
			for (int x = 0; x < 1920; x++)
			{
				long double realx = fractalX - (fractalScale / 2.0L) + ((long double)x) * ((long double)pixel_size * fractalScale / 1920.0L);
				long double realy = fractalY + (fractalScale * 540.0L / 1920.0L) - ((long double)(y + (long double)5 * 135) * ((long double)pixel_size * fractalScale / 1920.0L));

				pixeldata5[x + y * 1920] = (unsigned short int)fractal_func(realx, realy, max_iterations);
			}
		}
		});

	std::thread thread6([&]() {
		for (int y = 0; y < 135; y++)
		{
			for (int x = 0; x < 1920; x++)
			{
				long double realx = fractalX - (fractalScale / 2.0L) + ((long double)x) * ((long double)pixel_size * fractalScale / 1920.0L);
				long double realy = fractalY + (fractalScale * 540.0L / 1920.0L) - ((long double)(y + (long double)6 * 135) * ((long double)pixel_size * fractalScale / 1920.0L));

				pixeldata6[x + y * 1920] = (unsigned short int)fractal_func(realx, realy, max_iterations);
			}
		}
		});

	std::thread thread7([&]() {
		for (int y = 0; y < 135; y++)
		{
			for (int x = 0; x < 1920; x++)
			{
				long double realx = fractalX - (fractalScale / 2.0L) + ((long double)x) * ((long double)pixel_size * fractalScale / 1920.0L);
				long double realy = fractalY + (fractalScale * 540.0L / 1920.0L) - ((long double)(y + (long double)7 * 135) * ((long double)pixel_size * fractalScale / 1920.0L));

				pixeldata7[x + y * 1920] = (unsigned short int)fractal_func(realx, realy, max_iterations);
			}
		}
		});

	thread0.join();
	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();
	thread5.join();
	thread6.join();
	thread7.join();

	//array 0
	for (int y = 0; y < 135; y++)
	{
		for (int x = 0; x < 1920; x++)
		{
			unsigned char greenandblue;
			unsigned char red;

			colour_func((int)pixeldata0[x + y * 1920], greenandblue, red);

			renderer->DrawRect(x * pixel_size, (y + 0 * 135) * pixel_size, pixel_size + 1, pixel_size + 1, { red, greenandblue, greenandblue, 255 }, false);
		}
	}

	//array 1
	for (int y = 0; y < 135; y++)
	{
		for (int x = 0; x < 1920; x++)
		{
			unsigned char greenandblue;
			unsigned char red;

			colour_func((int)pixeldata1[x + y * 1920], greenandblue, red);

			renderer->DrawRect(x * pixel_size, (y + 1 * 135) * pixel_size, pixel_size + 1, pixel_size + 1, { red, greenandblue, greenandblue, 255 }, false);
		}
	}

	//array 2
	for (int y = 0; y < 135; y++)
	{
		for (int x = 0; x < 1920; x++)
		{
			unsigned char greenandblue;
			unsigned char red;

			colour_func((int)pixeldata2[x + y * 1920], greenandblue, red);

			renderer->DrawRect(x * pixel_size, (y + 2 * 135) * pixel_size, pixel_size + 1, pixel_size + 1, { red, greenandblue, greenandblue, 255 }, false);
		}
	}

	//array 3
	for (int y = 0; y < 135; y++)
	{
		for (int x = 0; x < 1920; x++)
		{
			unsigned char greenandblue;
			unsigned char red;

			colour_func((int)pixeldata3[x + y * 1920], greenandblue, red);

			renderer->DrawRect(x * pixel_size, (y + 3 * 135) * pixel_size, pixel_size + 1, pixel_size + 1, { red, greenandblue, greenandblue, 255 }, false);
		}
	}

	//array 4
	for (int y = 0; y < 135; y++)
	{
		for (int x = 0; x < 1920; x++)
		{
			unsigned char greenandblue;
			unsigned char red;

			colour_func((int)pixeldata4[x + y * 1920], greenandblue, red);

			renderer->DrawRect(x * pixel_size, (y + 4 * 135) * pixel_size, pixel_size + 1, pixel_size + 1, { red, greenandblue, greenandblue, 255 }, false);
		}
	}

	//array 5
	for (int y = 0; y < 135; y++)
	{
		for (int x = 0; x < 1920; x++)
		{
			unsigned char greenandblue;
			unsigned char red;

			colour_func((int)pixeldata5[x + y * 1920], greenandblue, red);

			renderer->DrawRect(x * pixel_size, (y + 5 * 135) * pixel_size, pixel_size + 1, pixel_size + 1, { red, greenandblue, greenandblue, 255 }, false);
		}
	}

	//array 6
	for (int y = 0; y < 135; y++)
	{
		for (int x = 0; x < 1920; x++)
		{
			unsigned char greenandblue;
			unsigned char red;

			colour_func((int)pixeldata6[x + y * 1920], greenandblue, red);

			renderer->DrawRect(x * pixel_size, (y + 6 * 135) * pixel_size, pixel_size + 1, pixel_size + 1, { red, greenandblue, greenandblue, 255 }, false);
		}
	}

	//array 7
	for (int y = 0; y < 135; y++)
	{
		for (int x = 0; x < 1920; x++)
		{
			unsigned char greenandblue;
			unsigned char red;

			colour_func((int)pixeldata7[x + y * 1920], greenandblue, red);

			renderer->DrawRect(x * pixel_size, (y + 7 * 135) * pixel_size, pixel_size + 1, pixel_size + 1, { red, greenandblue, greenandblue, 255 }, false);
		}
	}

	delete[] pixeldata0;
	delete[] pixeldata1;
	delete[] pixeldata2;
	delete[] pixeldata3;
	delete[] pixeldata4;
	delete[] pixeldata5;
	delete[] pixeldata6;
	delete[] pixeldata7;
}

void DrawFractal(MyRenderer* renderer, const unsigned char& fractal, const unsigned char& colouring, const unsigned char& quality, const long double& fractalX, const long double& fractalY, const long double& fractalScale)
{
	int max_iterations;
	int pixel_size;

	switch (quality)
	{
	case 1:
	{
		max_iterations = 510;
		pixel_size = 8;
		break;
	}
	case 2:
	{
		max_iterations = 510;
		pixel_size = 4;
		break;
	}

	case 3:
	{
		max_iterations = 510;
		pixel_size = 2;
		break;
	}
	case 4:
	{
		max_iterations = 510;
		pixel_size = 1;
		break;
	}
	default:
	{
		max_iterations = 510;
		pixel_size = 8;
		break;
	}
	}

	for (int y = 0; y < 1080 / pixel_size; y++)
	{
		for (int x = 0; x < 1920 / pixel_size; x++)
		{
			long double realx = fractalX - (fractalScale / 2.0L) + ((long double)x) * ((long double)pixel_size * fractalScale / 1920.0L);
			long double realy = fractalY + (fractalScale * 540.0L / 1920.0L) - ((long double)y * ((long double)pixel_size * fractalScale / 1920.0L));

			int iterations = 0;
			switch (fractal)
			{
			case 1:
				iterations = MandelbrotSet(realx, realy, max_iterations);
				break;
			case 2:
				iterations = BurningShip(realx, realy, max_iterations);
				break;
			case 3:
				iterations = Tricorn(realx, realy, max_iterations);
				break;
			case 4:
				iterations = Multibrot3(realx, realy, max_iterations);
				break;
			}

			unsigned char greenandblue = 255;
			unsigned char red = 255;
			switch (colouring)
			{
			case 1:
				ColourNormal(iterations, greenandblue, red);
				break;
			case 2:
				ColourCandy(iterations, greenandblue, red);
				break;
			case 3:
				ColourDark(iterations, greenandblue, red);
				break;
			case 4:
				ColourSaturated(iterations, greenandblue, red);
				break;
			case 5:
				ColourFragmented(iterations, greenandblue, red);
				break;
			}

			renderer->DrawRect(x * pixel_size, y * pixel_size, pixel_size + 1, pixel_size + 1, { red, greenandblue, greenandblue, 255 }, false);
		}
	}
}

int main(int argc, char* args[])
{
	SdlInitializer::SdlInit();

	MyWindow window = MyWindow();
	window.Initialize("Red Fractal 1.1.0", 1920, 1080);

	MyRenderer renderer = MyRenderer();
	renderer.Initialize(&window);

	Keymouse events = Keymouse(&window);

	unsigned char fractal = 0;
	unsigned char colouring = 0;
	unsigned char colour_mode = 0;

	srand(time(nullptr));

	while (MenuScreen(fractal, colouring, colour_mode, &renderer, events))
	{
		long double fractalX = 0;
		long double fractalY = 0;
		long double fractalScale = 4;
		
		int quality = 1;
		while (true)
		{
			if (quality < 3)
			{
				DrawFractal(&renderer, fractal, colouring, quality, fractalX, -fractalY, fractalScale);
				renderer.Present();
				renderer.Clear();
				quality++;
			}
			else if (quality < 4)
			{
				DrawFractalMultithreaded(&renderer, fractal, colouring, fractalX, -fractalY, fractalScale);
				renderer.Present();
				renderer.Clear();
				quality++;
			}
			else
			{
				SDL_Delay(100);
			}

			events.Process();
			if (events.KeyPressed(SDLK_LEFT) || events.KeyPressed(SDLK_a))
			{
				fractalX -= 0.005L * fractalScale;
				quality = 1;
			}
			if (events.KeyPressed(SDLK_RIGHT) || events.KeyPressed(SDLK_d))
			{
				fractalX += 0.005L * fractalScale;
				quality = 1;
			}
			if (events.KeyPressed(SDLK_UP) || events.KeyPressed(SDLK_w))
			{
				fractalY -= 0.005L * fractalScale;
				quality = 1;
			}
			if (events.KeyPressed(SDLK_DOWN) || events.KeyPressed(SDLK_s))
			{
				fractalY += 0.005L * fractalScale;
				quality = 1;
			}
			if (events.KeyPressed(SDLK_z))
			{
				fractalScale *= 0.98L;
				quality = 1;
			}
			if (events.KeyPressed(SDLK_x))
			{
				fractalScale /= 0.98L;
				quality = 1;
			}
			if (events.KeyPressed(SDLK_ESCAPE))
			{
				break;
			}
			if (events.KeyPressed(SDLK_p))
			{
				DrawFractal(&renderer, fractal, colouring, 1, fractalX, -fractalY, fractalScale);
				renderer.DrawRect(0, 0, 1920, 50, { 255, 0, 0, 255 }, false);
				renderer.DrawRect(0, 0, 50, 1080, { 255, 0, 0, 255 }, false);
				renderer.DrawRect(0, 1080 - 50, 1920, 70, { 255, 0, 0, 255 }, false);
				renderer.DrawRect(1920 - 50, 0, 70, 1080, { 255, 0, 0, 255 }, false);
				renderer.Present();
				renderer.Clear();

				std::string filepath = "..\\snapshots\\fractal_snapshot" + std::to_string(rand()) + ".png";
				Snapshot(filepath.c_str(), fractal, colouring, fractalX, -fractalY, fractalScale);

				quality = 1;
			}
			if (events.QuitEvent())
			{
				SdlInitializer::SdlQuit();
				exit(-1);
			}
		}
	}

	SdlInitializer::SdlQuit();
	return 0;
}