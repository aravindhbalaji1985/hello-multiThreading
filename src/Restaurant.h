#ifndef _RESTAURANT_H_
#define _RESTAURANT_H_
#include <mutex>                // std::mutex
#include <condition_variable>   // std::condition_variable
#include <deque>                // std::deque
#include <shared_mutex>         // std::shared_mutex
#include <thread>               // std::thread
#include <chrono>               // std::chrono
#include <iostream>             // std::endl
#include <random>               // std::random
#include "Menu.h"


#define MAX_ORDER 10
#define MIN_SERVING_WAIT_TIME 10
#define MAX_SERVING_WAIT_TIME 100

enum RestaurantStatus
{
    open,
    closed
};

class Restaurant
{
private:
    std::deque<std::unique_ptr<MealOrder> > _pendingOrders;
    std::deque<std::unique_ptr<MealOrder> > _completedOrders;
    std::mutex _orderMtx;
    std::mutex _serveMtx;
    std::shared_mutex _door;
    std::condition_variable _serveBell;
    std::condition_variable _orderBell;

    int _getSizeToServe();
    int _getSizePlacedOrder();

public:
    Restaurant(){};
    void prepareOrder();
    void serveOrder();
    void placeOrder(std::unique_ptr<MealOrder> &&order);
};


#endif