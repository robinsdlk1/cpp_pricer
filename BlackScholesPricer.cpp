#include "BlackScholesPricer.h"
using namespace std;
#include <iostream>
#include <cmath>

BlackScholesPricer::BlackScholesPricer(Option* option, double asset_price, double interest_rate, double volatility)
    : Option_(option), Asset_price_(asset_price), Interest_rate_(interest_rate), Volatility_(volatility) {}

double BlackScholesPricer::operator()() {
    double S = Asset_price_;
    double r = Interest_rate_;
    double T = Option_->getExpiry();
    double sigma = Volatility_;
    double d1, d2, prix;

    double K;
    bool isCall;
    bool isDigital = false;

    if (auto vanillaOption = dynamic_cast<EuropeanVanillaOption*>(Option_)) {
        K = vanillaOption->getStrike();
        isCall = (vanillaOption->GetOptionType() == EuropeanVanillaOption::optionType::call);
    }
    else if (auto digitalOption = dynamic_cast<EuropeanDigitalOption*>(Option_)) {
        K = digitalOption->getStrike();
        isCall = (digitalOption->GetOptionType() == EuropeanDigitalOption::optionType::call);
        isDigital = true;
    }
    else {
        throw std::logic_error("Option type does not support strike price.");
    }

    d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    d2 = d1 - sigma * std::sqrt(T);

    if (isDigital) {
        if (isCall) {
            prix = std::exp(-r * T) * 0.5 * std::erfc(-d2 / std::sqrt(2));
        }
        else {
            prix = std::exp(-r * T) * 0.5 * std::erfc(d2 / std::sqrt(2));
        }
    }
    else {
        if (isCall) {
            prix = S * 0.5 * std::erfc(-d1 / std::sqrt(2)) - K * std::exp(-r * T) * 0.5 * std::erfc(-d2 / std::sqrt(2));
        }
        else {
            prix = -S * 0.5 * std::erfc(d1 / std::sqrt(2)) + K * std::exp(-r * T) * 0.5 * std::erfc(d2 / std::sqrt(2));
        }
    }

    return prix;
}

double BlackScholesPricer::delta() {
    double S = Asset_price_;
    double r = Interest_rate_;
    double T = Option_->getExpiry();
    double sigma = Volatility_;
    double d, delta;

    double K;
    bool isCall;
    bool isDigital = false;

    if (auto vanillaOption = dynamic_cast<EuropeanVanillaOption*>(Option_)) {
        K = vanillaOption->getStrike();
        isCall = (vanillaOption->GetOptionType() == EuropeanVanillaOption::optionType::call);
    }
    else if (auto digitalOption = dynamic_cast<EuropeanDigitalOption*>(Option_)) {
        K = digitalOption->getStrike();
        isCall = (digitalOption->GetOptionType() == EuropeanDigitalOption::optionType::call);
        isDigital = true;
    }
    else {
        throw std::logic_error("Option type does not support strike price.");
    }

    d = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));

    if (isDigital) {
        double pdf_d = std::exp(-0.5 * d * d) / std::sqrt(2 * 3.14159265358979323846); //pi
        if (isCall) {
            delta = pdf_d / (S * sigma * std::sqrt(T));
        }
        else {
            delta = -pdf_d / (S * sigma * std::sqrt(T));
        }
    }
    else {
        if (isCall) {
            delta = 0.5 * std::erfc(-d / std::sqrt(2));
        }
        else {
            delta = 0.5 * std::erfc(-d / std::sqrt(2)) - 1;
        }
    }

    return delta;
}

BlackScholesPricer::~BlackScholesPricer() {}
