// #include "include/orderBook.h"
// #include "include/trader.h"
// #include <iostream>
// #include <vector>
// #include <thread>
// #include <mutex>
// #include <numeric>

// using namespace StockTradingSystem;

// void traderFunction(Trader& trader, OrderBook& orderBook, OrderFactory* factory) {
//     std::vector<Stock> stocks = {
//         Stock(145.50, "AAPL"), Stock(420.75, "TSLA"), Stock(280.20, "MSFT")
//     };
//     for (const auto& stock : stocks) {
//         trader.addStock(stock);
//     }
//     int quantity = 25;

//     // Calculate average price for mean-reversion strategy
//     double totalPrice = std::accumulate(stocks.begin(), stocks.end(), 0.0,
//         [](double sum, const Stock& stock) { return sum + stock.getPrice(); });
//     double avgPrice = totalPrice / stocks.size();

//     // Create baseline orders for all stocks using mean-reversion
//     for (const auto& stock : stocks) {
//         if (stock.getPrice() < avgPrice) {
//             trader.buy(stock, quantity);
//         } else {
//             trader.sell(stock, quantity);
//         }
//     }

//     // Add threshold-based trading
//     trader.trade(200, 400, 12, 13);
// }

// int main() {
//     OrderBook orderBook;
//     orderBook.setStrategy(std::make_unique<PriceTimeOrderMatchingStrategy>());

//     MarketOrderFactory factory;
//     std::vector<std::unique_ptr<Trader>> traders; // Store unique_ptr<Trader>
//     std::vector<std::thread> traderThreads;
//     int numTraders = 5;
//     for (int i = 0; i < numTraders; ++i) {
//         traders.push_back(std::make_unique<Trader>("Trader " + std::to_string(i + 1), 
//                                                   std::vector<Stock>{}, &factory, &orderBook));
//         traderThreads.emplace_back(traderFunction, std::ref(*traders.back()), 
//                                   std::ref(orderBook), &factory);
//     }

//     for (auto& thread : traderThreads) {
//         thread.join();
//     }

//     orderBook.matchOrders();
//     orderBook.printOrderBook();

//     return 0;
// }


// #include "include/orderBook.h"
// #include "include/trader.h"
// #include <iostream>
// #include <vector>
// #include <thread>
// #include <mutex>
// #include <numeric>

// using namespace StockTradingSystem;

// void traderFunction(Trader& trader, OrderBook& orderBook, OrderFactory* factory) {
//     std::vector<Stock> stocks = {
//         Stock(145.50, "AAPL"), Stock(420.75, "TSLA"), Stock(280.20, "MSFT")
//     };
//     for (const auto& stock : stocks) {
//         trader.addStock(stock);
//     }
//     int quantity = 25;

//     // Calculate average price for mean-reversion strategy
//     double totalPrice = std::accumulate(stocks.begin(), stocks.end(), 0.0,
//         [](double sum, const Stock& stock) { return sum + stock.getPrice(); });
//     double avgPrice = totalPrice / stocks.size();
//     std::cout << "Trader " << trader.getID() << " average price: " << avgPrice << "\n";

//     // Create baseline orders for all stocks using mean-reversion
//     for (const auto& stock : stocks) {
//         if (stock.getPrice() < avgPrice) {
//             std::cout << "Trader " << trader.getID() << " creating BUY order for " 
//                       << stock.getName() << " at " << stock.getPrice() << "\n";
//             trader.buy(stock, quantity);
//         } else {
//             std::cout << "Trader " << trader.getID() << " creating SELL order for " 
//                       << stock.getName() << " at " << stock.getPrice() << "\n";
//             trader.sell(stock, quantity);
//         }
//     }

//     // Add threshold-based trading
//     trader.trade(200, 400, 12, 13);
// }

// int main() {
//     OrderBook orderBook;
//     orderBook.setStrategy(std::make_unique<PriceTimeOrderMatchingStrategy>());

//     MarketOrderFactory factory;
//     std::vector<std::unique_ptr<Trader>> traders;
//     std::vector<std::thread> traderThreads;
//     int numTraders = 5;
//     for (int i = 0; i < numTraders; ++i) {
//         traders.push_back(std::make_unique<Trader>("Trader " + std::to_string(i + 1), 
//                                                   std::vector<Stock>{}, &factory, &orderBook));
//         traderThreads.emplace_back(traderFunction, std::ref(*traders.back()), 
//                                   std::ref(orderBook), &factory);
//     }

//     for (auto& thread : traderThreads) {
//         thread.join();
//     }

//     orderBook.matchOrders();
//     orderBook.printOrderBook();

//     return 0;
// }



#include "include/orderBook.h"
#include "include/trader.h"
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <numeric>

using namespace StockTradingSystem;

std::mutex coutMutex; // Global mutex for synchronized logging

void traderFunction(Trader& trader, OrderBook& orderBook, OrderFactory* factory) {
    std::vector<Stock> stocks = {
        Stock(145.50, "AAPL"), Stock(420.75, "TSLA"), Stock(280.20, "MSFT")
    };
    for (const auto& stock : stocks) {
        trader.addStock(stock);
    }
    int quantity = 25;

    // Calculate average price for mean-reversion strategy
    double totalPrice = std::accumulate(stocks.begin(), stocks.end(), 0.0,
        [](double sum, const Stock& stock) { return sum + stock.getPrice(); });
    double avgPrice = totalPrice / stocks.size();
    {
        std::lock_guard<std::mutex> lock(::coutMutex);
        std::cout << "Trader " << trader.getID() << " average price: " << avgPrice << "\n";
    }

    // Create baseline orders for all stocks using mean-reversion
    for (const auto& stock : stocks) {
        if (stock.getPrice() < avgPrice) {
            {
                std::lock_guard<std::mutex> lock(::coutMutex);
                std::cout << "Trader " << trader.getID() << " creating BUY order for " 
                          << stock.getName() << " at " << stock.getPrice() << "\n";
            }
            trader.buy(stock, quantity);
        } else {
            {
                std::lock_guard<std::mutex> lock(::coutMutex);
                std::cout << "Trader " << trader.getID() << " creating SELL order for " 
                          << stock.getName() << " at " << stock.getPrice() << "\n";
            }
            trader.sell(stock, quantity);
        }
    }

    // Add threshold-based trading
    trader.trade(500, 400, 12, 13); // Increased buy threshold to 500 for TSLA buy orders
}

int main() {
    OrderBook orderBook;
    orderBook.setStrategy(std::make_unique<PriceTimeOrderMatchingStrategy>());

    MarketOrderFactory factory;
    std::vector<std::unique_ptr<Trader>> traders;
    std::vector<std::thread> traderThreads;
    int numTraders = 5;
    for (int i = 0; i < numTraders; ++i) {
        traders.push_back(std::make_unique<Trader>("Trader " + std::to_string(i + 1), 
                                                  std::vector<Stock>{}, &factory, &orderBook));
        traderThreads.emplace_back(traderFunction, std::ref(*traders.back()), 
                                  std::ref(orderBook), &factory);
    }

    for (auto& thread : traderThreads) {
        thread.join();
    }

    orderBook.matchOrders();
    orderBook.printOrderBook();

    return 0;
}