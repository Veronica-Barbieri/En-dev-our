#ifndef QADDDIALOG_H
#define QADDDIALOG_H

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <iostream>
using std::cout;
using std::endl;

class QAddDialog : public QWidget
{
    Q_OBJECT
private:
    std::string name;
    std::string sname;
    std::string cf;
    std::string contr;
    QLineEdit* insert_name;
    QLineEdit* insert_sname;
    QLineEdit* insert_cf;
    QComboBox* insert_cont;


public:
    explicit QAddDialog(QWidget *parent = nullptr);

signals:
    void emitAdd(const std::string&, const std::string&, const std::string&, const std::string&);

public slots:
    void slotAdd();

};

#endif // QADDDIALOG_H
