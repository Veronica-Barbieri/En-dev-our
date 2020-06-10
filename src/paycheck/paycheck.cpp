#include "paycheck.h"

paycheck::paycheck(): pc(Container<worker*>()), tot_salaries(0), tot_bonus_salaries(0),  highest_sal(0), tot_worked_hours(0), highest_worked_hours(0), highest_seniority(0) {}

paycheck::~paycheck() {}

int paycheck::getSize() const{
    return pc.getSize();
}

worker* paycheck::getWorkerFromIndex(int i) const {
    return pc.getNodoFromIndex(i)->info;
}

void paycheck::updateTotSalaries(const double& up) {
    this->tot_salaries += up;
}

void paycheck::updateTotBonusSalaries(const double& up) {
    this->tot_bonus_salaries += up;
}

void paycheck::updateTotWorkedHours(const int& up) {
    this->tot_worked_hours += up;
}

double paycheck::getTotSal() const {
    return this->tot_salaries;
}

double paycheck::getTotBuonusSal() const {
    return this->tot_bonus_salaries;
}

worker* paycheck::retrieveWorkerFromCf(const std::string& cf) const {
    bool found = false;
    worker* aux = nullptr;
    for(int count=0; count < pc.getSize(); ++count){
        if(this->pc[count]->getCodFiscale() == cf){
            aux = pc[count];
            found = true;
        }
    }
    if(!found){
        std::cout << "Impiegato non trovato" << std::endl;
    }
    return aux;
}

worker* paycheck::getWorkerAtPos(const int& i) const {
    return pc.getNodoFromIndex(i)->info;
}

Container<worker *> paycheck::getWorkers() const {
    return pc;
}

void paycheck::resetPaycheck() {
    pc.clear();
    tot_salaries = 0;
    tot_bonus_salaries = 0;
    highest_sal = 0;
    tot_worked_hours = 0;
    highest_worked_hours = 0;
    highest_seniority = 0;
}


bool paycheck::isPresent(const std::string& w) const {
    if(retrieveWorkerFromCf(w)==nullptr){
        return false;
    } else {
        return true;
    }
}

bool paycheck::isPresent(worker* w) const {
    bool found=false;
    for(int count=0; count < pc.getSize(); ++count) {
        if(pc[count] == w){
            found=true;
            count = pc.getSize();
        }
    }
    return found;
}

bool paycheck::hasDirector() const {
    bool found = isPresent(findDirCodFisc());
    return found;
}

void paycheck::addEmp(const std::string& n, const std::string& sn, const std::string& cf, const std::string& tc) {
    worker* aux;

    if(tc=="Full-Time") {
        aux = new ftemployee(n, sn, cf);
    } else if (tc == "Part-Time") {
        aux = new ptemployee(n, sn, cf);
    } else if (tc == "Direttore") {
        aux = new director(n, sn, cf);
    } else {
        std::cout << "Input incorretto, selezionare un tipo di contratto tra director, fulltime e parttime" << std::endl;
        return;
    }

    this->pc.pushBack(aux);
}

void paycheck::addEmp(worker* emp) {
    this->pc.pushBack(emp);
}


void paycheck::remEmp(const std::string& n, const std::string& sn, const std::string& cf,  const std::string& tc) {
    worker* aux;

    if(tc=="fulltime") {
        aux = new ftemployee(n, sn, cf);
    } else if (tc == "parttime") {
        aux = new ptemployee(n, sn, cf);
    } else if(tc=="director") {
        aux = new director(n, sn, cf);
    } else {
        std::cout << "Input incorretto, selezionare un tipo di contratto tra director, fulltime e parttime" << std::endl;
        return;
    }

    this->pc.remove(pc.getNodoFromInfo(aux));
}

void paycheck::remEmp(worker* w) {
    pc.remove(pc.getNodoFromInfo(w));
    return;
}

void paycheck::calcAllFullSal() {
    int wd;
    int wh;
    this->resetPaycheckData();

    for(int count=0; count < pc.getSize(); count++){
        std::cout << "Inserire i giorni lavorati dal dipendente " << pc[count]->getName() << " "  << pc[count]->getSname() << std::endl;
        std::cin >> wd;
        std::cout << "Inserire le ore lavorate dal dipendente " << pc[count]->getName() << " "  << pc[count]->getSname() << std::endl;
        std::cin >> wh;
        pc[count]->calcFullSal(wd, wh);
        this->updateTotSalaries(pc[count]->getLastMonthSalary());
        this->updateTotBonusSalaries(pc[count]->getLastMonthBonusSalary());
        this->updateTotWorkedHours(pc[count]->getLastMonthWorkedHours());
    }

    this->updateHighestSal();
    this->updateHighestWorkedHours();
    this->updateHighestSeniority();
}

