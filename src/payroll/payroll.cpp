#include "payroll.h"
#include <exception>

payroll::payroll(): pc(Container<worker*>()), tot_salaries(0), tot_bonus_salaries(0),  highest_sal(0), tot_worked_hours(0), highest_worked_hours(0), highest_seniority(0), diff_hours(0), diff_sal(0) {}
payroll::payroll(const Container<worker*>& c, const double& s, const double& b, const double& hs, const int& wh, const int& hwh, const double& hsen, const double& diffs, const double& diffh)
    : pc(c), tot_salaries(s), tot_bonus_salaries(b), highest_sal(hs), tot_worked_hours(wh), highest_worked_hours(hwh), highest_seniority(hsen), diff_hours(diffh), diff_sal(diffs) {}

payroll::~payroll() {}

int payroll::getSize() const{
    return pc.getSize();
}

worker* payroll::getWorkerFromIndex(int i) const {
    return pc.getNodoFromIndex(i)->info;
}

void payroll::updateTotSalaries(const double& up) {
    this->tot_salaries += up;
}

void payroll::updateTotBonusSalaries(const double& up) {
    this->tot_bonus_salaries += up;
}

void payroll::updateTotWorkedHours(const int& up) {
    this->tot_worked_hours += up;
}

double payroll::getTotSal() const {
    return this->tot_salaries;
}

double payroll::getTotBuonusSal() const {
    return this->tot_bonus_salaries;
}

