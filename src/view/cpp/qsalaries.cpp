#include "../headers/qsalaries.h"
#include "../../controller/header/qtsalariescontroller.h"

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
    connect(calc_full_sal, SIGNAL(clicked()), this, SLOT(showCalcFullSalDialog()));


    // assemblo la menu bar
    QMenu* edit_menu = new QMenu("File", menu_bar);
    QAction* new_pr = new QAction("Nuovo", edit_menu);
    QAction* save = new QAction("Salva", edit_menu);
    QAction* load = new QAction("Carica", edit_menu);
    QAction* exit = new QAction("Esci", edit_menu);

    QMenu* about = new QMenu("Others", menu_bar);
    QAction* dev_info = new QAction("About", about);



    edit_menu->addAction(new_pr);
    edit_menu->addAction(save);
    edit_menu->addAction(load);
    edit_menu->addAction(exit);
    about->addAction(dev_info);
    menu_bar->addMenu(edit_menu);
    menu_bar->addMenu(about);

    connect(new_pr, SIGNAL(triggered()), controller, SLOT(reset()));
    connect(exit, SIGNAL(triggered()), this, SLOT(close()));

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
    buttons_layout->addWidget(add);
    buttons_layout->addWidget(del);
    buttons_layout->addWidget(promote);
    buttons_layout->addWidget(order);
    buttons_layout->addWidget(calc_full_sal);

    // creo il layout verticale per i due widget "statici"
    QVBoxLayout* stats_layout = new QVBoxLayout(this);
    stats_layout->addWidget(emp_info);
    stats_layout->addWidget(payroll_info);

    // assemblo i layout in modo che siano ordinati correttamente
    main_layout->addWidget(menu_bar);
    widgets_layout->addWidget(scroll);
    widgets_layout->addLayout(stats_layout);
    main_layout->addLayout(widgets_layout);
    main_layout->addLayout(buttons_layout);
    buttons_layout->setAlignment(Qt::AlignLeft);
    window_layout->addLayout(main_layout);
}

void QSalaries::showAddDialog() {
    QDialog* dialog = new QDialog(this);
    QAddDialog* addDialog = new QAddDialog(dialog);

    connect(addDialog, SIGNAL(emitAdd(const std::string&, const std::string&, const std::string&, const std::string&)),
            controller, SLOT(addEmp(const std::string&, const std::string&, const std::string&, const std::string&)));

    dialog->setFixedSize(QSize(230, 150));
    dialog->setModal(true);
    dialog->show();
}

void QSalaries::showDelDialog() {
    QDialog* dialog = new QDialog(this);
    QDelDialog* delDialog = new QDelDialog(dialog);

    connect(delDialog, SIGNAL(emitDel(const std::string&)),
            controller, SLOT(delEmp(const std::string&)));

    dialog->setFixedSize(QSize(340, 90));
    dialog->setModal(true);
    dialog->show();
}

void QSalaries::showPromoDialog() {
    QDialog* dialog = new QDialog(this);
    QPromoDialog* delDialog = new QPromoDialog(dialog);


    connect(delDialog, SIGNAL(emitPromo(const std::string&)),
            controller, SLOT(promoEmp(const std::string&)));

    dialog->setFixedSize(QSize(350, 90));
    dialog->setModal(true);
    dialog->show();
}

void QSalaries::showCalcFullSalDialog() {
    QDialog* dialog = new QDialog(this);
    QScrollArea* scroll_calc = new QScrollArea(dialog);

    Container<worker*> curr_workers = controller->getCurrCont();

    QEmployeeListForCalc* calcFullSalDialog = new QEmployeeListForCalc(dialog, curr_workers);

    scroll_calc->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy(2));
    scroll_calc->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy(1));
    scroll_calc->setWidgetResizable(true);
    scroll_calc->setWidget(calcFullSalDialog);
    scroll_calc->resize(430, 480);

    connect(calcFullSalDialog, SIGNAL(emitCalcFullSal(std::vector<std::pair<int, int>>)), controller, SLOT(calcFullSal(std::vector<std::pair<int, int>>)));
    dialog->setFixedSize(QSize(430, 480));
    dialog->setModal(true);
    dialog->show();
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
                                  const std::string & hs, const std::string & hwh, const std::string & sen) {
    payroll_info->updateInfo(s, bs, wh, hs, hwh, sen);
}

void QSalaries::clearView() {
    this->clearList();
    this->updateInfoField("N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A");
    this->updatePayrollInfo("N/A", "N/A", "N/A", "N/A", "N/A", "N/A");
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
