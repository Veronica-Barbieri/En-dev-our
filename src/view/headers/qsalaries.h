#ifndef QSALARIES_H
#define QSALARIES_H

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QComboBox>
#include <QMenuBar>
#include <QMenu>
#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include "qemployeelist.h"
#include "qemployeeinfo.h"
#include "qpayrollinfo.h"
#include "qadddialog.h"
#include "qdeldialog.h"
#include "qpromodialog.h"
#include "qemployeelistforcalc.h"

class QtSalariesController;

class QSalaries : public QWidget {
    Q_OBJECT
private:
    QMenuBar* menu_bar;
    QPushButton* add;
    QPushButton* del;
    QPushButton* promote;
    QPushButton* calc_full_sal;
    QComboBox* order;
    QEmployeeList* list;
    QEmployeeInfo* emp_info; // posso resettarlo
    QPayrollInfo* payroll_info; // posso resettarlo
    QtSalariesController* controller;
    void clearList();
    void fillList();

public:
    explicit QSalaries(QWidget *parent = nullptr, QtSalariesController* c = nullptr);


    void updateList();

    void addEmpToList(const std::string&, const std::string&, const std::string&, const std::string&);
    void addController(QtSalariesController* c);
    void updateInfoField(const std::string&, const std::string&, const std::string&,
                         const std::string&, const std::string&, const std::string&,
                         const std::string&, const std::string&, const std::string&,
                         const std::string&, const std::string&);
    void updatePayrollInfo(const std::string&, const std::string&, const std::string&,
                           const std::string&, const std::string&, const std::string&);
    void clearView();


signals:
    void applyAdd(const std::string&, const std::string&, const std::string&, const std::string&);
    void applyDel(const std::string&);
    void applyPromo(const std::string&);
    void applyCalcFullSal(/*???*/); // Quali parametri devo inserire?

public slots:
    void showAddDialog();
    void showDelDialog();
    void showPromoDialog();
    void showCalcFullSalDialog();
};

#endif // QSALARIES_H
