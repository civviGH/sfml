#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>

#include "UpdatePacket.h"
#include "Player.h"

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

  // network clients
  std::map<sf::Uint32, Player*> clients;

  if (packetType == 1)
  {
    packet >> ownId;
    std::cout << "Got response from server with id " << ownId << std::endl;
    clients[ownId] = new Player(ownId, name, sf::Color(100, 250, 50), "127.0.0.1", portToBindTo);
    sf::Uint32 clientId;
    std::string clientName;
    while (packet >> clientId >> clientName)
    {
      clients[clientId] = new Player(clientId, clientName, sf::Color::Red, sender, port);
    }
  }
  else
  {
    std::cout << "Unknown packet type " << packetType << " in server response" << std::endl;
    exit;
  }
  socket.setBlocking(false);

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
    // NETWORK
    socket.receive(packet, sender, port);
    while(packet >> packetType)
    {
      if (packetType == 2)
      {
        // playerUpdate
        PlayerUpdate pU;
        packet >> pU;
        Player *p = clients[pU.id];
        p->setPosition(pU.x_pos, pU.y_pos);
      }
      else if (packetType == 4)
      {
        std::cout << "got player added packet" << std::endl;
        sf::Uint32 clientId;
        packet >> clientId;
        std::string clientName;
        packet >> clientName;
        clients[clientId] = new Player(clientId, clientName, sf::Color::Red, sender, port);
      }
      else
      {
        std::cout << "unknown packet type received" << std::endl;
      }
      socket.receive(packet, sender, port);
    }
    // MOVEMENT
    Player *p = clients[ownId];
    if (wPressed)
    {
      p->movePosition(0, -1 * playerSpeed);
    }
    else if (sPressed)
    {
      p->movePosition(0, playerSpeed);
    }
    if (dPressed)
    {
      p->movePosition(playerSpeed, 0);
    }
    else if (aPressed)
    {
      p->movePosition(-1 * playerSpeed, 0);
    }

    // limit movement to boundaries
    // origin of shape is top left
    /*
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
    */
    // give server update about position
    PlayerUpdate pU(p->getXPos(), p->getYPos(), ownId);
    sf::Packet packet;
    packet << (sf::Uint32) 2 << pU;
    socket.send(packet, serverIpAddress, portOfServer);
    // draw everything
    window.clear(sf::Color::Black);
    for (auto const& x : clients)
    {
      window.draw(x.second->getShape());
      window.draw(x.second->getName());
    }
    window.display();
  }
}
