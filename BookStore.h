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
};

#endif /* BookStore_h */
