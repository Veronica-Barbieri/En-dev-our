#include "../headers/ptemployee.h"
#include <exception>
#include <iostream>

ptemployee::ptemployee(): worker(), level0() {}

ptemployee::ptemployee(std::string n, std::string sn, std::string cf): worker(n, sn, cf), level0() {};
ptemployee::ptemployee(std::string n, std::string sn, std::string cf, int wd, int wh, double base, double bonus, double salary, int sen, int hol): worker(n,sn,cf,wd,wh,base,bonus,salary,sen,hol), level0() {}


ptemployee::ptemployee(const worker& w): worker(w), level0() {}

double ptemployee::calcBaseSal() const {
    return worker::getLastMonthWorkedDays() * level0::getWorkHours() * level0::getSalary();
}

double ptemployee::calcBonus() const {
    double bonussal = (worker::getLastMonthWorkedHours() - (worker::getLastMonthWorkedDays() * level0::getWorkHours())) * (level0::getSalary()+level0::getSalaryBonus());
    if (bonussal < 0){
        throw std::domain_error("Something went wrong! The data you inserted is not coherent");
    }
    return bonussal;
}

void ptemployee::updateVacAcc() {
    setVacAcc(level0::getVacPerMonth());
}

double ptemployee::calcFullSal(const int& wd, const int& wh) {
    if((wh - (wd * level0::getWorkHours())) * (level0::getSalary()+level0::getSalaryBonus()) < 0){
        throw std::domain_error("Something went wrong! The data you inserted is not coherent");
    }
    updateWorkData(wd, wh);
    updateVacAcc();
    updateSeniority();
    this->setLastMonthBaseSalary(calcBaseSal());
    this->setLastMonthBonusSalary(calcBonus());
    setLastMonthSalary(this->getLastMonthBaseSalary() + this->getLastMonthBonusSalary());
    return getLastMonthSalary();
}
