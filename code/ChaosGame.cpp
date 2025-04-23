// Paul & Azelya
// 
// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime> 

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	vector<Vector2f> vertices;
	vector<Vector2f> points;

	// Font and text
	Font font;
	if (!font.loadFromFile("KOMIKAP_.ttf")) // load font
	{
		cout << "Unable to load font :(\n";
		return -1;
	}

	Text text; // set text settings
	text.setFont(font);
	text.setString("Welcome to the Chaos Game!");
	text.setCharacterSize(100);
	text.setFillColor(Color::Red);
	text.setPosition(14, 14);
	
	Text text2; // set text (instructions)
	text.setFont(font);
	text.setString("Pick any 3 points. Then pick a 4th point to generate Sierpinski Triangle!");
	text.setCharacterSize(50);
	text.setFillColor(Color::White);
	text.setPosition(20, 20);


	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				// Quit the game when the window is closed
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

					if (vertices.size() < 3)
					{
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
					else if (points.size() == 0)
					{
						if (event.type == sf::Event::MouseButtonPressed) ///fourth click 
						{
							if (event.mouseButton.button == sf::Mouse::Left)
							{
								points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));	///push back to points vector
							}
						}
					}
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/

		if (points.size() > 0)
		{
			while (points.size() < 1000)
			{
				// initialize last point as a temp value
				Vector2f temp = points.back();
				
				// select ran vertex
				int randNum = rand() % 3;
				Vector2f randVert(vertices[randNum].x, vertices[randNum].y);
				
				// cal midpoint	
				float midX = (temp.x + randVert.x) / 2.0;
				float midY = (temp.y + randVert.y) / 2.0;
				Vector2f midpoint(midX, midY);

				// add midpoint to points vector
				points.push_back(midpoint);
				// temp becomes this value
			}
		}

		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		for (unsigned long int i = 0; i < vertices.size(); i++)
		{
			RectangleShape rect(Vector2f(10, 10));
			rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
			rect.setFillColor(Color::Blue);
			window.draw(rect);
		}
		///TODO:  Draw points
		for (unsigned long int i = 0; i < points.size(); i++)
		{
			CircleShape circle(1);
			circle.setRadius(1);
			circle.setPosition(Vector2f(points[i].x, points[i].y));
			circle.setFillColor(Color::Green);
			window.draw(circle);
		}

		// Draw text
		window.draw(text);
		window.display();
	}
}
