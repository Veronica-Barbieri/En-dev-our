#include "../headers/ptemployee.h"

ptemployee::ptemployee(std::string n, std::string sn, std::string cf): worker(n, sn, cf), level0() {};

double ptemployee::calcBaseSal() const {
    return worker::getLastMonthWorkedDays() * level0::getWorkHours() * level0::getSalary();
}

double ptemployee::calcBonus() const {
    return ((worker::getLastMonthWorkedHours() - (worker::getLastMonthWorkedDays() * level0::getWorkHours())) * (level0::getSalary()+level0::getSalaryBonus()));
}

void ptemployee::updateVacAcc() {
    setVacAcc(level0::getVacPerMonth());
}

double ptemployee::calcFullSal(const int& wd, const int& wh) {
    updateWorkData(wd, wh);
    updateVacAcc();
    updateSeniority();
    this->setLastMonthBaseSalary(calcBaseSal());
    this->setLastMonthBonusSalary(calcBonus());
    setLastMonthSalary(this->getLastMonthBaseSalary() + this->getLastMonthBonusSalary());
    return getLastMonthSalary();
}
