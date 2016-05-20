//
//  BookStore.h
//  T11-Venta-Libros
//
//  Created by Alberto Miedes on 20/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef BookStore_h
#define BookStore_h

#include "HashMap.h"
#include "Book.h"
#include "BestSellers.h"
#include "BookStoreExceptions.h"
#include <list>
#include <string>

using namespace std;

class BookStore {
private:
    
    HashMap<BookTitle, Book> _books;
    BestSellers _best_sellers;
    
public:
    /**
     * Adds new book to the system with 'uds' units, or adds 'uds' units
     * if the book already exists.
     * Complexity: O(..)
     *
     * @param bt Book title
     * @param uds Units to be added into stock
     */
    void new_book(BookTitle bt, unsigned int uds) {
        
        // try to find book
        HashMap<BookTitle, Book>::Iterator it = _books.find(bt);    // O(1)
        
        // if it's not present, add it to the system
        if (it != _books.end()) {
            _books.insert(bt, Book(bt, uds));                       // O(1)
            
            // we also have to update the best-sellers (maybe best-seller has 0 sales...)
            _best_sellers.update(_books[bt]);
        }
        
        // otherwise, add 'uds' units to its stock
        else {
            Book* b = &(it.value());                                // O(1)
            b->add_stock(uds);                                      // O(1)
        }
    }
    
    /**
     * Sell one unit of bt book
     * Complexity: O(?)
     *
     * @param bt Title of the book to be sold
     * @throws OutOfRangeException si el libro no tiene ejemplares.
     * @throws InvalidArgumentException si el libro no está dado de alta.
     */
    void buy(BookTitle bt) {
        
        HashMap<BookTitle, Book>::Iterator it = _books.find(bt);    // O(1)
        
        // if book is not present, throw exception
        if (it == _books.end()) throw InvalidArgumentException();
        
        // if book is out of stock, throw exception
        Book* b = &(it.value());
        if ( !(b->has_stock()) ) throw OutOfRangeException();
        
        // update book sales
        b->sell_one();                                              // O(1)
        
        // update best sellers
        _best_sellers.update(*b);                                   // O(?)
    }
    
    /**
     * Complexity: O(1)
     * @returns true if book is present in the system, even if it is out of stock
     */
    bool has_book(BookTitle bt) const {
        return _books.contains(bt);
    }
    
    /**
     * Devuelve el número de ejemplares de un libro x que hay disponibles en el
     * sistema.
     * Complexity: O(1)
     *
     * @throws InvalidArgumentException if book doesn't exist
     */
    unsigned get_stock(BookTitle bt) const {
        
        HashMap<BookTitle, Book>::ConstIterator it = _books.find(bt);
        
        // if book doesn't exist, throw exception
        if (it == _books.cend()) throw InvalidArgumentException();
        
        // return book stock
        return it.value().stock();
    }
};

#endif /* BookStore_h */
