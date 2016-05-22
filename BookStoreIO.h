//
//  BookStoreIO.h
//  T11-Venta-Libros
//
//  Created by Alberto Miedes on 21/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef BookStoreIO_h
#define BookStoreIO_h

#include "BookStore.h"

using namespace std;

class BookStoreIO {
public:

    static void new_book(BookStore & bs) {

        unsigned stock;
        string title;

        // read stock
        cin >> stock; cin.ignore(1);

        // read title until end of line
        getline(cin, title);

        cout << "new_book(" << title << ", " << stock << ")" << endl;

        bs.new_book(title, stock);
    }

    static void buy_book(BookStore & bs) {

        BookTitle title;

        // read book title until end of line
        getline(cin, title);

        cout << "buy(" << title << ")" << endl;

        bs.buy(title);
    }

    static void has_book(BookStore & bs) {

        BookTitle title;

        // read book title until end of line
        getline(cin, title);

        if(bs.has_book(title)) cout << "El libro " << title << " esta en el sistema" << endl;
        else cout << "No existe el libro " << title << " en el sistema" << endl;
        cout << "---" << endl;
    }

    static void del_book(BookStore & bs) {

        BookTitle title;

        // read book title until end of line
        getline(cin, title);

        bs.remove_book(title);
    }

    static void book_stock(BookStore & bs) {

        BookTitle title;

        // read book title until end of line
        getline(cin, title);

        try {
            unsigned stock = bs.get_stock(title);
            cout << "Existen " << stock << " ejemplares del libro " << title << endl;
        } catch (InvalidArgumentException e) {
            cout << "No existe el libro " << title << " en el sistema" << endl;
        }
        cout << "---" << endl;
    }

    /**
     * Escribe los libros más comprados, uno en cada línea ordenados del más comprado al
     * menos comprado. Los libros que se han comprado el mismo número de veces se listan
     * del comprado más actual al más antiguo.
     */
    static void top_10(BookStore & bs) {

        list<Book> top_sellers = bs.top_10();

        list<Book>::const_iterator it = top_sellers.cbegin();
        while (it != top_sellers.cend()) {
            cout << (*it).title() << endl;
            it++;
        }

        cout << "---" << endl;
    }

    // static void top_n(BookStore & bs) {
    //     ...
    // }

    static void error() {
        // print nothing
    }

};

#endif /* BookStoreIO_h */
