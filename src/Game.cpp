#include "Game.h"

/*
	Game.cpp:
		Defines declarations in Game.h
		Please refer to Game.h for documentation of class purpose
*/

Game::Game() {}

Game::~Game() {
	for (Entity *entity : m_entitySet)
		delete entity;
	std::cout << "Entity List deleted" << std::endl;
	delete m_currentNodeMap;
	delete m_mainParty;
}

// Initializes Game class information. Returns false if dependencies not found
void Game::init() {
	m_mainParty = new PlayerParty();
	m_endGame = false;
	DIR *saveFolderDir = nullptr;
	if((saveFolderDir = opendir("../SaveFolder/")) == nullptr) {
		#if defined(_WIN32)
			mkdir("../SaveFolder/");
		#else
			mkdir("../SaveFolder/", 0777);
		#endif	
	}
	updateSaveFileList(); // -> can throw FileNotFound exception -> program exit
	loadEntityRoster("../EntityDirectory/EntityList.txt"); // -> throw FileNotFoundException -> program exit
}

// When a used, clear out previous saveFile list and re-list all available ones
bool Game::updateSaveFileList(){
	m_saveFileFolder.clear();
	DIR *saveFolderDir = nullptr;
	saveFolderDir = opendir("../SaveFolder/");
	//Attempts to read the SaveFolder directory, returns false if fails
	if(saveFolderDir == nullptr){
		std::cout << "SaveFolder not found. Create one to repair" << std::endl;
		return false;
	}
	//Reads all available files within the directory
	struct dirent *subSaveFiles;
	while((subSaveFiles = readdir(saveFolderDir)) != nullptr)
		if(subSaveFiles->d_name[0] != '.')
			m_saveFileFolder.push_back(subSaveFiles->d_name);
	closedir(saveFolderDir);
	return true;
}

// prompts the user to choose an available save file
void Game::selectSave(){
	if(!updateSaveFileList())
		throw FilesNotFound(" SaveDirectory is not present ", "../SaveFolder/");
	if(m_saveFileFolder.size() == 0)
		throw FilesNotFound(" No Files present in SaveDirectory " , "../SaveFolder/");
	//list out to the user all available files
	std::cout << "Which savefile would you like to load?" << std::endl;
	for(unsigned int x = 1; x <= m_saveFileFolder.size(); ++x)
		std::cout << x << ". " << m_saveFileFolder.at(x-1) << std::endl;
	int choice = 0;
	try {  
		bool valid_choice = false;
		while(!valid_choice){
		std::cin >> choice;
		if(std::cin.fail())
			throw new InputMismatchException("Invalid input");
		else if (choice > 4)
			throw new InputMismatchException("Invalid savefile choice");
		valid_choice = true;
		std::cin.clear();
		}	
	} catch (InputMismatchException &ex){
		std::cout << ex.what() << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	
	}
	//Once chosen, load that save file
	std::cin.ignore();
	loadSaveFile("../SaveFolder/" + m_saveFileFolder.at(choice-1) + "/");
}

// allows the user to create a save file that the program can load
void Game::createSave(){
	std::cin.ignore();
	int save_fileIndex = m_saveFileFolder.size();
	//loads filepath for which new save information will be stored
	std::string fileName = "../SaveFolder/saveFile" + std::to_string(save_fileIndex) + "/";
	#if defined(_WIN32)
		mkdir(fileName.c_str());
	#else
		mkdir(fileName.c_str(), 0777);
	#endif
	//creates character information and store it inside the save directory
	CharacterCreator character_creator_instance(fileName.c_str());
	std::cout << "Save file creation finished" << std::endl;

}

