#ifndef UPDATEPACKET_H
#define UPDATEPACKET_H

#include <string>
#include <SFML/Network.hpp>

struct WelcomePacket
{
  std::string name;
  sf::IpAddress ip;
  unsigned short port;
};
struct PlayerUpdate
{
  sf::Int64 x_pos;
  sf::Int64 y_pos;
  std::string name;
};
struct UpdatePacket
{
  PlayerUpdate *playerUpdates[16];
};
#endif
