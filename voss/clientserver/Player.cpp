#include <SFML/Graphics.hpp>
#include "Player.h"
#include <string>
#include <iostream>


Player::Player(sf::Uint32 i, std::string n, sf::Color c, sf::IpAddress ipA, unsigned short p)
{
  ipAddress = ipA;
  port = p;
  shape = sf::CircleShape(10);
  shape.setFillColor(c);
  shape.setPosition(0, 0);
  id = i;
  font.loadFromFile("arial.ttf");
  name.setFont(font);
  name.setString(n);
  name.setCharacterSize(15);
  name.setFillColor(sf::Color::Red);
  name.setStyle(sf::Text::Bold);
  offset = sf::Vector2f((name.getLocalBounds().width / 2) - shape.getLocalBounds().width/2, shape.getLocalBounds().height);
};
void Player::setPosition(sf::Int64 x, sf::Int64 y)
{
  shape.setPosition(x , y);
  this->updateNamePosition();
};
void Player::movePosition(sf::Int64 x, sf::Int64 y)
{
  shape.move(x, y);
  this->updateNamePosition();
}
void Player::printPosition()
{
  std::cout << shape.getPosition().x << "," << shape.getPosition().y << std::endl;
};
Player::Player()
{
  shape = sf::CircleShape(10);
  shape.setFillColor(sf::Color::Red);
  shape.setPosition(0, 0);
  id = 255;
  font.loadFromFile("arial.ttf");
  name.setFont(font);
  name.setString("DEFAULT");
  name.setCharacterSize(15);
  name.setFillColor(sf::Color::Red);
  name.setStyle(sf::Text::Bold);
  offset = sf::Vector2f((name.getLocalBounds().width / 2) - shape.getLocalBounds().width/2, shape.getLocalBounds().height);
};
sf::CircleShape Player::getShape()
{
  return shape;
};
sf::Text Player::getName()
{
  return name;
};
void Player::updateNamePosition()
{
  name.setPosition(shape.getPosition() - offset);
};
sf::Int64 Player::getXPos()
{
  return shape.getPosition().x;
};
sf::Int64 Player::getYPos()
{
  return shape.getPosition().y;
};
sf::Uint32 Player::getId()
{
  return id;
};
Player Player::operator =(const Player& p2)
{
  Player player;
  player.id = p2.id;
  player.name = p2.name;
  player.shape = p2.shape;
  player.offset = p2.offset;
  return player;
};
sf::IpAddress Player::getIp()
{
  return ipAddress;
};
unsigned short Player::getPort()
{
  return port;
};
std::string Player::getNameString()
{
  return name.getString();
};
