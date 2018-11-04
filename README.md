# robosim
Robo Sim.

Main.cpp contains the main method.
Input files are immediately read from a directory (called Input). Each line in each file is processed as a command.
Add more files to run with the program.

Allowed commands:
PLACE <X>,<Y>,<FACE> 
MOVE
LEFT
RIGHT
REPORT

<X>, <Y> : Integer between 0 and 4.
<FACE> : NORTH,EAST,WEST or SOUTH.

All command words are case sensitive. Extra chars after the word is ignored.

# Source code
Developed with  C++ compiler VS2017 provided. Probably C++ 14.
Dependent on std::experimental::filesystem to read directory files.

# Test code
Test code and frame work are included. Intended to use with Visual Studio 2017 on Windows.