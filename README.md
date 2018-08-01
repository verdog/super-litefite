# super litefite
super litefite is a local multiplayer fiting (haha get it?) game in a top-down perspective. hopefully i'll encorperate some lite (hehe haha) mechanics too.  

it's called "super" litefite because i scrapped the original game and started from scratch a second time.
i feel that it was a good decision.

## dependencies
this game uses SFML for handling graphics, sounds, and windows. you'll need it to run this game. get it [here](https://www.sfml-dev.org/ "SFML")

i'm building this game on linux (ubuntu 18.04). i've only tested it on linux. you'll probably need to be on linux.

i'm using some modern (c++17) features, so you'll need a compiler that supports them.

i'm personally compiling this game with gcc (g++), but it might work with other compilers too.

## how do i run it

try running these in the root directory:

```
make clean # deletes all object/binary files
make       # compiles the game
make run   # short for "./bin/super-litefite"
```

you can also try this:
```
make fast
```
to build with compiler optimizations on, which usually boosts performance a lot.

## warning
i write bad code. you have been warned.
