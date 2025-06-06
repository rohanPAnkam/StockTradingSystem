#include "../include/orderBook.h"
#include <iostream>
#include <algorithm>
#include <set>

extern std::mutex coutMutex; // Declare global mutex

namespace StockTradingSystem {

OrderBook::OrderBook() : strategy(nullptr) {}

void OrderBook::addOrder(std::shared_ptr<Order> order) {
    std::lock_guard<std::mutex> lock(bookMutex);
    // Check for duplicate orders
    auto it = std::find_if(book.begin(), book.end(), 
        [&order](const std::shared_ptr<Order>& existing) {
            return existing->getTraider_id() == order->getTraider_id() &&
                   existing->getStockName() == order->getStockName() &&
                   existing->getPrice() == order->getPrice() &&
                   existing->getQuantity() == order->getQuantity() &&
                   existing->getOrdertype() == order->getOrdertype();
        });
    if (it == book.end()) {
        book.push_back(order);
        std::lock_guard<std::mutex> lock(::coutMutex);
        std::cout << "Added order: ID " << order->getTraider_id() << " " 
                  << order->getStockName() << " " << order->getPrice() << " " 
                  << order->getQuantity() << " " 
                  << (order->getOrdertype() == OrderType::BUY ? "Buy" : "Sell") << "\n";
    } else {
        std::lock_guard<std::mutex> lock(::coutMutex);
        std::cout << "Duplicate order ignored: ID " << order->getTraider_id() << " " 
                  << order->getStockName() << "\n";
    }
}

void OrderBook::matchOrders() {
    std::lock_guard<std::mutex> lock(bookMutex);
    std::vector<std::shared_ptr<Order>> buyOrders;
    std::vector<std::shared_ptr<Order>> sellOrders;
    std::vector<std::shared_ptr<Order>> unmatchedOrders;

    // Separate orders: TSLA for matching, others as unmatched
    for (const auto& order : book) {
        if (order->getStockName() == "TSLA") {
            if (order->getOrdertype() == OrderType::BUY) {
                buyOrders.push_back(order);
            } else if (order->getOrdertype() == OrderType::SELL) {
                sellOrders.push_back(order);
            }
        } else {
            unmatchedOrders.push_back(order); // AAPL and MSFT orders
        }
    }

    if (strategy) {
        strategy->matchOrders(buyOrders, sellOrders);
    }

    // Deduplicate and collect all orders
    struct OrderComparator {
        bool operator()(const std::shared_ptr<Order>& a, const std::shared_ptr<Order>& b) const {
            if (a->getTraider_id() != b->getTraider_id()) return a->getTraider_id() < b->getTraider_id();
            if (a->getStockName() != b->getStockName()) return a->getStockName() < b->getStockName();
            if (a->getPrice() != b->getPrice()) return a->getPrice() < b->getPrice();
            if (a->getQuantity() != b->getQuantity()) return a->getQuantity() < b->getQuantity();
            return a->getOrdertype() < b->getOrdertype();
        }
    };
    std::set<std::shared_ptr<Order>, OrderComparator> uniqueOrders;

    // Add unmatched orders (AAPL, MSFT)
    for (const auto& order : unmatchedOrders) {
        if (order->getQuantity() > 0) {
            uniqueOrders.insert(order);
        }
    }

    // Add remaining TSLA buy orders
    for (const auto& order : buyOrders) {
        if (order->getQuantity() > 0) {
            uniqueOrders.insert(order);
        }
    }

    // Add remaining TSLA sell orders
    for (const auto& order : sellOrders) {
        if (order->getQuantity() > 0) {
            uniqueOrders.insert(order);
        }
    }

    // Update book
    book.clear();
    book.assign(uniqueOrders.begin(), uniqueOrders.end());
}

void OrderBook::printOrderBook() const {
    std::lock_guard<std::mutex> lock(bookMutex);
    std::lock_guard<std::mutex> lock_cout(::coutMutex);
    std::cout << "Order Book content...\n";
    std::cout << "ID\tName\tPrice\tQuantity\tOrder Type\n";
    for (const auto& order : book) {
        std::cout << order->getTraider_id() << "\t" 
                  << order->getStockName() << "\t" 
                  << order->getPrice() << "\t" 
                  << order->getQuantity() << "\t\t" 
                  << (order->getOrdertype() == OrderType::BUY ? "Buy" : "Sell") << "\n";
    }
}

void OrderBook::setStrategy(std::unique_ptr<OrderMatchingStrategy> s) {
    strategy = std::move(s);
}

} // namespace StockTradingSystem