// once the user picks a save file to load, the filepath is passed and the
// player entities are loaded.
void Game::loadSaveFile(const std::string& filepath){
	// load all .txt files within the directory
	std::vector<std::string> character_files;
	DIR *save_file = opendir(filepath.c_str());
	struct dirent *subFiles;
	while((subFiles = readdir(save_file)) != nullptr)
		if(subFiles->d_name[0] != '.')
			character_files.push_back(subFiles->d_name);
	// retrieve entity information from the file
	// name -> stat information -> action_information
	for(std::string filename : character_files){
		std::ifstream character_file(filepath+filename);
		std::vector<int> s_val;
		std::vector<int> a_val;
		std::string line;
		// retrieve name from first line in txt file
		std::getline(character_file, line);
		std::string name = line;

		// parse next two lines for stat and action information
		std::getline(character_file, line);
		int stat_index = 0;
		int mov_index = 0;
		// push the values retrieved into vectors
		// information_here -> s_val (stat value)
		while(line[mov_index] != ';'){
			if(line[mov_index] == ':'){
				s_val.push_back(std::stoi(line.substr(stat_index, (mov_index - stat_index))));
				stat_index = mov_index + 1;
			}
			++mov_index;	
		}
		s_val.push_back(std::stoi(line.substr(stat_index, (mov_index - stat_index))));

		std::getline(character_file, line);
		stat_index = 0;
		mov_index = 0;
		//parse for action values
		// information_here -> a_val (action values)
		while(line[mov_index] != ';'){
			if(line[mov_index] == ':'){
				a_val.push_back(std::stoi(line.substr(stat_index, (mov_index - stat_index))));
				stat_index = mov_index + 1;
			}
			++mov_index;	
		}
		a_val.push_back(std::stoi(line.substr(stat_index, (mov_index - stat_index))));
		
		// send retrieved information to substantiate PlayerEntity to be placed into
		// the player's main party
		m_mainParty->getPartyRoster().push_back(new PlayerEntity(name, s_val, a_val));
		character_file.close();
	}
	closedir(save_file);
	std::cout << "Save Characters loaded" << std::endl;
}
// Load in entity information to substantiate all entities
void Game::loadEntityRoster(const std::string& filepath){
	std::ifstream file;
	file.open(filepath);
	if(!file.is_open())
		throw FilesNotFound(" EntityList not found " , "../EntityDirectory/");
	std::string line;
	// continually retrieve entity information
	// three lines represent complete entity information
	while (std::getline(file, line)) {
		std::vector<int> s_val;
		std::vector<int> a_val;
		std::string name = line;
		// retrieve entity name from first of three lines
		std::getline(file, line);
		int stat_index = 0;
		int mov_index = 0;
		// parse next two lines for stat and action information
		while(line[mov_index] != ';'){
			if(line[mov_index] == ':'){

				s_val.push_back(std::stoi(line.substr(stat_index, (mov_index - stat_index))));
				stat_index = mov_index + 1;
			}
			++mov_index;	
		}
		s_val.push_back(std::stoi(line.substr(stat_index, (mov_index - stat_index))));
		
		std::getline(file, line);
		stat_index = 0;
		mov_index = 0;
		while(line[mov_index] != ';'){
			if(line[mov_index] == ':'){
				a_val.push_back(std::stoi(line.substr(stat_index, (mov_index - stat_index))));
				stat_index = mov_index + 1;
			}
			++mov_index;	
		}
		s_val.push_back(std::stoi(line.substr(stat_index, (mov_index - stat_index))));
		
		// send retrieved information to substantiate Entity to be placed into
		// the Game's entity list
		m_entitySet.push_back(new Entity(name, s_val, a_val));
	}
	std::cout << "Entities loaded" << std::endl;
	file.close();
}

