#include "budget_manager.h"
#include "datetime.h"

#include <string>
#include <iostream>


int main() {
    std::cout.precision(25);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int Q;
    std::cin>>Q;
    
    BudgetManager budget_manager;
	std::string query;
	Date from, to;

    
    while (Q>0) {
        
        std::cin >> query >> from >> to;

        if (query == "ComputeIncome") {
            std::cout << budget_manager.ComputeIncome(from, to) << '\n';
        }
            
        if (query == "Earn") {
            double value;
            std::cin >> value;

            budget_manager.Earn(from, to, value);
        }

        if (query == "PayTax") {
            int tax = 13;
            std::cin >> tax;

            budget_manager.PayTax(from, to, tax);
        }

        if (query == "Spend") {
            double value;
            std::cin >> value;

            budget_manager.Spend(from, to, value);
        }

        Q--;
    }

    return 0;
}