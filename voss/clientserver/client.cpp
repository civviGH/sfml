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
  socket.setBlocking(false);
  std::cout << "Please enter ip of server: ";
  std::cin >> serverIpAddress;
  sf::IpAddress recipient = serverIpAddress;
  // hard coded to 54000 for now
  //std::cout << "Please enter port of server: ";
  unsigned short portOfServer = 54000;
  //std::cin >> portOfServer;

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
    }
  }
}
