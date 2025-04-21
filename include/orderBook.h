#ifndef STOCK_TRADING_SYSTEM_ORDERBOOK_H
#define STOCK_TRADING_SYSTEM_ORDERBOOK_H

#include "order.h"
#include <vector>
#include <memory>
#include <mutex>

namespace StockTradingSystem
{
class OrderBook
{
public:
    OrderBook();
    void addOrder(std::shared_ptr<Order>);
    void matchOrders();
    void printOrderBook() const;
    void setStrategy(std::unique_ptr<OrderMatchingStrategy>);
private:
    std::vector<std::shared_ptr<Order>> book;
    std::unique_ptr<OrderMatchingStrategy> strategy; // Use unique_ptr
    mutable std::mutex bookMutex;
};
} // StockTradingSystem
#endif