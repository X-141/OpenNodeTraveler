#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(const std::string& t_name, std::vector<int> t_s_val, std::vector<int> t_a_val)
	:Entity(t_name, t_s_val, t_a_val){}

// Start turn is based on the startTurn virtual function
// This function allows the user to pick the entity to attack
// in combat as well as which action to perform
void PlayerEntity::startTurn(std::vector<Entity *> t_opp_party) {
	std::cout << "Current Player turn: " << m_name << std::endl;
	bool valid_input = false;
	int enemy_choice = 0;
	int action_choice = 0;
	// Prompts the user with the list of entites and actions available
	//	-> select the entity to attack
	//	-> select the action to perform on that entity
	while (!valid_input) {
		bool valid_choice = false;
		bool valid_choice2 = false;
		try {
			while (!valid_choice) {
				// list out actions that the player can perform
				std::cout << "Which action would you like to perform?" << std::endl;
				for (unsigned int x = 1; x <= m_actionList.size(); ++x) {
					std::cout << x << ". " << m_actionList.at(x - 1).m_actionName << std::endl;
				}
				std::cin >> action_choice;
				if (std::cin.fail()) {
					throw InputMismatchException("Invalid action");
				}
				if (action_choice > static_cast<int>(m_actionList.size())) {
					throw std::out_of_range("Invalid action");
				}
				valid_choice = true;
			}
			while (!valid_choice2) {
				std::cout << "Which enemy would you like to attack?" << std::endl;
				// list out entities
				for (unsigned int x = 1; x <= t_opp_party.size(); ++x) {
					if (t_opp_party.at(x - 1)->getAlive())
						std::cout << x << ". " << t_opp_party.at(x - 1)->getName() << std::endl;
				}
				std::cout << t_opp_party.size()+1 << ". Enemy Status" << std::endl;
				std::cout << t_opp_party.size()+2 << ". back" << std::endl;
				std::cin >> enemy_choice;
				if (std::cin.fail()) {
					throw InputMismatchException("Invalid enemy choice");
				}
				if (enemy_choice > static_cast<int>(t_opp_party.size())+2) {
					throw std::out_of_range("Invalid enemy choice");
				}
				if(enemy_choice == t_opp_party.size()+1){ // display enemy character HP
					for(Entity *entity : t_opp_party)
						std::cout << entity->getHealth() << " -> " << entity->getName() << std::endl;
					valid_choice2 = false;
				} else if(enemy_choice == t_opp_party.size()+2){ // This allows the player to selected a different action
					valid_choice = false;
					valid_choice2 = true;
				} else if (!t_opp_party.at(enemy_choice-1)->getAlive()){ // this prevents the player from selecting a dead enemy
					std::cout << "That opponent is not alive!" << std::endl;
					std::cin.clear();
				} else {
					valid_choice2 = true;
				}
			}
			if(valid_choice && valid_choice2)
				valid_input = true;
		}
		catch (const InputMismatchException &ex) {
			std::cout << ex.what() << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	
		}
		catch (const std::out_of_range &ex) {
			std::cout << ex.what() << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	
		}
	}
	m_performance.m_action_name = m_actionList.at(action_choice - 1).m_actionName;
	m_performance.m_action = action_choice - 1; //subtract 1 for the correct index
	m_performance.m_performer = m_ID;
	m_performance.m_offender = enemy_choice - 1;
	m_performance.m_offender_name = t_opp_party.at(enemy_choice -1)->getName();
	m_performance.m_set = true;
	//std::cout << "Performer: " << m_name << std::endl;
	//(this->*m_actionList.at(action_choice - 1).m_action)(t_opp_party.at(enemy_choice - 1));
	valid_input = true;
}

