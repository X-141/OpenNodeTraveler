#include "Game.h"
//#define SDL_MAIN_HANDLED
//#include <SDL2/SDL.h> 

/*
	To do list:
		> Fix a couple issues with combat information
		present to the user
		> Add the more options for menu prompts		
*/

/*
	OpenNodeTraveler Project :
		OpenNodeTraveler is small side project that combines two
		implementions meant to simulate a simple game.
		The basic structure of the program is to allow the user
		to create a "savefile" that will store the data of the
		player's party. Once the player creates a savefile, the player
		can traverse a nodemap that has enemies to fight. The game ends
		once the player reaches the end of the nodemap, from which then
		the player will be returned to the main menu.

		First Implementation: SampleCombat
		SampleCombat is an implementation of a turnbased combat
		system that is developed for the purpose of simulating
		basic combat. The information used to initiate combat
		is the entity list and the save file. 

		Second Implementation: NodeMap
		NodeMap is an implementation of a simple Linklist that the
		user can traverse through. Each Node inside the linklist has
		a stored value that can be used to dictate some sort of purpose.


		I have purposely left much of the stored data in the form of
		a txt file such that the user can manipulate any data to create
		any map and/or entity data.

		I have also left documentation on how to manipulate the data
		stored in the each of the folder coorelating to each data storage.
		Documentation is subject to change depending on the implementation
		of I/O within the program

		Feel free to modify anything in this project to your hearts content.
		I appreciate any form of advice, warnings, or general changes that
		can be made towards this project. I consider myself still relatively
		new to C++ programming, and likewise I wish to continue developing my
		ability to make projects.

		Email:X_141@protonmail.com

*/

enum MENU_STATES {
	LOAD_SAVE_FILES = 1,
	CREATE_SAVE_FILES,
	END_GAME_STATE
};
/*
	Basic menu states that allow the user to select
	different options once the application starts
*/
/*
	Main()
		->substiate Game object
			->Load Save File
				->starts the game; Loads SaveFile ; Loads NodeMap
			->Create Save File
				->start characterCreation instance -> creates save file
			->End Program
				->Ends the program 
					-> de-allocate Entitiies 
					-> de-allocate nodemap
						->de-allocate entity parties
					-> de-allocate PlayerParty
						->de-allocate PlayerEntities
*/

int main() {
	Game *game_1 = new Game();
	/*
		substantiate Game instance
		Game stores all information regarding nodemap, Entities, and playerEntities
		de-allocated at end of program
	*/
	try{
		game_1->init();
	} catch (const FilesNotFound &ex){
		std::cout << "program initialization failed" << std::endl;
		std::cout << ex.m_data << " " << ex.m_filePath << std::endl;
		return 1;
	}
	int menu_selection = 0;
	while(!game_1->getGameState()){
		try {
			std::cout << LOAD_SAVE_FILES << ". Load Save Files" << std::endl;
			std::cout << CREATE_SAVE_FILES << ". Create Save File" << std::endl;
			std::cout << END_GAME_STATE << ". End Game" << std::endl;
			std::cin >> menu_selection;
			if(std::cin.fail())
				throw InputMismatchException("Invalid input"); // -> cases of invalid input from user
			switch(menu_selection){
				case LOAD_SAVE_FILES: // -> initializes game
					game_1->selectSave();
					game_1->loadNodeMap(); // ->Loads from ../NodeMapDirectory/
					game_1->startGame(); // -> set the playerParty through NodeMap
					game_1->deallocNodeMap(); // -> destroy the contents of NodeMap
				break;
				case CREATE_SAVE_FILES:
					game_1->createSave(); // -> creates instance of CharacterCreator
				break;
				case END_GAME_STATE:
					game_1->setGameState(true); // -> exits while loop
				break;
				default:
					std::cout << "Try again" << std::endl; // invalid numeric input
				break;
			}
		} catch (const InputMismatchException &ex){
			std::cout << ex.m_data << std::endl;
			std::cin.clear(); // resets cin failbit
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	//ignore that user input
		} catch (const FilesNotFound &ex){
			std::cout << ex.m_data << " " << ex.m_filePath << std::endl;
			//Print out information regarding missing files
		}
	}
	delete game_1;
	std::getchar();
	return 0;
}
