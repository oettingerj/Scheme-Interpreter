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
    args))

(define list?
  (lambda (lst)
    (if (pair? lst)
        (if (null? (cdr lst))
            #t
            (lst? (cdr lst)))
        #f)))
    

(define length
  (lambda (lst)
    (if (null? lst)
        0
        (+ (length (cdr lst)) 1))))

(define list-ref
  (lambda (lst pos)
    (if (positive? pos)
        (if (< length(lst) pos)
            (if (zero? pos)
                (car lst)
                (list-ref (cdr lst) (- pos 1)))))))

(define list-tail
  (lambda (lst pos)
    (if (positive? pos)
        (if (< length(lst) pos)
            (if (zero? pos)
                lst
                (list-ref (cdr lst) (- pos 1)))))))

(define member
  (lambda (m lst)
    (if (null? lst)
        #f
        (if (eq? (car lst) m)
            #t
            (member m (cdr lst))))))

(define assq
  (lambda (m lst)
    (if (null? lst)
        #f
        (if (= (caar lst) m)
            (car lst)
            (assq m (cdr lst))))))

(define appendo
  (lambda (lst1 lst2)
    (if (null? lst2)
        lst1
        (append (cons lst1 (car lst2)) (cdr lst2)))))

(define reverse
  (lambda (lst)
    (if (<= (length lst) 1)
        lst
        (cons (reverse (cdr lst)) (car lst)))))

(define map
  (lambda (f lst)
    (if (null? lst)
        lst
        (cons (f (car lst)) (map f (cdr lst))))))

(define filter
  (lambda (f lst)
    (if (null? lst)
        lst
        (if (f (car lst))
            (cons #t (filter f (cdr lst)))
            (filter f (cdr lst))))))

(define foldl
  (lambda (f i lst)
    (if (null? lst)
        i
        (foldl f (f i (car lst)) (cdr lst)))))

(define foldr
  (lambda (f i lst)
    (if (null? lst)
        i
        (f (car lst) (foldr f (f z (cdr lst)))))))