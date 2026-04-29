#lang racket
(require rackunit)
(require "lpp.rkt")

;Ejercicio 1

;a)
(define (concat lista)
  (concat-iter lista ""))

(define (concat-iter lista resultado)
  (if (null? lista)
      resultado
      (concat-iter (rest lista) (string-append resultado (first lista)))))

;b)
(define (min-max lista)
  (min-max-iter lista (cons (first lista) (first lista))))


(define (min-max-iter lista resultado)
  (if (null? lista)
      resultado
      (min-max-iter (rest lista) (cons (min (car resultado) (first lista)) (max (cdr resultado) (first lista))))))

;Ejercicio 2

;a)

(define (expande-pareja pareja)
  (expande-pareja-iter pareja (cdr pareja) '()))

(define (expande-pareja-iter pareja cantidad resultado)
  (if (= cantidad 0)
      resultado
      (expande-pareja-iter pareja (- cantidad 1) (cons (car pareja) resultado))))

(define (expande-parejas . parejas)
  (expande-parejas-iter parejas `()))

(define (expande-parejas-iter list-parejas resultado)
  (if (null? list-parejas)
      resultado
      (expande-parejas-iter (rest list-parejas) (append resultado (expande-pareja (first list-parejas))))))


;b)

(define (rotar k lista)
  (if (= k 0)
      lista
      (rotar (- k 1) (append (rest lista) (list (first lista))))))

;Ejercicio 3

;a)

(define (mi-foldl func parametro lista)
  (mi-foldl-iter func lista parametro))

(define (mi-foldl-iter func lista parametro)
  (if (null? lista)
      parametro
      (mi-foldl-iter func (rest lista) (func (first lista) parametro))))

;b)

(define (binario-a-decimal lista)
  (binario-a-decimal-iter lista 0))

(define (binario-a-decimal-iter lista resultado)
  (cond [(null? lista)
         resultado]
        [(= (first lista) 1)
         (binario-a-decimal-iter (rest lista) (+ (* resultado 2) 1))]
        [else
         (binario-a-decimal-iter (rest lista) (* resultado 2))]))

;Ejercicio 4

(define diccionario (make-dic))

(define (key-trans x y)
  (string-append (number->string x) (number->string y)))

(define (pascal-memo x y dic)
  (cond [(= y 0)
         1]
        [(= x y)
         1]
        [(key-exists? (key-trans x y) dic)
         (get (key-trans x y) dic)]
        [else
         (put (key-trans x y)
              (+ (pascal-memo (- x 1) (- y 1) dic)
                 (pascal-memo (- x 1) y dic))
              dic)]))
              
         

