#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <string>

using std::string;

enum COLORS {
  NC = -1,
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
};

struct CharInColor {
  char character;
  int color;
};

class Board {
public:
  Board();
  void makeEmpty();
  bool isFull();
  const char *colorize(int font, int back, int style);
  void addWord(string word, string answer);
  void print();

private:
  CharInColor words[6][5];
  int currentPos;
};

#endif