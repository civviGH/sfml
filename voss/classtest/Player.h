#ifndef PLAYER_H
#define PLAYER_H

class Player
{
  private:
    int nummer;
  public:
    Player(const int n = 0);
    void setNummer(const int n);
    void printNummer() const;
};

#endif
