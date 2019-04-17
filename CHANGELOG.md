# Changelog


All notable changes to this project will be documented in this file.

## [0.5.0] - 17/04/2019

Added: 
--------
- Use of potions
- NPCs implemented
- Cutscene research implemented
- 2 Cutscenes added
- 3 enemies implemented (not fully)
- HUD added
- 3 characters implemented(not fully)
- Dynamic NPCs added
- Game icon added to exe

Changed:
--------
- Controller fully implemented
- Fountain fully implemented
- Debug screen fully implemented
- Shop logic fully implemented
- Drop sprite added
- Movement Quest
- Controls menu changed and fixed
- Warrior ability animation added

Removed: 
--------

Fixed: 
--------
- #195 Game crash at new game button (Bug photo inside)
- #180 Game crash if you click cancel button and then tutorial button
- #178 The game crash when you click in return main menu when dead
- #177 The game crash when you click Tutorial or cancel button to go to the tutorial map
- #145 Elements from inventory disappear (even the iventory, blocking the players game)
- #138 If you click in return when in control menu it returns to pause or main menu
- #137 If you click the options in the main menu it will click the fullscreen checkbox too

## [0.4.1] - 12/04/2019

Added: 
--------
- First Ability
- Go to quest
- Shop Logic (not finished)
- All tutorial rooms
- Room Logic
- Game over screen
- NPC shop
- Drops
- Debug Screen (not finished)



Changed:
--------
- Credits screen
- Focus improved
- More static entities (trees, rocks)
- Mouse icon changed
- Collision slide
- Movement change
- New controller controls

Removed: 
--------



Fixed: 
--------

- #134 If you try to connect the controller when the game is running it won't work
- #133 If you try to use inventory in option menu in the main menu then in the game you cannot use it
- #132 Fountain room crashes game
- #131 If you return to room 4 from room 5 the game crashes
- #130 Go to shop, pause menu go to main menu = crash
- #94 Options focus doesn't work properly on controls options
- #90 The option menu doesn't "remember visually the changes
- #88 Lobby Fountain incorrectly printed

## [0.4.0] - 07/04/2019

Added: 
--------

- Inventory
- Tutorial rooms
- Death Animation
- New lobby camera
- Death Logic
- Transitions between quest maps (not random)

Changed:
--------

- Lobby Tileset

Removed: 
--------

- Old lobby camera

Fixed: 
--------

- #98 Memory leaks when you enter and leave the home
- #97 The abilities menu appears in the option menu if you click the V key
- #96 The option menu text is too little compared to the focus
- #93 Option menu from main menu doesn't return to main menu
- #89 The lobby map blit sprites out of the map
- #86 New game Main menu loop crash the game
- #49 When you change map from hub - tutorial - hub the game crashes

## [0.3.1] - 05/04/2019

Added: 
--------

- UI focus
- Control change
- Option menu (not finished)
- Lobby camera (not polished)
- Credits Button
- Dialog System added

Changed:
--------

- Lobby Tileset


Removed: 
--------


Fixed: 
--------

- #34 The player sprite doesn't show up when you return to the main menu
- #46 When you enter to the home the screen stays black


## [0.3.0] - 01/04/2019

Added: 
--------

- Hub map
- Free movement works properly
- Colliders (non walkable tiles)
- Sensors
- Shop
- Home
- Transition Hub-Shop



Changed:
--------

- Now the transition between tutorial map and hub are the with the correct maps

Removed: 
--------

- Old hub map

Fixed: 
--------


## [0.2.1] - 29/03/2019

Added: 
--------

- Player attack.
- Now the player can choose the direction he/she wants to look to.


Changed:
--------


Removed: 
--------

Fixed: 
--------

- Issue 34 solved -> The player sprite doesn't show up when you return to the main menu.


## [0.2.0] - 24/03/2019

Added: 
--------

- Main menu
- Pause menu
- Abilities menu
- Enemy now look at the player
- Player's movement animation
- Player can attack
- First tutorial room
- Loop between hub and tutorial map

Changed:
--------

- Main menu button's position

Removed: 
--------

Fixed: 
--------

- Issue 7 solved -> Player's movement stop working properly when enemy is close to him.


## [0.1.0] - 17/03/2019

Added
 -----------
- Player movement 
- Entities management
- Pathfinding (not fully implemented)
- Turns system (not fully implemented)
- Transition between menu and scene

Changed
--------


Removed
--------


Fixed
--------

