# pragma once

#include "datetime.h"

#include <vector>
#include <iostream>


class BudgetManager {
public:
	BudgetManager() {
		money_calendar_ = std::vector<MoneyPerDay>(36600, MoneyPerDay());
	}

	void Earn(const Date& from, const Date& to, const double& money);

	void PayTax(const Date& from, const Date& to, int tax=13);

	void Spend(const Date& from, const Date& to, const double& money);

	double ComputeIncome(const Date& from, const Date& to) const;

private:
    struct MoneyPerDay {
        MoneyPerDay() {
			earned = 0;
			spent = 0;
        }

		double earned;
		double spent;
    };

	int tax_ = 13;

	std::vector<MoneyPerDay> money_calendar_;
};