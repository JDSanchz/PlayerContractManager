#pragma once
#include <string>

class Status
{
public:
    bool transferSt;

public:
    Status() : transferSt() {};

    void initialize(); 
    void display() const; 
    bool get_curr_status();
};