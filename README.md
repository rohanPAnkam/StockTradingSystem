## Stock Trading Simulator
A multithreaded C++ application simulating a stock exchange, featuring automated order creation and matching using advanced trading strategies.
- Overview:  This project implements a stock trading system where traders create buy and sell orders based on predefined strategies. Orders are managed in an order book and matched using the Price-Time Matching Strategy, ensuring efficient and fair trade execution. The system supports concurrent trading operations, making it scalable and robust.

### Features

1. Automated Trading Strategies:
   1. Mean-Reversion: Traders create orders based on stock prices relative to their average, buying low and selling high.
   2. Threshold-Based: Orders are generated based on price thresholds for buying or selling.
2. Price-Time Matching Strategy: Matches buy and sell orders prioritizing price and order timestamp.
3. Multithreaded Architecture: Supports concurrent trader operations with thread-safe order book management.
4. Duplicate Order Prevention: Ensures unique orders using a custom comparator.
5. Synchronized Logging: Thread-safe console output for clear order tracking.

### Prerequisites

- C++17 or higher
- CMake 3.10 or higher
- A C++ compiler (e.g., g++, clang++)
- POSIX threads support (pthread)
