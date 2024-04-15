#ifndef LIB_PLAYER_H_COMPANY_H
#define LIB_PLAYER_H_COMPANY_H


#include <string>

class Company {
public:
    Company(std::string name, float cashBalance);
    void setCashBalance();
    float getCashBalance();
    void setName();
    std::string getName();
private:
    std::string name;
    float cashBalance;
};


#endif  // LIB_PLAYER_H_COMPANY_H