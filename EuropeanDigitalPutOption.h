#ifndef EUROPEANDIGITALPUTOPTION_H
#define EUROPEANDIGITALPUTOPTION_H

#include "EuropeanDigitalOption.h"
#include <stdexcept>

#pragma once

class EuropeanDigitalPutOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalPutOption();
    EuropeanDigitalPutOption(double strike, double expiry);
    virtual ~EuropeanDigitalPutOption();

protected:
    optionType GetOptionType() override;
    friend class BlackScholesPricer;

public:
    double payoff(double z) const override;
};

#endif
