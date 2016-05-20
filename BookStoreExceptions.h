//
//  BookStoreExceptions.h
//  T11-Venta-Libros
//
//  Created by Alberto Miedes on 20/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef BookStoreExceptions_h
#define BookStoreExceptions_h

#include <string>

using namespace std;

/**
 * A generic exception class with message for this exercise
 */
class BookStoreException {
public:
    BookStoreException() {}
    BookStoreException(const string &msg) : _msg(msg) {}
    
    const string msg() const { return _msg; }
    
    friend ostream &operator<<(ostream &out, const BookStoreException &e);
protected:
    string _msg;
};

inline ostream &operator<<(ostream &out, const BookStoreException &e) {
    out << e._msg;
    return out;
}

/**
 *
 */
class InvalidArgumentException : public BookStoreException {
public:
    InvalidArgumentException() : BookStoreException("Libro no existente") {};
};

class OutOfRangeException : public BookStoreException {
public:
    OutOfRangeException() : BookStoreException("No hay ejemplares") {};
};

#endif /* BookStoreExceptions_h */
