// #include "../include/trader.h"
// #include <iostream>
// #include <stdexcept>

// using namespace StockTradingSystem;

// int Trader::id_counter = 0;

// Trader::Trader()
//     : name{""}, id{id_counter++}, orderFactory{nullptr}, orderBook{nullptr} {}

// Trader::Trader(const std::string& n)
//     : name{n}, orderBook{nullptr}, orderFactory{nullptr}, id{id_counter++} {}

// Trader::Trader(const std::string& n, const std::vector<Stock>& s, OrderFactory* o, OrderBook* b)
//     : id{id_counter++}, name{n}, stocks{s}, orderFactory{o}, orderBook{b} {}

// void Trader::buy(const StockTradingSystem::Stock& stock, int quantity) {
//     try {
//         if (orderFactory == nullptr || orderBook == nullptr) {
//             throw std::runtime_error("Order factory or order book not initialized");
//         }
//         if (quantity <= 0) {
//             throw std::invalid_argument("Quantity must be positive");
//         }
//         std::shared_ptr<Order> ord = orderFactory->createOrder(id, stock.getPrice(), quantity, stock.getName());
//         ord->setOrderType(OrderType::BUY);
//         {
//             std::lock_guard<std::mutex> lock(ordersMutex); // Protect orders
//             orders.push_back(ord);
//         }
//         orderBook->addOrder(ord);
//     } catch (const std::exception& e) {
//         std::cerr << "Exception in buy: " << e.what() << std::endl;
//     }
// }

// void Trader::sell(const StockTradingSystem::Stock& stock, int quantity) {
//     try {
//         if (orderFactory == nullptr || orderBook == nullptr) {
//             throw std::runtime_error("Order factory or order book not initialized");
//         }
//         if (quantity <= 0) {
//             throw std::invalid_argument("Quantity must be positive");
//         }
//         std::shared_ptr<Order> ord = orderFactory->createOrder(id, stock.getPrice(), quantity, stock.getName());
//         ord->setOrderType(OrderType::SELL);
//         {
//             std::lock_guard<std::mutex> lock(ordersMutex); // Protect orders
//             orders.push_back(ord);
//         }
//         orderBook->addOrder(ord);
//     } catch (const std::exception& e) {
//         std::cerr << "Exception in sell: " << e.what() << std::endl;
//     }
// }

// void Trader::trade(double buyThreshold, double sellThreshold, int buyQuantity, int sellQuantity) {
//     try {
//         if (orderFactory == nullptr || orderBook == nullptr) {
//             throw std::runtime_error("Order factory or order book not initialized");
//         }
//         if (buyQuantity <= 0 || sellQuantity <= 0) {
//             throw std::invalid_argument("Quantities must be positive");
//         }
//         for (const Stock& stock : stocks) {
//             if (stock.getPrice() < buyThreshold) {
//                 std::shared_ptr<Order> ord = orderFactory->createOrder(id, stock.getPrice(), buyQuantity, stock.getName());
//                 ord->setOrderType(OrderType::BUY);
//                 std::cout << "Trader " << id << " adding BUY order for " << stock.getName() << "\n";
//                 {
//                     std::lock_guard<std::mutex> lock(ordersMutex);
//                     orders.push_back(ord);
//                 }
//                 orderBook->addOrder(ord);
//             } else if (stock.getPrice() > sellThreshold) {
//                 std::shared_ptr<Order> ord = orderFactory->createOrder(id, stock.getPrice(), sellQuantity, stock.getName());
//                 ord->setOrderType(OrderType::SELL);
//                 std::cout << "Trader " << id << " adding SELL order for " << stock.getName() << "\n";
//                 {
//                     std::lock_guard<std::mutex> lock(ordersMutex);
//                     orders.push_back(ord);
//                 }
//                 orderBook->addOrder(ord);
//             }
//         }
//     } catch (const std::exception& e) {
//         std::cerr << "Exception in trade: " << e.what() << std::endl;
//     }
// }

// int Trader::getID() const {
//     return id;
// }

// const std::vector<std::shared_ptr<Order>>& Trader::getOrders() const {
//     return orders;
// }

// void Trader::addStock(const Stock& st) {
//     stocks.push_back(st);
// }

// std::vector<Stock> Trader::getStocks() const {
//     return stocks;
// }

// void Trader::addOrder(std::shared_ptr<Order> order) {
//     std::lock_guard<std::mutex> lock(ordersMutex); // Protect orders
//     orders.push_back(order);
// }

// Trader::~Trader() {}

// #include "../include/trader.h"
// #include <stdexcept>
// #include <iostream>

// namespace StockTradingSystem {

// Trader::Trader(const std::string& name, const std::vector<Stock>& st, OrderFactory* of, OrderBook* ob) 
//     : traderName(name), stocks(st), orderFactory(of), orderBook(ob), id(nextId++) {}

