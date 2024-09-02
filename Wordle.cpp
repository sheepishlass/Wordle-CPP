//============================================================================
// Name        : Wordle.cpp
// Author      : Wei-Yin (Christine) Chen, Willow Carlson-Huber
// Date        : April 17, 2023
// Description : Wordle game in C++
//============================================================================

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include "Board.hpp"
#include "HashType.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

const int REPEAT = 1; // Change whether repeat is allowed here, 0 for allowed, 1
                      // for not allowed

void buildHashTable(ifstream &inFile, HashType<string> &hashTable, int type,
                    int repeat);

int main() {
  // Build valid word library
  ifstream infile;
  int p;
  string str;

  infile.open("valid-wordle-words.txt");
  if (infile) {
    infile >> p;
  } else {
    cout << "Unable to open valid-wordle-words.txt" << endl;
    return 0;
  }

  HashType<string> validLibrary(p, 33);
  buildHashTable(infile, validLibrary, 0, REPEAT);
  infile.close();

  // Build answer library
  string *answerLibrary;
  infile.open("wordle-answers-alphabetical.txt");
  if (infile) {
    infile >> p;
  } else {
    cout << "Unable to open wordle-answers-alphabetical.txt" << endl;
    return 0;
  }
  answerLibrary = new string[p];
  for (int i = 0; i < p; i++)
    infile >> answerLibrary[i];
  infile.close();

  // Prompt user to play game
  char input = 'Y';
  while (input == 'Y' || input == 'y') {
    cout << "Play Wordle? (Y/N)";
    cin >> input;
    cout << endl;

    if (input == 'Y' || input == 'y') {
      // Choose random answer from answerLibrary
      srand(time(0));
      int index = 0;
      index = rand() % p;
      string answer = answerLibrary[index];

      Board Board1;
      string guess;
      bool found = false;

      cout << "You have at most 6 guesses." << endl;
      cout << "Please enter 5 letter words in lower case." << endl;
      cout << "Green background means the letter is in the right place."
           << endl;
      cout << "Yellow background means the letter exists in the word." << endl;
      cout << "White background means the letter does not exist in the word."
           << endl
           << endl;

      for (int i = 0; i < 6; i++) {
        do {
          // Prompt for answer
          cout << "Enter guess " << i + 1 << " : ";
          cin >> guess;
          cout << endl;

          // Check if guess is valid by searching validLibrary
          if (guess.size() == 5)
            validLibrary.RetrieveItem(guess, found, 0);

          if (found) {
            // If valid, add guess to board and display board
            Board1.addWord(guess, answer);
            Board1.print();
          }
        } while (!found);
        found = false;

        // End game if guess is correct
        if (guess == answer) {
          cout << "Congratulations!" << endl;
          break;
        }
      }
      cout << "The correct answer is: " << answer << endl << endl;
    }
  }

  cout << "Thank you for playing!" << endl;

  return 0;
}

void buildHashTable(ifstream &inFile, HashType<string> &hashTable, int type,
                    int repeat) {
  string word;
  bool inList = false;
  if (inFile.is_open()) {
    while (inFile >> word) {
      if (repeat)
        hashTable.RetrieveItem(word, inList, type);
      if (!inList) {
        if (type == 1)
          hashTable.InsertItemLinear(word);
        else
          hashTable.InsertItemQuadratic(word);
      }
    }
  }
}
