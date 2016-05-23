# Test descriptions

## Resumen de las operaciones disponibles

```
nuevoLibro [unidades] [titulo]
    ==> SALIDA: sin salida

compar [titulo]
    ==> SALIDA: InvalidArgumentException, OutOfRangeException

estaLibro [titulo]
    ==> SALIDA: "El libro X esta en el sistema"
                "No existe el libro X en el sistema"

elimLibro [titulo]
    ==> SALIDA: sin salida

numEjemplares [titulo]
    SALIDA: ==> Existen M ejemplares del libro X
            ==> InvalidArgumentException

top10
    ==> SALIDA: un título de libro por línea
```

## Formato de las excepciones

**`InvalidArgumentException`**

```
Libro no existente
---
```

**`OutOfRangeException`**

```
No hay ejemplares
---
```

## Tests

**test-1**

* nuevoLibro
* comprar
* estaLibro


**test-2**



**test-3**



**test-4**

## Operaciones

### 1. `nuevoLibro [ejemplares] [titulo]`

#### Descripción

Añade X ejemplares de un libro al sistema. Si no existe, se da de alta.
Si X=0, el libro se da de alta sin ejemplares.

#### Formato de salida

```
Sin salida
```

#### Casos

* Comprobar que un libro no dado de alta no existe
* Comprobar que un libro dado de alta existe
* Comprobar que el número de ejemplares tras ejecutar nuevoLibro por primera vez es correcto
* Comprobar que el número de ejemplares tras ejecutar nuevoLibro más de una vez sobre el mismo libro es correcto

```
11
estaLibro Harry Potter
estaLibro Memorias de Idhún
nuevoLibro 0 Harry Potter
nuevoLibro 2 Memorias de Idhún
estaLibro Harry Potter
estaLibro Memorias de Idhún
numEjemplares Harry Potter
numEjemplares Memorias de Idhún
nuevoLibro 4 Harry Potter
estaLibro Harry Potter
numEjemplares Harry Potter
```

```
No existe el libro Harry Potter en el sistema
---
No existe el libro Memorias de Idhún en el sistema
---
El libro Harry Potter esta en el sistema
---
El libro Memorias de Idhún esta en el sistema
---
Existen 0 ejemplares del libro Harry Poter
---
Existen 2 ejemplares del libro Memorias de Idhún
---
El libro Harry Potter esta en el sistema
---
Existen 4 ejemplares del libro Harry Poter
---
------
```

### 2. `comprar [titulo]`

#### Descripción

* Si no existen ejemplares disponibles, OutOfRangeException("No hay ejemplares")
* Si no está dado de alta, InvalidArgument("Libro no existente")

#### Formato de salida

Sólo muestra salida si se producen excepciones:

```
No hay ejemplares
---
Libro no existente
---
------
```

#### Casos

* Comprobar lanzamiento de OutOfRangeException
* Comprobar lanzamiento de InvalidArgument
* Intentar comprar un libro que no existe
* Intentar comprar un libro sin stock
* Volver a intantar comprar un libro que antes estaba agotado, pero ahora ya no

```
10
comprar Harry Potter
nuevoLibro 0 Harry Potter
nuevoLibro 2 Memorias de Idhún
comprar Harry Potter
comprar Memorias de Idhún
comprar Memorias de Idhún
comprar Memorias de Idhún
nuevoLibro 2 Harry Potter
comprar Harry Potter
comprar Harry Potter
comprar Harry Potter
```

```
Libro no existente
---
No hay ejemplares
---
No hay ejemplares
---
No hay ejemplares
---
------
```

### 3. `estaLibro [titulo]`

#### Descripción

Indica si un libro X se ha añadido al sistema. El resultado será cierto si el libro está en el sistema, aunque no haya ejemplares disponibles y será falso si no está en el sistema.

#### Formato de salida

Una línea diciendo si está o no está. No hay excepciones.

```
9
estaLibro Harry Potter
estaLibro Memorias de Idhún
nuevoLibro 0 Harry Potter
nuevoLibro 2 Memorias de Idhún
estaLibro Harry Potter
estaLibro Memorias de Idhún
comprar Memorias de Idhún
comprar Memorias de Idhún
estaLibro Memorias de Idhún
```

```
No existe el libro Harry Potter en el sistema
---
No existe el libro Memorias de Idhún en el sistema
---
El libro Harry Potter esta en el sistema
---
El libro Memorias de Idhún esta en el sistema
---
El libro Memorias de Idhún esta en el sistema
---
------
```

#### Casos

### 4. `elimLibro [titulo]`

#### Descripción

Elimina el libro X del sistema. Si el libro no existe la operación no tiene efecto.

#### Formato de salida

No hay ninguna salida

```
9
elimLibro Harry Potter
nuevoLibro 0 Harry Potter
nuevoLibro 2 Memorias de Idhún
estaLibro Harry Potter
estaLibro Memorias de Idhún
elimLibro Harry Potter
elimLibro Memorias de Idhún
estaLibro Harry Potter
estaLibro Memorias de Idhún
```

```
El libro Harry Potter esta en el sistema
---
El libro Memorias de Idhún esta en el sistema
---
No existe el libro Harry Potter en el sistema
---
No existe el libro Memorias de Idhún en el sistema
---
------
```

#### Casos

### 5. `numEjemplares [titulo]`

#### Descripción

Devuelve el número de ejemplares de un libro X. Lanza excepciones de tipo InvalidArguemnt("Libro no existente")

###CUIDADO:

* En el enunciado pone que imprime "Libro no existente", pero en el esquema que nos ha dado cuando no existe pone "No existe el libro X en el sistema"

#### Formato de salida

Si el libro está: "Existen Y ejemplares del libro X"

```
13
numEjemplares Harry Potter
nuevoLibro 0 Harry Potter
nuevoLibro 2 Memorias de Idhún
numEjemplares Harry Potter
numEjemplares Memorias de Idhún
comprar Memorias de Idhún
numEjemplares Memorias de Idhún
comprar Memorias de Idhún
numEjemplares Memorias de Idhún
elimLibro Harry Potter
elimLibro Memorias de Idhún
numEjemplares Harry Potter
numEjemplares Memorias de Idhún
```

```
No existe el libro Harry Potter en el sistema
---
Existen 0 ejemplares del libro Harry Potter
---
Existen 2 ejemplares del libro Memorias de Idhún
---
Existen 1 ejemplares del libro Memorias de Idhún
---
Existen 0 ejemplares del libro Memorias de Idhún
---
No existe el libro Harry Potter en el sistema
---
No existe el libro Memorias de Idhún en el sistema
---
------
```

#### Casos

### 6. `top10`

#### Descripción

* Lista con los 10 libros más vendidos, por orden de ventas. Hace uso de la última venta para resovler los desempates.
* Si la lista está vacía, no muestra nada
* Los libros que estaban en el top-10 pero se han eliminado, no deben aparecer
* Si no se han vendido todavía 10 libros, se listarán todos ellos
* Comprobar que no aparecen mas de 10 libros

#### Formato de salida

```
```

#### Casos