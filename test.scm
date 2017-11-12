(define len
  (lambda (lst)
    (if (null? lst)
        0
        (+ 1 (len (cdr lst))))))

(len (quote ()))
(len (quote (4 5 6)))

(define app
  (lambda (lst1 lst2)
    (if (null? lst1)
        lst2
        (cons (car lst1) (app (cdr lst1) lst2)))))

(app (quote (4 5)) (quote (6 7)))

(define rev
  (lambda (lst)
    (if (null? lst)
        lst
        (app (rev (cdr lst)) (cons (car lst) (quote ()))))))

(rev (quote ()))
(rev (quote (1 2 3 4)))
(quote (("computer" "science") "is" "awesome"))
(rev (quote (("computer" "science") "is" "awesome")))