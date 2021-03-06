#include <string>
#include <SFML/Network.hpp>
#include "UpdatePacket.h"

WelcomePacket::WelcomePacket(std::string n, std::string i, unsigned short p)
{
    name = n;
    ip = i;
    port = p;
}
PlayerUpdate::PlayerUpdate(sf::Int64 x, sf::Int64 y, sf::Uint32 i)
{
  x_pos = x;
  y_pos = y;
  id = i;
}
PlayerUpdate::PlayerUpdate()
{
  x_pos = 0;
  y_pos = 0;
  id = 0;
}
UpdatePacket::UpdatePacket()
{
  playerUpdates.reserve(16);
  size = 16;
}
UpdatePacket::UpdatePacket(sf::Uint32 n)
{
  playerUpdates.reserve(n);
  size = n;
}

sf::Packet& operator <<(sf::Packet& packet, const PlayerUpdate& pUpdate)
{
   return packet << pUpdate.x_pos << pUpdate.y_pos << pUpdate.id;
}
sf::Packet& operator >>(sf::Packet& packet, PlayerUpdate& pUpdate)
{
    return packet >> pUpdate.x_pos >> pUpdate.y_pos >> pUpdate.id;
}

sf::Packet& operator <<(sf::Packet& packet, const UpdatePacket& updateP)
{
  packet << updateP.size;
  for (unsigned i=0; i<updateP.size; i++)
  {
    packet << updateP.playerUpdates.at(i);
  }
  return packet;
}
sf::Packet& operator >>(sf::Packet& packet, UpdatePacket& updateP)
{
  packet >> updateP.size;
  for (unsigned i=0; i<updateP.size; i++)
  {
    packet >> updateP.playerUpdates.at(i);
  }
  return packet;
}
