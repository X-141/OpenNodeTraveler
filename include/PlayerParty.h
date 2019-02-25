#pragma once
#include "Party.h"

/*
	PlayerParty.h:
		Inherits from the Party class and serves as a class
		to differientiate itself from the standard Party class
		that is used for regular entities
*/

class PlayerParty : public Party {
public:
	PlayerParty(const std::string& filename);
	PlayerParty();
	~PlayerParty();
public:
	bool beginTurn(Party *opposing_party);

};

