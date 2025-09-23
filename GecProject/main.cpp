/*
    GecProject - For GEC students to use as a start point for their projects.
    Already has SFML linked and ImGui set up.
*/

#include "ExternalHeaders.h"
#include "RedirectCout.h"

#include <iostream>
#include <SFML/Graphics.hpp>

void DefineGUI();

float shapeRadius{ 50.f };
float shapeXPos{ 100.f };
float shapeYPos{ 100.f }; 

int main()
{
    // Redirect cout to the Visual Studio output pane
    outbuf ob;
    std::streambuf* sb{ std::cout.rdbuf(&ob) };

    // Redirect cerr
    outbuferr oberr;
    std::streambuf* sberr{ std::cerr.rdbuf(&oberr) };

    // Turn on memory leak checking
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "GEC Start Project");

    // Set up ImGui (the UI library)
    if (!ImGui::SFML::Init(window))
        return -1;

    // Create a simple shape to draw
    sf::CircleShape shape(shapeRadius);
    shape.setFillColor(sf::Color::Green);

    // Create a sprite and apply a texture
    /*sf::Texture texture;
    if (!texture.loadFromFile("Data/Textures/MaleZombie/Attack (1).png"))
    {
        std::cout << "Texture could not be loaded!" << std::endl;
        return -1;
    }

	sf::Sprite sprite(texture);
	sprite.setPosition({ 100.f, 100.f });*/

    // Loading a sprite sheet, then using that to create an animation for a sprite
    sf::Texture zombieAttackSpriteSheet;
    if (!zombieAttackSpriteSheet.loadFromFile("Data/Textures/MaleZombie/attack_combined.png"))
    {
        std::cout << "Texture could not be loaded!" << std::endl;
        return -1;
    }
    sf::Sprite zombieSprite(zombieAttackSpriteSheet);
	zombieSprite.setPosition({ 100.f, 100.f });

	const int frameWidth = 432;  // Width of a single frame
	const int frameHeight = 519; // Height of a single frame

	const int totalFrames = zombieAttackSpriteSheet.getSize().y / frameHeight; // Total number of frames in the sprite sheet
	int currentFrame = 0; // Current frame index

    sf::IntRect frameRect({ 0, 0 }, { frameWidth, frameHeight });

    zombieSprite.setTextureRect(frameRect); // Sets the initial frame

    sf::Clock animClock;


    
    // Clock required by ImGui
    sf::Clock uiDeltaClock;
  
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Feed ImGui
            ImGui::SFML::ProcessEvent(window, event.value());

            // User clicked on window close X
            if (event->is<sf::Event::Closed>())
                window.close();                          
        }

        // ImGui must be updated each frame
        ImGui::SFML::Update(window, uiDeltaClock.restart());

        // The UI gets defined each time
        DefineGUI();
        shape.setPosition({ shapeXPos, shapeYPos });
		shape.setRadius(shapeRadius);

        // Clear the window
        window.clear();
       
        // Draw the shape
        //window.draw(shape);
        //window.draw(sprite);
		window.draw(zombieSprite);

        // UI needs drawing last
        ImGui::SFML::Render(window);

        window.display();
    }

    std::cout << "Finished!" << std::endl;

	ImGui::SFML::Shutdown();

    return 0;
}

/* 
    Use IMGUI for a simple on screen GUI
    See: https://github.com/ocornut/imgui/wiki/
*/
void DefineGUI()
{
    // Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui::Begin("GEC");				// Create a window called "3GP" and append into it.

    ImGui::Text("Some Text.");	      	// Display some text (you can use a format strings too)	

    ImGui::Button("Button");			// Buttons return true when clicked (most widgets return true when edited/activated)
    
 //   ImGui::Checkbox("Wireframe", &m_wireframe);	// A checkbox linked to a member variable

  //  ImGui::Checkbox("Cull Face", &m_cullFace);

    //ImGui::SliderFloat("Shape Radius", &shapeRadius, 10.f, 300.f);	// Slider from 1.0 to 100.0
    //ImGui::SliderFloat("X Position", &shapeXPos, 0.f, 700.f);	// Slider from 0.0 to 1.0
    //ImGui::SliderFloat("Y Position", &shapeYPos, 0.f, 500.f);	// Slider from 0.0 to 1.0

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::End();
}
