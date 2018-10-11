# Keno 
Simple text-based version of the game Keno.

# Introduction

Keno is a popular gambling game with similarities to a lottery or bingo. Players place a bet and
choose anywhere from one to twenty numbers between 1 and 80, inclusive. Once the players have
chosen their numbers, the game generates twenty random numbers between 1 and 80, and players
receive a payoff based on how many numbers they picked that matched the chosen numbers.
For example, if a player picked seven numbers and all seven were chosen (very unlikely!), she
might win around $10.000 for a ten dollar bet. The actual payoffs are based on the probabilities of
hitting k numbers out of n chosen.

# Dependencies

To build this project you'll need some dependencies listed bellow:
* git
* g++
* cmake

And clone this repository, using `git clone <this repo>`

# Compiling

To compile this project move to keno directory and make a `build` directory;
```
mkdir build 
```
Create a makefile using `cmake`, to manage and build the project;
```
cmake ..
```
Then, build the project;
```
make
```

A bin file called `keno` will be created.
 
# Gameplay 

To run the program you'll need a `.dat` bet file, wich have this format

`bet_file.dat` 
---------------
Lines | Representing
----- | -----------
1500.0 | The player’s initial credit, expressed as a real value.
3	   | The number of rounds the game should run, represented by an integer.
21 12 64 | A set of up to 15 unique numbers in any order, separated by at least one white-space.

Any other representation for will be considered a **invalid** bet file.

Therefore, just execute the bin file, passing through argument line the `.dat` bet file:
```
$./keno bet_file.dat
```

The game will show you bet informations and play the rounds.

At the end of the game will be showed a **sumary** of the money that you spent, the money you have won and how much you have now.

# Authorship

This project has been developed by [Felipe Andrade](https://github.com/felpsisonfire) & [Marcos A. Cavalcanti Junior](https://github.com/marcosacj) to the Programming Language I course, from Information Technology bachelor degree of Federal University of Rio Grande do Norte.