worker* payroll::retrieveWorkerFromCf(const std::string& cf) const {
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

worker* payroll::getWorkerAtPos(const int& i) const {
    return pc.getNodoFromIndex(i)->info;
}

Container<worker *> payroll::getWorkers() const {
    if(pc.getSize() == 0){
        throw std::domain_error("There are no workers in this payroll");
    }
    return pc;
}

void payroll::resetPaycheck() {
    pc.clear();
    tot_salaries = 0;
    tot_bonus_salaries = 0;
    highest_sal = 0;
    tot_worked_hours = 0;
    highest_worked_hours = 0;
    highest_seniority = 0;
}

void payroll::resetLastMonthPaycheck() {
    for(int i=0; i<pc.getSize(); ++i){
        worker* aux = pc.getNodoFromIndex(i)->info;
        aux->updateWorkData(0,0);
        aux->setLastMonthBaseSalary(0);
        aux->setLastMonthBonusSalary(0);
        aux->setLastMonthSalary(0);
        aux->resetVacAcc();
        aux->resetSeniority();
    }
    tot_salaries = 0;
    tot_bonus_salaries = 0;
    highest_sal = 0;
    tot_worked_hours = 0;
    highest_worked_hours = 0;
    highest_seniority = 0;
}


bool payroll::isPresent(const std::string& w) const {
    if(retrieveWorkerFromCf(w)==nullptr){
        return false;
    } else {
        return true;
    }
}

bool payroll::isPresent(worker* w) const {
    bool found=false;
    for(int count=0; count < pc.getSize(); ++count) {
        if(pc[count] == w){
            found=true;
            count = pc.getSize();
        }
    }
    return found;
}

bool payroll::hasDirector() const {
    bool found = isPresent(findDirCodFisc());
    return found;
}

void payroll::addEmp(const std::string& n, const std::string& sn, const std::string& cf, const std::string& tc) {
    worker* aux;

    if(isPresent(cf)){
        throw std::domain_error("CF already exists in this payroll");
    }
    if(hasDirector() && tc == "Direttore"){
        throw std::domain_error("A director already exists in this payroll");
    }

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

void payroll::addEmp(worker* emp) {
    this->pc.pushBack(emp);
}


void payroll::remEmp(const std::string& n, const std::string& sn, const std::string& cf,  const std::string& tc) {
    worker* aux;

    if(!isPresent(cf)){
        throw std::domain_error("No employee with that CF in this payroll");
    }
    /*if(dynamic_cast<director*>(retrieveWorkerFromCf(cf))){
        throw std::domain_error("canot remove director");
    }*/

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

void payroll::remEmp(worker* w) {
    if(!isPresent(w)){
        throw std::domain_error("No employee with that CF in this payroll");
    }
    /*if(dynamic_cast<director*>(w)){
        throw std::domain_error("canot remove director");
    }*/
    pc.remove(pc.getNodoFromInfo(w));
    return;
}

void payroll::calcAllFullSal() { //to remove?
    int wd;
    int wh;
    double curr_worked_hours = tot_worked_hours;
    double curr_sal = tot_salaries;
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

    diff_hours = tot_worked_hours - curr_worked_hours;
    diff_sal = curr_sal - tot_salaries;

    this->updateHighestSal();
    this->updateHighestWorkedHours();
    this->updateHighestSeniority();
}

void payroll::calcAllFullSal(std::vector<std::pair<int, int>> collection) {
    int wd;
    int wh;
    int s_count = 0;
    double curr_worked_hours = tot_worked_hours;
    double curr_sal = tot_salaries;
    this->resetPaycheckData();

    for(std::vector<std::pair<int, int>>::const_iterator it = collection.begin(); it != collection.end(); it++){
        wd = it->first;
        wh = it->second;
        if(pc[s_count]->calcFullSal(wd, wh) < 0){
            throw std::domain_error("Something went wrong dati errati");
        }
        this->updateTotSalaries(pc[s_count]->getLastMonthSalary());
        this->updateTotBonusSalaries(pc[s_count]->getLastMonthBonusSalary());
        this->updateTotWorkedHours(pc[s_count]->getLastMonthWorkedHours());
        s_count++;
    }

    diff_hours = tot_worked_hours - curr_worked_hours;
    diff_sal = curr_sal - tot_salaries;

    this->updateHighestSal();
    this->updateHighestWorkedHours();
    this->updateHighestSeniority();
}

double payroll::getDiffHours() const {
    return this->diff_hours;
}

double payroll::getDiffSal() const {
    return this->diff_sal;
}

void payroll::promotePtEmp(const std::string& cf) {
    worker* aux = this->retrieveWorkerFromCf(cf);
    /*if(dynamic_cast<ptemployee*>(aux)){
        worker* new_worker = new ftemployee(*aux);
        pc.substitute(aux, new_worker);
    } else {
        std::cout << "Impiegato non trovato o gia' con contratto FullTime" << std::endl;
    }
    return;*/
    if(!isPresent(cf)){
        throw std::domain_error("No employee with that CF in this payroll");
    }
    if(!dynamic_cast<ptemployee*>(aux)){
        throw std::domain_error("Cannot promote a non part-time employee");
    }
    worker* new_worker = new ftemployee(*aux);
    pc.substitute(aux, new_worker);
    return;
}

void payroll::promotePtEmp(worker* w){
     /*if(dynamic_cast<ptemployee*>(w)){
        worker* new_worker = new ftemployee(*w);
        pc.substitute(w, new_worker);
     } else {
         std::cout << "Impiegato non trovato o gia' con contratto FullTime" << std::endl;
     }
     return;*/
    if(!isPresent(w)){
        throw std::domain_error("No employee with that CF in this payroll");
    }
    if(!dynamic_cast<ptemployee*>(w)){
        throw std::domain_error("Cannot promote a non part-time employee");
    }
    worker* new_worker = new ftemployee(*w);
    pc.substitute(w, new_worker);
    return;
}

std::string payroll::findDirCodFisc() const {
    for(int count=0; count < pc.getSize(); ++count){
        if(dynamic_cast<director*>(pc[count])){
            return pc[count]->getCodFiscale();
        }
    }
    return "";
}

double payroll::getHighestSal() const {
    double highestSal=0;
    for(int count=0; count < pc.getSize(); ++count){
        if(pc[count]->getLastMonthSalary() > highestSal){
            highestSal = pc[count]->getLastMonthSalary();
        }
    }
    return highestSal;
}

int payroll::getTotWorkedHours() const {
    return this->tot_worked_hours;
}

void payroll::updateHighestSal() {
    this->highest_sal = getHighestSal();
}

int payroll::getHighestWorkedHours() const {
    int highestWorkedHours=0;
    for(int count=0; count < pc.getSize(); ++count){
        if(pc[count]->getLastMonthWorkedHours() > highestWorkedHours){
            highestWorkedHours = pc[count]->getLastMonthWorkedHours();
        }
    }
    return highestWorkedHours;
}

void payroll::updateHighestWorkedHours() {
    this->highest_worked_hours = getHighestWorkedHours();
}

int payroll::getHighestSeniority() const {
    int highestSeniority=0;
    for(int count=0; count < pc.getSize(); ++count){
        if(pc[count]->getSeniority() > highestSeniority){
            highestSeniority = pc[count]->getSeniority();
        }
    }
    return highestSeniority;
}

void payroll::updateHighestSeniority() {
    this->highest_seniority = getHighestSeniority();
}


void payroll::resetPaycheckData() {
    this->tot_salaries = 0;
    this->tot_bonus_salaries = 0;
    this->tot_worked_hours = 0;
}

void payroll::orderByFullSalMax() {
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

void payroll::orderByBonusSalMax() {
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

void payroll::orderByWorkedHoursMax() {
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

void payroll::orderBySeniorityMax() {
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

void payroll::orderByFullSalMin() {
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

void payroll::orderByBonusSalMin() {
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

void payroll::orderByWorkedHoursMin() {
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

void payroll::orderBySeniorityMin() {
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

void payroll::orderByVacDayMax() {
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

void payroll::orderByVacDayMin() {
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

void payroll::orderByRole() {
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

void payroll::dispAll() const {
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

void payroll::dispInternalData() const {
    std::cout << std::endl;
    std::cout << "METRICHE DELL'ULTIMO MESE" << std::endl << std::endl;
    std::cout << "Totale soldi in uscita per gli stipendi: " << tot_salaries << std::endl;
    std::cout << "Totale soldi in uscite per buonus sugli stipendi: " << tot_bonus_salaries << std::endl;
    std::cout << "Totale ore lavorate: " << tot_worked_hours << std::endl;
    std::cout << "Stipendio più alto: " << highest_sal << std::endl;
    std::cout << "Ore di lavoro più alte: " << highest_worked_hours << std::endl;
    std::cout << "Anzianità più alta: " << highest_seniority << std::endl << std::endl;
}
