;;All the various concadentation of car and cdr
(define caar
  (lambda (lst)
    (car (car lst))))

(define cadr
  (lambda (lst)
    (car (cdr lst))))

(define cdar
  (lambda (lst)
    (cdr (car lst))))

(define cddr
  (lambda (lst)
    (cdr (cdr lst))))

(define caaar
  (lambda (lst)
    (car (caar lst))))

(define caadr
  (lambda (lst)
    (car (cadr lst))))

(define cadar
  (lambda (lst)
    (car (cdar lst))))

(define caddr
  (lambda (lst)
    (car (cddr lst))))

(define cdaar
  (lambda (lst)
    (cdr (caar lst))))

(define cdadr
  (lambda (lst)
    (cdr (cadr lst))))

(define cddar
  (lambda (lst)
    (cdr (cdar lst))))

(define cdddr
  (lambda (lst)
    (cdr (cddr lst))))

(define caaaar
  (lambda (lst)
    (car (caaar lst))))

(define caaadr
  (lambda (lst)
    (car (caadr lst))))

(define caadar
  (lambda (lst)
    (car (cadar lst))))

(define caaddr
  (lambda (lst)
    (car (caddr lst))))

(define cadaar
  (lambda (lst)
    (car (cdaar lst))))

(define cadadr
  (lambda (lst)
    (car (cdadr lst))))

(define caddar
  (lambda (lst)
    (car (cddar lst))))

(define cadddr
  (lambda (lst)
    (car (cdddr lst))))

(define cdaaar
  (lambda (lst)
    (cdr (caaar lst))))

(define cdaadr
  (lambda (lst)
    (cdr (caadr lst))))

(define cdadar
  (lambda (lst)
    (cdr (cadar lst))))

(define cdaddr
  (lambda (lst)
    (cdr (caddr lst))))

(define cddaar
  (lambda (lst)
    (cdr (cdaar lst))))

(define cdadr
  (lambda (lst)
    (cdr (cdadr lst))))

(define cdddar
  (lambda (lst)
    (cdr (cddar lst))))

(define cddddr
  (lambda (lst)
    (cdr (cdddr lst))))

;;Now the actually interesting stuff

(define list
  (lambda args
	args)

(define list?
  (lambda (lst)


(define length
  (lambda (lst)
    (if (null? lst)
      0
      (+ (length (cdr lst)) 1))))

(