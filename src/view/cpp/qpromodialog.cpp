#include "../headers/qpromodialog.h"

QPromoDialog::QPromoDialog(QWidget *parent) : QWidget(parent) {
    cf = "";

    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel(tr("Inserire il codice fiscale del dipendente da promuovere"), this);
    insert_cf = new QLineEdit(this);
    QPushButton* confirm = new QPushButton(tr("Conferma"));

    connect(confirm, SIGNAL(clicked()), this, SLOT(slotPromo()));

    layout->addWidget(label);
    layout->addWidget(insert_cf);
    layout->addWidget(confirm);
}

void QPromoDialog::slotPromo() {
    std::string ccf = insert_cf->text().toStdString();

    insert_cf->clear();
    emit emitPromo(ccf);
}
