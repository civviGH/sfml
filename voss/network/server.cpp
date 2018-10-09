#include <SFML/Network.hpp>
#include <iostream>

int main()
{
  sf::UdpSocket socket;

  if (socket.bind(54001) != sf::Socket::Done)
  {
    std::cout << "error binding socket to 54000" << std::endl;
  }
  std::cout << "server startet on server 54001" << std::endl;
  //socket.setBlocking(false);
  std::string s;
  sf::Packet packet;
  sf::IpAddress recipient;
  unsigned short port;
  while (true)
  {
    socket.receive(packet, recipient, port);
    if (packet >> s)
    {
      std::cout << recipient << " on port " << port << " sent " << s << std::endl;
    }
  }
}
