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

    worker* gino = new director("gino", "pasticcino", "GP1");
    worker* tony = new ftemployee("tony", "cartony", "TC1");
    worker* mona = new ptemployee("mona", "poltrona", "GP1");

    double stipg = gino->calcFullSal(24, 216); // ha alvorato 25 giorni per 9 ore ciascun giorno lavorativo
    int vacg = gino->getVacAcc();

    double stipt = tony->calcFullSal(20, 200);
    int vact = tony->getVacAcc();

    double stipm = mona->calcFullSal(20, 80);
    int vacm = mona->getVacAcc();

    cout << "Stipendio Gino: " << stipg << endl <<"Vacanze accumulate Gino: " << vacg << endl << endl;
    cout << "Stipendio Tony: " << stipt << endl <<"Vacanze accumulate Tony: " << vact << endl << endl;
    cout << "Stipendio Mona: " << stipm << endl <<"Vacanze accumulate Mona: " << vacm << endl << endl;

    cout << "test operator == :" << endl << "1) Risultato atteso: NON PASSATO" << endl;
    if(*gino == *tony){
        cout << "Primo test ugualianza passato" << endl << endl;
    } else {
        cout << "Primo test ugualianza non passato" << endl << endl;
    }

    cout << "2) Risultato atteso:PASSATO" << endl;
    if(*gino == *mona){
        cout << "Secondo test ugualianza passato" << endl << endl;
    } else {
        cout << "Secondo test ugualianza non passato" << endl << endl;
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
