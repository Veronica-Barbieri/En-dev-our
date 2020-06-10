#ifndef PAYCHECK_H
#define PAYCHECK_H

#include "../model/headers/director.h"
#include "../model/headers/ftemployee.h"
#include "../model/headers/ptemployee.h"
#include "../model/headers/container.h"
#include <iostream>
#include <vector>
#include <utility>

class paycheck {
private:
    Container<worker*> pc;
    double tot_salaries;
    double tot_bonus_salaries;
    double highest_sal;
    int tot_worked_hours;
    int highest_worked_hours;
    double highest_seniority;

    std::string findDirCodFisc() const; // Dir == director    cout << n << " " << sn << " " << ccf << " " << con << endl;

    bool isPresent(const std::string&) const;
    bool isPresent(worker*) const;
    bool hasDirector() const;

public:
    paycheck();
    ~paycheck();

    int getSize() const;
    worker* getWorkerFromIndex(int) const;
    worker* retrieveWorkerFromCf(const std::string&) const;
    worker* getWorkerAtPos(const int&) const;
    Container<worker*> getWorkers() const;
    void resetPaycheck();

    void addEmp(const std::string&, const std::string&, const std::string&, const std::string&);
    void addEmp(worker*);

    void remEmp(const std::string&, const std::string&, const std::string&, const std::string&);
    void remEmp(worker*);

    void calcAllFullSal();
    void calcAllFullSal(std::vector<std::pair<int, int>>);

    void promotePtEmp(const std::string&);
    void promotePtEmp(worker*);

    void updateTotSalaries(const double&);
    void updateTotBonusSalaries(const double&);
    void updateTotWorkedHours(const int&);

    double getTotSal() const;
    double getTotBuonusSal() const;
    double getHighestSal() const;
    int getTotWorkedHours() const;
    int getHighestWorkedHours() const;
    int getHighestSeniority() const;

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
