#include "Option.h"
#include <vector>
#include <stdexcept>
#include <sstream> 

Option::Option() : _expiry(0) {}

Option::Option(double _Expiry) : _expiry(_Expiry) {}

double Option::getExpiry() const {
    return _expiry;
}

double Option::payoffPath(std::vector<double>& prices) const {
    if (prices.empty()) {
        std::stringstream ss;
        ss << "empty list";
        throw std::invalid_argument(ss.str());
    }
    return payoff(prices.back());
}

Option::~Option() {}
