#ifndef QPAYROLLINFO_H
#define QPAYROLLINFO_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

class QPayrollInfo : public QWidget {
    Q_OBJECT

private:
    QGridLayout* p_info_layout;
    static QString sal_placeholder;
    static QString bonus_sal_placeholder;
    static QString w_hours_placeholder;
    static QString highest_sal_placeholder;
    static QString highest_w_hours_placeholder;
    static QString sen_placeholder;
    static QString diff_hours_placeholder;
    static QString diff_sal_placeholder;
    QLabel* sal;
    QLabel* bonus_sal;
    QLabel* highest_sal;
    QLabel* w_hours;
    QLabel* highest_w_hours;
    QLabel* sen;
    QLabel* diff_sal;
    QLabel* diff_hours;

public:
    explicit QPayrollInfo(QWidget *parent = nullptr);
    void updateInfo(const std::string&, const std::string&, const std::string&,
                    const std::string&, const std::string&, const std::string&,
                    const std::string&, const std::string&);
signals:

public slots:
};

#endif // QPAYROLLINFO_H
