#pragma once
#include "AnimationManager.h"
#include <SFML/Graphics.hpp>

class SpriteAnimator : public sf::Sprite
{
public:
    void setAnimation(const Animation& animation)
    {
        m_animation = &animation;
        this->setTexture(*m_animation->texture);
        m_currentFrame = 0;
        m_animClock.restart();
    }

	void update()
	{
        if (m_animation == nullptr)
            return;

        // After the set time, updates to the next sprite
        if (m_animClock.getElapsedTime().asSeconds() > m_animation->timeBetweenFrames)
        {
            m_currentFrame++;

            // If reached the last frame, loops back around
            if (m_currentFrame >= m_animation->numFrames)
            {
                m_currentFrame = 0;
            }

            int intRectsYPos = m_currentFrame * m_animation->spriteHeight;

            this->setTextureRect(sf::IntRect({ 0, intRectsYPos }, { m_animation->spriteWidth, m_animation->spriteHeight }));

            m_animClock.restart();
        }
	}
private:
	sf::Clock m_animClock;
    const Animation* m_animation{ nullptr };
    int m_currentFrame{ 0 };
};