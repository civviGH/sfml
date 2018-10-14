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
};
struct UpdatePacket
{
  std::vector<PlayerUpdate> playerUpdates;
  UpdatePacket();
};

// packet >> operator overwrite for PlayerUpdate
sf::Packet& operator <<(sf::Packet& packet, const PlayerUpdate& pUpdate)
{
    return packet << pUpdate.x_pos << pUpdate.y_pos << pUpdate.id;
}
sf::Packet& operator >>(sf::Packet& packet, PlayerUpdate& pUpdate)
{
    return packet >> pUpdate.x_pos >> pUpdate.y_pos >> pUpdate.id;
}
#endif
