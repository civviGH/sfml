#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
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
  Player(sf::Uint32 i, std::string n, sf::Color c);
  Player();
  void updateNamePosition();
  void setPosition(sf::Int64 x, sf::Int64 y);
  void printPosition();
  sf::CircleShape getShape();
  sf::Text getName();
  Player operator=(const Player& p2);
private:
  sf::Uint32 id;
  sf::Text name;
  sf::Font font;
  sf::CircleShape shape;
  sf::Vector2f offset;
};
#endif
