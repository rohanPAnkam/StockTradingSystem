#ifndef STOCK_TRADING_SYSTEM_ORDER_H
#define STOCK_TRADING_SYSTEM_ORDER_H

#include <string>
#include <memory>
#include <vector>
#include <ctime>
#include <iostream>
#include <mutex>

extern std::mutex coutMutex;

namespace StockTradingSystem {
	enum OrderType { BUY, SELL };
	class Order {
		public:
			Order(int, double, int, const std::string&);
			virtual ~Order();
			virtual std::string getOrderType() const = 0;
			int getTraider_id() const;
			double getPrice() const;
			int getQuantity() const;  
			std::string getStockName() const; // New method
			std::time_t getTimestamp() const;
			void reduceQuantity(int);
			OrderType getOrdertype() const;
			void setOrderType(OrderType);
		private:
			int traider_id;
			double price;
			std::string stockName; // New field
			int quantity;
			std::time_t timestamp;
			OrderType ordertype;
	};

	class MarketOrder : public Order  {
		public:
			MarketOrder(int trader_id, double price, int quantity, const std::string& stockName) : Order(trader_id, price, quantity, stockName) {}
			std::string getOrderType() const override;
	};

	class LimitOrder : public Order  {
		public:
			LimitOrder(int trader_id, double price, int quantity, const std::string& stockName) : Order(trader_id, price, quantity, stockName) {}
			std::string getOrderType() const override;
	};

	class OrderFactory {
		public:
			virtual std::unique_ptr<Order> createOrder(int, double, int, const std::string&) = 0;
			virtual ~OrderFactory();
	};

	class MarketOrderFactory : public OrderFactory {
		public:
			std::unique_ptr<Order> createOrder(int, double, int, const std::string&) override;
	};

	class LimitOrderFactory : public OrderFactory {
		public:
			std::unique_ptr<Order> createOrder(int, double, int, const std::string&) override;
	};

	class OrderMatchingStrategy {
		public:
			virtual void matchOrders(std::vector<std::shared_ptr<Order> >&, std::vector<std::shared_ptr<Order> >&) = 0;
			virtual ~OrderMatchingStrategy();
	};

	class PriceTimeOrderMatchingStrategy : public OrderMatchingStrategy {
		public:
			void matchOrders(std::vector<std::shared_ptr<Order> >&, std::vector<std::shared_ptr<Order> >&) override;
	};

}

#endif
