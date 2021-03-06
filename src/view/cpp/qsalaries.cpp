#include "../headers/qsalaries.h"
#include "../../controller/header/qtsalariescontroller.h"
#include <QMessageBox>
#include <string>
#include <QFile>
#include <QSaveFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
#include <QString>
 #include <QFileDialog>

QSalaries::QSalaries(QWidget *parent, QtSalariesController* c) : QWidget(parent), controller(c) {
    QVBoxLayout* window_layout = new QVBoxLayout(this);
    QHBoxLayout* widgets_layout = new QHBoxLayout();
    QVBoxLayout* main_layout = new QVBoxLayout();
    QHBoxLayout* buttons_layout = new QHBoxLayout();
    QScrollArea* scroll = new QScrollArea();

    menu_bar = new QMenuBar(this);

    list = new QEmployeeList();
    emp_info = new QEmployeeInfo();
    payroll_info = new QPayrollInfo();

    // creo i bottoni del widget
    add = new QPushButton(tr("Aggiungi"), this);
    del = new QPushButton(tr("Rimuovi"), this);
    promote = new QPushButton(tr("Promuovi dipendente"), this);
    calc_full_sal = new QPushButton(tr("Calcola stipendi del mese"), this);
    order = new QComboBox(this);


    connect(add, SIGNAL(clicked()), this, SLOT(showAddDialog()));
    connect(del, SIGNAL(clicked()), this, SLOT(showDelDialog()));
    connect(promote, SIGNAL(clicked()), this, SLOT(showPromoDialog()));
    connect(list, SIGNAL(emitInfoRequest(const std::string&)), controller, SLOT(updateInfEmp(const std::string&)));
    connect(list, SIGNAL(emitResVac(const std::string&)), controller, SLOT(resetVacFromEmp(const std::string&)));
    connect(calc_full_sal, SIGNAL(clicked()), this, SLOT(showCalcFullSalDialog()));

    // assemblo la menu bar
    QMenu* edit_menu = new QMenu("File", menu_bar);
    QAction* new_pr = new QAction("Nuovo", edit_menu);
    QAction* save = new QAction("Salva", edit_menu);
    QAction* load = new QAction("Carica", edit_menu);
    QAction* exit = new QAction("Esci", edit_menu);

    QMenu* about = new QMenu("Altro", menu_bar);
    QAction* dev_info = new QAction("About", about);

    edit_menu->addAction(new_pr);
    edit_menu->addAction(save);
    edit_menu->addAction(load);
    edit_menu->addAction(exit);
    about->addAction(dev_info);
    menu_bar->addMenu(edit_menu);
    menu_bar->addMenu(about);

    connect(save, SIGNAL(triggered()), this, SLOT(showWriteFileDialog()));
    connect(load, SIGNAL(triggered()), this, SLOT(showFileDialog()));
    connect(new_pr, SIGNAL(triggered()), controller, SLOT(reset()));
    connect(exit, SIGNAL(triggered()), this, SLOT(close()));
    connect(dev_info, SIGNAL(triggered()), this, SLOT(showAbout()));

    // assemblo la scroll area
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy(2));
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy(1));
    scroll->setWidgetResizable(true);
    scroll->setWidget(list);

    // inserisco le opzioni per il combo box
    order->addItem("N/A");
    order->addItem("Ordina per ruolo");
    order->addItem("Ordina per stipendio bonus massimo");
    order->addItem("Ordina per stipendio bonus minimo");
    order->addItem("Ordina per stipendio totale massimo");
    order->addItem("Ordina per stipendio totale minimo");
    order->addItem("Ordina per ore di lavoro massime");
    order->addItem("Ordina per ore di lavoro minime");
    order->addItem("Ordina per anzianità massima");
    order->addItem("Ordina per anzianità minima");
    order->addItem("Ordina per vacanze accumulate massime");
    order->addItem("Ordina per vacanze accumulate minime");

    // connect per il corretto ordinamento funzionamento del QComboBox
    connect(order, SIGNAL(activated(const QString&)), controller, SLOT(orderBy(const QString&)));

    // assemblo i bottoni nel loro layout e definiscio le posizioni
    buttons_layout->addSpacing(25);
    buttons_layout->addWidget(add);
    buttons_layout->addWidget(del);
    buttons_layout->addWidget(promote);
    buttons_layout->addWidget(order);
    buttons_layout->addWidget(calc_full_sal);
    buttons_layout->addSpacing(25);

    // creo il layout verticale per i due widget "statici"
    QVBoxLayout* stats_layout = new QVBoxLayout(this);
    stats_layout->setAlignment(Qt::AlignLeft);
    stats_layout->addWidget(emp_info);
    stats_layout->addSpacing(50);
    stats_layout->addWidget(payroll_info);

    // assemblo i layout in modo che siano ordinati correttamente
    main_layout->addWidget(menu_bar);
    main_layout->addSpacing(25);

    widgets_layout->addSpacing(25);
    widgets_layout->addWidget(scroll);
    widgets_layout->addSpacing(50);
    widgets_layout->addLayout(stats_layout);
    widgets_layout->addSpacing(25);

    main_layout->addLayout(widgets_layout);
    main_layout->addSpacing(25);
    main_layout->addLayout(buttons_layout);
    main_layout->addSpacing(25);

    buttons_layout->setAlignment(Qt::AlignLeft);
    window_layout->addLayout(main_layout);

    this->setFixedSize(1000, 800);
    connect(controller, SIGNAL(showError(std::string)), this, SLOT(showErrorDialog(std::string)));
}

