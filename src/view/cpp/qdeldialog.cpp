#include "../headers/qdeldialog.h"

QDelDialog::QDelDialog(QWidget *parent) : QWidget(parent) {
    cf = "";

    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel(tr("Inserire il codice fiscale del dipendente da rimuovere"), this);
    insert_cf = new QLineEdit(this);
    QPushButton* confirm = new QPushButton(tr("Conferma"));

    connect(confirm, SIGNAL(clicked()), this, SLOT(slotDel()));

    layout->addWidget(label);
    layout->addWidget(insert_cf);
    layout->addWidget(confirm);
}

void QDelDialog::slotDel() {
    std::string ccf = insert_cf->text().toStdString();

    insert_cf->clear();
    emit emitDel(ccf);
}


