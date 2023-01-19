#include <iostream>
#include <string>
#include <time.h>
#include <memory> 
#include "player.h"
#include <list>
#include<vector>
#include <algorithm>
#include <stdio.h>
#include <numeric>
#include <fstream>
using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;
using namespace teammanagment;

void add_player(std::list<Player>& myTeam);
void displayall(std::list<Player>& myTeam);
std::list<Player>::iterator find_by_id(std::list<Player>& member_list, int id);

int main()
{ 
    std::list<Player> myTeam;
    Player newPlayer1{ "Andres","Pulisic","DF",20,1020,5 };
    Player newPlayer2{ "Matheus","Teixeira","FW",18,460,21 };
    Player newPlayer3{ "Marcelo","Diaz","DF",28,500,13 };
    Player newPlayer4{ "Anthony","Weber","MF",18,2000,30 };
    myTeam.push_back(newPlayer1);
    myTeam.push_back(newPlayer2);
    myTeam.push_back(newPlayer3);
    myTeam.push_back(newPlayer4);

    bool menuIsRunning = true;
    while (menuIsRunning == true) {
        int menuOption = 0;
        std::cout << std::endl << ">> Team Management Menu" << std::endl <<
            "1. Create New Player Contract" << std::endl <<
            "2. My Team" << std::endl <<
            "3. My U23 Players" << std::endl <<
            "4. Contracts by Salary" << std::endl <<
            "5. Contracts expiring soon" << std::endl <<
            "6. Renew Contract" << std::endl <<
            "7. Transferables" << std::endl <<
            "8. Terminate Player" << std::endl <<
            "9. End of the Season & Update Squad" << std::endl <<
            "x.Save" << std::endl <<
            "0. Quit" << std::endl <<
            "Your choice: ";
        std::cin >> menuOption;
        if (menuOption == 1) {
            add_player(myTeam);
        }
        else if (menuOption == 2) {
            if (!myTeam.empty()) {
                std::for_each(myTeam.begin(), myTeam.end(),
                    [](auto& Player) {
                        Player.display_info();
                    }
                );
                std::cout << std::endl;
            }
            else {
                std::cout << "Add Players First\n";
            }
        }
        else if (menuOption == 3) {
            if (!myTeam.empty()) {
                std::for_each(myTeam.begin(), myTeam.end(),
                    [](auto& Player) {
                        if (Player.get_age() <= 23)
                            Player.display_cont_info();
                    }
                );
                std::cout << std::endl;
            }
            else {
                std::cout << "Add Players First\n";
            }
        }
        else if (menuOption == 4) {
            if (!myTeam.empty()) {
                myTeam.sort([](const Player& f, const Player& s) { return f.get_salary() > s.get_salary(); });
                std::for_each(myTeam.begin(), myTeam.end(),
                    [](auto& Player) {
                        Player.display_cont_info();
                    }
                );
            }
            else {
                std::cout << "Add Players First\n";
            }
        }
        else if (menuOption == 5) {
            if (!myTeam.empty())
            {
                std::for_each(myTeam.begin(), myTeam.end(),
                    [](auto& Player) {
                        if (Player.get_monthsleft() <= 13)
                            Player.display_cont_info();
                    }
                );
                std::cout << std::endl;
            }
            else {
                std::cout << "Add Players First\n";
            }
        }
        else if (menuOption == 6) {
            string tempid;
            std::cout << "Enter the Player ID: ";
            std::cin >> tempid;
            std::list<Player>::iterator it;
            it = find_by_id(myTeam, std::stoi(tempid));
            if (it != myTeam.end())
            {
                std::cout << "Found the Player!" << std::endl;
                it->renew_contract();

            }
            else {
                std::cout << "That ID does not exist" << std::endl;
            }

        }
        else if (menuOption == 7)
        {
            string tempid;
            std::cout << "Enter the Player ID to be made transferable: ";
            std::cin >> tempid;
            std::list<Player>::iterator it;
            it = find_by_id(myTeam, std::stoi(tempid));
            if (it != myTeam.end()) {
                std::cout << "Found it!" << std::endl;
                it->make_transferable();
            }
            if (!myTeam.empty())
            {
                std::for_each(myTeam.begin(), myTeam.end(),
                    [](auto& Player) {
                        if (Player.status_info != nullptr)
                            Player.display_cont_info();
                    }
                );
                std::cout << std::endl;
            }
        }
        else if (menuOption == 8)
        {
            int tempid;
            std::cout << "Enter the ID to remove: ";
            std::cin >> tempid;
            auto new_end = remove_if(myTeam.begin(), myTeam.end(),
                [tempid](Player& Player) {
                    return tempid == Player.get_id();
                }
            );

            // erase the items that matched remove_if
            myTeam.erase(new_end, myTeam.end());

        }
        else if (menuOption == 9) {
        int year_for_months = 12;
        int year_for_age = 1;
        std::cout << "Getting Ready for a new Season..."<< endl;
        transform(myTeam.begin(), myTeam.end(), myTeam.begin(),
            [year_for_age](auto& player) {
                player.update_age(player.get_age() + year_for_age);
                return player;
            });
        transform(myTeam.begin(), myTeam.end(), myTeam.begin(),
            [year_for_months](auto& player) {
                player.update_monthsleft(player.get_monthsleft() - year_for_months);
                return player;
            });
        std::cout << "..." << endl;
        std::cout << ".." << endl;
        std::cout << "." << endl;
        }


        //TO BE IMPLEMENTED
        //else if (menuOption == 10) { 
        //    std::cout << "Saving your progress... \n";
        //    std::fstream myPro;
        //    myPro.open("Progress.txt", std::ios::out);
        //    if (myFile.is_open())
        //    {
        //        myPro << std::to_string(myTeam);
        //    }
        //}


        else if (menuOption == 0) {
            std::cout << "Thanks for using Team Managment by Jesus Del Barrio \n";
            menuIsRunning = false;
        }
    }
}

void add_player(std::list<Player>& myTeam) {
    string newfname;
    string newlname;
    string newposition;
    int newage;
    float newsalary;
    int newmonths;
    std::cout << "First name: ";
    std::cin >> newfname;
    std::cout << "Last name: ";
    std::cin >> newlname;
    std::cout << "Monthly Salary: ";
    std::cin >> newsalary;
    std::cout << "Position: ";
    std::cin >> newposition;
    std::cout << "Age: ";
    std::cin >> newage ;
    std::cout << "Contract duration in Months: ";
    std::cin >> newmonths;
    Player newPlayer{newfname,newlname,newposition,newage,newsalary,newmonths};
    myTeam.push_back(newPlayer);
}
void displayall(std::list<Player>& myTeam) {
    std::list<Player>::iterator it;
    for (it = myTeam.begin(); it != myTeam.end(); it++)
    {
        it->display_info();
    }
}
std::list<Player>::iterator find_by_id(std::list<Player>& member_list, int id)
{
    std::list<Player>::iterator it;
    for (it = member_list.begin(); it != member_list.end(); it++)
    {
        if (it->get_id() == id)
        {
            return it; // Return iterator to Person matching the ID
        }
    }

    return it; // Person with that ID was not found
}