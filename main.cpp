#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
using namespace std;
using namespace sf;


int main()
{
	float desktopWidth = VideoMode::getDesktopMode().width;
	float desktopHeight = VideoMode::getDesktopMode().height;
	float aspectRatio = desktopHeight / desktopWidth;
	VideoMode vm(desktopWidth, desktopHeight);
	RenderWindow window(vm, "Mandelbrot", Style::Default);

	ComplexPlane screen(aspectRatio);

	Font textFont;
	if (!textFont.loadFromFile("fonts/Roboto-Thin.ttf"))
	{
		window.close();
	}

	Text viewAndMouse;
	viewAndMouse.setFont(textFont);
	Color color(255, 255, 255);
	viewAndMouse.setFillColor(color);
	viewAndMouse.setCharacterSize(50);

	VertexArray vArray;
	vArray.setPrimitiveType(Points);
	vArray.resize(desktopWidth * desktopHeight);

	enum class States { CALCULATING, DISPLAYING };
	States state = States::CALCULATING;

	Event event;

	// ::-Main Loop Start-:: //

	while (window.isOpen())
	{
		// ::-Input Segment-:: //

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::MouseButtonPressed)
			{
				Vector2f clickCoord = window.mapPixelToCoords(Mouse::getPosition(),
					screen.getView());

				if (event.mouseButton.button == Mouse::Left)
				{
					screen.zoomIn();
					screen.setCenter(clickCoord);
				}
				if (event.mouseButton.button == Mouse::Right)
				{
					screen.zoomOut();
					screen.setCenter(clickCoord);
				}
				state = States::CALCULATING;
			}

			if (event.type == Event::MouseMoved)
			{
				Vector2f mouseCoord = window.mapPixelToCoords(Mouse::getPosition(),
					screen.getView());

				screen.setMouseLocation(mouseCoord);
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
		} // End input segment

		// ::-Update Segment-:: //

		if (state == States::DISPLAYING)
		{
			screen.loadText(viewAndMouse);
		}

		if (state == States::CALCULATING)
		{
			for (int i = 0; i < desktopHeight; i++)
			{
				for (int j = 0; j < desktopWidth; j++)
				{
					vArray[j + i * desktopWidth].position = { float(j), float(i) };
					Vector2f iterCoord = window.mapPixelToCoords(Vector2i(j, i),
						screen.getView());
					size_t count = screen.countIterations(iterCoord);
					Uint8 r = 0;
					Uint8 g = 0;
					Uint8 b = 0;
					screen.iterationsToRGB(count, r, g, b);
					vArray[j + i * desktopWidth].color = { r, g, b };
				}
			}
			state = States::DISPLAYING;
		} // End update segment

		// ::-Draw Segment-:: //
		window.clear();
		window.draw(vArray);
		window.draw(viewAndMouse);
		window.display();
	}
	return 0;
}