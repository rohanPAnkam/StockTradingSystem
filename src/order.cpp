// #include "../include/order.h"

// #include <algorithm>
// #include <stdexcept>
// #include <iostream>

// // #include <memory>

// // namespace std {
// //     template <typename T, typename... Args>
// //     unique_ptr<T> make_unique(Args&&... args) {
// //         return unique_ptr<T>(new T(std::forward<Args>(args)...));
// //     }
// // }

// using namespace StockTradingSystem;

// Order::Order(int id, double p, int q, const std::string& s) 
//     : traider_id{id}, price{p}, quantity{q}, stockName(s), timestamp(std::time(nullptr)), ordertype(OrderType::BUY) {
// }

// Order::~Order() {

// }

// int Order::getTraider_id() const {
// 	return traider_id;
// }

// double Order::getPrice() const {
// 	return price;
// }

// std::string Order::getStockName() const
// {
//     return stockName;
// }

// int Order::getQuantity() const {
// 	return quantity;
// }

// std::time_t Order::getTimestamp() const {
// 	return timestamp;
// }

// void Order::reduceQuantity(int amount) {
// 	if (amount > 0 && amount <= quantity) {
// 		quantity -= amount;
//     }
//     else {
//         throw std::out_of_range{"Amount out of range."};
//     }
// }

// OrderType Order::getOrdertype() const {
//     	return ordertype;
// }

// void Order::setOrderType(OrderType type) {
//     	ordertype = type;
// }

// std::string MarketOrder::getOrderType() const
// {
// 	return "Market Order";
// }
 
// std::string LimitOrder::getOrderType() const
// {
// 	return "Limit Order";
// }

// OrderFactory::~OrderFactory()
// {
// }

// std::unique_ptr<Order> MarketOrderFactory::createOrder(int trader_id, double price, int quantity, const std::string& stockName) {
//     	return std::make_unique<MarketOrder>(trader_id, price, quantity, stockName);
// }

// std::unique_ptr<Order> LimitOrderFactory::createOrder(int trader_id, double price, int quantity, const std::string& stockName) {
//     	return std::make_unique<LimitOrder>(trader_id, price, quantity, stockName);
// }

// OrderMatchingStrategy::~OrderMatchingStrategy()
// {
// }

// // void PriceTimeOrderMatchingStrategy::matchOrders(std::vector<std::shared_ptr<Order>>& buyOrders, std::vector<std::shared_ptr<Order>>& sellOrders) {
// //     	std::vector<std::shared_ptr<Order>> matchedOrders;

// //     	for (auto sellOrder = sellOrders.begin(); sellOrder != sellOrders.end(); ++sellOrder) {
// //         	for (auto it = buyOrders.begin(); it != buyOrders.end();) {
// //             		if ((*sellOrder)->getPrice() <= (*it)->getPrice()) {
// //                 		matchedOrders.push_back(*it);
// //                 		it = buyOrders.erase(it); // Remove the matched buy order
// //             		} else {
// //                 		++it;
// //             		}
// //         	}
// //     	}

// //     	// Update the buyOrders vector with remaining unmatched orders
// //     	buyOrders.insert(buyOrders.end(), matchedOrders.begin(), matchedOrders.end());
// // }



// void PriceTimeOrderMatchingStrategy::matchOrders(std::vector<std::shared_ptr<Order>>& buyOrders, 
//                                                 std::vector<std::shared_ptr<Order>>& sellOrders) {
//     std::vector<std::shared_ptr<Order>> remainingBuyOrders;
//     for (auto& sellOrder : sellOrders) {
//         for (auto it = buyOrders.begin(); it != buyOrders.end();) {
//             if ((*it)->getPrice() >= sellOrder->getPrice()) {
//                 int tradeQuantity = std::min((*it)->getQuantity(), sellOrder->getQuantity());
//                 std::cout << "Matched: Buy ID " << (*it)->getTraider_id() << " with Sell ID " 
//                           << sellOrder->getTraider_id() << " for " << tradeQuantity << " shares of " 
//                           << sellOrder->getStockName() << " at " << sellOrder->getPrice() << "\n";
//                 (*it)->reduceQuantity(tradeQuantity);
//                 sellOrder->reduceQuantity(tradeQuantity);
//                 if ((*it)->getQuantity() > 0) {
//                     remainingBuyOrders.push_back(*it);
//                 }
//                 if (sellOrder->getQuantity() == 0) {
//                     break; // Sell order fulfilled
//                 }
//                 it = buyOrders.erase(it);
//             } else {
//                 ++it;
//             }
//         }
//     }
//     buyOrders = remainingBuyOrders; // Update with remaining buy orders
// }



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

    for (auto sellIt = sellOrders.begin(); sellIt != sellOrders.end();) {
        if ((*sellIt)->getQuantity() <= 0) {
            sellIt = sellOrders.erase(sellIt);
            continue;
        }
        for (auto buyIt = buyOrders.begin(); buyIt != buyOrders.end();) {
            if ((*buyIt)->getQuantity() <= 0) {
                buyIt = buyOrders.erase(buyIt);
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
                    // Only add buy order to remaining if it has quantity left
                    if ((*buyIt)->getQuantity() > 0) {
                        remainingBuyOrders.push_back(*buyIt);
                    }
                }
                buyIt = buyOrders.erase(buyIt); // Remove buy order from processing
                if ((*sellIt)->getQuantity() <= 0) break; // Exit inner loop if sell order is fully matched
            } else {
                remainingBuyOrders.push_back(*buyIt);
                ++buyIt;
            }
        }
        // Add sell order to remaining if it has quantity left
        if ((*sellIt)->getQuantity() > 0) {
            remainingSellOrders.push_back(*sellIt);
        }
        sellIt = sellOrders.erase(sellIt); // Remove sell order from processing
    }

    // Move remaining orders back to input vectors
    buyOrders.clear();
    sellOrders.clear();
    buyOrders = std::move(remainingBuyOrders);
    sellOrders = std::move(remainingSellOrders);
}

