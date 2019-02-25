#include "Entity.h"


Entity::Entity() {}

// initializes all values to be stored in entity
Entity::Entity(const std::string& t_name, std::vector<int>& t_s_val, std::vector<int>& t_a_val)
	: m_ID(t_s_val.at(0)) , m_name(t_name), m_health(t_s_val.at(2)), m_level(t_s_val.at(1)), m_attack(t_s_val.at(3)), m_defense(t_s_val.at(4))
{
	m_tempDefense = t_s_val.at(4);
	m_tempHealth = t_s_val.at(2);
	m_tempAttack = t_s_val.at(3);
	m_alive = true;
	m_action = false;
	// passes action vector containing values that coorelate to specific actions
	setAction(t_a_val);
	m_performance = Performance();
}

Entity::~Entity() { std::cout << "Deleted Entity" << std::endl; }

// substiate actions that each entity can utilize
void Entity::setAction(std::vector<int> t_a_val){
	m_actionList.reserve(3);
	for(int values : t_a_val){
		void (Entity::*temp_action)(Entity*);
		switch(values){
			case 1:
				temp_action = &Entity::Strike;
				m_actionList.push_back(Action("Strike", temp_action));
			break;
			case 2:
				temp_action = &Entity::Bulward;
				m_actionList.push_back(Action("Bulward", temp_action));
			break;
			case 3:
				temp_action = &Entity::Cast;
				m_actionList.push_back(Action("Cast", temp_action));
			break;
			default:
				std::cout << "Invalid action" << std::endl;
			break;
		}
	}
}


int Entity::calculateAttack() {
	return (m_level * .5) + (m_attack * 1.5);
}

int Entity::calculateDefense() {
	return (m_level * 0.5) + (m_tempDefense + (m_attack * 0.25));
}

void Entity::damageHealth(int &total_damage) {
	m_health = m_health - total_damage;
	if (m_health <= 0) {
		m_health = 0;
		m_alive = false;
	}
	std::cout << "Total Health: " << m_health << std::endl;
}

void Entity::Strike(Entity *t_opponent) {
	std::cout << "Targeted Entity: -> " << t_opponent->m_name << std::endl;
	int main_attack = calculateAttack();
	int t_opponent_defense = t_opponent->calculateDefense();
	int total_damage = main_attack - t_opponent_defense;
	std::cout << "Calculated Damage: " << main_attack << std::endl;
	std::cout << "Calculated Opposing Defense: " << t_opponent_defense << std::endl;
	std::cout << "Total Damage: " << total_damage << " -> " << t_opponent->m_name << std::endl;
	if (total_damage < 0)
		total_damage = 0;
	t_opponent->damageHealth(total_damage);
}

void Entity::Bulward(Entity *t_opponent) {
	std::cout << "Bulward Casted: -> " << m_name << std::endl;
	int increase_defense = (m_defense * 1.5) + (.5 * m_level);
	m_tempDefense += increase_defense;
	std::cout << "temporary defense up: +" << increase_defense << " -> " << m_tempDefense <<  std::endl;
}

void Entity::Cast(Entity *t_opponent){
	std::cout << "Targeted Entity: -> " << t_opponent->m_name << std::endl;
	int main_attack = calculateAttack();
	int t_opponent_defense = t_opponent->calculateDefense();
	int total_damage = main_attack - t_opponent_defense;
	std::cout << "Calculated Damage: " << main_attack << std::endl;
	std::cout << "Calculated Opposing Defense: " << t_opponent_defense << std::endl;
	std::cout << "Total Damage: " << total_damage << " -> " << t_opponent->m_name << std::endl;
	if (total_damage < 0)
		total_damage = 0;
	t_opponent->damageHealth(total_damage);
}

// base version of startTurn allows the entity to perform random selection
// as well as perform random actions
void Entity::startTurn(std::vector<Entity *> opposing_party) {
		//Allow the entity to select a random target from the vector
		//of opposing entities. -> basic vector default is 3
	int enemy_choice = rand() % 3;
	int action_choice = rand() % 2;
		//If the main entity selects a opposing entity that is dead.
		//continue to randomly choose until it finds a valid target.
	while (!opposing_party.at(enemy_choice)->m_alive)
		enemy_choice = rand() % 3;
	
	//m_performance = Performance(action_selector, enemy_selector, m_ID);
	m_performance.m_action_name = m_actionList.at(action_choice).m_actionName;
	m_performance.m_action = action_choice;
	m_performance.m_performer = m_ID;
	m_performance.m_offender = enemy_choice;
	m_performance.m_offender_name = opposing_party.at(enemy_choice)->getName();
	m_performance.m_set = true;
	//std::cout << "Performer: " << m_name << std::endl;
	//(this->*m_actionList.at(action_selector).m_action)(opposing_party.at(enemy_selector));
}

void Entity::performAction(std::vector <Entity *> opposing_party){
	(this->*m_actionList.at(m_performance.m_action).m_action)(opposing_party.at(m_performance.m_offender));
	m_performance.m_set = false;
}

// update specific state values based on certain checks
void Entity::updateTempState() {
	if (m_tempDefense > m_defense) {
		std::cout << m_name << " temp_defense: " << m_tempDefense << " -> " << m_defense << std::endl;
		m_tempDefense = m_defense;
	}
}

void Entity::printEntityData() {
	std::cout << "EntityID: " << m_ID << "\n" << std::endl;
	std::cout << "Name: " << m_name << std::endl;
	std::cout << "Level: " << m_level << std::endl;
	std::cout << "Health: " << m_health << std::endl;
	std::cout << "Attack: " << m_attack << std::endl;
	std::cout << "Defense: " << m_defense << std::endl;
	std::cout << std::endl;
}