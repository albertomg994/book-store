#!/bin/sh

#  cr.sh
#  T11-Venta-Libros
#
#  Created by Alberto Miedes on 21/5/16.
#  Copyright © 2016 Alberto Miedes. All rights reserved.

# Compilar
g++ -std=c++11 main.cpp -o bookstore

# Entrar en la carpeta de tests
cd test

# Ejecutar todos los test
# -------------------------------------------

# Ejecutar tests mezcla
echo "Ejecutando tests mezcla..."
cd varios

../../bookstore < test-1.in > test-1.out
diff test-1.out test-1.out.sample

../../bookstore < test-2.in > test-2.out
diff test-2.out test-2.out.sample

../../bookstore < test-3.in > test-3.out
diff test-3.out test-3.out.sample

cd ..

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

# Ejecutar tests de top10

echo "Ejecutando tests de top10"

cd top10
../../bookstore < test-1.in > test-1.out
diff test-1.out test-1.out.sample
cd ..

# Volver al directorio raíz del programa
# -------------------------------------------
cd ..


rm bookstore
