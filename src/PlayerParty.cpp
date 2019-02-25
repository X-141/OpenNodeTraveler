#include "PlayerParty.h"

PlayerParty::PlayerParty() {

}

PlayerParty::~PlayerParty() {

}

bool PlayerParty::beginTurn(Party *opposing_party){
    bool set_actions = false; //This flag will stop player turn and begin
                              //their actions
    int choice = 0;
    int x;
    try {
        while(!set_actions){
            std::cout << "Please set the actions for the characters:" << std::endl;
            for(x = 1; x <= m_PartyRoster.size(); ++x){
                std::cout << x << ". " << m_PartyRoster.at(x - 1)->getName() << 
                m_PartyRoster.at(x - 1)->getPerformance().getPerformanceStatus() << std::endl;
            }
            std::cout << x << ". Begin Performance" << std::endl;
            std::cin >> choice;
            if(std::cin.fail())
                throw InputMismatchException("Invalid Selection");
            if(choice > static_cast<int>(m_PartyRoster.size()+1))
                throw std::out_of_range("Invalid Selection");
        
            if(choice <= m_PartyRoster.size())
                m_PartyRoster.at(choice - 1)->startTurn(opposing_party->getPartyRoster());
            else {
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
    return opposing_party->getPartyKOStatus();
}
