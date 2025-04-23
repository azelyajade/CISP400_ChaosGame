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

std::string colorToString(Color& color)
{
	if (color == Color::Red) return "Red";
	if (color == Color::Green) return "Green";
	if (color == Color::Blue) return "Blue";
	if (color == Color::Yellow) return "Yellow";
}
int main()
{
// +=============================================+
// |		INITIALIZE VARIABLES		 |
// +=============================================+
// 
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
	text.setCharacterSize(50);
	text.setFillColor(Color::Green);
	text.setPosition(14, 14);

	Text prompt;
	prompt.setFont(font);
	prompt.setString("Press 'SPACE' to continue...");
	prompt.setCharacterSize(25);
	prompt.setFillColor(Color::Green);

	FloatRect promptBounds = prompt.getLocalBounds();
	prompt.setOrigin(0, promptBounds.height);
	prompt.setPosition(10, window.getSize().y - 10);

	// -----------------------------------------
	//		Menu Handling
	// -----------------------------------------
		Text menu_1;
		menu_1.setFont(font);
		menu_1.setString("1. Red");
		menu_1.setCharacterSize(30);
		menu_1.setFillColor(Color::Red);
		menu_1.setPosition(14, 100);

		Text menu_2;
		menu_2.setFont(font);
		menu_2.setString("2. Green");
		menu_2.setCharacterSize(30);
		menu_2.setFillColor(Color::Green);
		menu_2.setPosition(14, 150);

		Text menu_3;
		menu_3.setFont(font);
		menu_3.setString("3. Blue");
		menu_3.setCharacterSize(30);
		menu_3.setFillColor(Color::Blue);
		menu_3.setPosition(14, 200);

		Text menu_4;
		menu_4.setFont(font);
		menu_4.setString("4. Yellow");
		menu_4.setCharacterSize(30);
		menu_4.setFillColor(Color::Yellow);
		menu_4.setPosition(14, 250);
	// -----------------------------------------

	const int pointsPerFrame = 1; // Constant for num of points we wanna draw each frame
	bool showMenu = false;
	Color colorChoice;


// +=====================================+
// |		GAME LOOP		 |
// +=====================================+
//
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

			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				std::cout << "spacebar was pressed" << std::endl;
				text.setString("Choose a color: ");
				prompt.setString("");
				showMenu = true;
			}

			if (showMenu && event.type == Event::KeyPressed) // Menu logic
			{
				if (event.key.code == Keyboard::Num1) { colorChoice = Color::Red; } // Choice red
				else if (event.key.code == Keyboard::Num2) { colorChoice = Color::Green; } // Choice green
				else if (event.key.code == Keyboard::Num3) { colorChoice = Color::Blue; } // Choice blue
				else if (event.key.code == Keyboard::Num4) { colorChoice = Color::Yellow; } // Choice yellow

				if (event.key.code >= Keyboard::Num1 && event.key.code <= Keyboard::Num4)
				{
					showMenu = false;

					prompt.setFillColor(colorChoice);
					prompt.setString(colorToString(colorChoice) + " was selected");
					text.setFillColor(colorChoice);
					text.setString("Click 3 points to make a triangle.");
				}
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				std::cout << "the left button was pressed" << std::endl;
				std::cout << "mouse x: " << event.mouseButton.x << std::endl;
				std::cout << "mouse y: " << event.mouseButton.y << std::endl;

				if (vertices.size() < 3)
				{
					vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					prompt.setString("");
					if (vertices.size() == 3)
					{
						text.setString("Now, click anywhere to make a starting point!");
					}
				}
				else if (points.size() == 0)
				{
					if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) ///fourth click 
					{
						text.setString("WOAAAAAAAHHHHHHHHHHHHH!!!!");
						points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));	///push back to points vector
					}
				}
			}

			if (points.size() == 1000)
			{
				prompt.setFillColor(Color::Green);
				prompt.setString("Nice! Press 'R' to restart...");

				if (Keyboard::isKeyPressed(Keyboard::R))
				{
					points.clear();
					vertices.clear();
					window.clear();
					text.setString("Press 'SPACE' to choose a color");
					prompt.setString("");
					showMenu = false;
					text.setFillColor(Color::Green);
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

		if (points.size() > 0 && points.size() < 1000) // Hard limit of 1000 points
		{
			for (int i = 0; i < pointsPerFrame; i++) // Each loop, we only store a few points per frame of runtime (pointsPerFrame)
			{
				// initialize last point as a temp value
				Vector2f temp = points.back();
				
				// select ran vertex
				int randNum = rand() % 3;
				Vector2f randVert(vertices[randNum].x, vertices[randNum].y);
				
				// call midpoint	
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
			circle.setFillColor(colorChoice);
			window.draw(circle);
			
		}


		window.draw(text);
		window.draw(prompt);

		if (showMenu)
		{
			window.draw(menu_1);
			window.draw(menu_2);
			window.draw(menu_3);
			window.draw(menu_4);
		}

		window.display();
	}
}
