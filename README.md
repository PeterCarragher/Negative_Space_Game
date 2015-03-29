# Negative-Space
Puzzle game based on negative space and 2D platformer engine. 

Set in a strange world of greyscale and boxes, you must guide the two characters to their goals at the bottom of the map. The black character can only stand on black objects while the white character can only stand on white objects. Both can move through grey space and the space of the opposite colour. 

To play: Use A,S,D & W keys to move left, down, right and up repectively. Both characters are controlled by the same keys. 

Platformer engine:
Uses ALLEGRO5 libraries for event handling, image loading etc. 
Uses Tiled map editor and an XML parser for level maps. 
Classes for enemies have been created but are left out of this prototype for the purposes of just showing the main mechanic. 

To do:
Improve level design.
Add more gameplay elements: enemies, timer, traps etc. 
Add game menu to select levels. 
Implement a better collision detection system based on vectors to allow for sloping surfaces.
