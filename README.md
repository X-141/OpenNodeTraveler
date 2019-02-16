# OpenNodeTraveler
This project serves as a combination of both the SampleCombat and the SampleNodeMap programs. OpenNodeTraveler simulates a turnbased game where the user can generate a party, travel to different nodes, and confront different parties of entities.


# Requirements
1. C/C++ compilier -> 
  * Linux gcc/g++ v8.2.1 tested -> working
  * MacOS AppleClang v10.0.0 tested -> working
  * Windows MingW gcc/g++ v6.3.0 tested -> working
2. Make -> minimum version tested 3.81
3. Cmake -> minimum required 3.12

# How to Compile
Windows w/ MingW
1. Make a build directory -> "mkdir build"
1. in the project directory -> "cd build"
2. compile using cmake -> "cmake -G "Unix Makefiles" .."
3. after compilation finishes -> "make"
4. A windows executable named "RUN.exe" should've been created
5. "./Run"

Linux/Unix
1. Make a build directory -> "mkdir build"
1. in the project directory -> "cd build"
2. compile using cmake -> "cmake .."
3. after compilation finishes -> "make"
4. executable file named "RUN" should've been created
5. "./Run"


# How to Play
Once you have compiled the program and generated an executable, you will be prompted with a menu to either load a savefile (needed if there is no savefile present) or to create a savefile. If the player chooses to create a savefile, they will be prompted to create 3 characters for which they can assign stats. Once the player creates a savefile, they are free to select the save file to begin the game. The game will load the entities and the nodemap for the player to explore and fight within. The player can select actions against the opposing parties until they win. Once defeated, the player can navigate the map by entering values into the terminal that coorelate with the values presented. The player will continually fight and navigate until they reach the tailnode of the map (The end of the game). Once they reach the end, they will be booted back into the main menu.


# What Can I Do?
OpenNodeTraveler allows the user to customize their own nodeMap, Characters, and Entities (in the form of text files) to load into the program. I have provided various documentations on how to generate and customize the .txt files such that the user is free to manipulate those aspects of the program.

# Purpose of this project
This is a side project that I have created to continue learning how to develop and design programs for different platforms, and and combining smaller programs into one unified application. I have emphasized that aspects of this program must be configurable by the user. As such, the majority of the design decisions made have been directed towards this goal. I will continue to do my best to see this standard upheld and make them intuitive, but it is subject to change. I have provided external documentations and comments in the source code to explain how the program runs. 
I regard this project as still in it's infancy, and much of the program may drastically change or become null in the future.

# Notes:
* **Will there be graphics?**
In the future, I do plan to add graphics to make a presentable application using SDL2. I have added (but commented out) sections
of the program that allow for SDL2 testing. However, I wish to establish a solid program before commiting to a graphical presentation.
* **How frequently will this project be updated?**
I will continue to invest time into this project as long as time affords it. I do have many other side project ideas in mind that I'm really eager to try. I'm also still attending school and advancing my education. It is my hope that in the coming years, that I can continue to develop my design/programming abilities. This side project is just one example of my curiosity to develop on my ideas.
* **Final Note:**
Feel free to reach out to me via email to either give advice or criticism! I consider myself still novice, and likewise i present myself on this platform as a person that wishes to learn through experience and feedback.
Email: X_141@protonmail.com