void QSalaries::showAddDialog() {
    QDialog* dialog = new QDialog(this);
    QVBoxLayout* l = new QVBoxLayout(dialog);
    QAddDialog* addDialog = new QAddDialog(dialog);

    connect(addDialog, SIGNAL(emitAdd(const std::string&, const std::string&, const std::string&, const std::string&)),
            controller, SLOT(addEmp(const std::string&, const std::string&, const std::string&, const std::string&)));

    l->addWidget(addDialog);
    dialog->setLayout(l);
    dialog->setFixedSize(dialog->sizeHint());

    dialog->setModal(true);
    dialog->show();
}

void QSalaries::showDelDialog() {
    QDialog* dialog = new QDialog(this);
    QVBoxLayout* l = new QVBoxLayout(dialog);
    QDelDialog* delDialog = new QDelDialog(dialog);

    connect(delDialog, SIGNAL(emitDel(const std::string&)),
            controller, SLOT(delEmp(const std::string&)));

    l->addWidget(delDialog);
    dialog->setLayout(l);
    dialog->setFixedSize(dialog->sizeHint());
    dialog->setModal(true);
    dialog->show();
}

void QSalaries::showPromoDialog() {
    QDialog* dialog = new QDialog(this);
    QVBoxLayout* l = new QVBoxLayout(dialog);
    QPromoDialog* promoDialog = new QPromoDialog(dialog);


    connect(promoDialog, SIGNAL(emitPromo(const std::string&)),
            controller, SLOT(promoEmp(const std::string&)));

    //dialog->setFixedSize(QSize(350, 90));

    l->addWidget(promoDialog);
    dialog->setLayout(l);
    dialog->setFixedSize(dialog->sizeHint());
    dialog->setModal(true);
    dialog->show();
}

void QSalaries::showCalcFullSalDialog() {
    Container<worker*> curr_workers = controller->getCurrCont();

    if(curr_workers.getSize() != 0){

    QDialog* dialog = new QDialog(this);
    QScrollArea* scroll_calc = new QScrollArea(dialog);

    QEmployeeListForCalc* calcFullSalDialog = new QEmployeeListForCalc(dialog, curr_workers);

    scroll_calc->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy(2));
    scroll_calc->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy(1));
    scroll_calc->setWidgetResizable(true);
    scroll_calc->setWidget(calcFullSalDialog);
    scroll_calc->resize(430, 480);

    connect(calcFullSalDialog, SIGNAL(emitCalcFullSal(std::vector<std::pair<int, int>>)), controller, SLOT(calcFullSal(std::vector<std::pair<int, int>>)));
    connect(calcFullSalDialog, SIGNAL(emitCalcFullSal(std::vector<std::pair<int, int>>)), dialog, SLOT(close()));
    dialog->setModal(true);
    dialog->show();
    }
}

