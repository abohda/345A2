Assignment 2 (with distinct part 2) for COMP 345, Winter 2016
By Anastasiya Bohdanova, ID#40017040

This assignment was written in Visual Studio Enterprise 2015 and should be compiled in and run from VS. The main method is located in GameEngine.cpp. 

There are two components to this program. The first, located in the testPattern() method in GameEngine.cpp, demonstrates the full functional capacity of the observer pattern. It allows the user to add and remove cities, update connections between them, add players, build up to 3 houses per city, and print out the map's information through the MapView class. I recommend that you first evaluate the implementation of the observer pattern using the call to testPattern(), and then comment out that line to see that gameplay still works as before.

The second component can be found in the gameplay() method, and allows users to play a turn of PowerGrid, as in the intermediate project build, with some minor modifications made to make use of the observer pattern. The pattern's internal workings aren't evident in gameplay, however, which is why I have included all the functionalities listed in testPattern().