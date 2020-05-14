#include "contract.h"

contract::contract(int w, double s, double sb, int vpm): work_hours(w), salary(s), salary_bonus(sb), vac_per_month(vpm) {}

contract::~contract() {};

int contract::getWorkHours() const {
    return this->work_hours;
}

double contract::getSalary() const {
    return this->salary;
}

double contract::getSalaryBonus() const {
    return this->salary_bonus;
}

int contract::getVacPerMonth() const {
    return this->vac_per_month;
}
