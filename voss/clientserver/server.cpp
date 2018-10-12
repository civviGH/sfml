#include <SFML/Network.hpp>
#include <stdlib.h>
#include <iostream>
/*

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
  std::cout << "Started server on port 54000. Listening." << std::endl;

  // Window
  sf::Window window(sf::VideoMode(200, 200), "server");
  window.setFramerateLimt(60);
  window.setKeyRepeatEnabled(false);


  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
    }
  }
}
