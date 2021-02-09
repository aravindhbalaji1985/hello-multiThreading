#include "Restaurant.h"
#include "ThreadSafe.h"

/**
 * @brief Place an order and intimate the chef on the new order.
 *
 * @param order MealOrder
 */
void Restaurant::placeOrder(std::unique_ptr<MealOrder> &&order)
{
    std::unique_lock<std::mutex> _placeOrderLock(_orderMtx);
    // In order to prevent the chef from getting overwhelmed with the number of
    // orders to prepare, the waiter will wait when placed order maxes out.
    _orderBell.wait(_placeOrderLock, [this] {return _getSizePlacedOrder() < MAX_ORDER;});
    ThreadSafeCout{} << "Waiter thread: "<< std::this_thread::get_id() << " Placing order: "<< order->_orderNumber << std::endl;
    _pendingOrders.push_back(std::move(order));
    _orderBell.notify_one();
}

/**
 * @brief Serve the order that has been cooked.
 *
 */
void Restaurant::serveOrder()
{
    std::random_device _rd;
    std::mt19937 _eng(_rd());
    std::uniform_int_distribution<> _randomWait(MIN_SERVING_WAIT_TIME,
                                                MAX_SERVING_WAIT_TIME);
    bool stayAlive{true};
    while (stayAlive)
    {
        std::unique_lock<std::mutex> _serveOrderLock(_serveMtx);
        _serveBell.wait(_serveOrderLock, [this] {return !_completedOrders.empty(); });
        auto _order = std::move(_completedOrders.back());
        ThreadSafeCout{} << "Waiter thread: "<< std::this_thread::get_id() <<" Serving order: "<< _order->_orderNumber << std::endl;
        _completedOrders.pop_back();
        if (_order->_orderType == OrderType::thatsAllFolks)
            stayAlive = false;
        // The waiter takes sometime in serving the meal. The serving time is a
        // random number between 10-100 msec. We simulate this by putting the
        // thread to sleep for that amount of time.
        std::this_thread::sleep_for(std::chrono::milliseconds(_randomWait(_eng)));
    }
}

/**
 * @brief Prepare the order and intimate the waiter once the order is ready to
 * be served.
 *
 */

void Restaurant::prepareOrder()
{
    bool stayAlive{true};
    while (stayAlive)
    {
        std::unique_lock<std::mutex> _prepOrderLock(_orderMtx);
        _orderBell.wait(_prepOrderLock, [this] { return !_pendingOrders.empty(); });
        auto _order = std::move(_pendingOrders.front());
        _pendingOrders.pop_front();
#ifdef DEBUG
        ThreadSafeCout{} << "Chef thread: "<< std::this_thread::get_id() << " Processing order: "<< _order->_orderNumber << std::endl;
#endif
        // Cook this order.
        // For now we will put it to sleep. This can be ideally expanded to cooks
        // with synchronization. For now, we will assume that the chef does all the
        // work. He is an one man army.
        if (_order->_orderType != OrderType::thatsAllFolks)
            std::this_thread::sleep_for(std::chrono::milliseconds(_order->_meal._prepTime));
        else
            stayAlive = false;

        _orderBell.notify_one();
        _prepOrderLock.unlock();

        {
            std::lock_guard<std::mutex> _placeOrderLock(_serveMtx);
#ifdef DEBUG
            ThreadSafeCout{} << "Chef thread: "<< std::this_thread::get_id() << "Ready to serve order: "<< _order->_orderNumber << std::endl;
#endif
            _completedOrders.push_back(std::move(_order));
            _serveBell.notify_one();
        }
    }
}

int Restaurant::_getSizeToServe()
{
    std::shared_lock<std::shared_mutex> _sLock(_door);
    return _completedOrders.size();
}

int Restaurant::_getSizePlacedOrder()
{
    std::shared_lock<std::shared_mutex> _sLock(_door);
    return _pendingOrders.size();
}