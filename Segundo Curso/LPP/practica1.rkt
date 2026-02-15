#lang racket

(define (cuadrado x)
  (* x x))

(define (distancia p1 p2)
  (sqrt(+(cuadrado(-(car p2)(car p1)))(cuadrado(-(cdr p2)(cdr p1))))))


  (define (isosceles? p1 p2 p3)
   (and; Se envuelve todo en un and para que se tengan que cumplir ambas condiciones para que sea True, en caso contrario un triangulo con p1=p2=p3 daría #t
    (not(and(= (distancia p1 p2)(distancia p2 p3)))); ;Comprobar que no son los tres iguales
   (or(=(distancia p1 p2)(distancia p2 p3))
      (=(distancia p1 p3)(distancia p1 p2))
      (=(distancia p1 p3)(distancia p2 p3)))))