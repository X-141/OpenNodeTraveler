#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Combat.h"

/*
	Party.h:
		Represents each node that can be substiated by
		the nodemap class.
		Each node contains a list of pointers to other nodes
		in foward and backward direction (doubly linked).
		Each node also contains a m_party pointer which
		represents the entity party that exists at that current
		location. This pointer is used to be shared with the 
		combat class to simulate combat with the player class

		Note: as of this version, no storage of player party or
		misc. objects. Though in the future this may change.

*/


class Node {
public:
	Node(Party *party, const int &value);
	~Node();
public:
	void addNextPointer(Node *node);
	void addPrevPointer(Node *node);
	std::vector<Node *>& getNextPointerSet();
	std::vector<Node *>& getPrevPointerSet();
	int getValue() { return m_value; }
	Party* getParty() { return m_party; }
private:
	std::vector<Node*> m_prevLinkSet;
	std::vector<Node*> m_nextLinkSet;
	int m_value; // represents the value assigned to each node
				 // also coorelates to the party value
	Party *m_party;	// maintains a pointer to the party that exist
					// at this node
};