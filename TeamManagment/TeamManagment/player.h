#pragma once
#include <string>
#include <memory>
#include "status.h"

using std::string;

namespace teammanagment {
    class Player {
    private:
        int id;
        string fname;
        string lname;
        string position;
        int age;
        float mSalary;
        int monthsDur;
        static int globalid;


    public:
        Player() // default constructor
        {
            id = globalid++;
            fname = "";
            fname = "";
            position = "";
            age = 15; // The team cannot hire anyone under 15 
            mSalary = 200; // 200 is the minimum monthly salary 
            monthsDur = 1; // 1 month is the shortest contract time


        }
        Player(std::string firstname, std::string lastname, string position, int age, float mSalary, int months);
        void display_info();
        void display_cont_info();
        int get_id() const;
        float get_salary ()const;
        int get_age();
        int get_monthsleft();
        void renew_contract();
        void make_transferable();
        void update_age(int new_age);
        void update_monthsleft(int months);
        std::shared_ptr<Status> status_info;

    };

}

