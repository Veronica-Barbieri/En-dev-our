#ifndef PTEMPLOYEE_H
#define PTEMPLOYEE_H
#include "worker.h"
#include "level0.h"

class ptemployee: public worker, public level0 {
public:
    ptemployee(std::string, std::string, std::string);
    virtual double calcBaseSal() const override;
    virtual double calcBonus() const override;
    virtual double calcFullSal(const int&, const int&) override;
    virtual void updateVacAcc() override;
};

#endif // PTEMPLOYEE_H
