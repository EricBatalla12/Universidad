#lang racket
(require rackunit)
(require "lpp.rkt")

;Ejercicio 1




(define arbol1 '( 15 (4 (2) (3)) (8 (6)) (12 (9) (10) (11))))
(dato-arbol (second (hijos-arbol (third (hijos-arbol arbol1)))))

(define arbolb1 '(40 (23 (5 () () ) (32 (29 () () ) () )) (45 () (56 () () ))))
(dato-arbolb (hijo-izq-arbolb (hijo-der-arbolb (hijo-izq-arbolb arbolb1))))

;Ejercicio 2

;a)

(define arbol2 '(a (b (c (d)) (e)) (f)))

(define (to-string-arbol arbol)
 (string-append (symbol->string (dato-arbol arbol))
 (to-string-bosque (hijos-arbol arbol))))

(define (to-string-bosque bosque)
 (if (null? bosque)
 ""
 (string-append (to-string-arbol (first bosque))
 (to-string-bosque (rest bosque)))))

(define (to-string-arbol-fos arbol)
  (string-append (symbol->string (dato-arbol arbol))
  (foldr (lambda (elem acc)
           (string-append (to-string-arbol-fos elem) acc)) "" (hijos-arbol arbol))))

;b)

(define (veces-arbol dato arbol)
  (+ (if (equal? dato (dato-arbol arbol))
         1
         0)
     (veces-arbol-bosque dato (hijos-arbol arbol))))


(define (veces-arbol-bosque dato bosque)
  (if (null? bosque)
      0
      (+
       (veces-arbol dato (first bosque))
       (veces-arbol-bosque dato (rest bosque)))))
                    

(define (veces-arbol-fos dato arbol)
  (+ (if (equal? (dato-arbol arbol) dato)
         1
         0)
     (foldr (lambda (elem acc)
              (+ (veces-arbol-fos dato elem) acc)) 0 (hijos-arbol arbol))))

;Ejercicio 3

(define arbol3 '(10 (2) (12 (4) (2)) (10 (5))))

(define (hojas-cumplen pred arbol)
  (append (if (and (pred (dato-arbol arbol)) (hoja-arbol? arbol))
              (list (dato-arbol arbol))
              '())
          (hojas-cumplen-bosque pred (hijos-arbol arbol))))

(define (hojas-cumplen-bosque pred bosque)
  (if (null? bosque)
      '()
      (append
       (hojas-cumplen pred (first bosque))
       (hojas-cumplen-bosque pred (rest bosque)))))

(define (hojas-cumplen-fos pred arbol)
  (append (if (and (pred (dato-arbol arbol)) (hoja-arbol? arbol))
              (list (dato-arbol arbol))
              '())
              (foldr (lambda (elem acc)
                       (append (hojas-cumplen-fos pred elem) acc)) '() (hijos-arbol arbol))))

;Ejercicio 4

;a)

(define arbol4 '(20 (2) (8 (4) (2)) (9 (5))))

(define (suma-raices-hijos arbol)
  (foldr (lambda (elem acc)
           (+ (dato-arbol elem) acc)) 0 (hijos-arbol arbol)))


;b)
(define arbol5 '(20 (2) (8 (4) (5)) (9 (5))))

(define (raices-mayores-arbol? arbol)
  (and (> (dato-arbol arbol) (suma-raices-hijos arbol))
       (raices-mayores-arbol-bosque? (hijos-arbol arbol))))

(define (raices-mayores-arbol-bosque? bosque)
  (if (null? bosque)
      #t
      (and
       (raices-mayores-arbol? (first bosque))
       (raices-mayores-arbol-bosque? (rest bosque)))))

(define (raices-mayores-arbol-fos? arbol)
  (and (> (dato-arbol arbol) (suma-raices-hijos arbol))
       (foldr (lambda (elem acc)
                (and (raices-mayores-arbol-fos? elem) acc)) #t (hijos-arbol arbol))))
                                                               

;Ejercicio 5

;a)

(define (es-camino? lista arbol)
  (cond [(not (equal? (dato-arbol arbol) (first lista)))
         #f]
        [(and (null? (rest lista)) (hoja-arbol? arbol))
         #t]
        [(or (null? (rest lista)) (hoja-arbol? arbol))
         #f]
        [else
         (es-camino-bosque? (rest lista) (hijos-arbol arbol))]))

(define (es-camino-bosque? lista bosque)
  (if (null? bosque)
      #f
      (or
       (es-camino? lista (first bosque))
       (es-camino-bosque? lista (rest bosque)))))

;b)

(define (nodos-nivel nivel arbol)
  (if (= nivel 0)
      ; Si llegamos al nivel 0, guardamos el dato en una lista
      (list (dato-arbol arbol))
      ; Si no, bajamos al bosque restando 1 al nivel
      (nodos-nivel-bosque (- nivel 1) (hijos-arbol arbol))))

(define (nodos-nivel-bosque nivel bosque)
  (if (null? bosque)
      ; Si no hay más hijos, devolvemos la lista vacía
      '()
      ; Juntamos los resultados del primer hijo y del resto de los hijos
      (append (nodos-nivel nivel (first bosque))
              (nodos-nivel-bosque nivel (rest bosque)))))






