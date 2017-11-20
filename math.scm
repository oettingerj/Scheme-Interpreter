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
  (lambda (x y)
    (if (>= x y)
        x
        y)))

(define max
  (lambda (x y)
    (if (<= x y)
        x
        y)))


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
    (/ (* x y) (gcd x y))))

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
