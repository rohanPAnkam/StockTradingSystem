#include "../include/order.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

using namespace StockTradingSystem;

Order::Order(int id, double p, int q, const std::string& s) 
    : traider_id{id}, price{p}, quantity{q}, stockName(s), timestamp(std::time(nullptr)), ordertype(OrderType::BUY) {}

Order::~Order() {}

int Order::getTraider_id() const { return traider_id; }
double Order::getPrice() const { return price; }
std::string Order::getStockName() const { return stockName; }
int Order::getQuantity() const { return quantity; }
std::time_t Order::getTimestamp() const { return timestamp; }
OrderType Order::getOrdertype() const { return ordertype; }

void Order::setOrderType(OrderType type) { ordertype = type; }

void Order::reduceQuantity(int amount) {
    if (amount > 0 && amount <= quantity) {
        quantity -= amount;
    } else {
        throw std::out_of_range{"Amount out of range."};
    }
}

std::string MarketOrder::getOrderType() const { return "Market Order"; }
std::string LimitOrder::getOrderType() const { return "Limit Order"; }

OrderFactory::~OrderFactory() {}

std::unique_ptr<Order> MarketOrderFactory::createOrder(int trader_id, double price, int quantity, const std::string& stockName) {
    return std::make_unique<MarketOrder>(trader_id, price, quantity, stockName);
}

std::unique_ptr<Order> LimitOrderFactory::createOrder(int trader_id, double price, int quantity, const std::string& stockName) {
    return std::make_unique<LimitOrder>(trader_id, price, quantity, stockName);
}

OrderMatchingStrategy::~OrderMatchingStrategy() {}

void PriceTimeOrderMatchingStrategy::matchOrders(std::vector<std::shared_ptr<Order>>& buyOrders, 
                                                std::vector<std::shared_ptr<Order>>& sellOrders) {
    std::vector<std::shared_ptr<Order>> remainingBuyOrders;
    std::vector<std::shared_ptr<Order>> remainingSellOrders;

    // Sort buy orders by price (descending) and timestamp (ascending)
    std::sort(buyOrders.begin(), buyOrders.end(), 
              [](const std::shared_ptr<Order>& a, const std::shared_ptr<Order>& b) {
                  return a->getPrice() > b->getPrice() || 
                         (a->getPrice() == b->getPrice() && a->getTimestamp() < b->getTimestamp());
              });

    // Sort sell orders by price (ascending) and timestamp (ascending)
    std::sort(sellOrders.begin(), sellOrders.end(), 
              [](const std::shared_ptr<Order>& a, const std::shared_ptr<Order>& b) {
                  return a->getPrice() < b->getPrice() || 
                         (a->getPrice() == b->getPrice() && a->getTimestamp() < b->getTimestamp());
              });

    // Process each buy order to ensure it is fully matched
    for (auto buyIt = buyOrders.begin(); buyIt != buyOrders.end();) {
        if ((*buyIt)->getQuantity() <= 0) {
            buyIt = buyOrders.erase(buyIt);
            continue;
        }
        bool buyOrderMatched = false;
        for (auto sellIt = sellOrders.begin(); sellIt != sellOrders.end();) {
            if ((*sellIt)->getQuantity() <= 0) {
                sellIt = sellOrders.erase(sellIt);
                continue;
            }
            // Match only if stock names are the same and prices are compatible
            if ((*buyIt)->getStockName() == (*sellIt)->getStockName() && 
                (*buyIt)->getPrice() >= (*sellIt)->getPrice()) {
                int tradeQuantity = std::min((*buyIt)->getQuantity(), (*sellIt)->getQuantity());
                if (tradeQuantity > 0) {
                    {
                        std::lock_guard<std::mutex> lock(::coutMutex);
                        std::cout << "Matched: Buy ID " << (*buyIt)->getTraider_id() << " with Sell ID " 
                                  << (*sellIt)->getTraider_id() << " for " << tradeQuantity << " shares of " 
                                  << (*sellIt)->getStockName() << " at " << (*sellIt)->getPrice() << "\n";
                    }
                    (*buyIt)->reduceQuantity(tradeQuantity);
                    (*sellIt)->reduceQuantity(tradeQuantity);
                    buyOrderMatched = true;
                    // Only add sell order to remaining if it has quantity left
                    if ((*sellIt)->getQuantity() > 0) {
                        remainingSellOrders.push_back(*sellIt);
                    }
                }
                sellIt = sellOrders.erase(sellIt); // Remove sell order from processing
                if ((*buyIt)->getQuantity() <= 0) break; // Exit inner loop if buy order is fully matched
            } else {
                remainingSellOrders.push_back(*sellIt);
                ++sellIt;
            }
        }
        // Add buy order to remaining if it has quantity left
        if ((*buyIt)->getQuantity() > 0) {
            remainingBuyOrders.push_back(*buyIt);
        }
        buyIt = buyOrders.erase(buyIt); // Remove buy order from processing
    }

    // Add any remaining sell orders that were not processed
    for (auto& sellOrder : sellOrders) {
        if (sellOrder->getQuantity() > 0) {
            remainingSellOrders.push_back(sellOrder);
        }
    }

    // Move remaining orders back to input vectors
    buyOrders.clear();
    sellOrders.clear();
    buyOrders = std::move(remainingBuyOrders);
    sellOrders = std::move(remainingSellOrders);
}