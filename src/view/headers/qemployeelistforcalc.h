#ifndef QEMPLOYEELISTFORCALC_H
#define QEMPLOYEELISTFORCALC_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <vector>
#include <utility>
#include "qemployeeforcalc.h"
#include "../../model/headers/worker.h"
#include "../../model/headers/container.h"

class QEmployeeListForCalc : public QWidget
{
    Q_OBJECT
private:
    std::vector<std::pair<int, int>> collection;
    int size;
    QVBoxLayout* list;

public:
    explicit QEmployeeListForCalc(QWidget* parent = nullptr, Container<worker*> c = Container<worker*>());
    void clearData();
    bool isFilledOut();

signals:
    void emitCalcFullSal(std::vector<std::pair<int, int>>);
    void enableConfirm(const bool&);

public slots:
    void collectData();
    void checkFilled();
};

#endif // QEMPLOYEELISTFORCALC_H
