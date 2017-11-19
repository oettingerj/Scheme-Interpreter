(define =
  (lambda args
    (eq? args)))

(define >=
  (lambda args
    (<= (reverse args))))

(define <
  (lambda args
    (if (and (<= args) (= args))
        #f
        #t)))

(define >
  (lambda args
    (if (and (>= args) (= args))
        #f
        #t)))

(define zero?
  (lambda (x)
    (if (= x 0)
        #t
        #f)))

(define positive?
  (lambda (x)
    (if (> x 0)
        #t
        #f)))

(define negative?
  (lambda (x)
    (if (< x 0)
        #t
        #f)))

(define even?
  (lambda (x)
    (if x)))

(define odd?
  (lambda (x)
    (if (even? x)
        #f
        #t)))

(define max
  (lambda args
    (if (= (length args) 1)
        (car args)
        (let ((y (max (cdr args))))
          (if (> (car args) (max (cdr args)))
            (car args)
            y)))))

(define min
    (lambda args
    (if (= (length args) 1)
        (car args)
        (let ((y (min (cdr args))))
          (if (< (car args) (min (cdr args)))
            (car args)
            y)))))

(define abs
  (lambda (x)
    (if (negative? x)
        (* -1 x)
        x)))

(define gcd
  (lambda arg))

(define lcm
  (lambda arg))

(define modulo
  (lambda (x m)
    ))

(define floor
  (lambda (x)
    (if (negative? x)
        )))

(define ceiling
  (lambda (x)
    (if (positive? x)
        )))

(define truncate
  (lambda (x)
    ))

(define round
  (lambda (x)
    (if (> (- x (truncate x)) 0.5)
        (ceiling x)
        (floor x))))