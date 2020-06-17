#include <QApplication>

#include <iostream>
#include <QDesktopWidget>
#include "src/model/headers/director.h"
#include "src/model/headers/ftemployee.h"
#include "src/model/headers/ptemployee.h"
#include "src/model/headers/container.h"
#include "src/paycheck/paycheck.h"
#include "src/view/headers/qemployee.h"
#include "src/view/headers/qemployeelist.h"
#include "src/view/headers/qemployeeinfo.h"
#include "src/view/headers/qpayrollinfo.h"
#include "src/view/headers/qsalaries.h"
#include "src/controller/header/qtsalariescontroller.h"
#include "src/view/headers/qemployeeforcalc.h"

using std::endl;
using std::cout;
using std::cin;

int main(int argc, char *argv[])
{
/*
    cout<<"TEST WORKER E CONTRACT:"<<endl;
    cout<<"-----------------------"<<endl<<endl;

    worker* gino = new director("Gino", "Pasticcino", "GP1");
    worker* tony = new ftemployee("Tony", "Cartony", "TC1");
    worker* carla = new ftemployee("Carla", "Tegola", "CT2");
    worker* eolo = new ftemployee("Eolo", "Peolo", "EP9");
    worker* mona = new ptemployee("Mona", "Poltrona", "GP1");
    worker* gianni = new ptemployee("Gianni", "Malanni", "GM4");

    gino->calcFullSal(24, 216); // ha alvorato 25 giorni per 9 ore ciascun giorno lavorativo
    gino->calcFullSal(24, 200);

    tony->calcFullSal(20, 200);

    mona->calcFullSal(20, 80);

    cout << "Test oggetti worker e derivati: " << endl << endl;
    cout << "1)" << endl << "Nome: " << gino->getName() << endl;
    cout << "Cognome: " << gino->getSname() << endl;
    cout << "Codice Fiscale: " << gino->getCodFiscale() << endl;
    cout << "Giorni lavorati: " << gino->getLastMonthWorkedDays() << endl;
    cout << "Ore lavorate: " << gino->getLastMonthWorkedHours() << endl;
    cout << "Stipendio base: " << gino->getLastMonthBaseSalary() << endl;
    cout << "Bonus: " << gino->getLastMonthBonusSalary() << endl;
    cout << "Stipendio totale: " << gino->getLastMonthSalary() << endl;
    cout << "Anzianita': " << gino->getSeniority() << " mesi " << endl;
    cout << "Giorni ferie accumualti: " << gino->getVacAcc() << endl << endl;

    cout << "2)" << endl << "Nome: " << tony->getName() << endl;
    cout << "Cognome: " << tony->getSname() << endl;
    cout << "Codice Fiscale: " << tony->getCodFiscale() << endl;
    cout << "Giorni lavorati: " << tony->getLastMonthWorkedDays() << endl;
    cout << "Ore lavorate: " << tony->getLastMonthWorkedHours() << endl;
    cout << "Stipendio base: " << tony->getLastMonthBaseSalary() << endl;
    cout << "Bonus: " << tony->getLastMonthBonusSalary() << endl;
    cout << "Stipendio totale: " << tony->getLastMonthSalary() << endl;
    cout << "Anzianita': " << tony->getSeniority() << " mesi "  << endl;
    cout << "Giorni ferie accumualti: " << tony->getVacAcc() << endl << endl;

    cout << "1)" << endl << "Nome: " << mona->getName() << endl;
    cout << "Cognome: " << mona->getSname() << endl;
    cout << "Codice Fiscale: " << mona->getCodFiscale() << endl;
    cout << "Giorni lavorati: " << mona->getLastMonthWorkedDays() << endl;
    cout << "Ore lavorate: " << mona->getLastMonthWorkedHours() << endl;
    cout << "Stipendio base: " << mona->getLastMonthBaseSalary() << endl;
    cout << "Bonus: " << mona->getLastMonthBonusSalary() << endl;
    cout << "Stipendio totale: " << mona->getLastMonthSalary() << endl;
    cout << "Anzianita': " << mona->getSeniority() << " mesi "  << endl;
    cout << "Giorni ferie accumualti: " << mona->getVacAcc() << endl << endl;


    cout << "Test operator == :" << endl << "1) Risultato atteso: NON PASSATO" << endl;
    if(*gino == *tony){
        cout << "Primo test ugualianza PASSATO" << endl << endl;
    } else {
        cout << "Primo test ugualianza NON PASSATO" << endl << endl;
    }

    cout << "2) Risultato atteso: PASSATO" << endl;
    if(*gino == *mona){
        cout << "Secondo test ugualianza PASSATO" << endl << endl;
    } else {
        cout << "Secondo test ugualianza NON PASSATO" << endl << endl;
    }


    cout << "Test operator != :" << endl << "1) Risultato atteso: PASSATO" << endl;
    if(*gino != *tony){
        cout << "Primo test ugualianza PASSATO" << endl << endl;
    } else {
        cout << "Primo test ugualianza NON PASSATO" << endl << endl;
    }

    cout << "2) Risultato atteso: NON PASSATO" << endl;
    if(*gino != *mona){
        cout << "Secondo test ugualianza PASSATO" << endl << endl;
    } else {
        cout << "Secondo test ugualianza NON PASSATO" << endl << endl;
    }

    cout<<"TEST CONTAINER:"<<endl;
    cout<<"------------------"<<endl<<endl;

    Container<int> cont1;
    for(int i=0; i<3; ++i){
        cont1.pushBack(i);
    }
    cout<<"Container 1 completo: "<<endl;
    cout<<"size: "<<cont1.getSize()<<endl;
    for(int i=0; i<cont1.getSize(); ++i){
        cout<<(cont1.getNodoFromIndex(i))->info<<"  ";
    }

    cout<<endl;
    cout<<endl;

    Container<int> cont2;
    for(int i=0; i<6; ++i){
        cont2.pushBack(i);
    }
    cout<<"Container 2 completo: "<<endl;
    cout<<"size: "<<cont2.getSize()<<endl;
    for(int i=0; i<cont2.getSize(); ++i){
        cout<<(cont2.getNodoFromIndex(i))->info<<"  ";
    }

    cout<<endl;
    cout<<endl;

    Container<int> cont_sum;
    cont_sum = cont1+cont2;
    cout<<"Container somma completo: "<<endl;
    cout<<"size: "<<cont_sum.getSize()<<endl;
    for(int i=0; i<cont_sum.getSize(); ++i){
        cout<<(cont_sum.getNodoFromIndex(i))->info<<"  ";
    }

    cout<<endl;
    cout<<endl;

    cout<<"Container 1 completo after somma: "<<endl;
    cout<<"size: "<<cont1.getSize()<<endl;
    for(int i=0; i<cont1.getSize(); ++i){
        cout<<(cont1.getNodoFromIndex(i))->info<<"  ";
    }

    cout<<endl;
    cout<<endl;

    cout<<"Container 2 completo after somma: "<<endl;
    cout<<"size: "<<cont2.getSize()<<endl;
    for(int i=0; i<cont2.getSize(); ++i){
        cout<<(cont2.getNodoFromIndex(i))->info<<"  ";
    }

    cout<<endl;
    cout<<endl;

    cout<<"------------------"<<endl<<endl;

    Container<int> cont_assegn;
    cont_assegn = cont2;
    cout<<"Container assegnazione completo: "<<endl;
    cout<<"size: "<<cont_assegn.getSize()<<endl;
    for(int i=0; i<cont_assegn.getSize(); ++i){
        cout<<(cont_assegn.getNodoFromIndex(i))->info<<"  ";
    }

    cout<<endl;
    cout<<endl;

    cout<<"Container 2 completo: "<<endl;
    cout<<"size: "<<cont2.getSize()<<endl;
    for(int i=0; i<cont2.getSize(); ++i){
        cout<<(cont2.getNodoFromIndex(i))->info<<"  ";
    }

    cout<<endl;
    cout<<endl;

    cout<<"cont_sum[3]:  "<<endl;
    cout<<cont_sum[3];
    cout<<endl;

    cont2.swap(2,4);
    cout<<"Container 2 con swap completo: "<<endl;
    cout<<"size: "<<cont2.getSize()<<endl;
    for(int i=0; i<cont2.getSize(); ++i){
        cout<<(cont2.getNodoFromIndex(i))->info<<"  ";
    }

    cout<<endl;
    cout<<endl;

    Container<int*> cont_punt;
    int p1 = 1;
    int p2 = 2;
    int* p1p = &p1;
    int* p2p = &p2;

    cont_punt.pushBack(p1p);
    cont_punt.pushBack(p2p);

    cont_punt.swap(0, 1);

    cout<<"Container punt con swap: "<<endl;
    cout<<"size: "<<cont_punt.getSize()<<endl;
    for(int i=0; i<cont_punt.getSize(); ++i){
        cout<< *(cont_punt.getNodoFromIndex(i))->info<<"  ";
    }

    cout<<endl;
    cout<<endl;



    cout<<"TEST PAYCHECK:"<<endl;
    cout<<"-----------------------"<<endl<<endl;

    paycheck p;

    p.addEmp(mona);
    p.addEmp(gino);
    p.addEmp(tony);
    p.addEmp(carla);
    p.addEmp(gianni);
    p.addEmp(eolo);

    cout << "DISPLAY DEL CONTAINER ORIGINALE" << endl;

    p.dispAll();



    cout << "Test metodo isPresent() :" << endl << "1) Risultato atteso: NON PASSATO" << endl;
    if(p.isPresent("FF1")){
        cout << "Test PASSATO" << endl << endl;
    } else {
        cout << "Test NON PASSATO" << endl << endl;
    }

    cout << "Test metodo hasDirector() :" << endl << "2) Risultato atteso: PASSATO" << endl;
    if(p.hasDirector()){
        cout << "Test PASSATO" << endl << endl;
    } else {
        cout << "Test NON PASSATO" << endl << endl;
    }

    N.B.: Funziona tutto ma le stampe tutte insieme ti distruggono l'anima, controllare una per volta

    p.remEmp(mona);

    p.addEmp("Mona", "Poltrona", "MP1", "parttime");

    p.promotePtEmp("MP1");

    p.calcAllFullSal();

    cout << "DISPLAY DEI DATI RIORDINATI: " << endl << endl;

    cout << "ORDINATI PER RUOLO: " << endl << endl;

    p.orderByRole();

    p.dispAll();

    cout << "ORDINATI PER STIPENDIO PIU' ALTO: " << endl << endl;

    p.orderByFullSalMax();

    p.dispAll();

    cout << "ORDINATI PER BONUS STIPENDIO PIU' ALTO: " << endl << endl;

    p.orderByBonusSalMax();

    p.dispAll();

    cout << "ORDINATI PER ORE LAVORATE PIU' ALTE: " << endl << endl;

    p.orderByWorkedHoursMax();

    p.dispAll();

    cout << "ORDINATI PER ANZIANITA' PIU' ALTA: " << endl << endl;

    p.orderBySeniorityMax();

    p.dispAll();

    cout << "ORDINATI PER STIPENDIO PIU' BASSO: " << endl << endl;

    p.orderByFullSalMin();

    p.dispAll();

    cout << "ORDINATI PER BONUS STIPENDIO PIU' BASSO: " << endl << endl;

    p.orderByBonusSalMin();

    p.dispAll();

    cout << "ORDINATI PER ORE LAVORATE PIU' BASSE: " << endl << endl;

    p.orderByWorkedHoursMin();

    p.dispAll();

    cout << "ORDINATI PER ANZIANITA' PIU' BASSA: " << endl << endl;

    p.orderBySeniorityMin();

    p.dispAll();

    */

    QApplication a(argc, argv);

    paycheck* model = new paycheck();
    QtSalariesController* controller = new QtSalariesController(model);
    QSalaries* view = new QSalaries(nullptr, controller);
    controller->addView(view);

    view->adjustSize();
    view->move(QApplication::desktop()->screen()->rect().center() - (*view).rect().center());
    (*view).show();
    return a.exec();
}
