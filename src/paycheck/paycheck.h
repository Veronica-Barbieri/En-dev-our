#ifndef PAYCHECK_H
#define PAYCHECK_H

#include "../model/headers/director.h"
#include "../model/headers/ftemployee.h"
#include "../model/headers/ptemployee.h"
#include "../model/headers/container.h"
#include <iostream>

class paycheck
{
private:
    Container<worker*> pc;
    double tot_salaries;
    double tot_bonus_salaries;
    int tot_worked_hours;
    double highest_sal;
    int highest_worked_hours;
    double highest_seniority;

    worker* retrieveWorkerFromCf(const std::string&) const;
    std::string findDirCodFisc() const; // Dir == director

    bool isPresent(const std::string&) const;
    bool isPresent(worker*) const;
    bool hasDirector() const;

public:
    paycheck();
    ~paycheck();

    void addEmp(const std::string&, const std::string&, const std::string&, const std::string&);
    void addEmp(worker*);

    void remEmp(const std::string&, const std::string&, const std::string&, const std::string&);
    void remEmp(worker*);

    void calcAllFullSal();




    void promotePtEmp(const std::string&);
    void promotePtEmp(worker*);

    void updateTotSalaries(const double&);
    void updateTotBonusSalaries(const double&);
    void updateTotWorkedHours(const int&);

    double getHighestSal() const;
    int getHighestSeniority() const;
    int getHighestWorkedHours() const;

    void updateHighestSal();
    void updateHighestWorkedHours();
    void updateHighestSeniority();

    void resetPaycheckData();

    void orderByFullSalMax();
    void orderByBonusSalMax();

    void orderByWorkedHoursMax();
    void orderBySeniorityMax();

    void orderByFullSalMin();
    void orderByBonusSalMin();

    void orderByWorkedHoursMin();
    void orderBySeniorityMin();

    void orderByVacDayMax();
    void orderByVacDayMin();

    void orderByRole();

    void dispAll() const;
    void dispInternalData() const;
};

#endif // PAYCHECK_H
