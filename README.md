# Survival Adventure Game - COMP3016 - Harry Deane

Welcome to **Survival Adventure**! In this text-based survival game, you’ll need to manage resources, take actions, and make strategic choices to survive in the wilderness. This game was developed as a project using modern C++ and SDL, featuring unique mechanics and object-oriented design.

## Table of Contents
- [Youtube](#youtube)
- [Features](#features)
- [Installation](#installation)
- [Running the Game](#running-the-game)
- [Dependencies](#dependencies)
- [Game Design](#game-design)
- [Game Mechanics](#game-mechanics)
- [Exception Handling and Test Cases](#exception-handling-and-test-cases)
- [Prototype Details](#prototype-details)
- [Evaluation](#evaluation)
- [Resources](#resources)

---
## Youtube
[Link for demonstration video](https://youtu.be/LBdd_FZtENM)
## Features
- **Survival Mechanics**: Manage resources like wood, food, and water.
- **Environment Interactions**: Randomized chances of animal encounters.
- **OOP Design**: Utilizes object-oriented programming principles for a modular and maintainable codebase.
- **Save and Load High Score**: Records your score at the end of each game session and displays your highest score at the start of a new game.

## Installation
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/harryDeane/COMP3016.git
   cd COMP3016
2. **Ensure 64-Bit Architecture**:
This game must be built and run on x64 architecture. Make sure your IDE and build configuration are set to x64.
Install SDL2 and SDL_mixer:
3. **Download and install the SDL2 and SDL_mixer libraries**.
Place the SDL2 and SDL_mixer library files in the appropriate directories (e.g., include, lib, and bin) within your project or compiler environment.
4.**Build the Game**:
Open the project in an IDE like Visual Studio, which is recommended for this setup.
Ensure that your project configuration is set to x64.
Build the solution to generate the executable.

## Running the Game
1. **Run the Executable**:
Once built, navigate to the output directory (e.g., x64/Debug or x64/Release) and run the game executable.
2. **Audio Setup**:
Make sure the assets/sounds/background.mp3 file is in place, as this serves as the game’s background music.

## Dependencies
The game requires the following libraries:

SDL2: Used for creating the game window and handling graphics.

SDL_mixer: For loading and playing background music in the game.

SDL_image: For rendering images for the game.

SDL_ttf: for redning text for the game.

Please ensure that you have these dependencies installed and correctly referenced in your project settings.

## Game Design
### Programming Patterns
1. **Singleton Pattern**: Used for game settings to ensure only one instance exists and provides easy global access.
2. **State Pattern**: Manages game states (running, game over, etc.) for a clean flow.
3. **Observer Pattern**: Updates the UI and game state dynamically when player stats or resources change.

## Game Mechanics
The game includes:

**Resource Management**: Track wood, food, and water as the player makes decisions to survive.

**Foraging System**: Randomly rewards resources when players forage, introducing unpredictability.

**Hunting System**: Players can choose to hunt which has a 30% chance of having a wild animal encounter, reducing their health.

**High Score Tracking**: Saves the highest score to a file, which is then loaded at game start to display the player's best score.

## Coding Example
Here's a snippet from GameEngine.cpp for saving and loading high scores:
![image](https://github.com/user-attachments/assets/0afa107d-4a87-4e8d-8211-325e9cdeabdb)
## Exception Handling and Test Cases
Exception Handling: Ensures the game gracefully handles file I/O issues (e.g., loading or saving high scores), SDL initialization errors, and missing resources.

Testing: The game has been tested for various edge cases:

File loading errors for missing or corrupt files.
![image](https://github.com/user-attachments/assets/4ea40fc5-e14d-4b7f-a483-e5562ca1151a)

Player attempting actions without enough resources.
![image](https://github.com/user-attachments/assets/beffa628-0430-455b-840b-1686ad4f56bf)

Edge scenarios in resource management (e.g., resource depletion).

Stress tests for looped background music to ensure stability.

SDL initialization.
![image](https://github.com/user-attachments/assets/7a04c207-ea5c-44fb-92b8-9db6cb83b269)

## Prototype Details
This project prototype demonstrates OOP concepts and game development techniques in C++. It highlights:

Game Loop: A continuous loop to handle events, update game state, and render visuals.

Modular Structure: Clear separation between GameEngine, Player, and resource classes for easy scalability.

Cross-Session Persistence: The high score feature showcases file handling and session persistence.

## Evaluation
Achievements:

The game successfully integrates core survival mechanics with resource management, OOP design, and SDL-based graphics and audio.

The high score functionality adds a competitive edge, encouraging players to improve their survival strategy.

Future Improvements:

Expanded Mechanics: Adding more dynamic environmental effects and events could enrich gameplay  such as random weather events which have varying impacts on player stats.

Graphics Enhancement: Transitioning to sprite-based visuals would improve visual appeal.

Enhanced AI: Implementing an AI companion or adversary would add a new challenge.

This project has been a valuable experience in C++ game development and taught me a lot about modular design and real-time game loops.

## Resources
### Art
- [Pixel Joint](https://pixeljoint.com/pixelart/120493.htm)
- [Freepik - Icon 1](https://www.freepik.com/icon/shot_16811391#fromView=keyword&page=1&position=93&uuid=52eb38a2-9d17-44af-a415-7f9abcd66bc7)
- [Freepik - Icon 2](https://www.freepik.com/icon/carrot_16836438#fromView=search&page=1&position=13&uuid=acaf85b3-dc86-4ac7-b72b-c07db0004b56)
- [Pixilart](https://www.pixilart.com/draw#)

### Music
- [Pixabay - Nature Music](https://pixabay.com/music/search/nature/)

### Font
- [Google Fonts - Playwrite GB S](https://fonts.google.com/specimen/Playwrite+GB+S)
