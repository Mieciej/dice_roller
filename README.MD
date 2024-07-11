<p align="center" style="padding: none; margin:none;">
    <img src="./dice_roller.png" height="170">
</p>
# Dice Roller
Dice roller is simple linux program for rolling dice.

## Building
To build the project run:
```
./build.sh
```
## Usage
To roll the dice type number of dice `n` and number of sides `s` seprated by `d` character, e.g.:
```
./roll 3d6 
```
will roll 3 times a 6 sided die.

Program also supports basic math operations, e.g.: 
```
./roll '(3d6-1d4)*1d8'
```
will roll 3 times 6 sided die substract result of rolling 4 sided die and multiply the whole thing by the result of rolling 1d8.


