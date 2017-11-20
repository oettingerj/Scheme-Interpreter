(define <
  (lambda (x y)
    (if (<= x y)
        (if (= x y)
            #f
            #t)
        #f)))

(> 5 6)
