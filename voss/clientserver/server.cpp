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
antwort [4]:
  neuer spieler joined
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
  sf::Uint32 nextId = 0;
  std::map<sf::Uint32, Player*> clients;
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
        packetToSend << (sf::Uint32) 1 << nextId;
        // put all id and names into the packet
        for (int i=0; i<nextId; i++)
        {
          Player *p = clients[i];
          packetToSend << i << p->getNameString();
        }
        socket.send(packetToSend, sender, port);
        std::cout << "Sent id " << nextId << " to " << name << std::endl;
        // create player object, put it in map
        clients[nextId] = new Player(nextId, name, sf::Color::Red, sender, port);

        // tell all clients there is a new player
        sf::Packet newPlayerPacket;
        newPlayerPacket << (sf::Uint32) 4;
        newPlayerPacket << (sf::Uint32) nextId;
        newPlayerPacket << name;
        for (auto const& x : clients)
        {
          if (nextId == x.first)
            continue;
          socket.send(newPlayerPacket, x.second->getIp(), x.second->getPort());
        }
        nextId += 1;
      }
      else if (packetType == 2)
      {
        // update packet from player
        PlayerUpdate pU;
        packet >> pU;
        Player *p = clients[pU.id];
        p->setPosition(pU.x_pos, pU.y_pos);
        // send update to every client except the one who sent it
        for (auto const& x : clients)
        {
          if (x.second->getId() == pU.id)
            continue;
          sf::Packet packet;
          packet << (sf::Uint32) 2 << pU;
          socket.send(packet, x.second->getIp(), x.second->getPort());
        }
      }
      else
      {
        std::cout << "Got packet with unknown type " << packetType << std::endl;
      }
      socket.receive(packet, sender, port);
    }

    // submit position of all players to all players
    window.clear(sf::Color::Black);

    // draw all players.
    for (int i=0; i<nextId; i++)
    {
      Player *p = clients[i];
      window.draw(p->getShape());
      window.draw(p->getName());
    }
    window.display();
  }
}
