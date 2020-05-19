#include "../headers/worker.h"

worker::worker(std::string n, std::string sn, std::string cf): name(n), sname(sn), cod_fiscale(cf), last_month_worked_days(0), last_month_worked_hours(0), last_month_base_salary(0), last_month_bonus_salary(0), last_month_salary(0), seniority(0), vac_acc(0) {}

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

std::string worker::getCodFiscale() const {
    return this->cod_fiscale;
}

void worker::setCodFiscale(const std::string& cf){
   this->cod_fiscale = cf;
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

double worker::getLastMonthBaseSalary() const{
    return this->last_month_base_salary;
}

void worker::setLastMonthBaseSalary(const double& bs){
    this->last_month_base_salary = bs;
}

double worker::getLastMonthBonusSalary() const{
    return this->last_month_bonus_salary;
}

void worker::setLastMonthBonusSalary(const double& bs){
    this->last_month_bonus_salary = bs;
}

double worker::getLastMonthSalary() const {
    return this->last_month_salary;
}

void worker::setLastMonthSalary(const double& s) {
    this->last_month_salary = s;
}

bool worker::operator==(const worker& w) const{
    return (this->getCodFiscale() == w.getCodFiscale());
}

bool worker::operator!=(const worker& w) const{
    return (this->getCodFiscale() != w.getCodFiscale());
}


int worker::getSeniority() const{
    return this->seniority;
}

void worker::updateSeniority(){
    this->seniority += 1;
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
