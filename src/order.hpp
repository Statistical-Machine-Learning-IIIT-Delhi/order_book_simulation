#include "includes.hpp"
#include "support_types/ordertype.hpp"
#include "support_types/sidetype.hpp"
#include "support_types/using.hpp"

// Levels: price and quantity

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
    const LevelInfos& get_bids() const {return bids_;}
    const LevelInfos& get_asks() const {return asks_;}
};

class Order{
private:
    OrderType orderType_;
    OrderId orderId_;
    Side side_;
    Price price_;
    Quantity initialQuantity;
    Quantity remainingQuantity;

public:
    Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity): orderType_{orderType}, orderId_{orderId}, side_{side},
        price_{price}, initialQuantity{quantity}, remainingQuantity{quantity}{}

    OrderType get_orderType () const {return orderType_;}
    OrderId get_orderId () const {return orderId_;}
    Price get_price () const {return price_;}
    Side get_sideType () const{return side_;}
    Quantity get_initialQuantity () const{return initialQuantity;}
    Quantity get_remainingQuantity () const{return remainingQuantity;}
    Quantity get_fillQuantity () const{return initialQuantity - remainingQuantity;}

    bool is_filled() const {return get_remainingQuantity() == 0;}

    void fill(Quantity quantity){
        if(quantity > get_remainingQuantity()){
            std::string error_message = fmt::format("Order ({}) cannot be filled for more than remaining quantity.\n", get_orderId());
            throw std::logic_error(error_message);
        }
        remainingQuantity-=quantity;
    }
};

using OrderPointer = std::shared_ptr<Order>;
using OrderPointers = std::list<OrderPointer>;
class OrderModify{
private:
    OrderId orderId_;
    Price price_;
    Quantity quantity_;
    Side side_;
public:
    OrderModify(OrderId orderId, Price price, Quantity quantity, Side side):orderId_{orderId},  price_{price}, quantity_(quantity), side_{side}{}

    OrderId         get_orderId () const {return orderId_;}
    Price           get_price () const {return price_;}
    Quantity        get_quantity() const {return quantity_;}
    Side            get_side() const {return side_;}
    OrderPointer    to_orderPointer(OrderType type) const {return std::make_shared<Order>(type, get_orderId(), get_side(), get_price() ,get_quantity());}
};
