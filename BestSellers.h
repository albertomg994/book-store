//
//  BestSellers.h
//  T11-Venta-Libros
//
//  Created by Alberto Miedes on 26/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef BestSellers_h
#define BestSellers_h

#include "TreeMap.h"
#include "Book.h"
#include <list>

/**
 * Simple class used to set order between books inside the
 * BestSellers class.
 */
class BSKey {
public:
    unsigned _sales;
    unsigned _saledate;
    
    BSKey(Book* b) {
        _sales = b->sales();
        _saledate = b->sale_date();
    }
    
    bool operator<(const BSKey &other) const {
        if (_sales < other._sales) return false;
        else if (_sales > other._sales) return true;
        else return (_saledate > other._saledate);
    }
    
    bool operator==(const BSKey &other) const {
        return (_sales == other._sales) && (_saledate == other._saledate);
    }
};

/**
 * Class used to keep track of most sold books inside the bookstore
 */
class BestSellers {
private:
    
    TreeMap<BSKey, Book*> _bestsellers;
    
public:
    
    /**
     * Adds b book to bestsellers data structure
     * Complexity: O(logN)
     */
    void add_book(Book* b) {
        if (b->sales() != 0) _bestsellers.insert(BSKey(b), b);
    }
    
    /**
     * Removes b book from bestsellers data structure.
     * Complexity: O(logN)
     */
    void remove_book(Book* b) {
        if (b->sales() != 0) _bestsellers.erase(BSKey(b));
    }
    
    /**
     * Returns a list with N top sold book titles. If n > available books,
     * returns all of them.
     * Complexity: O(n)
     *
     * @param n Max of books to return.
     * @return list with n most sold book titles
     */
    list<BookTitle> get_top_n(unsigned n) {
        
        list<BookTitle> ret;
        unsigned idx = 0;
        
        TreeMap<BSKey, Book*>::ConstIterator it = _bestsellers.cbegin();
        while (it != _bestsellers.cend() && idx < n) {
            ret.push_back((it.value())->title());
            it++;
            idx++;
        }
        return ret;
    }
};

#endif /* BestSellers_h */
