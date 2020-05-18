#include "../headers/level0.h"

int level0::work_hours = 4;
double level0::salary = 7.5;
double level0::salary_bonus = 0.5;
int level0::vac_per_month = 1;
std::string level0::pt_contr_name = "Part-time";

level0::level0(): contract() {}

int level0::getWorkHours() const {
    return this->work_hours;
}

double level0::getSalary() const {
    return this->salary;
}

double level0::getSalaryBonus() const {
    return this->salary_bonus;
}

int level0::getVacPerMonth() const {
    return this->vac_per_month;
}


std::string level0::getContractType() const {
    return this->pt_contr_name;
}
