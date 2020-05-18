#ifndef WORKER_H
#define WORKER_H
#include <string>

class worker
{
private:
    std::string name;
    std::string sname;
    std::string cod_fiscale;
    int last_month_worked_days;
    int last_month_worked_hours;
    double last_month_base_salary;
    double last_month_bonus_salary;
    double last_month_salary;
    int vac_acc;

public:
    worker(std::string, std::string, std::string);
    virtual ~worker();

    std::string getName() const;
    void setName(const std::string&);

    std::string getSname() const;
    void setSname(const std::string&);

    std::string getCodFiscale() const;
    void setCodFiscale(const std::string&);

    int getLastMonthWorkedDays() const;
    void setLastMonthWorkedDays(const int&);

    int getLastMonthWorkedHours() const;
    void setLastMonthWorkedHours(const int&);

    double getLastMonthBaseSalary() const;
    void setLastMonthBaseSalary(const double&);

    double getLastMonthBonusSalary() const;
    void setLastMonthBonusSalary(const double&);

    double getLastMonthSalary() const;
    void setLastMonthSalary(const double&);

    int getVacAcc() const;
    void setVacAcc(const int&);
    void resetVacAcc();

    void updateWorkData(const int&, const int&); // aggiorna ore e giorni lavorati in un mese

    virtual double calcBaseSal() const =0; // calcola lo stipendio base partendo dalle ore lavorate nel mese e dai giorni lavorati nel mese
    virtual double calcBonus() const =0; // calcola il bonus da applicare allo stipendio base
    virtual void updateVacAcc() =0; // aggiorna le ferie accumulate
    virtual double calcFullSal(const int&, const int&) =0; // calcola lo stipendio totale

    bool operator!=(const worker&) const;
    bool operator==(const worker&) const;
};

#endif // WORKER_H
