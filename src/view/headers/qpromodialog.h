#ifndef QPROMODIALOG_H
#define QPROMODIALOG_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

class QPromoDialog : public QWidget
{
    Q_OBJECT
private:
    std::string cf;
    QLineEdit* insert_cf;

public:
    explicit QPromoDialog(QWidget *parent = nullptr);

signals:
    void emitPromo(const std::string&);

public slots:
    void slotPromo();

};

#endif // QPROMODIALOG_H
