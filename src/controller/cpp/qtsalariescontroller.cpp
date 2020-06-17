#include "../header/qtsalariescontroller.h"
#include <exception>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

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
    try {
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
    } catch (std::domain_error e) {
        model->resetLastMonthPaycheck();
        emit showError(e.what());
    }

}

void QtSalariesController::reset() {
    model->resetPaycheck();
    view->clearView();
}

void QtSalariesController::updateModel(paycheck* nm){
    delete model;
    model = nm;
}

void QtSalariesController::getPayrollFromFile(QJsonObject root){
    Container<worker*> cont; //empty container
    worker* w;
    paycheck* temp_payroll; //empty payroll

    //read data
    double ts = root.value("tot_salari").toDouble();
    double tbs = root.value("tot_bonus_salari").toDouble();
    double hs = root.value("highest_salary").toDouble();
    double twh = root.value("tot_worked_hours").toDouble();
    double hwh = root.value("highest_worked_hours").toDouble();
    double hsen = root.value("highest_seniority").toDouble();

    QJsonArray empl_list = root["employee_list"].toArray();

    for(int i=0; i<empl_list.size(); ++i){
        QJsonObject empl;
        empl = empl_list[i].toObject();

        QString tc = empl.value("Role").toString();
        QString n = empl.value("Name").toString();
        QString sn = empl.value("Surname").toString();
        QString cf = empl.value("CF").toString();

        int wd = empl.value("worked_days").toInt();
        int wh = empl.value("worked_hours").toInt();
        double base = empl.value("base_salary").toDouble();
        double bonus = empl.value("bonus_salary").toDouble();
        double salary = empl.value("total_salary").toDouble();
        int sen = empl.value("seniority").toInt();
        int hol = empl.value("holidays").toInt();

        try {
            if(tc=="Full-Time") {
                w = new ftemployee(n.toStdString(), sn.toStdString(), cf.toStdString(), wd,wh,base,bonus,salary,sen,hol);
            } else if (tc == "Part-Time") {
                w = new ptemployee(n.toStdString(), sn.toStdString(), cf.toStdString(), wd,wh,base,bonus,salary,sen,hol);
            } else if (tc == "Direttore") {
                w = new director(n.toStdString(), sn.toStdString(), cf.toStdString(), wd,wh,base,bonus,salary,sen,hol);
            } else {
                QString msg = "Ruolo dell'employee \"" + cf + "\" non corretto. Selezionare un tipo tra Direttore, Full-Time e Part-Time.";
                throw std::logic_error(msg.toStdString());
            }
            cont.pushBack(w);
        } catch (std::logic_error e) {
            emit view->showErrorDialog(e.what());
        }

    }

    reset(); //resets view and model
    temp_payroll = new paycheck(cont, ts, tbs, hs, twh, hwh, hsen);
    updateModel(temp_payroll);
    view->updateList();//updates view list
    view->updatePayrollInfo(QString::number(tbs).toStdString(),
                      QString::number(tbs).toStdString(),
                      QString::number(hs).toStdString(),
                      QString::number(twh).toStdString(),
                      QString::number(hwh).toStdString(),
                      QString::number(hsen).toStdString());
}

QJsonObject QtSalariesController::writePayrollToFile(){
    Container<worker*> temp = getCurrCont();
    QJsonArray employee_array;
    for(int i = 0; i<temp.getSize(); ++i){
        QJsonObject json_empl;
        worker* aux = temp.getNodoFromIndex(i)->info;

        if(dynamic_cast<ftemployee*>(aux)) {
            json_empl["Role"] = QString::fromStdString("Full-Time");
        } else if (dynamic_cast<ptemployee*>(aux)) {
            json_empl["Role"] = QString::fromStdString("Part-Time");
        } else if (dynamic_cast<director*>(aux)) {
            json_empl["Role"] = QString::fromStdString("Direttore");
        }

        json_empl["Name"] = QString::fromStdString(temp.getNodoFromIndex(i)->info->getName());
        json_empl["Surname"] = QString::fromStdString(temp.getNodoFromIndex(i)->info->getSname());
        json_empl["CF"] = QString::fromStdString(temp.getNodoFromIndex(i)->info->getCodFiscale());

        json_empl["worked_days"] = temp.getNodoFromIndex(i)->info->getLastMonthWorkedHours();
        json_empl["worked_hours"] = temp.getNodoFromIndex(i)->info->getLastMonthWorkedDays();
        json_empl["base_salary"] = temp.getNodoFromIndex(i)->info->getLastMonthBaseSalary();
        json_empl["bonus_salary"] = temp.getNodoFromIndex(i)->info->getLastMonthBonusSalary();
        json_empl["total_salary"] = temp.getNodoFromIndex(i)->info->getLastMonthSalary();
        json_empl["seniority"] = temp.getNodoFromIndex(i)->info->getSeniority();
        json_empl["holidays"] = temp.getNodoFromIndex(i)->info->getVacAcc();

        employee_array.push_back(json_empl);
    }

    QJsonObject json_payroll;
    QJsonValue ts = model->getTotSal();
    QJsonValue tbs = model->getTotBuonusSal();
    QJsonValue hs = model->getHighestSal();
    QJsonValue twh = model->getTotWorkedHours();
    QJsonValue hwh = model->getHighestWorkedHours();
    QJsonValue hsen = model->getHighestSeniority();

    json_payroll.insert(QString("tot_salari"), ts);
    json_payroll.insert(QString("tot_bonus_salari"), tbs);
    json_payroll.insert(QString("highest_salary"), hs);
    json_payroll.insert(QString("tot_worked_hours"), twh);
    json_payroll.insert(QString("highest_worked_hours"), hwh);
    json_payroll.insert(QString("highest_seniority"), hs);

    json_payroll.insert(QString("employee_list"), employee_array);

    return json_payroll;
}
