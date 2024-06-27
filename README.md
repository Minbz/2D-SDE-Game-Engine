## Architecture Diagram
![Architecture Diagram](assets/architecture%20diagram.png)

## Running

### Run the Game

**Run Game directly with built mygameengine.so module**

`python3 main.py`

### Run the Level Editor

**Run Game first**, then press `esc` to edit the current scene you're in.

- press any number between `1` and `5` to choose an _tile_ to add or move _Player_ or _Destination_.
- press `e` to erase a _tile_ or _enemy_. _Player_ and _Destination_ cannot be erased.
- press `s` to save
- press `esc` to quit editor mode without saving

## Game/Engine Publicity

**Project Website**: https://minbz.github.io/

## Compilation Instructions

**Rebuild mygameengine.so module in linux**

`python3 linuxbuildengine.py`

## Project Hieararchy

### ./Engine Directory Organization

- assets
  - Art assets
- src
  - source code(.cpp files) 
- include
  - header files(.h and .hpp files)
- lib
  - libraries (.so, .dll, .a, .dylib files).
- helper
  - helper function in py for the demo game
