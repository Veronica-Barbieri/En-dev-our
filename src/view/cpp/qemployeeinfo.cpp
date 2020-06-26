#include "../headers/qemployeeinfo.h"

QString QEmployeeInfo::name_placeholder = "Nome: ";
QString QEmployeeInfo::sname_placeholder = "Cognome: ";
QString QEmployeeInfo::cf_placeholder = "Cod. fisc: ";
QString QEmployeeInfo::contract_placeholder = "Tipo di contratto: ";
QString QEmployeeInfo::wdays_placeholder = "Giorni lavorati: ";
QString QEmployeeInfo::whours_placeholder = "Ore lavorate: ";
QString QEmployeeInfo::base_salary_placeholder = "Stipendio base (€): ";
QString QEmployeeInfo::bonus_salary_placeholder = "Stipendio bonus (€): ";
QString QEmployeeInfo::salary_placeholder = "Stipendio totale (€): ";
QString QEmployeeInfo::vac_placeholder = "Giorni feriali accumulati: ";
QString QEmployeeInfo::seniority_placeholder = "Anzianita' (mesi): ";

QEmployeeInfo::QEmployeeInfo(QWidget *parent) : QWidget(parent) {
    emp_info_layout = new QGridLayout(this);
    emp_info_layout->setAlignment(Qt::AlignTop);

    QLabel* n = new QLabel(this);
    QLabel* sn = new QLabel(this);
    QLabel* ccf = new QLabel(this);
    QLabel* con = new QLabel(this);
    QLabel* wd = new QLabel(this);
    QLabel* wh = new QLabel(this);
    QLabel* bs = new QLabel(this);
    QLabel* bbs = new QLabel(this);
    QLabel* s = new QLabel(this);
    QLabel* v = new QLabel(this);
    QLabel* sen = new QLabel(this);

    name = new QLabel(this);
    sname = new QLabel(this);
    cf = new QLabel(this);
    contract = new QLabel(this);
    wdays = new QLabel(this);
    whours = new QLabel(this);
    base_salary = new QLabel(this);
    bonus_salary = new QLabel(this);
    salary = new QLabel(this);
    vac = new QLabel(this);
    seniority = new QLabel(this);

    n->setText(name_placeholder);
    sn->setText(sname_placeholder);
    ccf->setText(cf_placeholder);
    con->setText(contract_placeholder);
    wd->setText(wdays_placeholder);
    wh->setText(whours_placeholder);
    bs->setText(base_salary_placeholder);
    bbs->setText(bonus_salary_placeholder);
    s->setText(salary_placeholder);
    v->setText(vac_placeholder);
    sen->setText(seniority_placeholder);

    n->setFont(QFont("Helvetica", 10, QFont::Bold));
    sn->setFont(QFont("Helvetica", 10, QFont::Bold));
    ccf->setFont(QFont("Helvetica", 10, QFont::Bold));
    con->setFont(QFont("Helvetica", 10, QFont::Bold));
    wd->setFont(QFont("Helvetica", 10, QFont::Bold));
    wh->setFont(QFont("Helvetica", 10, QFont::Bold));
    bs->setFont(QFont("Helvetica", 10, QFont::Bold));
    bbs->setFont(QFont("Helvetica", 10, QFont::Bold));
    s->setFont(QFont("Helvetica", 10, QFont::Bold));
    v->setFont(QFont("Helvetica", 10, QFont::Bold));
    sen->setFont(QFont("Helvetica", 10, QFont::Bold));

    this->updateInfo();

    emp_info_layout->addWidget(n, 0, 0);
    emp_info_layout->addWidget(sn, 1, 0);
    emp_info_layout->addWidget(ccf, 2, 0);
    emp_info_layout->addWidget(con, 3, 0);
    emp_info_layout->addWidget(wd, 4, 0);
    emp_info_layout->addWidget(wh, 5, 0);
    emp_info_layout->addWidget(bs, 6, 0);
    emp_info_layout->addWidget(bbs, 7, 0);
    emp_info_layout->addWidget(s, 8, 0);
    emp_info_layout->addWidget(v, 9, 0);
    emp_info_layout->addWidget(sen, 10, 0);

    emp_info_layout->addWidget(name, 0, 1);
    emp_info_layout->addWidget(sname, 1, 1);
    emp_info_layout->addWidget(cf, 2, 1);
    emp_info_layout->addWidget(contract, 3, 1);
    emp_info_layout->addWidget(wdays, 4, 1);
    emp_info_layout->addWidget(whours, 5, 1);
    emp_info_layout->addWidget(base_salary, 6, 1);
    emp_info_layout->addWidget(bonus_salary, 7, 1);
    emp_info_layout->addWidget(salary, 8, 1);
    emp_info_layout->addWidget(vac, 9, 1);
    emp_info_layout->addWidget(seniority, 10, 1);

}

void QEmployeeInfo::updateInfo(const std::string& nn, const std::string& ssn, const std::string& ccf,
                               const std::string& ccon, const std::string& wwd, const std::string& wwh,
                               const std::string& bbs, const std::string& bbbs, const std::string& ss,
                               const std::string& vac, const std::string& ssen) {
    this->name->setText(QString::fromStdString(nn));
    this->sname->setText(QString::fromStdString(ssn));
    this->cf->setText(QString::fromStdString(ccf));
    this->contract->setText(QString::fromStdString(ccon));
    this->wdays->setText(QString::fromStdString(wwd));
    this->whours->setText(QString::fromStdString(wwh));
    this->base_salary->setText(QString::fromStdString(bbs));
    this->bonus_salary->setText(QString::fromStdString(bbbs));
    this->salary->setText(QString::fromStdString(ss));
    this->vac->setText(QString::fromStdString(vac));
    this->seniority->setText(QString::fromStdString(ssen));
}

std::string QEmployeeInfo::getCurrentDisplayedWorker() {
    return this->cf->text().toStdString();
}
