#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
using namespace std;
using namespace sf;


int main()
{
	int desktopWidth = VideoMode::getDesktopMode().width;
	int desktopHeight = VideoMode::getDesktopMode().height;
	float aspectRatio = desktopWidth * desktopHeight;
	VideoMode vm(desktopWidth, desktopHeight);
	RenderWindow window(vm, "deez", Style::Default);
	
	ComplexPlane* obj = nullptr;

	Font titleFont;
	titleFont.loadFromFile("fonts/Roboto-Thin.ttf");
	if (!titleFont.loadFromFile("fonts/Roboto-Thin.ttf"))
	{
		window.close();
	}
	Text clickText;
	Text moveText;

	VertexArray vArray(PrimitiveType Points, float aspectRatio);

	enum class States { CALCULATING, DISPLAYING };
	States state = States::CALCULATING;

	Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					Vector2i pixelPos = Mouse::getPosition(window);
					Vector2f clickCoord = window.mapPixelToCoords(pixelPos);
					stringstream ss;
					ss << "Button @ " << Mouse::getPosition(window).x << " " << Mouse::getPosition(window).y << "\n";

					clickText.setFont(titleFont);
					string msg = ss.str();
					clickText.setString(msg);
					clickText.setCharacterSize(80);
					Color color(255, 255, 255);
					clickText.setFillColor(color);

					FloatRect textRect = clickText.getLocalBounds();
					clickText.setOrigin(textRect.left + textRect.width / 2.0, 0);
					clickText.setPosition(window.getSize().x / 2.0, 0);

				}
				if (event.mouseButton.button == Mouse::Right)
				{
					Vector2i pixelPos = Mouse::getPosition(window);
					Vector2f clickCoord = window.mapPixelToCoords(pixelPos);
					stringstream ss;
					ss << "Button @ " << Mouse::getPosition(window).x << " " << Mouse::getPosition(window).y << "\n";

					clickText.setFont(titleFont);
					string msg = ss.str();
					clickText.setString(msg);
					clickText.setCharacterSize(80);
					Color color(255, 255, 255);
					clickText.setFillColor(color);

					FloatRect textRect = clickText.getLocalBounds();
					clickText.setOrigin(textRect.left + textRect.width / 2.0, 0);
					clickText.setPosition(window.getSize().x / 2.0, 0);

					//obj->setCenter(coord);

				}
				state = States::CALCULATING;
			}

			if (event.type == Event::MouseMoved)
			{
				Vector2i pixel = Mouse::getPosition(window);
				Vector2f currCoord = window.mapPixelToCoords(pixel);
				stringstream ss;
				ss << "Current pos @ " << currCoord.x << " " <<  currCoord.y << endl;
				moveText.setFont(titleFont);
				string message = ss.str();
				moveText.setString(message);
				moveText.setCharacterSize(60);
				Color color(255, 255, 255);
				moveText.setFillColor(color);

				FloatRect textRect = moveText.getLocalBounds();
				moveText.setOrigin(textRect.left + textRect.width / 2.0, 0);
				moveText.setPosition(window.getSize().x / 2.0, window.getSize().y / 1.2);

				//obj->setMouseLocation(currCoord);
			}
			
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
		}

		/*if (state == States::CALCULATING)
		{
			for (int i = 0; i < vArray.size(); i++)
			{
				for (int j = 0; j < vArray.size(); i++)
				{
					vArray[j + i * pixelWidth].position = { (float)j,(float)i };
				}
			}
			Vector2i pixel = Mouse::getPosition(window);
			Vector2f currCoord = window.mapPixelToCoords(pixel);


		}
		*/

		window.clear();
		window.draw(clickText);
		window.draw(moveText);
		window.display();
	}
	return 0;
}

