#include "status.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory> 
#include <list>
#include <string>
#include <sstream>
#include "player.h"
#include <algorithm>
#include <numeric>
#include <limits> 
#include <ios>
using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;

void Status::initialize()
{
    string answer;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter 1 to confirm that the Player is Transferable: ";
    std::getline(std::cin, answer);
    if (answer == "1") {
        transferSt = true;
    }
    else {
        cout << "That is not a valid number please try again";
    }

}


bool Status::get_curr_status()
{
    return transferSt;
}

