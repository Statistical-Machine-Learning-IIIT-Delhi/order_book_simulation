#include "order.hpp"
#include <vector>

struct TradeInfo{
    OrderId     orderId_;
    Price       price_;
    Quantity    quantity_;
};


class Trade{
private:
    TradeInfo bidTrade_;
    TradeInfo askTrade_;
public:
    Trade(const TradeInfo& bidTrade, const TradeInfo& askTrade): bidTrade_{bidTrade}, askTrade_{askTrade}{}
    const TradeInfo& get_bidTrade() const {return bidTrade_;}
    const TradeInfo& get_askTrade() const {return askTrade_;}
};

using Trades = std::vector<Trade>;
