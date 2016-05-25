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
#include <string>

class BookStoreIO {
public:

    static void new_book(BookStore & bs) {

        unsigned stock;
        std::string title;

        // read stock
        std::cin >> stock; std::cin.ignore(1);

        // read title until end of line
        getline(std::cin, title);

        bs.new_book(title, stock);
    }

    static void buy_book(BookStore & bs) {

        BookTitle title;

        // read book title until end of line
        getline(std::cin, title);

        try {
            bs.buy(title);
        } catch (InvalidArgumentException e1) {
            std::cout << e1.msg() << endl;
            cout << "---" << endl;
        } catch (OutOfRangeException e2) {
            std::cout << e2.msg() << endl;
            cout << "---" << endl;
        }

    }

    static void has_book(BookStore & bs) {

        BookTitle title;

        // read book title until end of line
        getline(std::cin, title);

        if(bs.has_book(title)) std::cout << "El libro " << title << " esta en el sistema" << std::endl;
        else std::cout << "No existe el libro " << title << " en el sistema" << std::endl;
        std::cout << "---" << std::endl;
    }

    static void del_book(BookStore & bs) {

        BookTitle title;

        // read book title until end of line
        getline(std::cin, title);

        bs.remove_book(title);
    }

    static void book_stock(BookStore & bs) {

        BookTitle title;

        // read book title until end of line
        getline(std::cin, title);

        try {
            unsigned stock = bs.get_stock(title);
            std::cout << "Existen " << stock << " ejemplares del libro " << title << std::endl;
        } catch (InvalidArgumentException e) {
            std::cout << "No existe el libro " << title << " en el sistema" << std::endl;
        }
        std::cout << "---" << std::endl;
    }

    /**
     * Escribe los libros más comprados, uno en cada línea ordenados del más comprado al
     * menos comprado. Los libros que se han comprado el mismo número de veces se listan
     * del comprado más actual al más antiguo.
     */
    static void top_10(BookStore & bs) {

        list<BookTitle> top_sellers = bs.top_10();

        list<BookTitle>::const_iterator it = top_sellers.cbegin();
        while (it != top_sellers.cend()) {
            std::cout << (*it) << std::endl;
            it++;
        }

        std::cout << "---" << std::endl;
    }

    // static void top_n(BookStore & bs) {
    //     ...
    // }

    static void error() {
        // print nothing
    }

};

#endif /* BookStoreIO_h */
