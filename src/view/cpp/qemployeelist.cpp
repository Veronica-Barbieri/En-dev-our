#include "../headers/qemployeelist.h"

QEmployeeList::QEmployeeList(QWidget *parent) : QWidget(parent) {
    list_layout = new QVBoxLayout(this);
    list_layout->setAlignment(Qt::AlignTop);
}

void QEmployeeList::addEmp(const std::string& n, const std::string& sn, const std::string& cf, const std::string& con) {
    QEmployee* e = new QEmployee();
    e->updateInfo(n, sn, cf, con);
    connect(e, SIGNAL(emitInfoChange(const std::string&)), this, SLOT(receiveInfoReq(const std::string&)));
    qemp_cont.push_back(e);
    list_layout->addWidget(e);
}

void QEmployeeList::delEmp() {
    QLayoutItem* aux = list_layout->itemAt(list_layout->count()-1);
    QEmployee* aux_emp = static_cast<QEmployee*>(aux->widget());
    list_layout->removeWidget(aux_emp);
    delete qemp_cont.back();
    qemp_cont.pop_back();
}

void QEmployeeList::clearList() {
    while(qemp_cont.size()!=0){
        delEmp();
    }
}

void QEmployeeList::receiveInfoReq(const std::string& ccf) {
    emit emitInfoRequest(ccf);
}