void paycheck::calcAllFullSal(std::vector<std::pair<int, int>> collection) {
    int wd;
    int wh;
    int s_count = 0;
    this->resetPaycheckData();

    for(std::vector<std::pair<int, int>>::const_iterator it = collection.begin(); it != collection.end(); it++){
        wd = it->first;
        wh = it->second;
        pc[s_count]->calcFullSal(wd, wh);
        this->updateTotSalaries(pc[s_count]->getLastMonthSalary());
        this->updateTotBonusSalaries(pc[s_count]->getLastMonthBonusSalary());
        this->updateTotWorkedHours(pc[s_count]->getLastMonthWorkedHours());
        s_count++;
    }

    this->updateHighestSal();
    this->updateHighestWorkedHours();
    this->updateHighestSeniority();
}

void paycheck::promotePtEmp(const std::string& cf) {
    worker* aux = this->retrieveWorkerFromCf(cf);
    if(dynamic_cast<ptemployee*>(aux)){
        worker* new_worker = new ftemployee(*aux);
        pc.substitute(aux, new_worker);
    } else {
        std::cout << "Impiegato non trovato o gia' con contratto FullTime" << std::endl;
    }
    return;
}

void paycheck::promotePtEmp(worker* w){
     if(dynamic_cast<ptemployee*>(w)){
        worker* new_worker = new ftemployee(*w);
        pc.substitute(w, new_worker);
     } else {
         std::cout << "Impiegato non trovato o gia' con contratto FullTime" << std::endl;
     }
     return;
}

std::string paycheck::findDirCodFisc() const {
    for(int count=0; count < pc.getSize(); ++count){
        if(dynamic_cast<director*>(pc[count])){
            return pc[count]->getCodFiscale();
        }
    }
    return "";
}

double paycheck::getHighestSal() const {
    double highestSal=0;
    for(int count=0; count < pc.getSize(); ++count){
        if(pc[count]->getLastMonthSalary() > highestSal){
            highestSal = pc[count]->getLastMonthSalary();
        }
    }
    return highestSal;
}

int paycheck::getTotWorkedHours() const {
    return this->tot_worked_hours;
}

void paycheck::updateHighestSal() {
    this->highest_sal = getHighestSal();
}

int paycheck::getHighestWorkedHours() const {
    int highestWorkedHours=0;
    for(int count=0; count < pc.getSize(); ++count){
        if(pc[count]->getLastMonthWorkedHours() > highestWorkedHours){
            highestWorkedHours = pc[count]->getLastMonthWorkedHours();
        }
    }
    return highestWorkedHours;
}

void paycheck::updateHighestWorkedHours() {
    this->highest_worked_hours = getHighestWorkedHours();
}

int paycheck::getHighestSeniority() const {
    int highestSeniority=0;
    for(int count=0; count < pc.getSize(); ++count){
        if(pc[count]->getSeniority() > highestSeniority){
            highestSeniority = pc[count]->getSeniority();
        }
    }
    return highestSeniority;
}

void paycheck::updateHighestSeniority() {
    this->highest_seniority = getHighestSeniority();
}


void paycheck::resetPaycheckData() {
    this->tot_salaries = 0;
    this->tot_bonus_salaries = 0;
    this->tot_worked_hours = 0;
}

void paycheck::orderByFullSalMax() {
    bool swap_flag=true;
    while(swap_flag){
        swap_flag=false;
          for(int count=0; count < pc.getSize()-1; ++count){
            if(pc[count]->getLastMonthSalary() < pc[count+1]->getLastMonthSalary()){
                pc.swap(count, count+1);
                swap_flag = true;
            }
        }
    }
}

void paycheck::orderByBonusSalMax() {
    bool swap_flag=true;
    while(swap_flag){
        swap_flag=false;
          for(int count=0; count < pc.getSize()-1; ++count){
            if(pc[count]->getLastMonthBonusSalary() < pc[count+1]->getLastMonthBonusSalary()){
                pc.swap(count, count+1);
                swap_flag = true;
            }
        }
    }
}

void paycheck::orderByWorkedHoursMax() {
    bool swap_flag=true;
    while(swap_flag){
        swap_flag=false;
          for(int count=0; count < pc.getSize()-1; ++count){
            if(pc[count]->getLastMonthWorkedHours() < pc[count+1]->getLastMonthWorkedHours()){
                pc.swap(count, count+1);
                swap_flag = true;
            }
        }
    }
}

void paycheck::orderBySeniorityMax() {
    bool swap_flag=true;
    while(swap_flag){
        swap_flag=false;
          for(int count=0; count < pc.getSize()-1; ++count){
            if(pc[count]->getSeniority() < pc[count+1]->getSeniority()){
                pc.swap(count, count+1);
                swap_flag = true;
            }
        }
    }
}

void paycheck::orderByFullSalMin() {
    bool swap_flag=true;
    while(swap_flag){
        swap_flag=false;
          for(int count=0; count < pc.getSize()-1; ++count){
            if(pc[count]->getLastMonthSalary() > pc[count+1]->getLastMonthSalary()){
                pc.swap(count, count+1);
                swap_flag = true;
            }
        }
    }
}

void paycheck::orderByBonusSalMin() {
    bool swap_flag=true;
    while(swap_flag){
        swap_flag=false;
          for(int count=0; count < pc.getSize()-1; ++count){
            if(pc[count]->getLastMonthSalary() > pc[count+1]->getLastMonthSalary()){
                pc.swap(count, count+1);
                swap_flag = true;
            }
        }
    }
}

