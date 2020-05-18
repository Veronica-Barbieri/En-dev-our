#ifndef CONTRACT_H
#define CONTRACT_H
#include <string>

class contract
{
public:
    contract();
    virtual ~contract();
    virtual int getWorkHours() const =0;
    virtual double getSalary() const =0;
    virtual double getSalaryBonus() const =0;
    virtual int getVacPerMonth() const =0;
    virtual std::string getContractType() const =0;
};

#endif // CONTRACT_H
