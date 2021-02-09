#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_
#include <memory>   // std::unique_ptr
#include "Menu.h"

class Customer
{
    private:
        int _id{0};
    public:
        Customer(){}
        Customer(int id): _id(id){}
        std::unique_ptr<MealOrder> makeOrder(const std::vector<Meal> menu);
};
#endif