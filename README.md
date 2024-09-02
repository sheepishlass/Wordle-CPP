# Wordle Command Line Game Recreation in C++

## Overview

This group project is a recreation of the popular "Wordle" game, originally developed by The New York Times. The objective of the game is for the user to guess a randomly selected 5-letter word within 5 attempts. The game provides feedback on the accuracy of the guess through color-coded hints:

1. White: The letter is not in the word.
2. Yellow: The letter is in the word but in the wrong position.
3. Green: The letter is in the correct position.

The game continues until the word is guessed correctly or all attempts are exhausted. The user can then choose to play another round or exit the program.

## Why We Used Hashing

Hashing was employed to validate user guesses efficiently. By utilizing a hash function on the word dictionary, the program achieves constant time lookups, ensuring that the validation process remains quick regardless of the dictionary size. Additionally, hashing reduces memory consumption, which is crucial given the large dictionary used in the game.

## Project Structure

### Source Code:
1. Wordle.cpp: The main game logic.
2. Board.cpp, Board.hpp: Handles the console display of the game board.
3. HashType.cpp, HashType.hpp: Manages the hashing of words for quick validation.

### Data Files:
1. valid-wordle-words.txt: Contains a list of all valid words for the game.
2. wordle-answers-alphabetical.txt: Contains a list of possible answers, sorted alphabetically.

### Build Files:
1. meson.build: Build configuration for the project.
2. simple-build.sh: A simple shell script to build the project.
3. .gitignore: Specifies files to ignore in version control.

## Setup and Usage

1. Build the Project: Use the provided meson.build file and simple-build.sh script to compile the project.
2. Run the Game: Execute the compiled program. The user will be prompted to input 5-letter words and attempt to guess the correct word based on the feedback provided.
3. Play Again: After each game, the user can choose to play another round or exit.


