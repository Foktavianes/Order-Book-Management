# Order-Book-Management

Code folder contains several file which is needed to maintain order book, such as oredr.h, order_manager.h, etc.

order_manager_v1.cpp and order_manager_v2.cpp both trying to handle the new order in different ways. order_manager_v1.cpp handles the order by simply adding and sorting the vector afterwards whereas order_manager_v2.cpp utilizing binary search to check whether the order with same order id already exist in order book or not. Then, It will utilize lower bound to find the position for insertion for new order which means there is no need to do sorting after every insertion

The pdf file explains the time complexity of the code and how each versions maintain the order priority from coming orders.
