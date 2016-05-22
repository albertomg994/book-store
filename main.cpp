//
//  main.cpp
//  T11-Venta-Libros
//
//  Created by Alberto Miedes on 20/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#include <iostream>
#include "BookStore.h"
#include "BookStoreIO.h"

int main(int argc, const char * argv[]) {

    unsigned int num_ops;
    string operacion;

    BookStore bs;

    // Read number of operations in first case
    cin >> num_ops;
    cin.ignore();

    // For each set of operations
    while (!cin.eof()) {

        for (int i = 0; i < num_ops; i++) {

            cin >> operacion;

            if (operacion == "nuevoLibro") {
                cin.ignore(1);              // read space after op name
                BookStoreIO::new_book(bs);
            }

            else if (operacion == "comprar") {
                cin.ignore(1);              // read space after op name
                BookStoreIO::buy_book(bs);
            }

            else if (operacion == "estaLibro") {
                cin.ignore(1);              // read space after op name
                BookStoreIO::has_book(bs);
            }

            else if (operacion == "elimLibro") {
                cin.ignore(1);              // read space after op name
                BookStoreIO::del_book(bs);
            }

            else if (operacion == "numEjemplares") {
                cin.ignore(1);              // read space after op name
                BookStoreIO::book_stock(bs);
            }

            else if (operacion == "top10") {
                cin.ignore(1);              // read space after op name
                BookStoreIO::top_10(bs);
            }

            else {
                BookStoreIO::error();
            }

        }

        // Each case ends with six -
        cout << "------" << endl;

        // Read number of operations in next case (if exists)
        cin >> num_ops;
        cin.ignore();
    }

    return 0;
}
