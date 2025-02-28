#ifndef BLACKSCHOLESMCPRICER_H
#define BLACKSCHOLESMCPRICER_H

#include "Option.h"
#include "MT.h"
#include <vector>
#include <cmath>

class BlackScholesMCPricer {
private:
    Option* option_;
    double initial_price_;
    double interest_rate_;
    double volatility_;
    int nb_paths_ = 1;
    double price_estimate;
    double variance;
public:
    BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility);
    void generate(int);
    int getNbPaths() const;
    double operator()() const;
    std::vector<double> confidenceInterval() const;
};

#endif
