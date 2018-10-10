#include <iostream>
#include "Player.h"

int main()
{
  Player p1(2);
  Player p2(3);
  p1.printNummer();
  p2.printNummer();
  p1.setNummer(6);
  p1.printNummer();
}
