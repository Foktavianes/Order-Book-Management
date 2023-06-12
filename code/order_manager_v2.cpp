#include "order_manager.h"

#include <algorithm>
#include <iostream>

void OrderManager::Add(int price, int qty, const std::string& order_id, bool is_sell) {
    Order new_order(price, qty, order_id, is_sell);
    // Check if the order already exists using binary search to ensure that the order with same order_id is not added to order book
    auto checker = std::binary_search(orders_.begin(), orders_.end(), new_order,
                                 [](const Order& order1, const Order& order2) {
                                     return order1.order_id < order2.order_id;
                                 });
    
    // If the order already exists, return without adding it
    if (checker == true)
        return;
    
    // we can use either std::upper_bound or std::lower_bound. In this case, I will just use lower_bound. 
    // The difference is that std::lower_bound returns first element in the range that is not less than the given value 
    // while std::upper_bound returns first element in the range that is greater than the given value.
    
    // auto insertion_pos = std::upper_bound(orders_.begin(), orders_.end(), new_order,
    //                                   [](const Order& order1, const Order& order2) {
    //                                       return order1.price < order2.price || (order1.price == order2.price && order1.order_id < order2.order_id);
    //                                   });


    // Find the insertion position using lower_bound based on price. The body part of the lambda function ensure the vector is sorted in ascending manner.
    // This is because upper_bound and lower_bound work on sorted vector to ensure there is not incorrect results or undefined behavior.
    auto insertion_pos = std::lower_bound(orders_.begin(), orders_.end(), new_order,
                                          [](const Order& order1, const Order& order2) {
                                              return order1.price < order2.price || (order1.price == order2.price && order1.order_id < order2.order_id);
                                          });
    
    // Insert the new order at the determined position
    orders_.insert(insertion_pos, new_order);
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

