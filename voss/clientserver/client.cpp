#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>

int main()
{
  sf::UdpSocket socket;
  int portToBindTo;
  std::string serverIpAddress;
  std::cout << "Please enter port number for own socket: ";
  std::cin >> portToBindTo;
  if (socket.bind(portToBindTo) != sf::Socket::Done)
  {
    std::cout << "Error loading network socket in port " << portToBindTo << "!" << std::endl;
  }
  std::cout << "Please enter ip of server: ";
  std::cin >> serverIpAddress;
  sf::IpAddress recipient = serverIpAddress;
  // hard coded to 54000 for now
  //std::cout << "Please enter port of server: ";
  unsigned short portOfServer = 54000;
  //std::cin >> portOfServer;

  // connect to server by sending welcome package
  sf::Packet packet;
  sf::Uint32 packetType = 0;
  std::string name;
  std::cout << "Please enter your name: ";
  std::cin >> name;
  packet << packetType << name;
  socket.send(packet, recipient, portOfServer);

  // wait till response with id from server
  sf::Uint32 ownId;
  sf::IpAddress sender;
  unsigned short port;
  socket.receive(packet, sender, port);
  packet >> packetType;

  // client player stuff
  sf::CircleShape player(10);
  player.setFillColor(sf::Color(100, 250, 50));
  bool wPressed = false;
  bool dPressed = false;
  bool sPressed = false;
  bool aPressed = false;
  double playerSpeed = 5.0;

  if (packetType == 1)
  {
    packet >> ownId;
    std::cout << "Got response from server with id " << ownId << std::endl;
  }
  else {
    std::cout << "Unknown packet type " << packetType << " in server response" << std::endl;
    exit;
  }
  socket.setBlocking(false);

  // text over player head
  sf::Font font;
  if (!font.loadFromFile("arial.ttf"))
  {
    std::cout << "Could not load font arial.ttf" << std::endl;
    exit;
  }
  sf::Text playerName;
  playerName.setFont(font);
  playerName.setString(name);
  playerName.setCharacterSize(15);
  playerName.setFillColor(sf::Color::Red);
  playerName.setStyle(sf::Text::Bold);

  int offset_x = (playerName.getLocalBounds().width / 2) - player.getLocalBounds().width/2;
  int offset_y = player.getLocalBounds().height;
  sf::Vector2f offset(offset_x, offset_y);

  // window management
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "client");
  window.setFramerateLimit(60);
  window.setKeyRepeatEnabled(false);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
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
    }
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
    // put text over player
    playerName.setPosition(player.getPosition() - offset);

    // give server update about position
    PlayerUpdate pU(player.getPosition().x, player.getPosition().y, ownId);
    sf::Packet packet;
    packet << (sf::Uint32) 2 << pU;
    socket.send(packet, serverIpAddress, portOfServer);
    // draw everything
    window.clear(sf::Color::Black);
    window.draw(player);
    window.draw(playerName);
    window.display();
  }
}
