#include "../headers/director.h"

double director::dir_base_bonus_salary = 400;
double director::dir_bonus_bonus_salary = 1.5; // da aggiungere al bonus di base del contratto full time
int director::dir_bonus_vac_day = 1;

director::director(): worker(), level1() {}

director::director(std::string n, std::string sn, std::string cf): worker(n, sn, cf), level1() {}

director::director(const worker& w): worker(w), level1() {}

double director::getBaseBonusSalary() const {
    return this->dir_base_bonus_salary;
}

double director::getBonusBonusSalary() const {
    return this->dir_bonus_bonus_salary;
}

int director::getBonusVacDay() const {
    return this->dir_bonus_vac_day;
}

double director::calcBaseSal() const {
    return (worker::getLastMonthWorkedDays() * level1::getWorkHours() * level1::getSalary()) + dir_base_bonus_salary;
}

double director::calcBonus() const {
    return ((worker::getLastMonthWorkedHours() - (worker::getLastMonthWorkedDays() * level1::getWorkHours())) * (level1::getSalary()+level1::getSalaryBonus()+dir_bonus_bonus_salary));
}

void director::updateVacAcc() {
    setVacAcc(level1::getVacPerMonth() + dir_bonus_vac_day);
}

double director::calcFullSal(const int& wd, const int& wh) {
    updateWorkData(wd, wh);
    updateVacAcc();
    updateSeniority();
    this->setLastMonthBaseSalary(calcBaseSal());
    this->setLastMonthBonusSalary(calcBonus());
    setLastMonthSalary(this->getLastMonthBaseSalary() + this->getLastMonthBonusSalary());
    return getLastMonthSalary();
}



