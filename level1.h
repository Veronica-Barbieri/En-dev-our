#ifndef LEVEL1_H
#define LEVEL1_H
#include "contract.h"

class level1: public contract {
private:
    static std::string ft_contr_name;
public:
    level1();
    virtual std::string getContractType() const override;
};

#endif // LEVEL1_H
