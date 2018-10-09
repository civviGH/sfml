#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>

int main()
{
  // important states
  bool wPressed = false;
  bool dPressed = false;
  bool sPressed = false;
  bool aPressed = false;

  double playerSpeed = 5.0;
  
  // socket for network
  sf::UdpSocket socket;
  if (socket.bind(54000) != sf::Socket::Done)
  {
    std::cout << "Error loading network socket in port 54000" << std::endl;
  }
  socket.setBlocking(false);
  sf::Int64 clientPositionX;
  sf::Int64 clientPositionY;
  sf::Packet packet;
  sf::IpAddress sender;
  unsigned short port;
  

  // window management
  sf::RenderWindow window(sf::VideoMode(800, 600), "main");
  window.setFramerateLimit(60);
  window.setKeyRepeatEnabled(false);
  
  // create player
  sf::CircleShape player(10);
  player.setFillColor(sf::Color(100, 250, 50));
  // client player
  sf::CircleShape clientPlayer(10);
  clientPlayer.setFillColor(sf::Color(250, 50, 50));

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

    // check if we have network position information
    socket.receive(packet, sender, port);
    if (packet >> clientPositionX >> clientPositionY)
    {
      std::cout << "client position update to (" << clientPositionX << "," << clientPositionY << ")" << std::endl;
    }
    clientPlayer.setPosition(clientPositionX, clientPositionY);


    //DEBUG
    //std::cout << "control:" << wPressed << std::endl;
    //std::cout << window.getSize().x << "|" << window.getSize().y << std::endl;

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

    // limit movement to boundaries
    // origin of shape is top left
    if (player.getPosition().x < 0)
      player.setPosition(0, player.getPosition().y);
    if (player.getPosition().y < 0)
      player.setPosition(player.getPosition().x, 0);
    if (player.getPosition().x + player.getGlobalBounds().width > window.getSize().x)
      player.setPosition(window.getSize().x - player.getGlobalBounds().width, player.getPosition().y);
    if (player.getPosition().y + player.getGlobalBounds().height > window.getSize().y)
      player.setPosition(player.getPosition().x, window.getSize().y - player.getGlobalBounds().height);

    // DRAWING
    // clear everything black
    window.clear(sf::Color::Black);
  
    // draw player
    window.draw(player);
    window.draw(clientPlayer);

    // clear buffer and display
    window.display();
  }

return 0;
}
