#include "../header/qtsalariescontroller.h"
#include <exception>

QtSalariesController::QtSalariesController(paycheck* m, QSalaries* v, QObject *parent) : QObject(parent), model(m), view(v) {}

QtSalariesController::QtSalariesController(paycheck* m, QObject* parent): QObject(parent), model(m), view(nullptr) {}

worker* QtSalariesController::getEmpAtIndex(int i) const{
    return model->getWorkerFromIndex(i);
}

int QtSalariesController::getNumberOfEmp() const {
    return model->getSize();
}

void QtSalariesController::addView(QSalaries* q) {
    view = q;
}

int QtSalariesController::modelSize() const {
    return model->getSize();
}

Container<worker *> QtSalariesController::getCurrCont() {
    try {
        return model->getWorkers();
    } catch (std::domain_error e) {
        emit showError(e.what());
        return Container<worker*>();
    }
}

worker* QtSalariesController::operator[](const int& i) const {
    return model->getWorkerAtPos(i);
}

void QtSalariesController::addEmp(const std::string& n, const std::string& sn, const std::string& cf, const std::string& contr) {
    try {
        model->addEmp(n, sn, cf, contr);
        view->updateList();
    } catch (std::domain_error e) {
        emit showError(e.what());
        //view->showErrorDialog(e.what());
    }
}

void QtSalariesController::delEmp(const std::string& cf) {
    try {
        worker* aux = model->retrieveWorkerFromCf(cf);
        model->remEmp(aux);
        view->updateList();
    } catch (std::domain_error e) {
        emit showError(e.what());
    }
}

void QtSalariesController::promoEmp(const std::string& cf) {
    try {
        worker* aux = model->retrieveWorkerFromCf(cf);
        model->promotePtEmp(aux);
        view->updateList();
    } catch (std::domain_error e) {
        emit showError(e.what());
    }
}

void QtSalariesController::updateInfEmp(const std::string& cf) {
    worker* aux = model->retrieveWorkerFromCf(cf);
    std::string contr;
    if(dynamic_cast<ftemployee*>(aux)){
        contr = "Full-Time";
    }
    if(dynamic_cast<ptemployee*>(aux)){
        contr = "Part-Time";
    }
    if(dynamic_cast<director*>(aux)){
        contr = "Direttore";
    }
    std::string wwd = std::to_string(aux->getLastMonthWorkedDays());
    std::string wwh = std::to_string(aux->getLastMonthWorkedHours());
    std::string bs = std::to_string(aux->getLastMonthBaseSalary());
    std::string bbs = std::to_string(aux->getLastMonthBonusSalary());
    std::string s = std::to_string(aux->getLastMonthSalary());
    std::string vac = std::to_string(aux->getVacAcc());
    std::string sen = std::to_string(aux->getSeniority());

    view->updateInfoField(aux->getName(), aux->getSname(), aux->getCodFiscale(),
                          contr, wwd, wwh,
                          bs, bbs, s,
                          vac, sen);
}

void QtSalariesController::orderBy(const QString& option) {
    std::string tmp = option.toStdString();
    if(tmp == "Ordina per ruolo"){
        model->orderByRole();
    }

    if(tmp == "Ordina per stipendio bonus massimo"){
        model->orderByBonusSalMax();
    }

    if(tmp == "Ordina per stipendio bonus minimo"){
        model->orderByBonusSalMin();
    }

    if(tmp == "Ordina per stipendio totale massimo"){
        model->orderByFullSalMax();
    }

    if(tmp == "Ordina per stipendio totale minimo"){
        model->orderByFullSalMin();
    }

    if(tmp == "Ordina per ore di lavoro massime"){
        model->orderByWorkedHoursMax();
    }

    if(tmp == "Ordina per ore di lavoro minime"){
        model->orderByWorkedHoursMin();
    }

    if(tmp == "Ordina per anzianità massima") {
        model->orderBySeniorityMax();
    }

    if(tmp == "Ordina per anzianità minima") {
        model->orderBySeniorityMin();
    }

    if(tmp == "Ordina per vacanze accumulate massime") {
        model->orderByVacDayMax();
    }

    if(tmp == "Ordina per vacanze accumulate minime") {
        model->orderByVacDayMin();
    }

    view->updateList();
}

void QtSalariesController::calcFullSal(std::vector<std::pair<int, int>> stats) {
    model->calcAllFullSal(stats);
    //update view
    std::string s = std::to_string(model->getTotSal());
    std::string bs = std::to_string(model->getTotBuonusSal());
    std::string wh = std::to_string(model->getHighestSal());
    std::string hs = std::to_string(model->getTotWorkedHours());
    std::string hwh = std::to_string(model->getHighestWorkedHours());
    std::string sen = std::to_string(model->getHighestSeniority());

    view->updatePayrollInfo(s, bs, wh,
                            hs, hwh, sen);
    view->updateInfoField("N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A");

}

void QtSalariesController::reset() {
    model->resetPaycheck();
    view->clearView();
}
