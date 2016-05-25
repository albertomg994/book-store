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
#include "BestSellersLineal.h"
#include "BookStoreExceptions.h"
#include <list>
#include <string>

using namespace std;

/*struct myclass {
    bool operator() (Book* b1,Book* b2) {
        if (b1->sales() > b2->sales()) return b2;
        else { // b1->sales() == b2->sales()
            if (b1->sale_date() < b2->sale_date()) return true;
            else return false;
        }
    }
} myobject;*/

class BookComparator {
    bool operator() (Book* b1,Book* b2) {
        if (b1->sales() > b2->sales()) return b2;
        else { // b1->sales() == b2->sales()
            if (b1->sale_date() < b2->sale_date()) return true;
            else return false;
        }
    }
};

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
    BestSellersLineal _best_sellers;
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

            // we also have to update the best-sellers (maybe best-seller has 0 sales...)
            _best_sellers.update(&(_books[bt]));
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

        // update best sellers
        _best_sellers.update(b);
        //_best_sellers.update(*b);                                   // O(?)
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
            _best_sellers.remove_bestseller(bt);
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
     * Complejidad: O(..)
     */
    /*list<Book> top_n(unsigned int n = 10) {
        list<Book> ret;

        // Habrá que copiar la lista, no devolverla tal cual.

        return ret;
    }*/

    /*list<BookTitle> top_10() {
        return _best_sellers.get_bestsellers();
    }*/
    
    // Implementación muy ineficiente, solo la hago para pasar el juez antes del viernes
    list<BookTitle> top_10() {
        
        //cout << "you called top_10() method" << endl;
        
        list<Book*> todos;
        list<BookTitle> ret;
        
        // Primero creamos una lista con todos los titulos
        //cout << "Creating a list with all books in system" << endl;
        HashMap<BookTitle, Book>::Iterator it = _books.begin();
        while (it != _books.end()) {
            if ((it.value()).sales() > 0) todos.push_back(&(it.value()));
            it++;
        }
        //cout << "list with all books has " << todos.size() << " elements." << endl;
        
        // Ordenamos la lista
        //cout << "Ordering list..." << endl;
        todos.sort(compare_function);
        //cout << "ordered list has " << todos.size() << " elements." << endl;
        //std::list::sort (todos.begin(), todos.end(), compare_function);     //(12 26 32 33 45 53 71 80)
        
        // Devolvemos los 10 primeros
        //cout << "Returning first 10 books..." << endl;
        list<Book*>::iterator it_list = todos.begin();
        unsigned size = 0;
        
        while (it_list != todos.end() && size < 10) {
            ret.push_back((*it_list)->title());
            size++;
            it_list++;
        }
        
        //cout << "Returned list has " << ret.size() << " elements." << endl;
        return ret;
    }

};

#endif /* BookStore_h */
