/*
    GecProject - For GEC students to use as a start point for their projects.
    Already has SFML linked and ImGui set up.
*/

#include "ExternalHeaders.h"
#include "RedirectCout.h"

#include "TextureManager.h"
#include "AnimationManager.h"
#include "SpriteAnimator.h"

#include <iostream>
#include <SFML/Graphics.hpp>

void DefineGUI();

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

    // Animation Logic
    TextureManager textureManager;
    AnimationManager animationManager(textureManager);

    // Zombie Idle Animation Setup
    animationManager.configureAnimation("zombieIdle", "Data/Textures/MaleZombie/idle_combined.png", 15);
    SpriteAnimator zombie(animationManager.getAnimation("zombieIdle")); // Defaults to Idle Animation
    zombie.setAnimation(animationManager.getAnimation("zombieIdle"));

    // Zombie Attack Animation Setup
    animationManager.configureAnimation("zombieAttack", "Data/Textures/MaleZombie/attack_combined.png", 8);
    zombie.setAnimation(animationManager.getAnimation("zombieAttack"));

	// Zombie Death Animation Setup
    animationManager.configureAnimation("zombieDeath", "Data/Textures/MaleZombie/dead_combined.png", 12);
    zombie.setAnimation(animationManager.getAnimation("zombieDeath"));

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

        zombie.update();

        // Clear the window
        window.clear();
       
		window.draw(zombie);

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

    ImGui::Begin("GEC"); // Create a window called "3GP" and append into it.

    //ImGui::Text("Some Text."); // Display some text (you can use a format strings too)	

    //ImGui::Button("Button"); // Buttons return true when clicked (most widgets return true when edited/activated)
    
    //ImGui::Checkbox("Wireframe", &m_wireframe); // A checkbox linked to a member variable

    //ImGui::Checkbox("Cull Face", &m_cullFace);

    //ImGui::SliderFloat("Animation Speed", animationSpeed, 0.01f, 1.f);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::End();
}