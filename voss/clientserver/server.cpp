#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <iostream>
#include "UpdatePacket.h"
#include "Player.h"
/*
welcome [0]:
  name
anwort [1]:
  id

update [2]:
  position vom spieler
  id
antwort [3]:
  position und name aller spieler
*/
int main()
{
  // socket for Network
  sf::UdpSocket socket;
  if (socket.bind(54000) != sf::Socket::Done)
  {
    std::cout << "Error binding socket to port 54000. Exiting." << std::endl;
    exit;
  }
  socket.setBlocking(false);
  sf::Packet packet;
  sf::Uint32 packetType;
  std::cout << "Started server on port 54000. Listening." << std::endl;

  // Window
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "server");
  window.setFramerateLimit(60);
  window.setKeyRepeatEnabled(false);

  sf::IpAddress sender;
  unsigned short port;

  // client mgmt
  sf::Uint32 lowestId = 0;
  std::map<sf::Uint32, Player> clients;
  //std::map& operator

  while (window.isOpen())
  {
    // check all events
    sf::Event event;
    while (window.pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
    }
    socket.receive(packet, sender, port);
    while(packet >> packetType)
    {
      // as long as we have packets on the socket, keep reading them
      if (packetType == 0)
      {
        // welcome packet
        std::string name;
        packet >> name;
        std::cout << "Welcome packet from " << sender << " with name " << name << std::endl;
        // send id
        sf::Packet packetToSend;
        packetToSend << (sf::Uint32) 1 << lowestId;
        socket.send(packetToSend, sender, port);
        std::cout << "Sent id " << lowestId << " to " << name << std::endl;
        // create player object, put it in map
        clients[lowestId] = Player(lowestId, name, sf::Color::Red);
        lowestId += 1;
      }
      else if (packetType == 2)
      {
        // update packet from player
        PlayerUpdate pU;
        packet >> pU;
	std::cout << "Update packet from id " << pU.id << " | " << pU.x_pos << "," << pU.y_pos << std::endl;
      }
      else
      {
        std::cout << "Got packet with unknown type " << packetType << std::endl;
      }
      socket.receive(packet, sender, port);
    }
    window.clear(sf::Color::Black);

    window.display();
  }
}
