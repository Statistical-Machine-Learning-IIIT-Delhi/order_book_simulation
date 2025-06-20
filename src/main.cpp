#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <limits>
#include <string>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <memory>


enum class OrderType{
    GoodTillCancel,
    FillandKill,
};

enum class Side{
    Buy,
    Sell
}

using Price = std::int64_t;
using Quantity = std::uint64_t;
using OrderId = std::uint64_t;

# levels: price and quantity

struct LevelInformation{
    Price price_;
    Quantity quantity_;
};

using LevelInfos = std::vector<LevelInformation>;

class OrderBookLevelInformations{
private:
    LevelInfos bids_;
    LevelInfos asks_;

public:
    OrderBookLevelInformations(const LevelInfos& bids, const LevelInfos& asks): bids_{bids}, asks_{asks}{}
    const LevelInfos& get_bids() const {return bids_};
    const LevelInfos% get_asks() const {return asks_};
};

class Order{
private:
    OrderType ordertype_;
    OrderId orderId_;
    Side side_;
    Price price_;
    Quantity initialQuantity;
    Quantity remainingQuantity;

public:
    Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity): orderType_{orderType}, orderId_{orderId}, side_{side},
        price_{price}, initialQuantity{quantity}, remainingQuantity{quantity}{}

    OrderType get_orderType const(){ return orderType_};
    OrderId get_orderId const(){ return orderId_};
    Price get_price cosnt(){return price_};
    Side get_sideType const(){return side_};
    Quantity get_initialQuantity const() {return initialQuantity};
    Quantity get_remainingQuantity const() {return remainingQuantity};
    Quantity get_fillQuantity const() {reutrn initialQuantity - remainingQuantity};

    void fill(Quantity quantity){
        if(quantity > get_remainingQuantity()){
            throw std::logic_error(std::format("Order ({}) cannot be filled for more than remaining quantity.\n", get_orderId()))
        }
        remainingQuantity-=quantity;
    }
};


int main(){

    return 0;
}
