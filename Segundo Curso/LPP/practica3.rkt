#lang racket
(require rackunit)
(require "lpp.rkt")
(require "practica2.rkt")

;Ejercicio 1
;a.1) Utilizo los métodos de la práctica2 con un (require "practica2.rkt") en este fichero
;en el fichero de la práctica2 he puesto (provide (all-defined-out)) para que comparta todos los métodos


(define (minimo lista)
  (cond ((null? (rest lista)) (first lista))
      (else
  (menor (first lista)
         (minimo (rest lista))))))

;a.2)
;¿Qué lista se pasa como parámetro a la primera llamada recursiva a la función?
 ;El resto de la lista original

;¿Qué devuelve esa llamada recursiva?
 ;El mínimo del resto de la lista a la hora de la "subida" de la recursión

;¿Con qué argumentos se llama a la función menor que devuelve el resultado final?
 ;Con el primer elemento de la lista y el mínimo recursivo del resto de la lista


;b)

(define (concatena lista-chars)
  (cond ((null? lista-chars) "")
        (else
         (string-append(string (first lista-chars))
                        (concatena (rest lista-chars))))))

;c)

(define (cifra-cadena cad desplazamiento)
  (cond ((= (string-length cad) 0) "")
        (else
        (string-append(string (cifra-caracter (string-ref cad 0) desplazamiento))
                      (cifra-cadena (substring cad 1 (string-length cad)) desplazamiento)))))

(define (descifra-cadena cad desplazamiento)
  (cond ((= (string-length cad) 0) "")
        (else
        (string-append(string (descifra-caracter (string-ref cad 0) desplazamiento))
                      (descifra-cadena (substring cad 1 (string-length cad)) desplazamiento)))))

;d)

(define (contiene? lista elemento)
  (cond [(null? lista) #f]
        [(equal? (first lista) elemento)]
        [else (contiene? (rest lista) elemento)]))

(define (str-contiene? cadena char)
  (contiene? (string->list cadena) char))

;Ejercicio 2
;a)
(define (todos-iguales? lista)
  (cond [(null? lista) #t]
        [(= (length lista) 1) #t]
        [(equal? (first lista) (second lista))
        (todos-iguales? (rest lista))]
        [else #f]))

;b)
(define (todos-distintos? lista)
  (cond [(null? lista) #t]
        [(= (length lista) 1) #t]
        [(contiene? (rest lista) (first lista)) #f]
        [else (todos-distintos? (rest lista))]))

;c)

(define (solo-dos-iguales? lista)
  (= (veces-aparece lista) 1))

(define (veces-aparece lista)
    (cond [(null? lista) 0]
        [(contiene? (rest lista) (first lista))
          (+ 1 (veces-aparece (rest lista)))]
        [else (veces-aparece (rest lista))]))


;(define (solo-dos-iguales? lista)


;Ejercicio 3
;a.1)

;(caja-puntero (cons (cons'a 'b) (list 'c (list 'd 'e))))

;a.2)

;(cdr(car p1)) para b
;(cdr(rest(first p1))) para d

;b.1)

;(caja-puntero (cons (cons (cons 'a (cons 'b 'c)) (cons (list 'd 'e) (list 'f))) (list 'g)))

;Ejercicio 4


(define (contar-datos-iguales lista-parejas)
      (cond [(null? lista-parejas) 0]
        [(equal? (car (first lista-parejas)) (cdr (first lista-parejas)))
          (+ 1 (contar-datos-iguales (rest lista-parejas)))]
        [else (contar-datos-iguales (rest lista-parejas))]))

;Ejercicio 5

(define (palo-carta symbol)
 (cond ((char=? (string-ref(symbol->string symbol) 1) #\♠) "Picas")
       ((char=? (string-ref(symbol->string symbol) 1) #\♥) "Corazones")
       ((char=? (string-ref(symbol->string symbol) 1) #\♦) "Diamantes")
       (else "Tréboles")))


































