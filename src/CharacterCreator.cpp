#include "CharacterCreator.h"

CharacterCreator::CharacterCreator(const std::string& filepath){
        for(int character_index = 0; character_index < 3; ++character_index){
        std::string character_name;
        std::cout << "What would you like to name your character?" << std::endl;
        std::getline(std::cin, character_name);
        int allocation_points = 40;
        bool player_set = false;
        std::cout << "Please enter a stat set that follows the format {Health}:{Attack}:{Defense}" << std::endl;
        std::cout << "Current allocation points == 40" << std::endl;
        std::cout << "Example stat set input is 14:16:10. Health=140 ; Attack=16 ; Defense=10" << std::endl;
        std::cout << "Note: health is modified by *10 meaning that the base health is 10*10 == 100" << std::endl;
        while(!player_set){
            try{
                std::vector<int> stat_values(3);
                std::string alloc_values;
                std::getline(std::cin, alloc_values);
                std::cout << alloc_values << std::endl;
                auto pos_1 = alloc_values.find_first_of(':');
                auto pos_2 = alloc_values.find_last_of(':');

                int value_1 = std::stoi(alloc_values.substr(0, pos_1));
                stat_values.at(0) = value_1;

                int value_2 = std::stoi(alloc_values.substr(pos_1+1, pos_2 - pos_1));
                stat_values.at(1) = value_2;

                int value_3 = std::stoi(alloc_values.substr(pos_2+1, alloc_values.size() - pos_2));
                stat_values.at(2) = value_3;

                int total_value = value_1 + value_2 + value_3;

                if(total_value > 40)
                    std::cout << "Invalid allocation" << std::endl;
                else if (total_value < 40) {
                    allocation_points = 40 - total_value;
                    std::cout << "Please allocated the remaining " << allocation_points 
                    << " for " << character_name << "\n" << std::endl;
                } else {
                    std::ofstream characterfile(filepath+character_name+".txt");
                    std::cout << "Valid setting" << std::endl;
                    player_set = true;
                    stat_values.at(0) = stat_values.at(0) * 10;
                    characterfile << character_name+"\n";
                    characterfile << character_index;
                    characterfile << ":";
                    characterfile << 10;
                    characterfile << ":";
                    for(int x = 0; x < stat_values.size(); ++x){
                        characterfile << stat_values.at(x);
                        if(x != stat_values.size()-1)
                            characterfile << ":";
                    }
                    characterfile << ";\n";
                    characterfile << "1:2:3;";
                    characterfile.close();
                }
            } catch(const std::invalid_argument &ex){
                std::cout << "Invalid input" << std::endl;
                std::cin.clear();
            }
        }
    }    
}

CharacterCreator::~CharacterCreator(){}