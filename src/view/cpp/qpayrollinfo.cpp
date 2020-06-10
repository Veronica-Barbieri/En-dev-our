#include "../headers/qpayrollinfo.h"

QString QPayrollInfo::sal_placeholder = "Totale salari: ";
QString QPayrollInfo::bonus_sal_placeholder = "Totale salari bonus: ";
QString QPayrollInfo::w_hours_placeholder = "Totale ore lavorate: ";
QString QPayrollInfo::highest_sal_placeholder = "Stipendio più alto: ";
QString QPayrollInfo::highest_w_hours_placeholder = "Maggior numero di ore lavorate: ";
QString QPayrollInfo::sen_placeholder = "Anznianità più alta: ";


QPayrollInfo::QPayrollInfo(QWidget *parent) : QWidget(parent) {
    p_info_layout = new QGridLayout(this);
    p_info_layout->setAlignment(Qt::AlignCenter);

    QLabel* sal_tag = new QLabel(this);
    QLabel* bonus_sal_tag = new QLabel(this);
    QLabel* w_hours_tag = new QLabel(this);
    QLabel* highest_sal_tag = new QLabel(this);
    QLabel* highest_w_hours_tag = new QLabel(this);
    QLabel* sen_tag = new QLabel(this);

    sal = new QLabel(this);
    bonus_sal = new QLabel(this);
    w_hours = new QLabel(this);
    highest_sal = new QLabel(this);
    highest_w_hours = new QLabel(this);
    sen = new QLabel(this);

    sal_tag->setText(sal_placeholder);
    bonus_sal_tag->setText(bonus_sal_placeholder);
    w_hours_tag->setText(w_hours_placeholder);
    highest_sal_tag->setText(highest_sal_placeholder);
    highest_w_hours_tag->setText(highest_w_hours_placeholder);
    sen_tag->setText(sen_placeholder);

    sal_tag->setFont(QFont("Helvetica", 10, QFont::Bold));
    bonus_sal_tag->setFont(QFont("Helvetica", 10, QFont::Bold));
    w_hours_tag->setFont(QFont("Helvetica", 10, QFont::Bold));
    highest_sal_tag->setFont(QFont("Helvetica", 10, QFont::Bold));
    highest_w_hours_tag->setFont(QFont("Helvetica", 10, QFont::Bold));
    sen_tag->setFont(QFont("Helvetica", 10, QFont::Bold));

    this->updateInfo("N/A", "N/A", "N/A", "N/A", "N/A", "N/A");

    p_info_layout->addWidget(sal_tag, 0, 0);
    p_info_layout->addWidget(bonus_sal_tag, 1, 0);
    p_info_layout->addWidget(w_hours_tag, 2, 0);
    p_info_layout->addWidget(highest_sal_tag, 3, 0);
    p_info_layout->addWidget(highest_w_hours_tag, 4, 0);
    p_info_layout->addWidget(sen_tag, 5, 0);

    p_info_layout->addWidget(sal, 0, 1);
    p_info_layout->addWidget(bonus_sal, 1, 1);
    p_info_layout->addWidget(w_hours, 2, 1);
    p_info_layout->addWidget(highest_sal, 3, 1);
    p_info_layout->addWidget(highest_w_hours, 4, 1);
    p_info_layout->addWidget(sen, 5, 1);


}

void QPayrollInfo::updateInfo(const std::string & s, const std::string & bs, const std::string & wh,
                              const std::string & hs, const std::string & hwh, const std::string & sen) {
    this->sal->setText(QString::fromStdString(s));
    this->bonus_sal->setText(QString::fromStdString(bs));
    this->w_hours->setText(QString::fromStdString(wh));
    this->highest_sal->setText(QString::fromStdString(hs));
    this->highest_w_hours->setText(QString::fromStdString(hwh));
    this->sen->setText(QString::fromStdString(sen));
}
