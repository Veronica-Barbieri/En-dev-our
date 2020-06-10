#ifndef QEMPLOYEEFORCALC_H
#define QEMPLOYEEFORCALC_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>


class QEmployeeForCalc : public QWidget {
    Q_OBJECT
private:
    QLineEdit* wd;
    QLineEdit* wh;

public:
    explicit QEmployeeForCalc(QWidget *parent = nullptr, const std::string& n = "", const std::string& sn = "", const std::string& cf = "");
    int getWDaysContent();
    int getWHoursContent();

signals:

public slots:
};

#endif // QEMPLOYEEFORCALC_H
