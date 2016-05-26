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

    HashMap<BookTitle, Book> _books;    // data structure which contains the books in the store
    BestSellers _bestsellers;           // data structure that keeps track of most-sold books
    SaleDate _next_date;                // counter used to resolve ties between books with same number of sales

public:

    /**
     * Constructor
     */
    BookStore() : _next_date(0) {}
    
    /**
     * Adds new book to the system with 'uds' units, or adds 'uds' units
     * if the book already exists.
     * Complexity: O(1)
     *
     * @param bt Book title
     * @param uds Units to be added into stock
     */
    void new_book(BookTitle bt, unsigned int uds) {

        // try to find book
        HashMap<BookTitle, Book>::Iterator it = _books.find(bt);    // O(1)

        // if it's not present, add it to the system
        if (it == _books.end()) {
            _books.insert(bt, Book(bt, _next_date, uds));           // O(1)
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
     * Complexity: O( max(logN), m ), m = _books.size, N = books with (sales > 0)
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
        _bestsellers.remove_book(&(_books[bt]));                    // O(logN), N = books with (sales > 0)

        b->sell_one(_next_date);                                    // O(1)
        _next_date++;

        // update best sellers
        _bestsellers.add_book(&(_books[bt]));                       // O(logN), N = books with (sales > 0)
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
        if (_books.contains(bt)) {
            _bestsellers.remove_book(&(_books[bt]));    // remove book from bestsellers
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
     * Returns list with titles of top N sold books.
     *  - If two books have the same sales, the most-recently bought one appears first.
     *  - If there are less than N books in the system, all of them will appear in the list.
     *  - Books with zero sales never appear in the list.
     * Complexity: O(n)
     */
    list<BookTitle> top_n(unsigned n) {
        return _bestsellers.get_top_n(n);
    }
    
    /**
     * Fixed size equivalente of the top_n() upper method.
     * This method should never be used since the upper one is more flexible and
     * more efficient. I just keep this implementation because it's different
     * from the upper one and it's the firt one I did.
     * Complexity: awful
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
    
    /**
     * Function to compare 2 books so we can sort them by
     * sales<->las_sale_date
     * @return true if b1 goes before b2
     */
    static bool compare_function (Book* b1,Book* b2) {
        if (b1->sales() > b2->sales()) return true;
        else if (b1->sales() < b2->sales()) return false;
        else { // b1->sales() == b2->sales()
            if (b1->sale_date() > b2->sale_date()) return true;
            else return false;
        }
    }
    
};

#endif /* BookStore_h */
