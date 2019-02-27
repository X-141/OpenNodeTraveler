#include "Combat.h"


//Pass in two pointers to a combat contructor to begin combat
Combat::Combat(Party *party_1, Party *party_2)
	: m_party_1(party_1), m_party_2(party_2) {
	std::cout << "initializing combat!" << std::endl;
}

Combat::~Combat() {
	//In previous implementations, both parties were to be deleted. However,
	//given that m_party_2 must be kept in order for proper deallocation, and
	//m_party_1 is the player party. Both are no longer deallocated.
  //at the end of the combat instance
	/*delete m_party_1;
	delete m_party_2;*/
}

void Combat::startFight() {
	while (true) {
		if(m_party_1->beginTurn(m_party_2)) // if return true that means the player party won
			break;
		std::cin.get();
		m_party_2->updatePartyState();
		std::cout << std::endl;
		if(m_party_2->beginTurn(m_party_1)) // if return true that means the player party lost
			break;
		m_party_1->updatePartyState();
		std::cin.get();
		std::cout << std::endl;
	}
}
