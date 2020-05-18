#ifndef PARTTIME_H
#define PARTTIME_H
#include "contract.h"

class level0: public contract {
private:
    static std::string pt_contr_name;
public:
    level0();
    virtual std::string getContractType() const override;
};


#endif // PARTTIME_H
