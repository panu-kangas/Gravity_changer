# Gravity changer

Gravity changer is sort-of-a platformer, that has a gravitation changing mechanism to make the gameplay more interesting.

The program utilizes the SFML (Simple and Fast Multimedia Library) and uses CMake as it's build system. It should work on macOS, Linux and Windows (on Windows: use the Visual Studio -program).  

NOTE:   
If you are using Windows, you might need to move the executable file (called "gravity") from the out/build -folder to the root of the repository. I'll fix this later, sorry for the inconvenience 🙈

More detailed information about the game can be found below. 
I really hope you enjoy the game! 😊 

# Installation

Instructions on how to use the game.

## Prerequisites

1. You need to install (and/or update) **CMake** and **Git** in order to be able to compile this project.  
2. On Windows, you need the Visual Studio -program.  
3. If you use Linux, install SFML's dependencies using your system package manager. On Ubuntu and other Debian-based distributions you can use the following commands:
    ```
    sudo apt update
    sudo apt install \
        libxrandr-dev \
        libxcursor-dev \
        libudev-dev \
        libfreetype-dev \
        libopenal-dev \
        libflac-dev \
        libvorbis-dev \
        libgl1-mesa-dev \
        libegl1-mesa-dev
    ```

## Compilation instructions

Run the following commands in your terminal:

1. ```git clone https://github.com/panu-kangas/Gravity_changer.git && cd Gravity_changer```  
2. ```cmake -B build```  
3. ```cmake --build build```
*(4. on Windows: move the executable file to the root of the repository)*
5. ```./gravity```

# About the game

In Gravity changer, the player (green rectangle) has to collect as many collectibles (red rectangle) as possible until the game time runs out. The map consists of orange rectangles, which can be jumped on.  

The speciality of this game is it's gravity changing mechanism: by using the arrow keys, player can change the direction of gravitational pull. Gravitational changes only affect the player, not collectibles.  
By using the gravity changer player can reach collectibles faster, or reach collectibles that are otherwise out of reach.  
Gravity changer has a small recharge time, so it cannot be spammed constantly; use it wisely!

In the beginning, player has 20 seconds on the game timer. Every collectible rewards a small chunk of time back to the timer and 100 points to the score counter. The game ends, when the timer hits 0 seconds.  
  
How many points can you get before the time runs out...? 😉

### Game controls

WASD - Move the player  
*(NOTE: if gravity pulls down, you can jump by pressing W, but if gravity pulls to the right, you jump by using A etc)*  
ARROW KEYS - Change gravitation's direction 
ESC - Exit the game

# Future develompent ideas

I want to develop this game further once I have more time on my hands. Here are a few ideas for further development:  

1. Multiplayer mode. Maybe the game time could be fixed (2 minutes etc) and the one who gets more points in that time wins. There could also be a mechanism that would make interference possible, like jumping on top of the other player and stun them.
2. Gravity changing logic. I'm curious about the gravity changing logic and how it could be used: now the gravity changer has a recharge time, but what if it would cost player 2 seconds from the timer to use it? Or 100 points? These changes might make the game even more fun and versatile! 

