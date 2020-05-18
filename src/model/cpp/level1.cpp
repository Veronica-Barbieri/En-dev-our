#include "../headers/level1.h"

int level1::work_hours = 8;
double level1::salary = 8.0;
double level1::salary_bonus = 1.0;
int level1::vac_per_month = 1;
std::string level1::ft_contr_name = "Full-time";

level1::level1(): contract() {}

int level1::getWorkHours() const {
    return this->work_hours;
}

double level1::getSalary() const {
    return this->salary;
}

double level1::getSalaryBonus() const {
    return this->salary_bonus;
}

int level1::getVacPerMonth() const {
    return this->vac_per_month;
}


std::string level1::getContractType() const {
    return this->ft_contr_name;
}
