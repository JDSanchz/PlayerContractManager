#include "player.h"
#include <iostream>
#include <string> 
#include <memory>
#include "status.h"
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>


using teammanagment::Player;

int Player::globalid = 0;



// Non-default constructor
Player::Player(std::string firstname, std::string lastname, string position, int age, float mSalary, int months) :
    fname(firstname), lname(lastname), mSalary(mSalary), id(globalid++), position(position) , age(age), monthsDur(months)
{
}

void Player::display_cont_info() {
    std::cout << "Player ID: " << id << "  Name: " << fname + " " + lname << "  Position: " << position << "  Age: " << age << "  Salary: $" << mSalary << "  Months Left: " << monthsDur << std::endl;

}

void Player::display_info() {
    std::cout << "Player ID: " << id << "  Name: " << fname + " " + lname + " " << "Position: " << position << std::endl;

}

int Player::get_id() const
{
    return id;
}
int Player::get_age() 
{
    return age;
}
int Player::get_monthsleft()
{
    return monthsDur;
}
void Player::update_monthsleft(int months)
{
    monthsDur = months;
}
void Player::update_age(int new_age)
{
    age = new_age;
}
float Player::get_salary() const
{
    return mSalary;
}
void Player::renew_contract()
{
    int new_salary;
    int new_monthsDur;
    std::cout << "What is the new Salary? ";
        std::cin >> new_salary;
        std::cout << "How many months? ";
        std::cin >> new_monthsDur;


    if (new_salary != mSalary)
        mSalary = new_salary;
    if (new_monthsDur != monthsDur)
        monthsDur = new_monthsDur;

    std::fstream myFile;
    //Generate and save a different contract for each player based on the date
    myFile.open(lname +" "+fname+" " + __DATE__ + " Agreement.html", std::ios::out); 
    if (myFile.is_open())
    {
        myFile << """<h1 style=\"text-align:center\" >Player Agreement</h1>""";
        myFile << """<p style=\"text-align:center; \"><img src=\"https://iconarchive.com/download/i12927/giannis-zographos/spanish-football-club/Real-Madrid.ico\" alt=\"Logo\"> </p>""";
        myFile << "<p style=\"text-align:center\" >" + fname + " " + lname + " has agreed to play for this institution for a period of " + std::to_string(monthsDur) + " months."+"</p>";
        myFile << "<p style=\"text-align:center; padding-bottom: 40px\" >The player's salary will be of " + std::to_string(static_cast<int>(mSalary))+ " dollars per month.</p>";
        myFile << "<p style=\"text-align:left\;margin-left:220px\" >______________________</p>";
        myFile << "<p style=\"text-align:left; margin-left:220px\" >Date</p>";
        myFile << "<p style=\"text-align:left\;margin-left:220px\" >______________________</p>";
        myFile << "<p style=\"text-align:left; margin-left:220px\" >Player's signature</p>";
        myFile << "<p style=\"text-align:left\;margin-left:220px\" >______________________</p>";
        myFile << "<p style=\"text-align:left; margin-left:220px\" >President's signature</p>";
        myFile.close();
    }
}
void Player::make_transferable()
{
    status_info = std::make_shared<Status>();
    status_info->initialize();
}


