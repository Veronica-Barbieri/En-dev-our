#include "level0.h"

std::string level0::pt_contr_name = "Part-time";

level0::level0(): contract(4, 7.5, 0.5, 1) {}

std::string level0::getContractType() const {
    return this->pt_contr_name;
}
