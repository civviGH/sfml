#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main()
{
  // important states
  bool wPressed;
  bool dPressed;
  bool sPressed;
  bool aPressed;

  double playerSpeed = 5.0;

  sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
  window.setFramerateLimit(60);
  window.setKeyRepeatEnabled(false);
  
  // create player
  sf::CircleShape player(10);
  player.setFillColor(sf::Color(100, 250, 50));

  // run the program as long as the window is open
  while (window.isOpen())
  {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window.pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
      
      // movement event
      if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::W)
          wPressed = true;
        if (event.key.code == sf::Keyboard::D)
          dPressed = true;
        if (event.key.code == sf::Keyboard::S)
          sPressed = true;
        if (event.key.code == sf::Keyboard::A)
          aPressed = true;
      }
      if (event.type == sf::Event::KeyReleased)
      {
        if (event.key.code == sf::Keyboard::W)
          wPressed = false;
        if (event.key.code == sf::Keyboard::D)
          dPressed = false;
        if (event.key.code == sf::Keyboard::S)
          sPressed = false;
        if (event.key.code == sf::Keyboard::A)
          aPressed = false;
      }
      // mouseclick events
      if (event.type == sf::Event::MouseButtonPressed)
      {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
          std::cout << "left mouse clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")" << std::endl;
        }
      }
    }

    //DEBUG
    //std::cout << "control:" << wPressed << std::endl;

    // MOVEMENT
    if (wPressed)
    {
      player.move(0, -1 * playerSpeed);
    }
    else if (sPressed)
    {
      player.move(0, playerSpeed);
    }
    if (dPressed)
    {
      player.move(playerSpeed, 0);
    }
    else if (aPressed)
    {
      player.move(-1 * playerSpeed, 0);
    }

    // DRAWING
    // clear everything black
    window.clear(sf::Color::Black);
  
    // draw player
    window.draw(player);

    // clear buffer and display
    window.display();
  }

return 0;
}
