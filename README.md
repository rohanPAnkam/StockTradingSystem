The Stock Trading System project is a C++ application designed to simulate a stock trading environment. The system supports multiple traders who can buy and sell stocks, and it manages an order book for processing transactions. Here are its key components:

•	Trader : Represents a trader who places buy or sell orders.

•	Stock : Represents a stock with a price and name.

•	Order : A base class for all types of orders.

•	MarketOrder: Executes a buy/sell order at the current market price.

•	LimitOrder: Executes a buy/sell order at a specified price.

•	OrderFactory: Creates different types of orders.

•	OrderMatchingStrategy: Implements strategies for matching buy and
