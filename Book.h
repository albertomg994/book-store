//
//  Book.h
//  T11-Venta-Libros
//
//  Created by Alberto Miedes on 20/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef Book_h
#define Book_h

#include <string>

typedef std::string BookTitle;   // BookTitle type

/**
 * Book class
 */
class Book {
private:

    BookTitle _title;
    unsigned _stock;      // Number uf units currently available
    unsigned _sales;      // Number of units sold

public:

    // Constructor
    Book() {}
    Book(BookTitle t, unsigned units = 0) : _title(t), _stock(units), _sales(0) {}

    // Getters
    BookTitle title() const { return _title; }
    unsigned  stock() const { return _stock; }
    unsigned  sales() const { return _sales; }

    // Setters
    void set_stock(unsigned stock) { _stock = stock; }
    void set_sales(unsigned sales) { _sales = sales; }

    // Observers
    bool has_stock() const { return _stock > 0; }

    // Modifiers
    void sell_one() { _sales++; _stock--; }
    void add_stock(unsigned uds) { _stock += uds; }

    // The < operator is redefined this way so we can use it to retrieve
    // the 'best-sellers'
    bool operator< (const Book & other) {
        return (_sales < other._sales);
    }

};

#endif /* Book_h */
