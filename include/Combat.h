#pragma once
#include "PlayerParty.h"

/*
    Combat.h:
      The combat class handles all instances of combat within the node
      traveler program. When an instance is initiated, pointers are passed
      into the instance and the entities are used to simulate a turn based
      combat system. Each party contains three entities that cycle turns
      with each turn performing a specific action dictated by the player, or
      if by the entity randomly.

      The current iteration of this project only allows the entities to select
      random action and random opposing entities. There is not a set way to
      change entity order unless modified in the nodemap linker. The player
      entities are ordered by alphabetical order.
*/

class Combat {
public:
	Combat(Party *party_1, Party *party_2);
	~Combat();
	void startFight();
private:
	Party *m_party_1;
	Party *m_party_2;
};

