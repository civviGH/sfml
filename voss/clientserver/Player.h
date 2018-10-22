#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
/*
player needs
position
circle object
name
id
*/

//class Player : public sf::Drawable, public sf::Transformable
class Player
{
public:
  Player(sf::Uint32 i, std::string n, sf::Color c, sf::IpAddress ipA, unsigned short p);
  Player();
  void updateNamePosition();
  void setPosition(sf::Int64 x, sf::Int64 y);
  void movePosition(sf::Int64 x, sf::Int64 y);
  void printPosition();
  sf::CircleShape getShape();
  sf::Text getName();
  std::string getNameString();
  sf::Int64 getXPos();
  sf::Int64 getYPos();
  sf::Uint32 getId();
  sf::IpAddress getIp();
  unsigned short getPort();
  Player operator=(const Player& p2);
private:
  unsigned short port;
  sf::IpAddress ipAddress;
  sf::Uint32 id;
  sf::Text name;
  sf::Font font;
  sf::CircleShape shape;
  sf::Vector2f offset;
};
#endif
