//
// Created by wangheng on 2020/5/8.
//

#ifndef CPP_PRIMER_EX15_03_H
#define CPP_PRIMER_EX15_03_H

#include <iostream>

class Quote {
public:
    Quote() = default;
    Quote(const std::string& book, double sales_price) :
        bookNo(book), price(sales_price) {}
    std::string isbn() const { return bookNo; }
    virtual double net_price(std::size_t n) const { return n * price; }
    virtual void debug() const ;
    virtual ~Quote() = default;

private:
    std::string bookNo;

protected:
    double price = 0.0;
};

void Quote::debug() const {
    std::cout << "data member of this class\n"
                 << "bookNo = " << bookNo << " "
                 << "price = " << price << std::endl;
}
#endif //CPP_PRIMER_EX15_03_H
