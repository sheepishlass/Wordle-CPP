#include "Board.hpp"

using std::cout;
using std::endl;
using std::string;

// Color display for windows
// https://stackoverflow.com/a/69355721
#ifdef _WIN32
#include <windows.h>

void activateVirtualTerminal() {
  HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD consoleMode;
  GetConsoleMode(handleOut, &consoleMode);
  consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  consoleMode |= DISABLE_NEWLINE_AUTO_RETURN;
  SetConsoleMode(handleOut, consoleMode);
}
#endif

Board::Board() {
  CharInColor emptyChar;
  emptyChar.character = '_';
  emptyChar.color = WHITE;

  for (int i = 0; i < 6; i++)
    for (int j = 0; j < 5; j++)
      words[i][j] = emptyChar;
  currentPos = 0;
}

void Board::makeEmpty() {
  CharInColor emptyChar;
  emptyChar.character = '_';
  emptyChar.color = WHITE;

  for (int i = 0; i < 6; i++)
    for (int j = 0; j < 5; j++)
      words[i][j] = emptyChar;
  currentPos = 0;
}

bool Board::isFull() { return currentPos > 5; }

void Board::addWord(string word, string answer) {
  CharInColor temp[5];
  if (currentPos < 6) {
    // Mark all correct letters green first
    for (int i = 0; i < 5; i++) {
      temp[i].character = word.at(i);
      if (word.at(i) == answer.at(i))
        temp[i].color = GREEN;
    }

    // If letter has not been marked green, mark letter yellow if letter exists
    // elsewhere in word AND letter is not marked green where it is located AND 
    // prior locations have not been marked yellow
    for (int i = 0; i < 5; i++) {
      int count = 0;
			for (int n = 0; n < 5; n++) {
			    if (answer.at(n) == word.at(i))
			    	count++;
			}
      for (int j = 1; j < 5; j++) {
        if (word.at(i) == answer.at((i + j) % 5) &&
            temp[(i + j) % 5].color != GREEN && temp[i].color != GREEN)
          temp[i].color = YELLOW;
      }
      if(temp[i].color != GREEN) {
				int found = 0;
				for(int k = 0; k < i; k++)
				{
					if(word.at(i) == word.at(k) && (temp[k].color == YELLOW || temp[k].color == GREEN))
						found ++;
					if (found == count && found !=0) temp[i].color = WHITE;
				}
			}
    }

    // Mark the remaining letters white
    for (int i = 0; i < 5; i++) {
      if (temp[i].color != GREEN && temp[i].color != YELLOW)
        temp[i].color = WHITE;
    }
    for (int i = 0; i < 5; i++)
      words[currentPos][i] = temp[i];
    currentPos += 1;
  }
}

/**
 * Colorize terminal colors ANSI escape sequences.
 *
 * @param font font color (-1 to 7), see COLORS enum
 * @param back background color (-1 to 7), see COLORS enum
 * @param style font style (1==bold, 4==underline)
 **/

const char *Board::colorize(int font, int back = -1, int style = -1) {
  static char code[36];

  if (font >= 0)
    font += 30;
  else
    font = 0;
  if (back >= 0)
    back += 40;
  else
    back = 0;

  if (back > 0 && style > 0) {
    sprintf(code, "\033[%d;%d;%dm", font, back, style);
  } else if (back > 0) {
    sprintf(code, "\033[%d;%dm", font, back);
  } else {
    sprintf(code, "\033[%dm", font);
  }

  return code;
}

void Board::print() {
#ifdef _WIN32
  activateVirtualTerminal();
#endif

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 5; j++) {
      cout << colorize(BLACK, words[i][j].color) << words[i][j].character;
    }
    cout << colorize(NC, NC) << endl;
  }
  cout << endl;
}
