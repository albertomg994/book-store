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
#include "BookStoreExceptions.h"
#include <list>
#include <string>

using namespace std;

/**
 * Function to compare 2 books so we can sort them by
 * sales<->las_sale_date
 * @return true if b1 goes before b2
 */
bool compare_function (Book* b1,Book* b2) {
    if (b1->sales() > b2->sales()) return true;
    else if (b1->sales() < b2->sales()) return false;
    else { // b1->sales() == b2->sales()
        if (b1->sale_date() > b2->sale_date()) return true;
        else return false;
    }
}

class BookStore {
private:

    HashMap<BookTitle, Book> _books;
    SaleDate _next_date;

public:

    /**
     * Constructor
     */
    BookStore() : _next_date(0) {}
    
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
        if (it == _books.end()) {
            _books.insert(bt, Book(bt, _next_date, uds));                       // O(1)
            _next_date++;
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
        b->sell_one(_next_date);                                              // O(1)
        _next_date++;
    }

    /**
     * Complexity: O(1)
     * @returns true if book is present in the system, even if it is out of stock
     */
    bool has_book(BookTitle bt) const {
        return _books.contains(bt);
    }

    /**
     * Elimina el libro x del sistema. Si el libro no existe la operación no
     * tiene efecto.
     * Complejidad: O(1)
     */
    void remove_book(BookTitle bt) {
        // NOTE: what happens if it's present in 'best-sellers'? ---> I think it'll just be updated over time
        
        // TODO: evitar la búsqueda dos veces, juntar las dos líneas en una misma búsqueda
        if (_books.contains(bt)) {
            _books.erase(bt);   // O(1)
        }
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

    /**
     * Devuelve una lista con los 10 libros más vendidos. Si hay más de 10 libros
     * distintos con un máximo número de ventas la aplicación obtiene los 10 de venta
     * más reciente. Si no se han vendido 10 libros distintos se listarán todos ellos.
     * La lista estará ordenada por número de ventas primero los más vendidos y los libros
     * que se hayan vendido el mismo número de veces se ordenan del que tenga la venta más
     * moderna a la más antigua.
     * Complejidad: O(AWFUL) ---> Must iprove it, just made this implementation to pass judge tests on time
     */
    list<BookTitle> top_10() {
        
        list<Book*> todos;
        list<BookTitle> ret;
        
        // First create a list with all titles
        HashMap<BookTitle, Book>::Iterator it = _books.begin();
        while (it != _books.end()) {
            if ((it.value()).sales() > 0) todos.push_back(&(it.value()));
            it++;
        }
        
        // Sort list
        todos.sort(compare_function);
        
        // Return first 10 books in list
        list<Book*>::iterator it_list = todos.begin();
        unsigned size = 0;
        
        while (it_list != todos.end() && size < 10) {
            ret.push_back((*it_list)->title());
            size++;
            it_list++;
        }
        
        return ret;
    }

};

#endif /* BookStore_h */
