#include "../headers/ftemployee.h"

double ftemployee::ft_base_bonus_salary = 100;
int ftemployee::ft_bonus_vac_day = 1;

ftemployee::ftemployee(std::string n, std::string sn, std::string cf): worker(n, sn, cf), level1() {}

double ftemployee::getBaseBonusSalary() const {
    return this->ft_base_bonus_salary;
}

int ftemployee::getBonusVacDay() const {
    return this->ft_bonus_vac_day;
}

double ftemployee::calcBaseSal() const {
    return (worker::getLastMonthWorkedDays() * level1::getWorkHours() * level1::getSalary()) + ft_base_bonus_salary;
}

double ftemployee::calcBonus() const {
    return ((worker::getLastMonthWorkedHours() - (worker::getLastMonthWorkedDays() * level1::getWorkHours())) * (level1::getSalary()+level1::getSalaryBonus()));
}

void ftemployee::updateVacAcc() {
    setVacAcc(level1::getVacPerMonth() + ft_bonus_vac_day);
}

double ftemployee::calcFullSal(const int& wd, const int& wh) {
    worker::updateWorkData(wd, wh);
    updateVacAcc();
    this->setLastMonthBaseSalary(calcBaseSal());
    this->setLastMonthBonusSalary(calcBonus());
    setLastMonthSalary(this->getLastMonthBaseSalary() + this->getLastMonthBonusSalary());
    return getLastMonthSalary();
}

