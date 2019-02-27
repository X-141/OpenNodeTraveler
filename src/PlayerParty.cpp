#include "PlayerParty.h"

PlayerParty::PlayerParty() {

}

PlayerParty::~PlayerParty() {

}

bool PlayerParty::beginTurn(Party *opposing_party){
    bool set_actions = false; //This flag will stop player turn and begin the action
    int choice = 0;
    int x = 0;
    try {
        while(!set_actions){
            std::cout << "Please set the actions for the characters:" << std::endl; // list out player moves, and player status for each entity
            std::cout << " { ";
            for(Entity *set_entity : m_performance_sequence){
                std::cout << set_entity->getName() << " , ";
            }
            std::cout << " END } " << std::endl;
            for(x = 1; x <= m_PartyRoster.size(); ++x){
                std::cout << x << ". " << m_PartyRoster.at(x - 1)->getName();
                m_PartyRoster.at(x - 1)->getAlive() ? std::cout << m_PartyRoster.at(x - 1)->getPerf().getPerfStatus() << std::endl
                    : std::cout << " KO'd " << std::endl;
            }
            std::cout << x << ". Begin Performance" << std::endl;
            std::cin >> choice;

            if(std::cin.fail()) //catch input exceptions
                throw InputMismatchException("Invalid Selection");
            if(choice > static_cast<int>(m_PartyRoster.size()+1))
                throw std::out_of_range("Invalid Selection");
        
            if(choice <= m_PartyRoster.size()){
                if(m_PartyRoster.at(choice - 1)->getAlive()){
                    if(m_PartyRoster.at(choice - 1)->getPerf().m_set){ // if that entity already set an action.
                        for(int x = 0; x < m_performance_sequence.size(); x++)
                            if(m_PartyRoster.at(choice - 1)->getPerf().m_performer == m_performance_sequence.at(x)->getPerf().m_performer)
                                m_performance_sequence.erase(m_performance_sequence.begin()+x); // delete the element that the entity already set previously
                    }
                    m_PartyRoster.at(choice - 1)->startTurn(opposing_party->getPartyRoster()); // set the player action for the entity
                    m_performance_sequence.push_back(m_PartyRoster.at(choice-1)); // place that active entity in the deque for performance
                } else {
                std::cout << "That Player is out cold!" << std::endl;
                }
            } 
            else { // if the player selects the last option begin the performance
                std::cout << std::endl;
                startPerformance(opposing_party->getPartyRoster());
                set_actions = true;
            }
        }
    } catch (const InputMismatchException &ex){
        	std::cout << ex.what() << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } catch (const std::out_of_range &ex) {
			std::cout << ex.what() << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	
	}
    opposing_party->checkPartyStatus(); // update the KO state of the opposing party
    return opposing_party->getPartyKOStatus(); // return the status of the opposing party
}
