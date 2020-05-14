#include <iostream>
#include "director.h"
#include "ftemployee.h"
#include "ptemployee.h"
using std::endl;
using std::cout;
using std::cin;

int main()
{
    worker* gino = new director("gino", "pasticcino");
    worker* tony = new ftemployee("tony", "cartony");
    worker* mona = new ptemployee("mona", "poltrona");

    double stipg = gino->calcFullSal(24, 216); // ha alvorato 25 giorni per 9 ore ciascun giorno lavorativo
    int vacg = gino->getVacAcc();

    double stipt = tony->calcFullSal(20, 200);
    int vact = tony->getVacAcc();

    cout << tony->calcBonus();

    double stipm = mona->calcFullSal(20, 80);
    int vacm = mona->getVacAcc();

    cout << "Stipendio Gino: " << stipg << endl <<"Vacanze accumulate Gino: " << vacg << endl << endl;
    cout << "Stipendio Tony: " << stipt << endl <<"Vacanze accumulate Tony: " << vact << endl << endl;
    cout << "Stipendio Mona: " << stipm << endl <<"Vacanze accumulate Mona: " << vacm << endl << endl;

    return 0;
}
