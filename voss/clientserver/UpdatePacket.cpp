#include "UpdatePacket.h"
#include <string>
#include <SFML/Network.hpp>

WelcomePacket::WelcomePacket(std::string n, std::string i, unsigned short p)
{
    name = n;
    ip = i;
    port = p;
}
PlayerUpdate::PlayerUpdate(sf::Int64 x, sf::Int64 y, std::string n)
{
  x_pos = x;
  y_pos = y;
  name = n;
}
UpdatePacket::UpdatePacket()
{
  playerUpdates.reserve(16);
}
