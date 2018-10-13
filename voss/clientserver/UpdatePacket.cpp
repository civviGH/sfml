#include "UpdatePacket.h"
#include <string>
#include <SFML/Network.hpp>

UpdatePacket::WelcomePacket(std::string n, std::string i, unsigned short p)
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
UpdatePacket::UpdatePacket(PlayerUpdate *updates)
{
  playerUpdates = updates;
}
