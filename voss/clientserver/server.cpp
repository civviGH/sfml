#include <SFML/Network.hpp>
#include <stdlib.h>

int main()
{
  // socket for Network
  sf::UdpSocket socket;
  if (socket.bind(54000) != sf::Socket::Done)
  {
    std::cout << "Error binding socket to port 54000. Exiting." << std::endl;
    exit;
  }
}
