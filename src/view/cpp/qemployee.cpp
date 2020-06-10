#include "../headers/qemployee.h"

QString QEmployee::name_placeholder = "Nome: ";
QString QEmployee::sname_placeholer = "Cognome: ";
QString QEmployee::cf_placeholder = "Cod. Fiscale: ";
QString QEmployee::contract_placeholder = "Tipo di contratto: ";

QEmployee::QEmployee(QWidget *parent): QWidget(parent) {
    info_layout = new QGridLayout(this);
    info_layout->setSizeConstraint(QLayout::SizeConstraint(3));

    QLabel* name_tag = new QLabel(this);
    QLabel* sname_tag = new QLabel(this);
    QLabel* cf_tag = new QLabel(this);
    QLabel* contract_tag = new QLabel(this);
    QPushButton* info = new QPushButton(tr("Info"), this);

    name = new QLabel(this);
    sname = new QLabel(this);
    cf = new QLabel(this);
    contract = new QLabel(this);

    name_tag->setText(name_placeholder);
    sname_tag->setText(sname_placeholer);
    cf_tag->setText(cf_placeholder);
    contract_tag->setText(contract_placeholder);

    name_tag->setFont(QFont("Helvetica", 10, QFont::Bold));
    sname_tag->setFont(QFont("Helvetica", 10, QFont::Bold));
    cf_tag->setFont(QFont("Helvetica", 10, QFont::Bold));
    contract_tag->setFont(QFont("Helvetica", 10, QFont::Bold));

    this->updateInfo("N/A", "N/A", "N/A", "N/A");

    connect(info, SIGNAL(clicked()), this, SLOT(slotInfoChange()));

    info_layout->addWidget(name_tag, 0, 0);
    info_layout->addWidget(sname_tag, 1, 0);
    info_layout->addWidget(cf_tag, 2, 0);
    info_layout->addWidget(contract_tag, 3, 0);
    info_layout->addWidget(info, 4, 0);

    info_layout->addWidget(name, 0, 1);
    info_layout->addWidget(sname, 1, 1);
    info_layout->addWidget(cf, 2, 1);
    info_layout->addWidget(contract, 3, 1);

}

void QEmployee::updateInfo(const std::string& n, const std::string& sn, const std::string& ccf, const std::string& con) {
    this->name->setText(QString::fromStdString(n));
    this->sname->setText(QString::fromStdString(sn));
    this->cf->setText(QString::fromStdString(ccf));
    this->contract->setText(QString::fromStdString(con));
}

void QEmployee::slotInfoChange() {
    std::string ccf = cf->text().toStdString();

    emit emitInfoChange(ccf);
}
