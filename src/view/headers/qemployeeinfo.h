#ifndef QEMPLOYEEINFO_H
#define QEMPLOYEEINFO_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

class QEmployeeInfo : public QWidget {
    Q_OBJECT
private:
    QGridLayout* emp_info_layout;
    static QString name_placeholder;
    static QString sname_placeholder;
    static QString cf_placeholder;
    static QString contract_placeholder;
    static QString wdays_placeholder;
    static QString whours_placeholder;
    static QString base_salary_placeholder;
    static QString bonus_salary_placeholder;
    static QString salary_placeholder;
    static QString vac_placeholder;
    static QString seniority_placeholder;
    QLabel* name;
    QLabel* sname;
    QLabel* cf;
    QLabel* contract;
    QLabel* wdays;
    QLabel* whours;
    QLabel* base_salary;
    QLabel* bonus_salary;
    QLabel* salary;
    QLabel* vac;
    QLabel* seniority;

public:
    explicit QEmployeeInfo(QWidget *parent = nullptr);
    void updateInfo(const std::string& = "N/A", const std::string& = "N/A", const std::string& = "N/A",
                    const std::string& = "N/A", const std::string& = "N/A", const std::string& = "N/A",
                    const std::string& = "N/A", const std::string& = "N/A", const std::string& = "N/A",
                    const std::string& = "N/A", const std::string& = "N/A");
    std::string getCurrentDisplayedWorker();
};

#endif // QEMPLOYEEINFO_H
