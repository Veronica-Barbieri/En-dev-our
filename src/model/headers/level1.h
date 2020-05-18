#ifndef LEVEL1_H
#define LEVEL1_H
#include "contract.h"

class level1: public contract {
private:
    static int work_hours;
    static double salary;
    static double salary_bonus;
    static int vac_per_month;
    static std::string pt_contr_name;
    static std::string ft_contr_name;
public:
    level1();
    virtual int getWorkHours() const override;
    virtual double getSalary() const override;
    virtual double getSalaryBonus() const override;
    virtual int getVacPerMonth() const override;
    virtual std::string getContractType() const override;
};

#endif // LEVEL1_H
