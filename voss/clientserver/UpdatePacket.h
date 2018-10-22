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
  sf::Uint32 id;
  PlayerUpdate(sf::Int64 x, sf::Int64 y, sf::Uint32 i);
  PlayerUpdate();
};
struct UpdatePacket
{
  std::vector<PlayerUpdate> playerUpdates;
  sf::Uint32 size;
  UpdatePacket();
  UpdatePacket(sf::Uint32 n);
};

sf::Packet& operator <<(sf::Packet& packet, const PlayerUpdate& pUpdate);
sf::Packet& operator >>(sf::Packet& packet, PlayerUpdate& pUpdate);
sf::Packet& operator <<(sf::Packet& packet, const UpdatePacket& updateP);
sf::Packet& operator >>(sf::Packet& packet, UpdatePacket& updateP);
#endif
