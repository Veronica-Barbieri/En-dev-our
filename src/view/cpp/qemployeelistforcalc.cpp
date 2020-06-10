#include "../headers/qemployeelistforcalc.h"

QEmployeeListForCalc::QEmployeeListForCalc(QWidget *parent, Container<worker*> c) : QWidget(parent) {
    list = new QVBoxLayout(this);
    QPushButton* confirm = new QPushButton(tr("Conferma"), this);
    size = 0;

    for(int i=0; i<c.getSize(); i++) {
        QEmployeeForCalc* emp = new QEmployeeForCalc(this, c.getNodoFromIndex(i)->info->getName(),
                                                     c.getNodoFromIndex(i)->info->getSname(), c.getNodoFromIndex(i)->info->getCodFiscale());
        list->addWidget(emp);
        size++;
    }

    connect(confirm, SIGNAL(clicked()), this, SLOT(collectData()));
    list->setAlignment(confirm, Qt::AlignBottom);
    list->addWidget(confirm);
}

void QEmployeeListForCalc::clearData() {
    collection.clear();
}

void QEmployeeListForCalc::collectData() {
    for(int i=0; i<size; i++){
        QLayoutItem* aux = list->itemAt(i);
        QEmployeeForCalc* emp_aux = static_cast<QEmployeeForCalc*>(aux->widget());
        std::pair<int, int> stats(emp_aux->getWDaysContent(), emp_aux->getWHoursContent());
        collection.push_back(stats);
    }
    emit emitCalcFullSal(collection);
}

