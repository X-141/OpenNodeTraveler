#include "NodeGraph.h"

// sets the node and party cardinality for the nodegraph
NodeGraph::NodeGraph(int party_size, int graph_cardinality) {
	m_PartyList.reserve(party_size);
	for (int x = 0; x < party_size; ++x) {
		m_PartyList.push_back(new Party());
	}
	m_VertexSet.resize(graph_cardinality);
	m_headNode = nullptr;
	m_tailNode = nullptr;
}

// deletes each node and parties
NodeGraph::~NodeGraph() {
	for (Node *node : m_VertexSet)
		delete node;
	for (Party *party : m_PartyList)
		delete party;
	std::cout << "Finalized destructor" << std::endl;
}

// operation for adding nodes to graph
void NodeGraph::addNode(Node *node) {
	if (m_headNode->getNextPointerSet().empty()) {
		m_headNode->addNextPointer(node);
		node->addPrevPointer(m_headNode);
		m_tailNode = node;
		m_VertexSet.push_back(node);
	}
	else {
		m_tailNode->addNextPointer(node);
		node->addPrevPointer(m_tailNode);
		m_tailNode = node;
		m_tailNode = node;
		m_VertexSet.push_back(node);
	}
}

//links each node (doubly linked)
void NodeGraph::linkNode(Node *node_0, Node *node_1) {
	//node_0 is the parent node
	//node_1 is the child node
	node_0->addNextPointer(node_1);
	node_1->addPrevPointer(node_0);
}

void NodeGraph::printNodeGraph() {
	for (Node *node : m_VertexSet) {
		if (node != NULL) {
			int primary_node_value = node->getValue();
			std::cout << "Prev pointer set" << std::endl;
			if (node->getPrevPointerSet().empty()) {
				std::cout << "NULL <- " << primary_node_value << std::endl;
			}
			else {
				for (Node *pre_pointer : node->getPrevPointerSet()) {
					std::cout << pre_pointer->getValue() << " <- " << primary_node_value << std::endl;
				}
			}
			std::cout << "next pointer set" << std::endl;
			if (node->getNextPointerSet().empty()) {
				std::cout << primary_node_value << " -> NULL" << std::endl;
			}
			else {
				for (Node *next_pointer : node->getNextPointerSet()) {
					std::cout << primary_node_value << " -> " << next_pointer->getValue() << std::endl;
				}
			}
		}
	}
}

// prompts the user to select a node to go to next. Prints out available nodes to travel to
void NodeGraph::partyMove() {
	// check to see if there is an enemy party at that node that is alive
	if (!m_currentNode->getParty()->getPartyKOStatus()) {
		m_currentCombatInstance = new Combat(m_playerParty, m_currentNode->getParty());
		m_currentCombatInstance->startFight();
		delete m_currentCombatInstance;
		if (m_currentNode->getParty()->getPartyKOStatus()) 
			std::cout << "Enemy Party has been defeated!" << std::endl;
	}

	// as long as the player party is not dead, ask for movement
	bool valid_choice = false; // as long as the player has not chosen 
							   // ask for location
	if (!m_playerParty->getPartyKOStatus()) {
		printPossibleMovements(m_currentNode);
		std::cout << "Which node would you like to move to?" << std::endl;
		while (!valid_choice) {
			int choice;
			std::cin >> choice;
			//See if you can implement this as one for loop that iterates
			//through both vectors

			//foward directions
			for (Node *node : m_currentNode->getNextPointerSet()) {
				if (node->getValue() == choice) {
					m_currentNode = node;
					valid_choice = true;
					break;
				}
			}
			//backward directions
			if (!valid_choice) {
				for (Node *node : m_currentNode->getPrevPointerSet()) {
					if (node->getValue() == choice) {
						m_currentNode = node;
						valid_choice = true;
						break;
					}
				}
			}
			std::cin.clear();
			std::cin.ignore();
		}
		//check to see if the node reached is the end
		if (m_currentNode == m_tailNode) 
			m_NodeMapReached = true;
	}
	// if the player party is defeated, exit the map by marking reached as true
	else {
		std::cout << "Player has been defeated!" << std::endl;
		m_NodeMapReached = true;
	}
	
}

// prints entire map with node values for each (value represents party value)
void NodeGraph::printPossibleMovements(Node *node) {
	if (node->getPrevPointerSet().empty()) {
		std::cout << "NULL <- " << node->getValue() << std::endl;
	}
	else {
		for (Node *prevPlaces : node->getPrevPointerSet()) {
			std::cout << prevPlaces->getValue() << " <- " << node->getValue() << std::endl;
		}
	}
	if (node->getNextPointerSet().empty()) {
		std::cout << node->getValue() << " -> NULL" << std::endl;
	}
	else {
		for (Node *nextPlaces : node->getNextPointerSet()) {
			std::cout << node->getValue() << " -> " << nextPlaces->getValue() << std::endl;
		}
	}
}
