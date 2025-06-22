#include "trade.hpp"
#include <unordered_map>

class OrderBook{
private:
    struct OrderEntry{
        OrderPointer            order_{nullptr};
        OrderPointers::iterator location_;
    };

    std::map<Price, OrderPointers, std::greater<Price>> bids_;
    std::map<Price, OrderPointers, std::less<Price>>    asks_;
    std::unordered_map<OrderId, OrderEntry>             orders_;

    bool can_match(Side side, Price price) const {
        if(side == Side::Buy){
            if(asks_.empty()){
                return false;
            }

            const auto &[bestAsk_, _] = *asks_.begin();
            return price>=bestAsk_;
        } else{
            if(bids_.empty())
                return false;
            const auto& [bestBid_, _] = *bids_.begin();
            return price<=bestBid_;
        }
    }

    Trades match_orders(){
        Trades trades;
        trades.reserve(orders_.size());
        while(true){
            if(bids_.empty() || asks_.empty()) break;

            auto &[bidPrice, bids] = *bids_.begin();
            auto &[askPrice, asks] = *asks_.begin();

            if(bidPrice < askPrice) break;

            // - - - Order pointers. Trying to find a match in the sorted map.
            while(bids.size() && asks.size()){
                auto bid = bids.front();
                auto ask = asks.front();

                Quantity quantity  = std::min(bid->get_remainingQuantity(), ask->get_remainingQuantity());

                // - - - matching orders and filling them up.
                bid->fill(quantity);
                ask->fill(quantity);

                if(bid->is_filled()){
                    bids.pop_front();
                    orders_.erase(bid->get_orderId());
                }

                if(ask->is_filled()){
                    asks.pop_front();
                    orders_.erase(ask->get_orderId());
                }
                if(asks.empty()) asks_.erase(askPrice);
                if(bids.empty()) bids_.erase(bidPrice);

                // - - - Generate and mark the trade
                // NOTE: Casting Trade and TradeInfo to let the compiler know what we are constructing
                trades.push_back(Trade{TradeInfo{ bid->get_orderId(), bid->get_price(), quantity},
                    TradeInfo{ask->get_orderId(), ask->get_price(), quantity}});
            }
        }

        if(!bids_.empty()){
            auto& [_, bids] = *bids_.begin();
            auto& order = bids.front();
            if(order->get_orderType() == OrderType::FillandKill){
                // - - - Implement cancel order here
            }
        }

        if(!asks_.empty()){
            auto& [_, asks] = *asks_.begin();
            auto& order = asks.front();
            if(order->get_orderType() == OrderType::FillandKill){
                // - - - Implement cancel order here as well
            }
        }

        return trades;
    }

public:
    // - - - To implement in next dev run: modify_order, cancel_order
    Trades add_order(OrderPointer order){
        if(orders_.find(order->get_orderId()) != orders_.end())
            return {};

        OrderPointers::iterator itr;
        if(order->get_sideType() == Side::Buy){
            auto& orders = bids_[order->get_price()];
            orders.push_back(order);
            // - - - setting the itr
            itr = std::next(orders.begin(), orders.size() - 1);
        }
        else{
            auto& orders = asks_[order->get_price()];
            orders.push_back(order);
            // - - - setting the itr
            itr = std::next(orders.begin(), orders.size() - 1);
        }
        orders_.insert({order->get_orderId(), OrderEntry{order , itr}});
        return match_orders();
    }

    void cancel_order(); // - - - to cancel any bid or asks
    Trades modify_order(); // - - - literally cancel + new ;-;
};
