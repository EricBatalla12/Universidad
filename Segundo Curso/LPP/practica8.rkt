#lang racket
(require rackunit)
(require "lpp.rkt")

(define arbol '(15(4 (2)(3))(8(6))(12(9)(10)(11))))

(define (tamaño-arbol arboles)
  (cond [(null? arboles)
             0]
      [else
      (+ 1 (tamaño-bosque(hijos-arbol arboles)))]))

(define (tamaño-bosque bosque)
  (cond [(null? bosque)
             0]
      [else
      (+ (tamaño-arbol(first bosque))
         (tamaño-bosque(rest bosque)))]))

;a2)
;1.- La suma de todos los elementos de la rama de un árbol
;2.- La suma de la lista de las ramas restantes

;a3)
;1.- Una lista de subárboles
;2.- 

;b1)

(define arbolb '(40 (23 (5) (32 ( 29))) (45 (56))))
(check-equal? (dato-arbolb (hijo-izq-arbolb (hijo-der-arbolb (hijo-izq-arbolb arbolb)))) 29)
