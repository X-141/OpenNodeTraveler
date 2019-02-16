#pragma once
#include "Combat.h"
#include "NodeGraph.h"
#include "CharacterCreator.h"

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

//Set macros for matching NodeMap commands -> Check documentations in the "NodeMapDirectory" for details
#define CREATE_NODE "create_node" // -> creates node
#define LINK_NODE "link_node"	  // -> links node
#define LINK_PARTY "link_party"   // -> links entites to party values

/*
	Game.h:
		The purpose of this class is to allow the user
		to play through an instance of both traversing a
		Linklist (nodemap) as well as competing with hostile
		entities. The Game class handles all operation of file
		I/O and is dependant on those files in order to function.
		
		File Dependencies:
			-> ../SaveFile/saveFileN/*.txt
				>Read in *.txt files in this saveFileN
				directory and creates PlayerEntity objects
				that the player uses to operate the party

			-> ../EntityDirectory/EntityList.txt
				>Storage of all entities and their information.
				Entity objects are created from the information, and
				those objects are copied to their induvidual EntityParty
				depending on the requirements of the NodeMap file

			-> ../NodeMapDirectory/NodeMapN.txt
				>Stores Linklist information and substantiates each node
				to link them. Each node substiated has a induvidual party
				value from which new parties are created and entities are
				copied to.

		This class is de-allocated once the program loop ends, freeing up
		memory. NodeMap is de-allocated once the player has reached the end
		of the linkedlist ( Node == NodeMap->m_tailNode )
*/

class Game {

public:
	Game();
	~Game();

public:
	void init();
	void selectSave();
	void createSave();
	bool updateSaveFileList();
	bool getGameState() { return m_endGame; }
	void setGameState(bool tf) { m_endGame = tf; }
	void deallocNodeMap();
	void listEntities();
	void loadSaveFile(const std::string& filepath);
	void loadEntityRoster(const std::string& filepath);
	void loadNodeMap();
	void startGame();
	void printNodeGraphInfomation();
private:
	std::vector<std::string> m_saveFileFolder; 	// ->stores all available savefiles
												// updated each time new file is created
	bool m_endGame;	//Controls when the program ends
	//std::vector<NodeGraph*> m_mapSet; // For future version, stores all nodeMaps available
	std::vector<Entity *> m_entitySet; // contains all entity information. excludes PlayerEntites
	NodeGraph *m_currentNodeMap; // indicates what nodeMap is being used
	PlayerParty *m_mainParty; // stores the playerParty information
	Combat *m_currentCombat; // tracks the current combat instance the player is going through



};