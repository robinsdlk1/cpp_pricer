#ifndef EUROPEANDIGITALOPTION_H
#define EUROPEANDIGITALOPTION_H

#include "Option.h"
#include <stdexcept>

#pragma once

class EuropeanDigitalOption : public Option {
private:
    double _strike;
protected:
    enum class optionType { call, put };
    virtual optionType GetOptionType();
    double getStrike() const;
    friend class BlackScholesPricer;

public:
    EuropeanDigitalOption();
    EuropeanDigitalOption(double expiry, double strike);
    virtual ~EuropeanDigitalOption();
};

#endif

