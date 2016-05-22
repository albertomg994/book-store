//
//  BestSellers.h
//  T11-Venta-Libros
//
//  Created by Alberto Miedes on 20/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef BestSellers_h
#define BestSellers_h

#include "Book.h"
#include <list>
#include <string>
#include <iostream>

#define BEST_SELLERS_SIZE 10

using namespace std;

/**
 * Best-sellers class
 */
class BestSellers {
private:
    
    //list<Book*> _books;
    TreeMap<unsigned,list<Book*>> _bestsellers;
    
public:
    
    /**
     *
     */
    void update_tree(Book* b) {
        
        unsigned sales = b->sales() - 1;    // book sales before increment
        
        TreeMap<unsigned, list<Book*>>::Iterator it = _bestsellers.find(sales);
        
        // if book was not in the tree
        if (it == _bestsellers.end()) {
            
        }
        // else
        else {
            
            // borrar el libro de la antigua lista
            list<Book*>* same_sales = &(it.value());
            list<Book*>::const_iterator sales_it = same_sales->cbegin();
            bool deleted = false;
            
            while (sales_it != same_sales->cend() && !deleted) {
                if ((*sales_it)->title() == b->title()) {
                    same_sales->erase(sales_it);
                    deleted = true;
                }
            }
            
            // y añadirlo en la de las ventas + 1
            list<Book*>* new_sales =
            
            

        }
    }
    
    /**
     * @parm b Pointer to the new book, which has already been added to the system
     */
    void update_with_new_book(Book* b) {
        // if best sellers list hasn't yet reached it max size, insert new book at the back
        // ISSUE: #1
        if (_books.size() < BEST_SELLERS_SIZE) {
            _books.push_back(b);
        }
        else {
            // NOTA: la especificación del ejericio es ambigua en lo que respecta a cómo
            // resolver los empates entre libros con 0 ventas.
        }
    }
    
    void update_with_existing_book(Book* b) {
        
        Book* last = _books.back();
        unsigned sales = b->sales() - 1;    // book sales before increment
        
        // if book was already in the top-sellers
        if (sales > last->sales()) {
            
        }
        // if there was a tie with the last book in top-sellers, and the
        // top-sellers list was already full
        else if (sales == last->sales() && _books.size() == BEST_SELLERS_SIZE) {
            
        }
        // if it was about to enter in the top-sellers list
        else if (sales == last->sales() {
            
        }
        
    }
    
    /**
     * Returns string representation of best-sellers list
     */
    string to_string(unsigned n = BEST_SELLERS_SIZE) const {
        
        string ret;
        if (n > BEST_SELLERS_SIZE) n = BEST_SELLERS_SIZE;
        
        list<Book*>::const_iterator it = _books.cbegin();
        unsigned i = 0;
        while (it != _books.cend() && i < n) {
            ret += (*it)->title();
            if (it != _books.cend()) ret += " ";
            
            it++; i++;
        }
        return ret;
    }
};

#endif /* BestSellers_h */