// Trader::~Trader() {}

// std::string Trader::getName() const { return traderName; }
// int Trader::getID() const { return id; }
// void Trader::addStock(const Stock& stock) { stocks.push_back(stock); }

// void Trader::buy(const Stock& stock, int quantity) {
//     try {
//         if (orderFactory == nullptr || orderBook == nullptr) {
//             throw std::runtime_error("Order factory or order book not initialized");
//         }
//         if (quantity <= 0) {
//             throw std::invalid_argument("Quantity must be positive");
//         }
//         std::shared_ptr<Order> ord = orderFactory->createOrder(id, stock.getPrice(), quantity, stock.getName());
//         ord->setOrderType(OrderType::BUY);
//         {
//             std::lock_guard<std::mutex> lock(ordersMutex);
//             orders.push_back(ord);
//         }
//         orderBook->addOrder(ord);
//         std::lock_guard<std::mutex> lock(::coutMutex);
//         std::cout << "Trader " << id << " adding BUY order for " << stock.getName() << "\n";
//     } catch (const std::exception& e) {
//         std::lock_guard<std::mutex> lock(::coutMutex);
//         std::cerr << "Exception in buy: " << e.what() << std::endl;
//     }
// }

// void Trader::sell(const Stock& stock, int quantity) {
//     try {
//         if (orderFactory == nullptr || orderBook == nullptr) {
//             throw std::runtime_error("Order factory or order book not initialized");
//         }
//         if (quantity <= 0) {
//             throw std::invalid_argument("Quantity must be positive");
//         }
//         std::shared_ptr<Order> ord = orderFactory->createOrder(id, stock.getPrice(), quantity, stock.getName());
//         ord->setOrderType(OrderType::SELL);
//         {
//             std::lock_guard<std::mutex> lock(ordersMutex);
//             orders.push_back(ord);
//         }
//         orderBook->addOrder(ord);
//         std::lock_guard<std::mutex> lock(::coutMutex);
//         std::cout << "Trader " << id << " adding SELL order for " << stock.getName() << "\n";
//     } catch (const std::exception& e) {
//         std::lock_guard<std::mutex> lock(::coutMutex);
//         std::cerr << "Exception in sell: " << e.what() << std::endl;
//     }
// }

// void Trader::trade(double buyThreshold, double sellThreshold, int buyQuantity, int sellQuantity) {
//     try {
//         if (orderFactory == nullptr || orderBook == nullptr) {
//             throw std::runtime_error("Order factory or order book not initialized");
//         }
//         if (buyQuantity <= 0 || sellQuantity <= 0) {
//             throw std::invalid_argument("Quantities must be positive");
//         }
//         for (const Stock& stock : stocks) {
//             std::lock_guard<std::mutex> lock(::coutMutex);
//             std::cout << "Trader " << id << " evaluating stock " << stock.getName() 
//                       << " price " << stock.getPrice() << " buyThreshold " << buyThreshold 
//                       << " sellThreshold " << sellThreshold << "\n";
//             if (stock.getPrice() < buyThreshold) {
//                 std::cout << "Trader " << id << " creating BUY order for " << stock.getName() 
//                           << " quantity " << buyQuantity << "\n";
//                 std::shared_ptr<Order> ord = orderFactory->createOrder(id, stock.getPrice(), buyQuantity, stock.getName());
//                 ord->setOrderType(OrderType::BUY);
//                 {
//                     std::lock_guard<std::mutex> lock(ordersMutex);
//                     orders.push_back(ord);
//                 }
//                 orderBook->addOrder(ord);
//                 std::cout << "Trader " << id << " adding BUY order for " << stock.getName() << "\n";
//             } else if (stock.getPrice() > sellThreshold) {
//                 std::cout << "Trader " << id << " creating SELL order for " << stock.getName() 
//                           << " quantity " << sellQuantity << "\n";
//                 std::shared_ptr<Order> ord = orderFactory->createOrder(id, stock.getPrice(), sellQuantity, stock.getName());
//                 ord->setOrderType(OrderType::SELL);
//                 {
//                     std::lock_guard<std::mutex> lock(ordersMutex);
//                     orders.push_back(ord);
//                 }
//                 orderBook->addOrder(ord);
//                 std::cout << "Trader " << id << " adding SELL order for " << stock.getName() << "\n";
//             }
//         }
//     } catch (const std::exception& e) {
//         std::lock_guard<std::mutex> lock(::coutMutex);
//         std::cerr << "Exception in trade: " << e.what() << std::endl;
//     }
// }

// void Trader::addOrder(std::shared_ptr<Order> order) {
//     std::lock_guard<std::mutex> lock(ordersMutex);
//     orders.push_back(order);
// }

// int Trader::nextId = 0;

// } // namespace StockTradingSystem



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