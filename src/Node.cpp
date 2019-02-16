#include "Node.h"

// substantiate node. As of this version, each node can only have 4 pointers
// connected to nodes foward and back
Node::Node(Party *party, const int &value) : m_party(party), m_value(value) {
	m_nextLinkSet.reserve(4);
	m_prevLinkSet.reserve(4);
}

Node::~Node(){
	delete m_party;
	std::cout << "Node destroyed" << std::endl;
}

void Node::addNextPointer(Node *node) {
	m_nextLinkSet.push_back(node);
}

void Node::addPrevPointer(Node *node) {
	m_prevLinkSet.push_back(node);
}

std::vector<Node*>& Node::getNextPointerSet() {
	return m_nextLinkSet;
}

std::vector<Node*>& Node::getPrevPointerSet() {
	return m_prevLinkSet;
}
