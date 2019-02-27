#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "CustomException.h"

/*
	Entity.h:
		This class stores all information regarding all entities
		within this program. It defines all actions they can perform
		as well as functions that is used to verify different states
		of the object.

		Within the current version: All actions are defined within
		the Entity class, with each action being selected using a 
		switch case. However this is to be changed in the future 
		once more actions are added.

		Within the Entity.h, the struct Action is defined that stores
		a function pointer as well as the name of the function that it
		coorelates with. This allows the user to set an action that can
		be performed during combat
*/

class Entity 
{
	// Action contains information such as the name of the action
	// as well as a function pointer to the action it will perform
	struct Action {
		Action(std::string name, void(Entity::*pointer)(Entity*)) {
			m_actionName = name;
			m_action = pointer;
		}
		std::string m_actionName;
		void (Entity::*m_action)(Entity*);
	};

	struct Performance {
		Performance(){
			m_set = false;
		}
		Performance(int t_action, int t_performer, int t_offender)
			:  m_action(t_action), m_performer(t_performer), m_offender(t_offender)
		{
			m_set = false;
		}
		std::string getPerfStatus(){
			if(m_set == false)
				return " NOT READY";
			return " READY -> " + m_action_name + " -> " + m_offender_name;
		}
		std::string m_action_name, m_offender_name;
		int m_action, m_performer, m_offender;
		bool m_set;
	};

	protected:
		int m_ID; // represents the number within the party it is stored
		std::string m_name; 
		int m_level, m_health, m_attack, m_defense;
		int m_tempHealth, m_tempAttack, m_tempDefense; // temporary values used in combat
		bool m_alive; // m_alive == represents if the entity is alive. 
		bool m_action;	// m_action is used to verify
		std::vector<Action> m_actionList; // maintains a vector of actions that the player can perform
		Performance m_performance; // Performance is the action to be commited.
	public:
		Entity();
		Entity(const std::string& t_name, std::vector<int>& t_s_val, std::vector<int>& t_a_val);	
		~Entity();
		virtual void setAction(std::vector<int> t_a_val);
	public:
		// mutators and retrievers
		std::string& getName() { return m_name; }
		int& getLevel() { return m_level; }
		int& getHealth() { return m_health; }
		int& getAttack() { return m_attack; }
		int& getDefense() { return m_defense; }
		bool& getAlive() { return m_alive; }
		int& getTempAttack() { return m_tempAttack; }
		int& getTempDefense() { return m_tempDefense; }
		void setHealth(int health) { m_health = health; }
		void setLevel(int level) { m_level = level; }
		void setAttack(int attack) { m_attack = attack; }
		void setDefense(int defense) { m_defense = defense; }
		void setAlive(bool alive) { m_alive = alive; }
		void setAction(bool action) { m_action = action; }
		void setTempDefense(int defense) { m_tempDefense = defense; }

		Performance getPerf() { return m_performance; }
		void performAction(std::vector<Entity *> opposing_party);
	public:
		// declarations of actions/functions used for combat instances
		void damageHealth(int &t_total_damage);
		int calculateAttack();
		int calculateDefense();
		void Strike(Entity *t_opponent);
		void Bulward(Entity *t_opponent);
		void Cast(Entity *t_opponent);
		
	public:
		virtual void startTurn(std::vector<Entity *> t_opposing_party);
		void updateTempState();
		void printEntityData();
};