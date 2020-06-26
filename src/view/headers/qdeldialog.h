#ifndef QDELDIALOG_H
#define QDELDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

class QDelDialog : public QWidget {
    Q_OBJECT
private:
    std::string cf;
    QLineEdit* insert_cf;

public:
    explicit QDelDialog(QWidget *parent = nullptr);

signals:
    void emitDel(const std::string&);

public slots:
    void slotDel();
};

#endif // QDELDIALOG_H
