#include "../headers/qemployeeforcalc.h"

QEmployeeForCalc::QEmployeeForCalc(QWidget *parent, const std::string& n, const std::string& sn, const std::string& cf) : QWidget(parent) {
    QHBoxLayout* main = new QHBoxLayout(this);
    QVBoxLayout* for_labels = new QVBoxLayout();

    QLabel* name = new QLabel(this);
    QLabel* sname = new QLabel(this);
    QLabel* cod_fisc = new QLabel(this);

    name->setText("Nome: " + QString::fromStdString(n));
    sname->setText("Cognome: " + QString::fromStdString(sn));
    cod_fisc->setText("Cod.Fisc.: " + QString::fromStdString(cf));

    for_labels->addWidget(name);
    for_labels->addWidget(sname);
    for_labels->addWidget(cod_fisc);

    wd = new QLineEdit(this);
    wh = new QLineEdit(this);

    main->setAlignment(Qt::AlignTop);

    main->addLayout(for_labels);
    main->addWidget(wd);
    main->addWidget(wh);
}

int QEmployeeForCalc::getWDaysContent() {
    return wd->text().toInt();
}

int QEmployeeForCalc::getWHoursContent() {
    return wh->text().toInt();
}


