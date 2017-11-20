(define =
  (lambda (x y)
    (eq? x y)))

(define >=
  (lambda (x y)
    (<= y x)))

(define <
  (lambda (x y)
    (if (<= x y)
        (if (= x y)
            #f
            #t)
        #f)))

(define >
  (lambda (x y)
    (if (>= x y)
        (if (= x y)
            #f
            #t)
        #f)))

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
    (if (zero? (modulo x 2))
        #t
        #f)))

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
  (lambda (x y)
    (if (zero? y)
        x
        (gcd y (modulo x y)))))

(define lcm
  (lambda (x y)
    x))

(define modulo
  (lambda (x m)
    (if (positive? x)
        (- x (* (truncate (/ x m)) m))
        (* (truncate (/ x m)) (+ 1 m)))))

(define floor
  (lambda (x)
    (if (negative? x)
        (+ 1 (truncate x))
        (truncate x))))

(define ceiling
  (lambda (x)
    (if (positive? x)
        (+ 1 (truncate x))
        (truncate x))))

(define round
  (lambda (x)
    (if (> (- x (truncate x)) 0.5)
        (ceiling x)
        (floor x))))
