#ifndef UPDATEPACKET_H
#define UPDATEPACKET_H

#include <string>
#include <vector>
#include <SFML/Network.hpp>

struct WelcomePacket
{
  std::string name;
  sf::IpAddress ip;
  unsigned short port;
  WelcomePacket(std::string n, std::string i, unsigned short p);
};
struct PlayerUpdate
{
  sf::Int64 x_pos;
  sf::Int64 y_pos;
  std::string name;
  PlayerUpdate(sf::Int64 x, sf::Int64 y, std::string n);
};
struct UpdatePacket
{
  std::vector<PlayerUpdate> playerUpdates;
  UpdatePacket();
};

// packet >> operator overwrite for custom packets
//sf::Packet& operator <<(sf::Packet& packet, const Character& character)
//{
//    return packet << character.age << character.name << character.weight;
//}
#endif
