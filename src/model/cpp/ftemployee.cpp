#include "../headers/ftemployee.h"
#include <exception>
#include <iostream>

double ftemployee::ft_base_bonus_salary = 100;
int ftemployee::ft_bonus_vac_day = 1;

ftemployee::ftemployee(): worker(), level1() {}

ftemployee::ftemployee(std::string n, std::string sn, std::string cf): worker(n, sn, cf), level1() {}

ftemployee::ftemployee(std::string n, std::string sn, std::string cf, int wd, int wh, double base, double bonus, double salary, int sen, int hol): worker(n,sn,cf,wd,wh,base,bonus,salary,sen,hol), level1() {}

ftemployee::ftemployee(const worker& w): worker(w), level1() {}

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
    double bonussal = (worker::getLastMonthWorkedHours() - (worker::getLastMonthWorkedDays() * level1::getWorkHours())) * (level1::getSalary()+level1::getSalaryBonus());
    if (bonussal < 0){
        throw std::domain_error("Something went wrong! The data you inserted is not coherent");
    }
    return bonussal;
}

void ftemployee::updateVacAcc() {
    setVacAcc(level1::getVacPerMonth() + ft_bonus_vac_day);
}

double ftemployee::calcFullSal(const int& wd, const int& wh) {
    updateWorkData(wd, wh);
    updateVacAcc();
    updateSeniority();
    this->setLastMonthBaseSalary(calcBaseSal());
    this->setLastMonthBonusSalary(calcBonus());
    setLastMonthSalary(this->getLastMonthBaseSalary() + this->getLastMonthBonusSalary());
    return getLastMonthSalary();
}

