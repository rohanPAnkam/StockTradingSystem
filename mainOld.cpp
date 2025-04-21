#include "include/orderBook.h" 
#include "include/trader.h"
//https://github.com/NalbandyanElmira/StockTradingSystem/tree/main
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <curl/curl.h>
#include <numeric>
// #include <nlohmann/json.hpp>

using namespace StockTradingSystem;


// using json = nlohmann::json;

// Callback for libcurl to store response
// size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
//     s->append((char*)contents, size * nmemb);
//     return size * nmemb;
// }

// std::vector<Stock> fetchStockData(const std::vector<std::string>& symbols) {
//     std::vector<Stock> stocks;
//     CURL* curl = curl_easy_init();
//     std::string response;

//     if (curl) {
//         for (const auto& symbol : symbols) {
//             std::string url = "https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol=" + symbol + "&apikey=55LCZRJ1ZC9BBMHP";
//             curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
//             curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//             curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

//             CURLcode res = curl_easy_perform(curl);
//             if (res == CURLE_OK) {
//                 json j = json::parse(response);
//                 double price = j["Global Quote"]["05. price"].get<double>();
//                 stocks.emplace_back(price, symbol);
//             }
//             response.clear();
//         }
//         curl_easy_cleanup(curl);
//     }
//     return stocks;
// }

// void priceUpdateThread(std::vector<Stock>& stocks, const std::vector<std::string>& symbols) {
//     while (true) {
//         stocks = fetchStockData(symbols);
//         std::this_thread::sleep_for(std::chrono::minutes(1));
//     }
// }

// Define a trader function to simulate traders placing orders
// void traderFunction(Trader& trader, OrderBook& orderBook) {
//     Stock someStock(145, "a");
//     Stock anotherStock(154, "b");
//     trader.addStock(someStock);
//     trader.addStock(anotherStock);
//     int quantity = 25;

//     // Place buy and sell orders
//     std::shared_ptr<Order> buyOrder = std::make_shared<MarketOrder>(trader.getID(), someStock.getPrice(), quantity);
//     buyOrder->setOrderType(OrderType::BUY);
//     std::shared_ptr<Order> sellOrder = std::make_shared<MarketOrder>(trader.getID(), anotherStock.getPrice(), quantity);
//     sellOrder->setOrderType(OrderType::SELL);
    
//     trader.trade(150, 160, 12, 13);

//     // Add orders to the order book
//     orderBook.addOrder(buyOrder);
//     orderBook.addOrder(sellOrder);
// }


// void traderFunction(Trader& trader, OrderBook& orderBook) {

//     // std::vector<std::string> symbols = {"AAPL", "TSLA", "MSFT"};
//     // std::vector<Stock> stocks = fetchStockData(symbols);
//     // for (const auto& stock : stocks) {
//     //     trader.addStock(stock);
//     // }

//     int quantity = 25;
//     std::vector<Stock> stocks = {
//         Stock(145.50, "AAPL"), Stock(420.75, "TSLA"), Stock(280.20, "MSFT")
//     };
//     for (const auto& stock : stocks) {
//         trader.addStock(stock);
//         std::shared_ptr<Order> order = std::make_shared<MarketOrder>(trader.getID(), stock.getPrice(), quantity);
//     }

//     // Optional: Add threshold-based trading
//     trader.trade(150, 300, 12, 13);
// }


void traderFunction(Trader& trader, OrderBook& orderBook) {
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

    // Create baseline orders for all stocks using mean-reversion
    for (const auto& stock : stocks) {
        std::shared_ptr<Order> order;
        bool isBuy = stock.getPrice() < avgPrice; // Buy if below average, sell if above
        order = std::make_shared<MarketOrder>(trader.getID(), stock.getPrice(), quantity);
        order->setOrderType(isBuy ? OrderType::BUY : OrderType::SELL);
        trader.getOrders().push_back(order);
        orderBook.addOrder(order);
    }

    // Add threshold-based trading
    trader.trade(200, 400, 12, 13); // Adjusted thresholds to cover more stocks
}


int main() {
    OrderBook orderBook;
    orderBook.setStrategy(new PriceTimeOrderMatchingStrategy());

    std::vector<std::thread> traderThreads;
    int numTraders = 5;
    for (int i = 0; i < numTraders; ++i) {
        Trader trader("Trader " + std::to_string(i + 1));
        traderThreads.emplace_back(traderFunction, std::ref(trader), std::ref(orderBook));
    }

    for (auto& thread : traderThreads) {
        thread.join();
    }

    orderBook.matchOrders();
    orderBook.printOrderBook();

    return 0;
}