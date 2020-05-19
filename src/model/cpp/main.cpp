#include <iostream>
#include "../headers/director.h"
#include "../headers/ftemployee.h"
#include "../headers/ptemployee.h"
#include "../headers/container.h"

using std::endl;
using std::cout;
using std::cin;

int main()
{
    cout<<"TEST WORKER E CONTRACT:"<<endl;
    cout<<"-----------------------"<<endl<<endl;

    worker* gino = new director("Gino", "Pasticcino", "GP1");
    worker* tony = new ftemployee("Tony", "Cartony", "TC1");
    worker* mona = new ptemployee("Mona", "Poltrona", "GP1");

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

    /*cout<<"cont_sum[3]:  "<<endl;
    cout<<cont_sum[3];
    cout<<endl;*/

    return 0;
}
