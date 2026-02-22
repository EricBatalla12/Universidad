#lang racket

;Ejericio 1
;########################
          ;a)
;########################
(define (es-prefijo? prefijo palabra)
  (equal? (substring palabra 0 (string-length prefijo)) prefijo))

(define (contiene-prefijo prefijo lista-pal)
  (if (null? lista-pal)
      '()
  (cons (es-prefijo? prefijo (first lista-pal))
        (contiene-prefijo prefijo (rest lista-pal)))))

;########################
          ;b)
;########################
