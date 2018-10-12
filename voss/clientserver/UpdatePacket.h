#ifndef UPDATEPACKET_H
#define UPDATEPACKET_H

#include <string>
#include <SFML/Network>
/*
welcome:
  name
  eigene ip, eigener port
anwort:
  id

update:
  position vom spieler
  id
antwort:
  position und name aller spieler
*/

struct WelcomePacket
{
  std::string name;
  std::string ip;
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
