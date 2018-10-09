#include <SFML/Network.hpp>
#include <iostream>

int main()
{
  sf::UdpSocket socket;

  // bind the socket to a port
  if (socket.bind(54000) != sf::Socket::Done)
  {
    std::cout << "error binding socket to 54000" << std::endl;
  }
  // forge packet
  std::string s = "hello from client!";
  sf::Packet packet;
  packet << s;
  // server information
  sf::IpAddress recipient = "192.168.178.92";
  unsigned short port = 54001;
  socket.send(packet, recipient, port);
}
