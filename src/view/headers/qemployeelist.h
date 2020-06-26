#ifndef QEMPLOYEELIST_H
#define QEMPLOYEELIST_H

#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <vector>
#include "qemployee.h"


#include "../../model/headers/container.h"

class QEmployeeList : public QWidget {
    Q_OBJECT
private:
    QHBoxLayout* button_layout;
    QVBoxLayout* list_layout;
    std::vector<QEmployee*> qemp_cont;

public:
    explicit QEmployeeList(QWidget *parent = nullptr);

signals:
    void emitInfoRequest(const std::string&);
    void emitResVac(const std::string&);

public slots:
    void addEmp(const std::string&, const std::string&, const std::string&, const std::string&);
    void receiveInfoReq(const std::string&);
    void receiveResVac(const std::string&);
    void delEmp();
    void clearList();

};

#endif // QEMPLOYEELIST_H
