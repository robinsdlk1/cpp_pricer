#include "AmericanOption.h"
#include <iostream>
#include <sstream>

AmericanOption::AmericanOption() : _strike(0) {}

AmericanOption::AmericanOption(double expiry, double strike) : Option(expiry), _strike(strike) {
    if (expiry < 0) {
        std::stringstream ss;
        ss << "ERROR : Expiry " << expiry << " is negative.";
        throw std::invalid_argument(ss.str());
    }
    if (strike < 0) {
        std::stringstream ss;
        ss << "ERROR : Strike " << strike << " is negative.";
        throw std::invalid_argument(ss.str());
    }
}

double AmericanOption::getStrike() const {
    return _strike;
}

bool AmericanOption::isAmericanOption() const {
    return true;
}

AmericanOption::~AmericanOption() {}
