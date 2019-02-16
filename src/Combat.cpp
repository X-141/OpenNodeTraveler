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
		//For each party give start each entity off to begin the turn
			//->check if the party is dead first
			//->if they are dead do not go any further in the program
				//->select a party member that isnt dead to fight
				//->if the opposing party member is dead, find a different target.
				//->attack target and set the status of the opposing target to reflect
		//repeat until break case is reached
    //break case is reached once a party has achieved defeat (ex, if 
    //m_party_1 -> getKOstatus() == true)
		//break case will be achieved if any of the beginTurn functions return false
		if (m_party_1->beginTurn(m_party_2))
			break;
		std::cin.get();
		m_party_2->updatePartyState();
		if (m_party_2->beginTurn(m_party_1))
			break;
		m_party_1->updatePartyState();
		std::cin.get();
	}
}