void paycheck::orderByWorkedHoursMin() {
    bool swap_flag=true;
    while(swap_flag){
        swap_flag=false;
          for(int count=0; count < pc.getSize()-1; ++count){
            if(pc[count]->getLastMonthSalary() > pc[count+1]->getLastMonthSalary()){
                pc.swap(count, count+1);
                swap_flag = true;
            }
        }
    }
}

void paycheck::orderBySeniorityMin() {
    bool swap_flag=true;
    while(swap_flag){
        swap_flag=false;
          for(int count=0; count < pc.getSize()-1; ++count){
            if(pc[count]->getLastMonthSalary() > pc[count+1]->getLastMonthSalary()){
                pc.swap(count, count+1);
                swap_flag = true;
            }
        }
    }
}

void paycheck::orderByVacDayMax() {
    bool swap_flag=true;
    while(swap_flag){
        swap_flag=false;
          for(int count=0; count < pc.getSize()-1; ++count){
            if(pc[count]->getVacAcc() < pc[count+1]->getVacAcc()){
                pc.swap(count, count+1);
                swap_flag = true;
            }
        }
    }
}

void paycheck::orderByVacDayMin() {
    bool swap_flag=true;
    while(swap_flag){
        swap_flag=false;
          for(int count=0; count < pc.getSize()-1; ++count){
            if(pc[count]->getVacAcc() > pc[count+1]->getVacAcc()){
                pc.swap(count, count+1);
                swap_flag = true;
            }
        }
    }
}

void paycheck::orderByRole() {
    Container<worker*> aux;

    bool found = true;
    while(found){
        found=false;
          for(int count=0; count < pc.getSize(); ++count){
            if(dynamic_cast<director*>(pc[count])){
                aux.pushBack(pc[count]);
                pc.remove(count);
                found = true;
            }
        }
    }

    found = true;
    while(found){
        found=false;
          for(int count=0; count < pc.getSize(); ++count){
            if(dynamic_cast<ftemployee*>(pc[count])){
                aux.pushBack(pc[count]);
                pc.remove(count);
                found = true;
            }
        }
    }

    found = true;
    while(found){
        found=false;
          for(int count=0; count < pc.getSize(); ++count){
            if(dynamic_cast<ptemployee*>(pc[count])){
                aux.pushBack(pc[count]);
                pc.remove(count);
                found = true;
            }
        }
    }

    this->pc = aux;
}

void paycheck::dispAll() const {
    std::cout << std::endl;
    std::cout << "METRICHE DELL'ULTIMO MESE" << std::endl << std::endl;
    std::cout << "Totale soldi in uscita per gli stipendi: " << tot_salaries << std::endl;
    std::cout << "Totale soldi in uscite per buonus sugli stipendi: " << tot_bonus_salaries << std::endl;
    std::cout << "Totale ore lavorate: " << tot_worked_hours << std::endl;
    std::cout << "Stipendio più alto: " << highest_sal << std::endl;
    std::cout << "Ore di lavoro più alte: " << highest_worked_hours << std::endl;
    std::cout << "Anzianità più alta: " << highest_seniority << std::endl << std::endl;

    std::cout << "METRICHE PER OGNI DIPENDENTE" << std::endl << std::endl;
    for(int count=0; count < pc.getSize(); ++count){
        std::cout << count+1 << ")" << std::endl << "Nome: " << pc[count]->getName() << std::endl;
        std::cout << "Cognome: " << pc[count]->getSname() << std::endl;
        std::cout << "Codice Fiscale: " << pc[count]->getCodFiscale() << std::endl;
        std::cout << "Giorni lavorati: " << pc[count]->getLastMonthWorkedDays() << std::endl;
        std::cout << "Ore lavorate: " << pc[count]->getLastMonthWorkedHours() << std::endl;
        std::cout << "Stipendio base: " << pc[count]->getLastMonthBaseSalary() << std::endl;
        std::cout << "Bonus: " << pc[count]->getLastMonthBonusSalary() << std::endl;
        std::cout << "Stipendio totale: " << pc[count]->getLastMonthSalary() << std::endl;
        std::cout << "Anzianita': " << pc[count]->getSeniority() << " mesi " << std::endl;
        std::cout << "Giorni ferie accumualti: " << pc[count]->getVacAcc() << std::endl << std::endl;
     }
}

void paycheck::dispInternalData() const {
    std::cout << std::endl;
    std::cout << "METRICHE DELL'ULTIMO MESE" << std::endl << std::endl;
    std::cout << "Totale soldi in uscita per gli stipendi: " << tot_salaries << std::endl;
    std::cout << "Totale soldi in uscite per buonus sugli stipendi: " << tot_bonus_salaries << std::endl;
    std::cout << "Totale ore lavorate: " << tot_worked_hours << std::endl;
    std::cout << "Stipendio più alto: " << highest_sal << std::endl;
    std::cout << "Ore di lavoro più alte: " << highest_worked_hours << std::endl;
    std::cout << "Anzianità più alta: " << highest_seniority << std::endl << std::endl;
}
