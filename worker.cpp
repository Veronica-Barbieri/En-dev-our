#include "worker.h"

worker::worker(std::string n, std::string sn): name(n), sname(sn), last_month_worked_days(0), last_month_worked_hours(0), last_month_salary(0), vac_acc(0) {}

worker::~worker() {};

std::string worker::getName() const {
    return this->name;
}

void worker::setName(const std::string& s){
    this->name = s;
}

std::string worker::getSname() const {
    return this->sname;
}

void worker::setSname(const std::string& sn){
    this->sname = sn;
}

int worker::getLastMonthWorkedDays() const {
    return this->last_month_worked_days;
}

void worker::setLastMonthWorkedDays(const int& wd){
    this->last_month_worked_days = wd;
}

int worker::getLastMonthWorkedHours() const {
    return this->last_month_worked_hours;
}

void worker::setLastMonthWorkedHours(const int& wh){
    this->last_month_worked_hours = wh;
}

double worker::getLastMonthSalary() const {
    return this->last_month_salary;
}

void worker::setLastMonthSalary(const double& s) {
    this->last_month_salary = s;
}

int worker::getVacAcc() const {
    return this->vac_acc;
}

void worker::setVacAcc(const int& va) {
    this->vac_acc += va;
}

void worker::resetVacAcc() {
    this->vac_acc = 0;
}

void worker::updateWorkData(const int& wd, const int& wh) {
    this->setLastMonthWorkedDays(wd);
    this->setLastMonthWorkedHours(wh);
}
