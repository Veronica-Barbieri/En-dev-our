#include "level1.h"

std::string level1::ft_contr_name = "Full-time";

level1::level1(): contract(8, 8.0, 1.0, 1) {}

std::string level1::getContractType() const {
    return this->ft_contr_name;
}
