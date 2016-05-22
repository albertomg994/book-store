#!/bin/sh

#  cr.sh
#  T11-Venta-Libros
#
#  Created by Alberto Miedes on 21/5/16.
#  Copyright © 2016 Alberto Miedes. All rights reserved.

g++ -std=c++11 main.cpp -o bookstore
./bookstore < test/test-1.in > test/test-1.out
rm bookstore