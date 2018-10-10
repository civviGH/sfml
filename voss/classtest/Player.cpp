#include <iostream>
#include "Player.h"

Player::Player(const int n)
{
  nummer = n;
}

void Player::setNummer(const int n)
{
  nummer = n;
}

void Player::printNummer() const
{
  std::cout << "Nummer ist " << nummer << std::endl;
}
