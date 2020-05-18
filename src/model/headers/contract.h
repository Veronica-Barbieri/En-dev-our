#ifndef CONTRACT_H
#define CONTRACT_H
#include <string>

class contract
{
private:
    int work_hours; // ore di lavoro giornaliero
    double salary; // guadagno orario
    double salary_bonus; // surplus sul guadagno per ore di straordinario
    int vac_per_month; // ferie accumulate settimanalmente

public:
    contract(int, double, double, int);
    virtual ~contract();
    virtual int getWorkHours() const;
    virtual double getSalary() const;
    virtual double getSalaryBonus() const;
    virtual int getVacPerMonth() const;
    virtual std::string getContractType() const=0;
};

#endif // CONTRACT_H
