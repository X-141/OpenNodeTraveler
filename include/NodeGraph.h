#pragma once
#include "Node.h"
#include <fstream>

/*
	NodeGraph.h
		The purpose of this class is to set up
		a linklist that allows the player to traverse
		through until they arrive at the end (tail node).
		The NodeGraph class maintains a main_party (player party)
		and a m_party vector which contains pointers to all
		parties existing on the map. Each node is assigned
		a copy of each party if party_id of that node matches
		the index in the party list.

		The class will prompt the player to select a node that is
		incident to other nodes, and if a living party exist at that
		node they will enter a combat instance

*/

class NodeGraph {
public:
	NodeGraph(int party_size, int graph_cardinality);
	~NodeGraph();
public:
	void addNode(Node *node);
	void linkNode(Node *node_0, Node *node_1);
	void printNodeGraph();
	Node * getHeadNode() { return m_headNode; }
	Node * getTailNode() { return m_tailNode; }
	Node * getCurrentNode() { return m_currentNode; }
	bool& getNodeMapReached() { return m_NodeMapReached; }
	std::vector<Node*>& getVertexSet() { return m_VertexSet; }
	std::vector<Party*>& getPartyList() { return m_PartyList; }
	int getGraphCardinality() { return m_VertexSet.size(); }
	int getPartyCardinality() { return m_PartyList.size(); }
	PlayerParty * getPlayerParty() { return m_playerParty; }
	void setPlayerParty(PlayerParty *playerParty) { m_playerParty = playerParty; }
	void setHeadNode(Node *headNode) { m_headNode = headNode; }
	void setTailNode(Node *tailNode) { m_tailNode = tailNode; }
	void setCurrentNode(Node *currentNode) { m_currentNode = currentNode; }
	void partyMove();
	void printPossibleMovements(Node *node);
private:
	Node *m_headNode;
	Node *m_tailNode;
	std::vector<Node *> m_VertexSet; // maintains a list of all available nodes
	std::vector<Party *> m_PartyList; // maintains a list of all parties. excluding party copies in each node
	PlayerParty *m_playerParty; // represents the player party
	Combat *m_currentCombatInstance; // once the player reaches a node with a living hostile party.
									 // combat instance is created
	Node *m_currentNode; // tracks the current location of the player party
	bool m_NodeMapReached; // states whether the player has reached the end. ends node traveling
};