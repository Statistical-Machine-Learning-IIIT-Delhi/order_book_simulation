#include "trade.hpp"
#include <unordered_map>

class OrderBook{
private:
    struct OrderEntry{
        OrderPointer order_{nullptr};
        OrderPointers::iterator location_;
    };

    std::map<Price, OrderPointers, std::greater<Price>> bids_;
    std::map<Price, OrderPointers, std::less<Price>> asks_;
    std::unordered_map<OrderId, OrderEntry> orders_;


};


int main(){
    std::cout << "============================ TEST RUN =============================" << '\n';
    return 0;
}
