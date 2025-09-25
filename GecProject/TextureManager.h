#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

class TextureManager
{
public:
	// Creates a method that checks whether the texture has already been loaded, if so it doesn't load it again. If not it attemps to load it.
	sf::Texture& getTexture(const std::string& filename)
	{
		// A check whether the texture hasn't been loaded
		if (textures.find(filename) == textures.end())
		{
			sf::Texture texture;
			if (!texture.loadFromFile(filename))
				std::cout << "Texture " << filename << " could not be loaded!" << std::endl;
			else
				textures[filename] = texture;
		}

		return textures.at(filename); // Returns the texture, either if already loaded, or just loaded
	}
private:
	std::map<std::string, sf::Texture> textures;
};