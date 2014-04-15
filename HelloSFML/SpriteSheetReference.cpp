//#include <SFML/Graphics.hpp>
//#include "AnimatedSprite.hpp"
//#include <iostream>
//
//int main()
//{
//	// setup window
//	sf::Vector2i screenDimensions(800, 600);
//	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Animations!");
//	window.setFramerateLimit(60);
//
//	// load texture (spritesheet)
//	sf::Texture texture;
//	if (!texture.loadFromFile("player.png"))
//	{
//		std::cout << "Failed to load player spritesheet!" << std::endl;
//		return 1;
//	}
//
//	// set up the animations for all four directions (set spritesheet and push frames)
//	Animation walkingAnimationDown;
//	walkingAnimationDown.setSpriteSheet(texture);
//	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
//	walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
//	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
//	walkingAnimationDown.addFrame(sf::IntRect(0, 0, 32, 32));
//
//	Animation walkingAnimationLeft;
//	walkingAnimationLeft.setSpriteSheet(texture);
//	walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
//	walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
//	walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
//	walkingAnimationLeft.addFrame(sf::IntRect(0, 32, 32, 32));
//
//	Animation walkingAnimationRight;
//	walkingAnimationRight.setSpriteSheet(texture);
//	walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
//	walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
//	walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
//	walkingAnimationRight.addFrame(sf::IntRect(0, 64, 32, 32));
//
//	Animation walkingAnimationUp;
//	walkingAnimationUp.setSpriteSheet(texture);
//	walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
//	walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
//	walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
//	walkingAnimationUp.addFrame(sf::IntRect(0, 96, 32, 32));
//
//	Animation* _currentAnimation = &walkingAnimationDown;
//
//	// set up AnimatedSprite
//	AnimatedSprite _animatedSprite(sf::seconds(0.2), true, false);
//	_animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));
//
//	sf::Clock frameClock;
//
//	float speed = 80.f;
//	bool noKeyWasPressed = true;
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
//				window.close();
//		}
//
//		sf::Time frameTime = frameClock.restart();
//
//		// if a key was pressed set the correct animation and move correctly
//		sf::Vector2f movement(0.f, 0.f);
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//		{
//			_currentAnimation = &walkingAnimationUp;
//			movement.y -= speed;
//			noKeyWasPressed = false;
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//		{
//			_currentAnimation = &walkingAnimationDown;
//			movement.y += speed;
//			noKeyWasPressed = false;
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//		{
//			_currentAnimation = &walkingAnimationLeft;
//			movement.x -= speed;
//			noKeyWasPressed = false;
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//		{
//			_currentAnimation = &walkingAnimationRight;
//			movement.x += speed;
//			noKeyWasPressed = false;
//		}
//		_animatedSprite.play(*_currentAnimation);
//		_animatedSprite.move(movement * frameTime.asSeconds());
//
//		// if no key was pressed stop the animation
//		if (noKeyWasPressed)
//		{
//			_animatedSprite.stop();
//		}
//		noKeyWasPressed = true;
//
//		// update AnimatedSprite
//		_animatedSprite.update(frameTime);
//
//		// draw
//		window.clear();
//		window.draw(_animatedSprite);
//		window.display();
//	}
//
//	return 0;
//}
