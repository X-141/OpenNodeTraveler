#pragma once

#include <fstream>
#include <queue>
#include "PlayerEntity.h"


/*
	Party.h:
		Establishes a party of entities to simulate a combat party for
		the program. Collectively these entitiy represent the status of the
		party. If atleast one entity is alive, the party KO_Status is false.
		Otherwise the party KO_Status is true representing a dead party.

		NOTE: The only way for the party to be reorganized is to modify
		the way the party is loaded into each party object at program startup
*/

class Party {


protected:
	std::vector<Entity *> m_PartyRoster;
	int m_PartyID;
	bool m_partyKO; // false == party is still alive
					// true == party is dead
public:
	Party() {}
	~Party();
public:
	std::vector<Entity *>& getPartyRoster();
	std::queue<void(*)()>& getActionList();
	int& getPartyID();
	bool& getPartyKOStatus() { return m_partyKO; }
	virtual bool beginTurn(Party *opposing_party);
	void startPerformance(std::vector<Entity *> opposing_party);
	void addEntity(Entity *entity);
	void checkPartyStatus(); // updates the temporary states of each entity.
							 // example if an entity has a defense boost and
							 // it needs to be reverted back to original value.
	void updatePartyState();
	void printParty();
};


