#include "../include/trader.h"
#include <stdexcept>
#include <iostream>

extern std::mutex coutMutex; // Declare global mutex

namespace StockTradingSystem {

Trader::Trader(const std::string& name, const std::vector<Stock>& st, OrderFactory* of, OrderBook* ob) 
    : traderName(name), stocks(st), orderFactory(of), orderBook(ob), id(nextId++) {}

Trader::~Trader() {}

std::string Trader::getName() const { return traderName; }
int Trader::getID() const { return id; }
void Trader::addStock(const Stock& stock) { stocks.push_back(stock); }

void Trader::buy(const Stock& stock, int quantity) {
    try {
        if (orderFactory == nullptr || orderBook == nullptr) {
            throw std::runtime_error("Order factory or order book not initialized");
        }
        if (quantity <= 0) {
            throw std::invalid_argument("Quantity must be positive");
        }
        std::shared_ptr<Order> ord = orderFactory->createOrder(id, stock.getPrice(), quantity, stock.getName());
        ord->setOrderType(OrderType::BUY);
        {
            std::lock_guard<std::mutex> lock(ordersMutex);
            orders.push_back(ord);
        }
        orderBook->addOrder(ord);
        std::lock_guard<std::mutex> lock(::coutMutex);
        std::cout << "Trader " << id << " adding BUY order for " << stock.getName() << "\n";
    } catch (const std::exception& e) {
        std::lock_guard<std::mutex> lock(::coutMutex);
        std::cerr << "Exception in buy: " << e.what() << std::endl;
    }
}

void Trader::sell(const Stock& stock, int quantity) {
    try {
        if (orderFactory == nullptr || orderBook == nullptr) {
            throw std::runtime_error("Order factory or order book not initialized");
        }
        if (quantity <= 0) {
            throw std::invalid_argument("Quantity must be positive");
        }
        std::shared_ptr<Order> ord = orderFactory->createOrder(id, stock.getPrice(), quantity, stock.getName());
        ord->setOrderType(OrderType::SELL);
        {
            std::lock_guard<std::mutex> lock(ordersMutex);
            orders.push_back(ord);
        }
        orderBook->addOrder(ord);
        std::lock_guard<std::mutex> lock(::coutMutex);
        std::cout << "Trader " << id << " adding SELL order for " << stock.getName() << "\n";
    } catch (const std::exception& e) {
        std::lock_guard<std::mutex> lock(::coutMutex);
        std::cerr << "Exception in sell: " << e.what() << std::endl;
    }
}

void Trader::trade(double buyThreshold, double sellThreshold, int buyQuantity, int sellQuantity) {
    try {
        if (orderFactory == nullptr || orderBook == nullptr) {
            throw std::runtime_error("Order factory or order book not initialized");
        }
        if (buyQuantity <= 0 || sellQuantity <= 0) {
            throw std::invalid_argument("Quantities must be positive");
        }
        for (const Stock& stock : stocks) {
            {
                std::lock_guard<std::mutex> lock(::coutMutex);
                std::cout << "Trader " << id << " evaluating stock " << stock.getName() 
                          << " price " << stock.getPrice() << " buyThreshold " << buyThreshold 
                          << " sellThreshold " << sellThreshold << "\n";
            }
            if (stock.getPrice() < buyThreshold) {
                std::shared_ptr<Order> ord = orderFactory->createOrder(id, stock.getPrice(), buyQuantity, stock.getName());
                ord->setOrderType(OrderType::BUY);
                {
                    std::lock_guard<std::mutex> lock(ordersMutex);
                    orders.push_back(ord);
                }
                {
                    std::lock_guard<std::mutex> lock(::coutMutex);
                    std::cout << "Trader " << id << " creating BUY order for " << stock.getName() 
                              << " quantity " << buyQuantity << "\n";
                }
                orderBook->addOrder(ord);
                {
                    std::lock_guard<std::mutex> lock(::coutMutex);
                    std::cout << "Trader " << id << " adding BUY order for " << stock.getName() << "\n";
                }
            } else if (stock.getPrice() > sellThreshold) {
                std::shared_ptr<Order> ord = orderFactory->createOrder(id, stock.getPrice(), sellQuantity, stock.getName());
                ord->setOrderType(OrderType::SELL);
                {
                    std::lock_guard<std::mutex> lock(ordersMutex);
                    orders.push_back(ord);
                }
                {
                    std::lock_guard<std::mutex> lock(::coutMutex);
                    std::cout << "Trader " << id << " creating SELL order for " << stock.getName() 
                              << " quantity " << sellQuantity << "\n";
                }
                orderBook->addOrder(ord);
                {
                    std::lock_guard<std::mutex> lock(::coutMutex);
                    std::cout << "Trader " << id << " adding SELL order for " << stock.getName() << "\n";
                }
            }
        }
    } catch (const std::exception& e) {
        std::lock_guard<std::mutex> lock(::coutMutex);
        std::cerr << "Exception in trade: " << e.what() << std::endl;
    }
}

void Trader::addOrder(std::shared_ptr<Order> order) {
    std::lock_guard<std::mutex> lock(ordersMutex);
    orders.push_back(order);
}

int Trader::nextId = 0;

} // namespace StockTradingSystem