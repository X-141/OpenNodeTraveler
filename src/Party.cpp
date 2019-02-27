#include "Party.h"

Party::~Party() {
	for (Entity *entity : m_PartyRoster) {
		delete entity;
	}
	std::cout << "Party deleted" << std::endl;
}

std::vector<Entity *>& Party::getPartyRoster() { return m_PartyRoster; }

int& Party::getPartyID() { return m_PartyID; }

bool Party::beginTurn(Party *opposing_party) {
	for (Entity * current_members : m_PartyRoster) {
		if (current_members->getAlive()) {
			current_members->startTurn(opposing_party->getPartyRoster());
			m_performance_sequence.push_back(current_members);
			//opposing_party->checkPartyStatus();
		}
		if (opposing_party->getPartyKOStatus())
			return opposing_party->getPartyKOStatus();
	}
	startPerformance(opposing_party->getPartyRoster()); //this will perform all the actions the player wishes to
														//commit
	//After fighting the opposing team, check the status to flag whether or not
	//they have been defeated
	return opposing_party->getPartyKOStatus();
	//party status will return a boolean value to where it was called. If the value
	//returned is true, then combat will stop. If it returns false, it will continue.
}

void Party::startPerformance(std::vector<Entity*> opposing_party){
	Entity *performer = nullptr;
	while(!m_performance_sequence.empty()){
		std::cout << "Performer: " << m_performance_sequence.front()->getName() << std::endl;
		m_performance_sequence.front()->performAction(opposing_party);
		m_performance_sequence.pop_front();
	}

	// for(Entity *entity : m_PartyRoster){
	// 	if(entity->getPerformance().m_set == true){
	// 		std::cout << "Peformer: " << entity->getName() << std::endl;
	// 		entity->performAction(opposing_party);
	// 	}
	// }
}	

void Party::addEntity(Entity * entity){
	m_PartyRoster.push_back(entity);
}

void Party::checkPartyStatus() {
	//boolean flag is set to true by default to indicate
	//the assumption that the party has been defeated
	bool status = true;
	for (Entity *entity : m_PartyRoster) {
		if (entity->getAlive()) {
			//As long as one member lives,
			//status of the partyKO == false meaning alive
			status = false;
			break;
		}
	}
	//set the flag of the party object to the given function flag
	m_partyKO = status;
}

void Party::updatePartyState() {
	for (Entity *entity : m_PartyRoster)
		entity->updateTempState();
}

void Party::printParty() {
	std::cout << "PartyID: " << m_PartyID << std::endl;
	for (Entity * entity : m_PartyRoster)
		entity->printEntityData();
}