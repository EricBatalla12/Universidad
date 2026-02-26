#lang racket
(require "lpp.rkt")

;Ejercicio 1
;################
;       a)
;################

(define (aplica-veces f1 f2 n x)
  (if (= 0 n)
      x
      (f2 (f1 (aplica-veces f1 f2 (- n 1) x)))))

;################
;       b)
;################

(define (elimina-primero elem lista)
  (cond [(null? lista)
         '()]
        [(equal? elem (first lista)) (rest lista)]
        [else (cons (first lista)(elimina-primero elem (rest lista)))]))

(define (mueve-al-principio-condicion pred lista)
  (cond [(null? lista)
         '()]
         [(pred (first lista))
          (elimina-primero (first lista) lista)]
         [else
          (cons (first lista)(mueve-al-principio-condicion pred (rest lista)))]))


              

            
  

  