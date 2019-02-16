#pragma once
#include "Entity.h"
#include <exception>

/*
	PlayerEntity.h:
		Inherits from the standard Entity class that is used for 
		standard entities. This class defines special functions that
		are available to only player entities
*/

class PlayerEntity : public Entity {

public:
	PlayerEntity(const std::string& name, std::vector<int> s_val, std::vector<int> a_val);
	~PlayerEntity();
	void startTurn(std::vector<Entity *> opposing_party);
	//Based on the virtual function of the parent class
};