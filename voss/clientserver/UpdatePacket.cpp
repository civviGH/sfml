#include "UpdatePacket.h"
#include <string>
#include <SFML/Network.hpp>

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
}
