#include "../headers/qadddialog.h"

QAddDialog::QAddDialog(QWidget *parent) : QWidget(parent) {
    name = "";
    sname = "";
    cf = "";
    contr = "";

    QVBoxLayout* main = new QVBoxLayout(this);
    QFormLayout* l = new QFormLayout();
    QHBoxLayout* btn = new QHBoxLayout();

    QPushButton* confirm = new QPushButton(tr("Conferma"));

    insert_name = new QLineEdit(this);
    insert_sname = new QLineEdit(this);
    insert_cf = new QLineEdit(this);
    insert_cont = new QComboBox(this);

    insert_cont->addItem("Direttore");
    insert_cont->addItem("Full-Time");
    insert_cont->addItem("Part-Time");

    l->addRow(tr("&Nome: "), insert_name);
    l->addRow(tr("&Cognome: "), insert_sname);
    l->addRow(tr("&Cod. Fiscale: "), insert_cf);
    l->addRow(tr("&Contratto: "), insert_cont);

    confirm->setDisabled(true); //disable confirm
    //confirm->setFlat(true);
    btn->addWidget(confirm);

    connect(insert_name, SIGNAL(editingFinished()), this, SLOT(checkFilled()));
    connect(insert_sname, SIGNAL(editingFinished()), this, SLOT(checkFilled()));
    connect(insert_cf, SIGNAL(editingFinished()), this, SLOT(checkFilled()));
    connect(confirm, SIGNAL(clicked()), this, SLOT(slotAdd()));

    connect(this, SIGNAL(enableConfirm(bool)), confirm, SLOT(setEnabled(bool)));

    main->addLayout(l);
    main->addLayout(btn);
}

void QAddDialog::slotAdd() {
    std::string n = insert_name->text().toStdString();
    std::string sn = insert_sname->text().toStdString();
    std::string ccf = insert_cf->text().toStdString();
    std::string con = insert_cont->currentText().toStdString();

    insert_name->clear();
    insert_sname->clear();
    insert_cf->clear();
    insert_cont->setCurrentIndex(0);

    checkFilled();

    emit emitAdd(n, sn, ccf, con);
}

void QAddDialog::checkFilled() {
    if(insert_name->text() != "" && insert_sname->text() != "" && insert_cf->text() != ""){
        emit QAddDialog::enableConfirm(true);
    }else{
        emit QAddDialog::enableConfirm(false);
    }
}
