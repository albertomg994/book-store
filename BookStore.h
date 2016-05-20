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
     * Complexity: O(1)
     * @returns true if book is present in the system, even if it is out of stock
     */
    bool has_book(BookTitle bt) const {
        return _books.contains(bt);
    }
};

#endif /* BookStore_h */
