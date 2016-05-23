//
//  BestSellersLineal.h
//  T11-Venta-Libros
//
//  Created by Alberto Miedes on 22/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef BestSellersLineal_h
#define BestSellersLineal_h

#include "Book.h"
#include <list>
#include <string>
#include <iostream>

#define BEST_SELLERS_SIZE 10

using namespace std;

/**
 * Best-sellers class
 */
class BestSellersLineal {
private:
    
    list<Book*> _bestsellers;
    
    /**
     * Returns iterator pointing to position where Book b should
     * be inserted, deleting in its way previous appearances of b,
     * in case they existed.
     * If b Book shouldn't be in best_sellers, returns _books.end()
     */
    list<Book*>::iterator find_place(Book* b) {
        
        // NOTA: b->sales() has already been updated()
        unsigned current_sales = b->sales();
        
        //cout << "a";
        
        // if book isn't iportant enough, return iterator pointing to end()
        if (!_bestsellers.empty() && (_bestsellers.back())->sales() > current_sales) {
            //cout << "b";
            return _bestsellers.end();
        }
        
        // find position where it belongs
        list<Book*>::iterator it = _bestsellers.begin();
        
        //cout << "c";
        
        while (it != _bestsellers.end() && current_sales > (*it)->sales()  ) {
            
            //cout << "d";
            
            // if we found previous appearance of this same book, erase it
            if ( (*it)->title() == b->title() ) {
                _bestsellers.erase(it);
                //cout << "e";
            }

            it++;
        }
        
        it--;
        
        // if list is full, kick the last one
        if (_bestsellers.size() == BEST_SELLERS_SIZE) {
            _bestsellers.pop_back();
            //cout << "f";
        }
        
        //cout << endl;
        
        // return iterator
        return it;
    }

public:
    
    /**
     *
     */
    void update(Book* b) {
        
        //cout << "bestsellers.size() = " << _bestsellers.size() << endl;
        
        if (_bestsellers.empty()) {
            _bestsellers.push_back(b);
        }
        
        list<Book*>::iterator it = find_place(b);
        
        if (it != _bestsellers.end()) {
            //cout << "Estoy insertando en bestsellers" << endl;
            _bestsellers.insert(it, b);
        }
        
        //cout << "bestsellers.size() = " << _bestsellers.size() << endl;
    }
    
    /**
     *
     */
    list<BookTitle> get_bestsellers() const {
        
        list<BookTitle> ret;
        
        list<Book*>::const_iterator it = _bestsellers.cbegin();
        while (it != _bestsellers.cend()) {
            ret.push_back((*it)->title());
            it++;
        }
        
        return ret;
    }
    
    /**
     * Este método puede mejorarse para que solo recorra la lista
     * si el libro a borrar está dentro de ella (comprar las ventas).
     */
    void remove_bestseller(BookTitle bt) {
        list<Book*>::iterator it = _bestsellers.begin();
        bool erased = false;
        
        while (it != _bestsellers.end() && !erased) {
            if ( (*it)->title() == bt ) {
                _bestsellers.erase(it);
                erased = true;
            }
            it++;
        }
    }

};


#endif /* BestSellersLineal_h */
