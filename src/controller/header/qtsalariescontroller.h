#ifndef QTSALARIESCONTROLLER_H
#define QTSALARIESCONTROLLER_H

#include <QObject>
#include <QFile>
#include "../../paycheck/paycheck.h"
#include "../../view/headers/qsalaries.h"


class QtSalariesController : public QObject {
    Q_OBJECT
private:
    paycheck* model;
    QSalaries* view;

public:
    explicit QtSalariesController(paycheck*, QSalaries*, QObject *parent = nullptr);
    explicit QtSalariesController(paycheck*, QObject *parent = nullptr);
    worker* getEmpAtIndex(int) const;
    int getNumberOfEmp() const;
    void addView(QSalaries*);
    void updateModel(paycheck*);
    int modelSize() const;
    Container<worker*> getCurrCont();
    worker* operator[](const int&) const;

    void getPayrollFromFile(QJsonObject root);
    QJsonObject writePayrollToFile();

signals:
    void showError(const std::string&);

public slots:
    void addEmp(const std::string&, const std::string&, const std::string&, const std::string&);
    void delEmp(const std::string&);
    void promoEmp(const std::string&);
    void updateInfEmp(const std::string&);
    void resetVacFromEmp(const std::string&);
    void orderBy(const QString&);
    void calcFullSal(std::vector<std::pair<int, int>>);
    void reset();
};

#endif // QTSALARIESCONTROLLER_H
