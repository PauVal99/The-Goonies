# The Goonies

The Goonies is a recreation of [The Goonies](https://www.youtube.com/watch?v=yhFCiZIcjgE) video game for MSX made in VJ at FIB for educational purposes. It is made with OpenGL and C++.

There is a [video demo](demo.mp4).

Made by:
 + Sergi Doce
 + Pau Val

## Play

In order to play download the [bin](bin) folder and run the `.exe`.

It is only available on Windows.

## Instructions
Keys:
 + **Arrow Up** Jump - Move Up on Vine - Take Portal on Portal
 + **Arrow Left** Move Left
 + **Arrow Right** Move Rigt
 + **Arrow Down** Move Down on Vine
 + **Space** Attack
 + **T** Use Time Clock

God Mode
 + **G** Activate God Mode, becomes invulnerable and gets all perks
 + **S** Go to next scene
 + **F** Save a friend of the current scene

## Functionalities

 - There are five scenes of three screens each. Each one is a different color, the yellow one is vertical.
 - Portals are implemented between scenes. You can only go through a portal if you have rescued all friends in the scene.
 - There are lianas to go up and down platforms.
 - The player can jump to avoid obstacles.
 - Player can press space to attack and eliminate enemies.
 - There are a total of 13 friends to rescue. Each friend is locked in a door that requires a key or two to open.
 - There are two enemies, the skull moves from side to side on the ground and the bat flies and chases you.
 - There are three obstacles:
     * Water drop: A drop falls from the ceiling.
     * Stone: A stone that rises and falls.
     * Water leak: a leak that activates every so often.
 - The player has 100 life points which increases with each level. You level up every 100 experience points. Killing enemies gives experience.
 - There are five different power ups:
     * Potion of Vitality: You recover all life.
     * Experience Potion: Increases experience by 60 points.
     * Shield: Ignores the next three hits.
     * Boots of Mobility: You move twice as fast.
     * Time clock: pressing the T key stops the time 10 seconds.
 - Pressing the G key activates God Mode, you are invulnerable and gives a key, mobility boots and a magic watch. Pressing G again disables the invulnerability.
 - If you have God Mode activated by pressing S you go to the next scene.
 - If you have God Mode activated by pressing F you rescue all friends in the scene automatically.
 - There is a main menu with the credits, if you press the spacebar the instructions come out and the game starts.
 - There is a screen in case of Game Over and in case the game is passed to you.
 - There are sounds for all interactions and a background soundtrack.

## Modify

All source code and assets are in the [src](src) folder. The game is made with [Visual Studio](https://visualstudio.microsoft.com/es/vs/) 2019. To modify it open the project file [src/The Goonies.sln](src/The%20Goonies.sln), the rest is configured by default.

## Contact

Any doubt email me at pau.val.tubau99@gmail.com

## License

[MIT](https://choosealicense.com/licenses/mit/)
