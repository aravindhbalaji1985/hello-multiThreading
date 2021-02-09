#include <thread>
#include <future>
#include <atomic>
#include <chrono>
#include <iostream>
#include <random>
#include "Menu.h"
#include "Customer.h"
#include "Restaurant.h"
#include <memory>
#define NUM_WAITER 2
#define NUM_CHEF 1
#define MIN_TIME 10
#define MAX_TIME 30
#define OPEN_HOURS 1000 // 1 second.

/**
 * @brief Simulate a day in the restaurant
 *
 * @param menu Vectors of meals to choose from
 */
void simulateADay(const std::vector<Meal> menu)
{
    // Declare the day open and instantiate the workers. The restaurant has a
    // chef and waiters to keep the orders moving.
    RestaurantStatus resStatus {RestaurantStatus::open};

    // Create the objects for the classes.
    std::shared_ptr<Restaurant> sharedRestaurant(new Restaurant());
    std::shared_ptr<Customer> cust(new Customer());

    // Kick start the chef and the waiter threads.
    std::thread chefTh(&Restaurant::prepareOrder, sharedRestaurant);
    std::thread serverThread (&Restaurant::serveOrder, sharedRestaurant);

#ifdef DEBUG
    for (auto &it: menu)
        std::cout<<it._name<<std::endl;
#endif

    // Start the timer thread. Work life balance is very important.
    std::future<void> statusFuture = std::async(std::launch::async,
                                                [&resStatus]() {
#ifdef DEBUG
                                                    std::cout << "Worker thread id = " << std::this_thread::get_id()
                                                              << std::endl;
#endif
                                                    std::this_thread::sleep_for(std::chrono::milliseconds(OPEN_HOURS));
                                                    resStatus = RestaurantStatus::closed;
                                                });

    // Order id.
    int id{0};
    auto generateId = [&id]() { return ++id; };

    std::random_device _rd;
    std::mt19937 _eng(_rd());
    std::uniform_int_distribution<> _randomCustomerEntry(MIN_TIME, MAX_TIME);

    while (resStatus == RestaurantStatus::open)
    {
        //Simulate Customer Order
        auto newOrder = cust->makeOrder(menu);
        newOrder->_orderNumber = generateId();
        sharedRestaurant->placeOrder(std::move(newOrder));
        // We are putting this thread to sleep to mimic random customer entry.
        std::this_thread::sleep_for(std::chrono::milliseconds(_randomCustomerEntry(_eng)));
    }

    // Intimate the workers that there are no more new orders.
    std::unique_ptr<MealOrder> shutDownOrder(new MealOrder);
    shutDownOrder->_orderType = OrderType::thatsAllFolks;
    shutDownOrder->_meal._prepTime = 0;
    shutDownOrder->_orderNumber = generateId();

    std::future<void> shutDownFuture = std::async(std::launch::deferred,
                                                  &Restaurant::placeOrder,
                                                  sharedRestaurant,
                                                  std::move(shutDownOrder));


    statusFuture.wait();
    shutDownFuture.wait();
    serverThread.join();
    chefTh.join();
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "Usage: restaurantFoodPrep <Menu file>" << std::endl;
        return EXIT_FAILURE;
    }

    // Get the menu for the day
    try{
        // Read menu from file.
        std::shared_ptr<Menu> _menuObj(new Menu(argv[1]));
        auto menu = _menuObj->getMenu();
        simulateADay(menu);
    }
    catch (std::runtime_error e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}