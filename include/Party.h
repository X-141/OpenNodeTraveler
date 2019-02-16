#pragma once

#include <fstream>
#include <queue>
#include "PlayerEntity.h"


class Party {
protected:
	std::vector<Entity *> m_PartyRoster;
	int m_PartyID;
	bool m_partyKO;
public:
	Party() {}
	~Party();
public:
	std::vector<Entity *>& getPartyRoster();
	std::queue<void(*)()>& getActionList();
	int& getPartyID();
	bool& getPartyKOStatus() { return m_partyKO; }
	bool beginTurn(Party *opposing_party);
	void addEntity(Entity *entity);
	void checkPartyStatus();
	void updatePartyState();
	void printParty();
};

// bool operator<(const Entity &entity_1, const Entity &entity_2);

