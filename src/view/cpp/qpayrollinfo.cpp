#include "../headers/qpayrollinfo.h"

QString QPayrollInfo::sal_placeholder = "Totale salari (€): ";
QString QPayrollInfo::bonus_sal_placeholder = "Totale salari bonus (€): ";
QString QPayrollInfo::w_hours_placeholder = "Totale ore lavorate: ";
QString QPayrollInfo::highest_sal_placeholder = "Stipendio più alto (€): ";
QString QPayrollInfo::highest_w_hours_placeholder = "Maggior numero di ore lavorate: ";
QString QPayrollInfo::sen_placeholder = "Anzianità più alta (mesi): ";
QString QPayrollInfo::diff_hours_placeholder = "Δ ore lavorate rispetto al mese precedente:  ";
QString QPayrollInfo::diff_sal_placeholder = "Δ salari rispetto al mese precedente: ";


QPayrollInfo::QPayrollInfo(QWidget *parent) : QWidget(parent) {
    p_info_layout = new QGridLayout(this);
    p_info_layout->setAlignment(Qt::AlignTop);

    QLabel* sal_tag = new QLabel(this);
    QLabel* bonus_sal_tag = new QLabel(this);
    QLabel* w_hours_tag = new QLabel(this);
    QLabel* highest_sal_tag = new QLabel(this);
    QLabel* highest_w_hours_tag = new QLabel(this);
    QLabel* sen_tag = new QLabel(this);
    QLabel* diff_h_tag = new QLabel(this);
    QLabel* diff_sal_tag = new QLabel(this);

    sal = new QLabel(this);
    bonus_sal = new QLabel(this);
    w_hours = new QLabel(this);
    highest_sal = new QLabel(this);
    highest_w_hours = new QLabel(this);
    sen = new QLabel(this);
    diff_sal = new QLabel(this);
    diff_hours = new QLabel(this);

    sal_tag->setText(sal_placeholder);
    bonus_sal_tag->setText(bonus_sal_placeholder);
    w_hours_tag->setText(w_hours_placeholder);
    highest_sal_tag->setText(highest_sal_placeholder);
    highest_w_hours_tag->setText(highest_w_hours_placeholder);
    sen_tag->setText(sen_placeholder);
    diff_h_tag->setText(diff_hours_placeholder);
    diff_sal_tag->setText(diff_sal_placeholder);

    sal_tag->setFont(QFont("Helvetica", 10, QFont::Bold));
    bonus_sal_tag->setFont(QFont("Helvetica", 10, QFont::Bold));
    w_hours_tag->setFont(QFont("Helvetica", 10, QFont::Bold));
    highest_sal_tag->setFont(QFont("Helvetica", 10, QFont::Bold));
    highest_w_hours_tag->setFont(QFont("Helvetica", 10, QFont::Bold));
    sen_tag->setFont(QFont("Helvetica", 10, QFont::Bold));
    diff_h_tag->setFont(QFont("Helvetica", 10, QFont::Bold));
    diff_sal_tag->setFont(QFont("Helvetica", 10, QFont::Bold));

    this->updateInfo();

    p_info_layout->addWidget(sal_tag, 0, 0);
    p_info_layout->addWidget(bonus_sal_tag, 1, 0);
    p_info_layout->addWidget(w_hours_tag, 2, 0);
    p_info_layout->addWidget(highest_sal_tag, 3, 0);
    p_info_layout->addWidget(highest_w_hours_tag, 4, 0);
    p_info_layout->addWidget(sen_tag, 5, 0);
    p_info_layout->addWidget(diff_sal_tag, 6, 0);
    p_info_layout->addWidget(diff_h_tag, 7, 0);

    p_info_layout->addWidget(sal, 0, 1);
    p_info_layout->addWidget(bonus_sal, 1, 1);
    p_info_layout->addWidget(w_hours, 2, 1);
    p_info_layout->addWidget(highest_sal, 3, 1);
    p_info_layout->addWidget(highest_w_hours, 4, 1);
    p_info_layout->addWidget(sen, 5, 1);
    p_info_layout->addWidget(diff_sal, 6, 1);
    p_info_layout->addWidget(diff_hours, 7, 1);

}

void QPayrollInfo::updateInfo(const std::string & s, const std::string & bs, const std::string & wh,
                              const std::string & hs, const std::string & hwh, const std::string & sen,
                              const std::string & ddf, const std::string & ddh) {
    this->sal->setText(QString::fromStdString(s));
    this->bonus_sal->setText(QString::fromStdString(bs));
    this->w_hours->setText(QString::fromStdString(wh));
    this->highest_sal->setText(QString::fromStdString(hs));
    this->highest_w_hours->setText(QString::fromStdString(hwh));
    this->sen->setText(QString::fromStdString(sen));
    if(ddf == "N/A" && ddh == "N/A"){
        this->diff_sal->setText(QString::fromStdString(ddf));
        this->diff_hours->setText(QString::fromStdString(ddh));
        this->diff_sal->setStyleSheet("QLabel {color:black;}");
        this->diff_hours->setStyleSheet("QLabel {color:black;}");
    } else {
        this->diff_sal->setText(QString::fromStdString(ddf));
        this->diff_hours->setText(QString::fromStdString(ddh));

        double s = stod(ddf);
        double h = stod(ddh);

        if(s>0)
            this->diff_sal->setStyleSheet("QLabel {color:green;}");
        else if(s<0)
            this->diff_sal->setStyleSheet("QLabel {color:red;}");
        else
            this->diff_sal->setStyleSheet("QLabel {color:black;}");
        if(h>0)
            this->diff_hours->setStyleSheet("QLabel {color:green;}");
        else if(h<0)
            this->diff_hours->setStyleSheet("QLabel {color:red;}");
        else
            this->diff_hours->setStyleSheet("QLabel {color:black;}");
    }
}
