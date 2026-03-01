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

(define (mayor pal1 pal2)
  (> (string-length pal1) (string-length pal2)))


(define (cadenas-mayores lista1 lista2)
  (cond [(null? lista1)
        lista2]
      [(null? lista2)
        lista1]
        [(mayor (first lista1) (first lista2))
        (cons (first lista1) (cadenas-mayores (rest lista1) (rest lista2)))]
        [(mayor (first lista2) (first lista1))
        (cons (first lista2) (cadenas-mayores (rest lista1) (rest lista2)))]))


;Ejercicio 2
;########################
          ;a)
;########################


(define (inserta-pos dato pos lista)
  (cond [(null? lista)
         '()]
        [(= pos 0)
         (cons dato lista)]
        [else
         (cons (first lista) (inserta-pos dato (- pos 1) (rest lista)))]))

;########################
          ;b)
;########################

(define (inserta-ordenada n lista-ordenada)
  (cond [(null? lista-ordenada)
         lista-ordenada n]
        [(< n (first lista-ordenada))
         (cons n lista-ordenada)]
        [else
         (cons (first lista-ordenada) (inserta-ordenada n (rest lista-ordenada)))]))

(define (menor-lista lista)
  (cond [(null? (rest lista))
         (first lista)]
        [(< (first lista) (second lista))
         (menor-lista (cons (first lista) (rest (rest lista))))]
        [else
         (menor-lista (rest lista))]))

(define (borra-numero n lista)
  (cond [(null? lista) '()]
        [(= n (first lista)) (rest lista)]
        [else (cons (first lista) (borra-numero n (rest lista)))]))

(define (ordena lista-des)
  (cond [(null? lista-des)
         '()]
        [else
         (cons (menor-lista lista-des) 
               (ordena (borra-numero (menor-lista lista-des) lista-des)))]))
         

       
             
      
        






























