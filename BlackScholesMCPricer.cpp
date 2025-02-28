#include "BlackScholesMCPricer.h"
#include "AsianOption.h"
#include <stdexcept>
#include <vector>
#include <cmath>

BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility)
    : option_(option), initial_price_(initial_price), interest_rate_(interest_rate), volatility_(volatility), nb_paths_(0), price_estimate(0.0), variance(0.0) {}

void BlackScholesMCPricer::generate(int nb_paths) {
    double sum_payoffs = 0.0;
    double sum_payoffs_squared = 0.0;

    for (int i = 0; i < nb_paths; ++i) {
        double ST;
        if (option_->isAsianOption()) {
            std::vector<double> prices;
            AsianOption* asian_option_ = dynamic_cast<AsianOption*>(option_);
            for (double t : asian_option_->getTimeSteps()) {
                double random_value = MT::rand_norm();
                double price = initial_price_ * std::exp((interest_rate_ - 0.5 * volatility_ * volatility_) * t + volatility_ * std::sqrt(t) * random_value);
                prices.push_back(price);
            }
            ST = option_->payoffPath(prices);
        }
        else {
            double random_value = MT::rand_norm();
            ST = initial_price_ * std::exp((interest_rate_ - 0.5 * volatility_ * volatility_) + volatility_ * random_value);
        }

        double payoff = option_->payoff(ST) * std::exp(-interest_rate_);
        sum_payoffs += payoff;
        sum_payoffs_squared += payoff * payoff;
    }

    nb_paths_ += nb_paths;
    double mean_payoff = sum_payoffs / nb_paths;
    price_estimate = (price_estimate * (nb_paths_ - nb_paths) + mean_payoff * nb_paths) / nb_paths_;

    variance = (sum_payoffs_squared / nb_paths - mean_payoff * mean_payoff) / nb_paths;
}

int BlackScholesMCPricer::getNbPaths() const {
    return nb_paths_;
}

double BlackScholesMCPricer::operator()() const {
    if (nb_paths_ == 0) {
        throw std::logic_error("Aucune trajectoire n'a été générée pour estimer le prix.");
    }
    return price_estimate;
}

std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
    if (nb_paths_ == 0) {
        throw std::logic_error("Aucune trajectoire n'a été générée pour calculer l'intervalle de confiance.");
    }
    double margin_of_error = 1.96 * std::sqrt(variance / nb_paths_);
    return { price_estimate - margin_of_error, price_estimate + margin_of_error };
}
