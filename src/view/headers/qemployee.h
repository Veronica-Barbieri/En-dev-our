#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

class QEmployee : public QWidget {
    Q_OBJECT
private:
    QGridLayout* info_layout;
    static QString name_placeholder;
    static QString sname_placeholer;
    static QString cf_placeholder;
    static QString contract_placeholder;
    QLabel* name;
    QLabel* sname;
    QLabel* cf;
    QLabel* contract;

public:
    QEmployee(QWidget *parent = nullptr);
    void updateInfo(const std::string& = "N/A", const std::string& = "N/A",
                    const std::string& = "N/A", const std::string& = "N/A");

signals:
    void emitInfoChange(const std::string&);
    void emitResetVac(const std::string&);

public slots:
    void slotInfoChange();
    void slotResetVac();
};
#endif // WIDGET_H
