#ifndef DIRECTOR_H
#define DIRECTOR_H
#include "worker.h"
#include "level1.h"


class director: public worker, public level1 {
private:
    static double dir_base_bonus_salary;
    static double dir_bonus_bonus_salary; // da aggiungere al bonus di base del contratto full time
    static int dir_bonus_vac_day;

public:
    director(std::string, std::string, std::string);

    double getBaseBonusSalary() const;
    double getBonusBonusSalary() const;
    int getBonusVacDay() const;

    virtual double calcBaseSal() const override;
    virtual double calcBonus() const override;
    virtual double calcFullSal(const int&, const int&) override;
    virtual void updateVacAcc() override;

};

#endif // DIRECTOR_H
