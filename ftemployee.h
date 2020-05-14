#ifndef FTEMPLOYEE_H
#define FTEMPLOYEE_H
#include "worker.h"
#include "level1.h"

class ftemployee: public worker, public level1 {
private:
    static double ft_base_bonus_salary;
    static int ft_bonus_vac_day;
public:
    ftemployee(std::string, std::string);

    double getBaseBonusSalary() const;
    int getBonusVacDay() const;

    virtual double calcBaseSal() const override;
    virtual double calcBonus() const override;
    virtual double calcFullSal(const int&, const int&) override;
    virtual void updateVacAcc() override;
};

#endif // FTEMPLOYEE_H