void QSalaries::showAbout() {
    QMessageBox box(QMessageBox::Information, "Info",
                    QString("Università degli studi di Padova<br>"
                            "Facoltà di Informatica<br>"
                            "A.A. 2019/2020<br><br>"
                            "Progetto svolto per il corso di <b>Programmazione ad Oggetti</b><br>"
                            "da <u>Barbieri Veronica</u> e <u>Bulbarelli Giacomo</u>"), QMessageBox::Ok, this);
    box.exec();
}

void QSalaries::updateList() {
    clearList();
    fillList();
}

void QSalaries::updateInfoField(const std::string& nn, const std::string& ssn, const std::string& ccf,
                                const std::string& ccon, const std::string& wwd, const std::string& wwh,
                                const std::string& bbs, const std::string& bbbs, const std::string& ss,
                                const std::string& vac, const std::string& ssen) {
    emp_info->updateInfo(nn, ssn, ccf, ccon, wwd, wwh, bbs, bbbs, ss, vac, ssen);
}

void QSalaries::updatePayrollInfo(const std::string & s, const std::string & bs, const std::string & wh,
                                  const std::string & hs, const std::string & hwh, const std::string & sen,
                                  const std::string & dds, const std::string & ddh) {
    payroll_info->updateInfo(s, bs, wh, hs, hwh, sen, dds, ddh);
}

void QSalaries::clearView() {
    this->clearList();
    this->updateInfoField();
    this->updatePayrollInfo();
}

std::string QSalaries::currentDisplayedWorker() {
    return this->emp_info->getCurrentDisplayedWorker();
}

void QSalaries::addEmpToList(const std::string& n, const std::string& sn, const std::string& cf, const std::string& con) {
    this->list->addEmp(n, sn, cf, con);
}

void QSalaries::addController(QtSalariesController* c) {
    this->controller = c;
}

void QSalaries::clearList() {
    this->list->clearList();
}

void QSalaries::fillList() {
    for(int i=0; i < controller->getNumberOfEmp(); i++) {
        worker* curr_emp = controller->getEmpAtIndex(i);
        std::string contr;
        if(dynamic_cast<ftemployee*>(curr_emp)){
            contr = "Full-Time";
        }
        if(dynamic_cast<ptemployee*>(curr_emp)){
            contr = "Part-Time";
        }
        if(dynamic_cast<director*>(curr_emp)){
            contr = "Direttore";
        }
        addEmpToList(curr_emp->getName(), curr_emp->getSname(), curr_emp->getCodFiscale(), contr);
    }
}

void QSalaries::showErrorDialog(const std::string& err) {
    QMessageBox* err_dialog = new QMessageBox(this);
    err_dialog->setText(QString::fromStdString(err));

    err_dialog->setFixedSize(QSize(230, 150));
    err_dialog->setModal(true);
    err_dialog->show();
}

void QSalaries::showFileDialog() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "/home", tr("Json Files (*.json)"));
    if (!fileName.isEmpty()) buildPayrollFromFile(fileName);
}

void QSalaries::buildPayrollFromFile(QString fileName){

    QFile file(fileName); //open file
    if(!file.open(QIODevice::ReadOnly)){
        showErrorDialog("Failed to write to file");
        exit(1);
    }

    //read all from file and close
    QTextStream file_text(&file);
    QString json_string;
    json_string = file_text.readAll();
    file.close();
    QByteArray json_bytes = json_string.toLocal8Bit();
     QJsonDocument list;
    try {
        list = QJsonDocument::fromJson(json_bytes);
        if(list.isEmpty()){
            throw std::logic_error("Formato json errato, correggere e riprovare");
        }
    } catch (std::logic_error e) {
        showErrorDialog(e.what());
    }
    QJsonObject root = list.object();
    controller->getPayrollFromFile(root);
}

//slot apre dialogo per salvataggio
void QSalaries::showWriteFileDialog() {
    QJsonDocument towrite = writeToFile();

    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save payroll"),  "/home/payroll.json", tr("Json Files (*.json)"));
    if(fileName != ""){
        //throw std::logic_error("Nessun nome di file specificato! Operazione annullata");
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        showErrorDialog("Failed to write to file");
        exit(1);
    }

    file.write(towrite.toJson());
    file.close();
    }
}

QJsonDocument QSalaries::writeToFile() {
    QJsonObject towrite = controller->writePayrollToFile();
    QJsonDocument saveFile(towrite);
    return saveFile;
}
