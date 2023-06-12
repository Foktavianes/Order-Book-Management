#include "order_manager.h"

#include <algorithm>
#include <iostream>

void OrderManager::Add(int price, int qty, const std::string& order_id, bool is_sell) {
    Order new_order(price, qty, order_id, is_sell);
    orders_.push_back(new_order); // add the new order to the vector

    // std::sort did not preserve the order of equal elements which is why it is better to use stable sort which preserve the order.
    // I also utilize lambda function here and put the orders as parameters. In first layer, I deciding the sorting based on price.
    // If the different orders have the same price, then sort the order based on the order_id.
    std::stable_sort(orders_.begin(), orders_.end(), [](const Order &order1, const Order &order2){ 
        return order1.price < order2.price || (order1.price == order2.price && order1.order_id < order2.order_id);
         });
}

void OrderManager::Update(const std::string& order_id, int updated_open_qty) {
    // Find the order_id that need to be updated
    auto search = std::find_if(orders_.begin(), orders_.end(), [&](const Order& order) {
        return order.order_id == order_id;
        });
    if (search != orders_.end()){
        (*search).open_qty = updated_open_qty;
        if (updated_open_qty == 0){ //if the updated_qty is, remove the order from the order book
            orders_.erase(search);
        }
    }
}

void OrderManager::PrintAllOrders() const {
    // Print all elements in the vector using std::for_each and a lambda function
    std::for_each(orders_.begin(), orders_.end(), [](const Order& orders) {
        std::cout << orders << "\n";
    });
    std::cout << std::endl;
}