// read from NodeMapDirectory nodemap information to create a linklist
// for player to traverse
void Game::loadNodeMap() {
	std::ifstream nodeMapFile;
	nodeMapFile.open("../NodeMapDirectory/NodeMap1.txt");
	std::string line;
	if(!nodeMapFile.is_open())
		throw FilesNotFound(" Default NodeMap not found " , "../NodeMapDirectory/");
	// retrieve first two lines representing
	// cardinality of the nodemap
	// cardinality of parties existing in the nodemap
	std::getline(nodeMapFile, line);
	int party_size = std::stoi(line);
	std::getline(nodeMapFile, line);
	int node_size = std::stoi(line);
	// Parse each line to create/link/fill each node
	// CREATE_NODE -> creates a node with party value
	// LINK_NODE -> links two nodes (doubly linked to allow foward and back movement)
	// LINK_PARTY -> links entites in the m_entitySet
	m_currentNodeMap = new NodeGraph(party_size, node_size);
	while (std::getline(nodeMapFile, line)) {
		auto pos_1 = line.find_first_of(':');
		auto pos_2 = line.find_last_of(':');
		const int value_1 = std::stoi(line.substr(0, pos_1));
			// -> Entity_ID
			// -> Node_ID
		const int value_2 = std::stoi(line.substr(pos_2 + 1, line.size()));
			// -> Party_ID
			// -> Node_ID
		std::string command = line.substr(pos_1 + 1, (pos_2 - (1 + pos_1)));
			// Commands available: create_node, link_node, link_party

		if (command == CREATE_NODE) {
			// if that party does not exist, create a new party
			if (m_currentNodeMap->getVertexSet().at(value_1) == NULL) {
				Party *party_cpy = new Party();
				std::vector<Entity *> temp_roster = m_currentNodeMap->getPartyList().at(value_2)->getPartyRoster();
				for(Entity * entity : temp_roster){
					Entity *ent_cpy = new Entity();
					*ent_cpy = *entity;
					party_cpy->addEntity(ent_cpy);
				}
				m_currentNodeMap->getVertexSet()[value_1] = new Node(party_cpy, value_2);
			}
			else {
				std::cout << "Node already exists at this index. No Node created" << std::endl;
			}
		}
		else if (command == LINK_NODE) {
			if ((m_currentNodeMap->getVertexSet().at(value_1) == NULL) 
				|| (m_currentNodeMap->getVertexSet().at(value_2) == NULL)) {
				std::cout << "No node exists at this index!" << std::endl;
					//catches segmentation flag
			}
			else {
				m_currentNodeMap->linkNode(m_currentNodeMap->getVertexSet().at(value_1), 
					m_currentNodeMap->getVertexSet().at(value_2));
			}
		}
		else if (command == LINK_PARTY) {
			if ((m_entitySet.at(value_1) == NULL)) {
				std::cout << "flag Entity does not exist" << std::endl;
			} else if ((value_2 > m_currentNodeMap->getPartyCardinality()) || (value_2 < 0)) {
				std::cout << "No parties in that index. Out of bounds" << std::endl;
			}
			else {
				Entity *cpy = new Entity();
				*cpy = *m_entitySet.at(value_1);	
				m_currentNodeMap->getPartyList().at(value_2)->getPartyRoster().push_back(cpy);
			}
		}
	}
	// sets the head/starting point and the last node in the list
	// as the tailnode
	Node *temp_tail = nullptr;
	for (Node *node : m_currentNodeMap->getVertexSet()) {
		if (node != nullptr) {
			temp_tail = node;
			if (m_currentNodeMap->getHeadNode() == nullptr) {
				m_currentNodeMap->setHeadNode(node);
				m_currentNodeMap->setCurrentNode(m_currentNodeMap->getHeadNode());
			}
		}
	}
	m_currentNodeMap->setTailNode(temp_tail);
	std::cout << "Map loaded" << std::endl;
	nodeMapFile.close();
}

void Game::deallocNodeMap(){
	delete m_currentNodeMap;
}

// begins the game by sharing the playerparty to the nodemap object
void Game::startGame() {
	m_currentNodeMap->setPlayerParty(m_mainParty);
	while (!m_currentNodeMap->getNodeMapReached()) {
		m_currentNodeMap->partyMove();
	}
}

void Game::listEntities() {
	for (Entity *entity : m_entitySet)
		entity->printEntityData();
}

void Game::printNodeGraphInfomation() {
	for (Node *node : m_currentNodeMap->getVertexSet()) {
		std::cout << "Party value : " << node->getValue() << std::endl;
		for (Entity *entity : node->getParty()->getPartyRoster()) {
			entity->printEntityData();
		}
	}
	m_currentNodeMap->printNodeGraph();
	for (Entity *entity : m_mainParty->getPartyRoster()) {
		entity->printEntityData();
	}
}