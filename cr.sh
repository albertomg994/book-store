#!/bin/sh

#  cr.sh
#  T11-Venta-Libros
#
#  Created by Alberto Miedes on 21/5/16.
#  Copyright © 2016 Alberto Miedes. All rights reserved.

g++ -std=c++11 main.cpp -o bookstore

# Ejecutar tests mezcla
# -------------------------------------------

echo "Ejecutando tests mezcla..."

./bookstore < test/test-1.in > test/test-1.out
diff test/test-1.out test/test-1.out.sample

./bookstore < test/test-2.in > test/test-2.out
diff test/test-2.out test/test-2.out.sample

./bookstore < test/test-3.in > test/test-3.out
diff test/test-3.out test/test-3.out.sample


# Entramos en la carpeta de tests específicos
# -------------------------------------------
cd test

echo "Ejecutando tests específicos..."

# Ejecutar tests de nuevoLibro

echo "Ejecutando tests de nuevoLibro"

cd nuevoLibro
../../bookstore < test-1.in > test-1.out
diff test-1.out test-1.out.sample
cd ..

# Ejecutar tests de estaLibro

echo "Ejecutando tests de estaLibro"

cd estaLibro
../../bookstore < test-1.in > test-1.out
diff test-1.out test-1.out.sample
cd ..

# Ejecutar tests de comprar

echo "Ejecutando tests de comprar"

cd comprar
../../bookstore < test-1.in > test-1.out
diff test-1.out test-1.out.sample
cd ..

# Ejecutar tests de elimLibro

echo "Ejecutando tests de elimLibro"

cd elimLibro
../../bookstore < test-1.in > test-1.out
diff test-1.out test-1.out.sample
cd ..

# Ejecutar tests de numEjemplares

echo "Ejecutando tests de numEjemplares"

cd numEjemplares
../../bookstore < test-1.in > test-1.out
diff test-1.out test-1.out.sample
cd ..

# Volver al directorio raíz del programa
# -------------------------------------------
cd ..


rm bookstore
