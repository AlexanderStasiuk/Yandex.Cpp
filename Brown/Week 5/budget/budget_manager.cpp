#include "budget_manager.h"


void BudgetManager::Earn(const Date& from, const Date& to, const double& money)
{
	const double money_per_day = money / 
		(static_cast<double>(Date::ComputeDaysDiff(from, to)) + 1);

	const size_t n = Date::GetIndexFromDay(to);

    for (size_t i = Date::GetIndexFromDay(from); i <= n; ++i)
    {
		money_calendar_[i].earned += money_per_day;
    }
}


void BudgetManager::PayTax(const class Date& from, const class Date& to, int tax)
{
	if (tax_ != tax)
		tax_ = tax;

	const size_t n = Date::GetIndexFromDay(to);

	for (size_t i = Date::GetIndexFromDay(from); i <= n; ++i)
	{
		money_calendar_[i].earned *= ((100.0 - tax_ * 1.0) / 100.0);
	}
}


void BudgetManager::Spend(const Date& from, const Date& to, const double& money)
{
	const double money_per_day = money /
		(static_cast<double>(Date::ComputeDaysDiff(from, to)) + 1);

	const size_t n = Date::GetIndexFromDay(to);

	for (size_t i = Date::GetIndexFromDay(from); i <= n; ++i)
	{
		money_calendar_[i].spent += money_per_day;
	}
}


double BudgetManager::ComputeIncome(const class Date& from, const class Date& to) const
{
	double result = 0;

	const size_t n = Date::GetIndexFromDay(to);

	for (size_t i = Date::GetIndexFromDay(from); i <= n; ++i)
	{
		const auto& money_per_day = money_calendar_[i];

		result += (money_per_day.earned - money_per_day.spent);
	}

	return result;
}
   