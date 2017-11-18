(let ((x 6)
        (y 9)
        (z 6))
        (+ x y z))

(letrec ((x z)
        (y x)
        (z 6))
        (+ y x z))

(let* ((x y)
        (y 6)
        (z y))
        (+ x y z))
