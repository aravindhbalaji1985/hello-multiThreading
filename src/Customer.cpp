#include "Customer.h"
#include <random>   // std::random

std::unique_ptr<MealOrder> Customer::makeOrder(const std::vector<Meal> menu)
{
    auto _numMealsOffered = menu.size();
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> _randomOrderType(0, 1);
    std::uniform_int_distribution<> _randomMealType(0, _numMealsOffered-1);
    std::unique_ptr<MealOrder> _newOrder(new MealOrder);
    _newOrder->_meal = menu[_randomMealType(eng)];
    _newOrder->_orderType = static_cast<OrderType>(_randomOrderType(eng));
    _newOrder->_orderNumber = this->_id;
    return (std::move(_newOrder));
}