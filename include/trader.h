// #ifndef STOCK_TRADING_SYSTEM_TRADER_H
// #define STOCK_TRADING_SYSTEM_TRADER_H

// #include "stock.h"
// #include "order.h"
// #include "orderBook.h"

// #include <string>

// namespace StockTradingSystem {

// // class TraderException : public std::exception {
// // 	public:
// //     	TraderException(const std::string&);
// //     	// virtual const char* what() const noexcept override;
// // 		virtual const char* what() const _NOEXCEPT;
// // 	private:
// //     	std::string message;
// // };

// class TraderException : public std::exception {
// public:
//     TraderException(const std::string& msg) : message(msg) {}
//     virtual const char* what() const noexcept override {
//         return message.c_str();
//     }
// private:
//     std::string message;
// };


// class Trader {
// 	public:
// 		Trader();
// 		Trader(const std::string&);
// 		Trader(const std::string&, const std::vector<Stock>&, OrderFactory*, OrderBook*);
// 		void buy(const Stock&, int);
// 		void sell(const Stock&, int);
// 		void trade(double, double, int, int);
// 		int getID() const;
// 		const std::vector<std::shared_ptr<Order> >& getOrders() const;
// 		void addStock(const Stock&);
// 		void addOrder(std::shared_ptr<Order>);
// 		std::vector<Stock> getStocks() const;
// 		~Trader();
// 	private:
// 		static int id_counter;
// 		int id;
// 		std::string name;
// 		std::vector<Stock> stocks;
// 		OrderFactory* orderFactory;
// 		OrderBook* orderBook;
// 		std::vector<std::shared_ptr<Order> > orders;
// };

// } 

// #endif


// #ifndef STOCK_TRADING_SYSTEM_TRADER_H
// #define STOCK_TRADING_SYSTEM_TRADER_H

// #include "stock.h"
// #include "order.h"
// #include "orderBook.h"
// #include <string>
// #include <mutex>

// namespace StockTradingSystem {

// class TraderException : public std::exception {
// public:
//     TraderException(const std::string& msg) : message(msg) {}
//     virtual const char* what() const noexcept override {
//         return message.c_str();
//     }
// private:
//     std::string message;
// };

// class Trader {
// public:
//     Trader();
//     Trader(const std::string&);
//     Trader(const std::string&, const std::vector<Stock>&, OrderFactory*, OrderBook*);
//     void buy(const Stock&, int);
//     void sell(const Stock&, int);
//     void trade(double, double, int, int);
//     int getID() const;
//     const std::vector<std::shared_ptr<Order>>& getOrders() const;
//     void addStock(const Stock&);
//     void addOrder(std::shared_ptr<Order>);
//     std::vector<Stock> getStocks() const;
//     ~Trader();
// private:
//     static int id_counter;
//     int id;
//     std::string name;
//     std::vector<Stock> stocks;
//     OrderFactory* orderFactory;
//     OrderBook* orderBook;
//     std::vector<std::shared_ptr<Order>> orders;
//     std::mutex ordersMutex; // Add mutex for thread safety
// };

// } 

// #endif



#ifndef STOCK_TRADING_SYSTEM_TRADER_H
#define STOCK_TRADING_SYSTEM_TRADER_H

#include "order.h"
#include "stock.h"
#include "orderBook.h"
#include <string>
#include <vector>
#include <mutex>

extern std::mutex coutMutex; // Declare extern mutex in global scope

namespace StockTradingSystem {

class Trader {
public:
    Trader(const std::string&, const std::vector<Stock>&, OrderFactory*, OrderBook*);
    ~Trader();
    std::string getName() const;
    int getID() const;
    void addStock(const Stock&);
    void buy(const Stock&, int);
    void sell(const Stock&, int);
    void trade(double, double, int, int);
    void addOrder(std::shared_ptr<Order>);
private:
    std::string traderName;
    std::vector<Stock> stocks;
    std::vector<std::shared_ptr<Order>> orders;
    OrderFactory* orderFactory;
    OrderBook* orderBook;
    int id;
    static int nextId;
    std::mutex ordersMutex;
};

} // namespace StockTradingSystem

#endif