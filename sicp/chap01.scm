; T1.3
(define (sum-of-larger-two a b c)
  (- (+ a b c) (min a b c)))
(define (sum-of-larger-two a b c)
  (cond ((and (> a c) (> b c)) (+ a b))
        ((and (> a c) (> c b)) (+ a c))
        (else (+ b c))))
(sum-of-larger-two 2 9 1)


; T1.4
; 妙啊，过程和数据地位等同都可以作为表达式的求值结果
(define (a-plus-abs-b a b)
  ((if (> b 0) + -) a b))
(a-plus-abs-b 2 4)


; T1.5
(define (p) (p))
(define (test x y)
  (if (= x 0)
    0
    y))
;; (test 0 (p)) ; 死循环
; 我也不知道该说什么了，继续说妙吧
; 应用序是先求值参数后应用，而正则序是完全展开而后规约
; (test 0 (p))
; 应用序在这儿会先无限递归的展开过程p，导致程序死循环
; => ((if (= x 0) 0 y) 0 (p))
; 而正则序先应用过程test，对参数求值是惰性的，无需计算出，因而会得到结果为0
; 前面书上说了Scheme是应用序，因而程序会进入死循环
; 6.001课上教授画过一张图，eval和apply
; 应用序大概是先eval后apply，而正则序大概是先apply后eval


; 1.1.7
(define (average x y)
  (/ (+ x y) 2))
(define (square x)
  (* x x))
(define (good-enough? guess x)
  (< (abs (- (square guess) x)) 0.0001))
(define (improve guess x)
  (average guess (/ x guess)))
(define (sqrt-iter guess x)
  (if (good-enough? guess x)
    guess
    (sqrt-iter (improve guess x) x)))
(define (sqrt x)
  (sqrt-iter 1 x))
(sqrt 9)

(define (sqrt x)
  (define (average x y)
    (/ (+ x y) 2))
  (define (square x)
    (* x x))
  (define (good-enough? guess x)
    (< (abs (- (square guess) x)) 0.0001))
  (define (improve guess x)
    (average guess (/ x guess)))
  (define (sqrt-iter guess x)
    (if (good-enough? guess x)
      guess
      (sqrt-iter (improve guess x) x)))
  (sqrt-iter 1.0 x))
(sqrt 9)


; T1.6
(define (new-if predicate then-clause else-clause)
  (cond (predicate then-clause)
        (else else-clause)))
; 用new-if替换1.1.7牛顿法求平方根中的if会无限递归调用，导致套娃死循环
; 是这样子的，Lisp中的条件语句if/cond都是特殊过程，不完全遵循替换原则
; 而new-if在封装cond的过程中，将其特殊性一同抹掉了
; 因而这里由于Scheme的应用序求值，导致sqrt-iter死循环
; 也就是说递归过程里用new-if就会导致死循环


; T1.7
; 现实计算机中，数值计算都有精度限制，1.1.7中用差的绝对值是否足够小来衡量猜测值的好坏
; 这显然是不合理的，因为这个精度值对于特别大的数显得过于小，对于特别小的数则显得过于大
; (sqrt 0.00001)
; (sqrt 100000000000000000000000000000000000000000000000000000000000000000)
; 级数审敛主要也是看数值波动是否足够小，趋于收敛，常用方法是比较审敛法和比值审敛法
; 用差值不行，那就用比值嘛
(define (average x y)
  (/ (+ x y) 2))
(define (square x)
  (* x x))
(define (good-enough? guess prev-guess)
  (< (/ (abs (- guess prev-guess)) guess) 0.0001))
(define (improve guess x)
  (average guess (/ x guess)))
(define (sqrt-iter guess prev-guess x)
  (if (good-enough? guess prev-guess)
    guess
    (sqrt-iter (improve guess x) guess x)))
(define (sqrt x)
  (sqrt-iter 1.0 0.5 x))
(sqrt 9)
(sqrt 0.00001)
(sqrt 100000000000000000000000000000000000000000000000000000000000000000)


; T1.8
; 牛顿法求立方根
; 开立方根对自变量的约束放宽到了实数域
; 那不如统一先转成正数处理
(define (cube-root x)
  (define (square x)
    (* x x))
  (define (abs x)
    (if (< x 0) (- x) x))
  (define (good-enough? guess prev-guess)
    (< (/ (abs (- guess prev-guess)) guess) 0.0001))
  (define (improve guess x)
    (/ (+ (/ x (square guess)) (* 2 guess)) 3))
  (define (cube-iter guess prev-guess x)
    (if (good-enough? guess prev-guess)
      guess
      (cube-iter (improve guess x) guess x)))
  ((if (> x 0) + -) (cube-iter 1.0 0.5 (abs x))))
(cube-root 8)
(cube-root -8)


; 1.2.1
; 递归和迭代是两种思考问题的方式
; Scheme采用应用序求值的缘故，平凡的递归会比迭代占用更多的空间
(define (factorial n)
  (if (= n 1)
    1
    (* n (factorial (- n 1)))))
(define (factorial n)
  (define (fact-iter product counter max-count)
    (if (> counter max-count)
      product
      (fact-iter (* counter product)
                 (+ counter 1)
                 max-count)))
  (fact-iter 1 1 n))


; T1.9
;; (define (+ a b)
;;   (if (= a 0)
;;     b
;;     (inc (+ (dec a) b))))
; (+ 4 5)
; => (inc (+ 4 5))
; => (inc (inc (+ 2 5)))
; => (inc (inc (inc (+ 1 5))))
; => (inc (inc (inc (inc (+ 0 5)))))
; => (inc (inc (inc (inc 5))))
; => (inc (inc (inc 6)))
; => (inc (inc 7))
; => (inc 8)
; => 9
;; (define (+ a b)
;;   (if (= a 0)
;;     b
;;     (+ (dec a) (inc b))))
; (+ 4 5)
; => (+ 3 6)
; => (+ 2 7)
; => (+ 1 8)
; => (+ 0 9)
; => 9


; T1.10
(define (A x y)
  (cond ((= y 0) 0)
        ((= x 0) (* 2 y))
        ((= y 1) 2)
        (else (A (- x 1)
                 (A x (- y 1))))))
(A 1 10)    ; 1024
(A 2 4)     ; 65536
(A 3 3)     ; 65536
(define (f n) (A 0 n))  ; f(n) = 2*n
(define (g n) (A 1 n))  ; g(n) = 2^n
(define (h n) (A 2 n))  ; h(n) = 2↑↑n
(define (k n) (A 3 n))  ; k(n) = 2↑↑↑n
; f(n)和g(n)表达式容易写出
; h(n)找找规律也能写，k(n)真不好写
; ↑ 是 Knuth's up-arrow notation，用来描述特别大的数字的计数符号
; https://en.wikipedia.org/wiki/Knuth%27s_up-arrow_notation


; 1.2.2
; fibonacci递归计算过程
; 递归过程的复杂度一般不太容易度量，这里画出递归树
; 最基本的计算是fib(0)和fib(1)，那不如统计这部分，在树上的表示就是叶子节点的数量
; 在数值上等于fib(n+1)，而fibonacci函数的解析式是可以写出来的，一个指数级的式子
; 那大致就可以认为递归计算至少也是O(x^n)
(define (fib n)
  (cond ((= n 0) 0)
        ((= n 1) 1)
        (else (+ (fib (- n 1)) (fib (- n 2))))))
(fib 6)
; fibonacci迭代计算过程
; 迭代计算过程的复杂度一目了然，O(n)
(define (fib n)
  (define (fib-iter a b counter)
    (if (= counter 0)
      b
      (fib-iter (+ a b) a (- counter 1))))
  (fib-iter 1 0 n))
(fib 6)


; 1.2.2
; 递归计算版本的找零钱
; 换钱方式个数等于不选某面值的个数加上选某面值的个数
; 背背背背背背包啊
; 俺不会写递归啊
(define (count-change amount)
  (define (first-denomination kinds-of-coins)
    (cond ((= kinds-of-coins 1) 1)
          ((= kinds-of-coins 2) 5)
          ((= kinds-of-coins 3) 10)
          ((= kinds-of-coins 4) 25)
          ((= kinds-of-coins 5) 50)))
  (define (cc amount kinds-of-coins)
    (cond ((= amount 0) 1)
          ((or (< amount 0) (= kinds-of-coins 0)) 0)
          (else (+ (cc amount
                       (- kinds-of-coins 1))
                   (cc (- amount
                          (first-denomination kinds-of-coins))
                       kinds-of-coins)))))
  (cc amount 5))
(count-change 100)


; T1.11
(define (f n)
  (if (< n 3)
    n
    (+ (f (- n 1)) (* (f (- n 2)) 2) (* (f (- n 3)) 3))))
(f 3)
; 改迭代也容易，记录前三个函数值即可
(define (f n)
  (define (iter a b c counter)
    (if (= counter 0)
      a
      (iter b c (+ c (* 2 b) (* 3 a)) (- counter 1))))
  (iter 0 1 2 n))
(f 3)


; T1.12
; f(row, col) = f(row-1,col-1) + f(row-1,col)
(define (element-of-pascal-triangle row col)
  (if (or (= col 1) (= row col)) 1
    (+ (element-of-pascal-triangle (- row 1)
                                   (- col 1))
       (element-of-pascal-triangle (- row 1)
                                   col))))
(element-of-pascal-triangle 4 2)


; T1.15
; 同形式的恒等式+等价无穷小，双倍快乐
; 比如可以用来做数值计算
; 三倍角公式：sinx = 3sin(x/3) - 4sin(x/3)^3
; 等价无穷小：sinx = x
; 用三倍角公式不断减小x，使得其满足等价代换的条件，即可归约求出sinx的近似值
(define (sine x)
  (define (cube x) (* x x x))
  (define (p x)
    (- (* 3 x) (* 4 (cube x))))
  (if (not (> (abs x) 0.1))
    x
    (p (sine (/ x 3.0)))))
; (sine 12.15)
; => (p (sine 4.05))
; => (p (p (sine 1.35)))
; => (p (p (p (sine 0.45))))
; => (p (p (P (p (sine 0.15)))))
; => (p (p (p (p (p (sine 0.05))))))
; 因而p被调用了5次
; 至于复杂度，408选手狂喜，x/3^n < 0.1，立即推θ(logn)


; 1.2.4
; 线性递归，时间复杂度和空间复杂度均为θ(n)
(define (power b n)
  (if (= n 0)
    1
    (* b (power b (- n 1)))))
(power 2 4)
; 迭代，时间复杂度θ(n)，空间复杂度θ(1)
(define (power b n)
  (define (pow-iter product counter)
    (if (> counter n)
      product
      (pow-iter (* product b) (+ counter 1))))
  (pow-iter 1 1))
(power 2 4)

; 幂函数性质优化求幂过程，n为偶数时b^n = (b^(n/2))/2，n为奇数时b^n = b * b^(n-1)
; 数据规模每次计算减半，因而时间复杂度为θ(logn)
; 递归
(define (fast-expt b n)
  (cond ((= n 0) 1)
        ((even? n) (square (fast-expt b (/ n 2))))
        (else (* b (fast-expt b (- n 1))))))
(fast-expt 2 4)
; T1.16
; fast-expt迭代实现
(define (fast-expt b n)
  (define (iter product counter)
    (if (= counter 0)
      product
      (if (even? counter)
        (iter (fast-expt b (/ n 2)) (/ n 2))
        (iter (* b (fast-expt b (- n 1))) (- n 1)))))
  (iter 1 n))
;; (fast-expt 1 2)
;;;;;;;;;;;; 不会写


; T1.17
(define (mul a b)
  (if (= b 0)
    0
    (+ a (* a (- b 1)))))
(mul 3 6)
(define (fast-mul a b)
  (define (double x)
    (+ x x))
  (define (halve x)
    (/ x 2))
  (cond ((= b 0) 0)
        ((even? b) (double (fast-mul a (halve b))))     ; 这似乎是递归计算  
        (else (+ a (fast-mul a (- b 1))))))             ; 似乎也是递归计算
(fast-mul 3 6)
; 最开始我竟然这么写了，太蠢了啊
; 想到了递归会把a改掉，特意加了个局部变量，然而没得用
; 另外DrRacket调试功能不错
; (define (fast-mul a b)
;   (define (double x)
;     (+ x x))
;   (define (halve x)
;     (/ x 2))
;   (let ((product a))
;     (cond ((= b 0) 0)
;           ((= b 1) product)
;           ((even? b) (fast-mul (double a) (halve b)))
;           (else (fast-mul (+ product a) (- b 1))))))
; (fast-mul 3 6)


; T1.18
; 俄罗斯农夫乘法
; a*b = 2a * (b/2)          b为偶数
; a*b = 2a * (b-1)/2 + a    b为奇数
(define (fast-mul a b)
  (define (double x)
    (+ x x))
  (define (halve x)
    (/ x 2))
  (define (iter m n)
    (cond ((= n 0) 0)
          ((even? n) (fast-mul (double m) (halve n)))               ; 迭代计算
          (else (+ (fast-mul (double m) (halve (- n 1))) a))))      ; 递归计算？
  (iter a b))
(fast-mul 3 6)


; 1.2.5
(define (gcd a b)
  (if (= b 0)
    a
    (gcd b (remainder a b))))
(gcd 8 12)
(gcd 3 7)


; T1.20
(gcd 206 40)
; 正则序
; => (gcd 40 (remainder 206 40))
; => (gcd (remainder 206 40) (remainder 40 (remainder 206 40)))
; => (gcd (remainder 40 (remainder 206 40)) (remainder (remainder 206 40) (remainder (40 (remainder 206 40)))))
; => 太长了，不继续展开了
; 正则序调用remainder的次数可以这么着算，记gcd(a,b)展开了n次
; 那么记a位置调用了a(n)次remainder，b位置调用了b(n)次remainder
; 有a(1) = 0, b(1) = 1
; a(n) = b(n-1), b(n) = a(n-1) + b(n-1) + 1
; 应用序
; => (gcd 40 6)
; => (gcd 6 4)
; => (gcd 4 2)
; => (gcd 2 0)
; => 2


; 1.2.6
(define (smallest-divisor n)
  (find-divisor n 2))

(define (find-divisor n test-divisor)
  (cond ((> (square test-divisor) n) n)
        ((divides? n test-divisor) test-divisor)
        (else (find-divisor n (+ 1 test-divisor)))))

(define (divides? a b)
  (= (remainder a b) 0))

(define (prime? n)
  (= (smallest-divisor n) n))
(prime? 3)
(prime? 8)


; 费马检查素数判定
(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((even? exp)
         (remainder (square (expmod base (/ exp 2) m))
                    m))
        (else
          (remainder (* base (expmod base (- exp 1) m))
                     m))))

(define (fermat-test n)
  (define (try-it a)
    (= (expmod a n n) a))
  (try-it (+ 1 (random (- n 1)))))

(define (fast-prime? n times)
  (cond ((= times 0) true)
        ((fermat-test n) (fast-prime? n (- 1 times)))
        (else false)))

(fast-prime? 88 10)


; T1.21
(smallest-divisor 199)      ; 199
(smallest-divisor 1999)     ; 1999
(smallest-divisor 19999)    ; 7


; T1.22
(define (timed-prime-test n)
  (newline)
  (display n)
  (start-prime-test n (runtime)))

(define (start-prime-test n start-time)
  (if (prime? n)
    (report-prime (- (runtime) start-time))))

(define (report-prime elapsed-time)
  (display " *** ")
  (display elapsed-time))

;;;;;;;;;;;;;;;;;;;;


; T1.25
; (define (expmod base exp m)
;   (remainder (fast-expt base exp) m))
; 正确性肯定是没问题的啦
; 有过其他编程语言学习经验的话，遇到大数运算都会格外注意溢出问题
; Scheme不知道用了什么“魔法”，自带大数运算就罢了，支持还格外的好
; 但天下没有免费的午餐，一定有着额外的时间空间开销
; 此处便是此原因
; 原来的expmod展开时是下面这样子
; => (remainder (square (remainder (square (......)))))
; 也就是说每次平方之后立刻跟一个取余，使得中间的计算结果都不至于很大
; 然而改成fast-exp后展开是如下
; => (remainder (fast-expt base exp) m)
; fast-expt计算出来的结果会很大很大，接取余操作的时间开销也会随之飙升


; T1.26
(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((even? exp)
         (remainder (* (expmod base (/ exp 2) m)
                       (expmod base (/ exp 2) m))
                    m))
        (else
          (remainder (* base (expmod base (- exp 1) m))
                     m))))
(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((even? exp)
         (remainder (square (expmod base (/ exp 2) m)) m))
        (else
          (remainder (* base (expmod base (- exp 1) m)) m))))
; 第一个版本手动将square展开，时间复杂度为θ(n)
; 第二个版本调用square，时间复杂度为θ(log n)
; 这就很离谱
; 至少c/c++选手表示很离谱，第一个版本做的操作不就是手动inline么
; 为什么inline还会使得复杂度升阶呢？
; 是这样的，Scheme应用序求值
; 第一个版本:   (* (expmod ...) (expmod ...))
; 第二个版本：  (square (expmod ...))
; 看到区别了吗，版本一会重复求值参数，并且递归的原因，并不是表面上的翻倍，而是升阶了


;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; T1.27
; T1.28
;;;;;;;;;;;;;;;;;;;;;;;;;;;;


; ∑f(n), f(n) = n
(define (sum-integers a b)
  (if (> a b)
    0
    (+ a (sum-integers (+ 1 a) b))))
(sum-integers 0 100)

; ∑f(n), f(n) = n^3
(define (sum-cubes a b)
  (if (> a b)
    0
    (+ (cube a) (sum-cubes (+ 1 a) b))))
(sum-cubes 1 5)

; ∑f(n), f(n) = 1/(n * (n+2))
(define (pi-sum a b)
  (if (> a b)
    0
    (+ (/ 1.0 (* a (+ a 2))) (pi-sum (+ a 4) b))))

; 这个过程，都有着公共的基础模式
; (define (<name> a b)
;   (if (> a b)
;     0
;     (+ (<term> a)
;        (<name> (<next> a) b))))
; 不同的仅仅是term和next部分
(define (sum term a next b)
  (if (> a b)
    0
    (+ (term a)
       (sum term (next a) next b))))

(define (inc x) (+ 1 x))
(define (identity x) x)
(define (sum-integers a b)
  (sum identity a inc b))
(sum-integers  1 100)
(define (sum-cubes a b)
  (sum cube a inc b))
(sum-cubes 1 10)
(define (pi-sum a b)
  (define (pi-term x)
    (/ 1.0 (* x (+ x 2))))
  (define (pi-next x)
    (+ x 4))
  (sum pi-term a pi-next b))
(* 8 (pi-sum 1 1000))


; 1.3.1
(define (integral f a b dx)
  (define (add-dx x)
    (+ x dx))
  (* (sum f (+ a (/ dx 2.0)) add-dx b) dx))
(integral cube 0 1 0.0001)


; T1.29
(define (simpson-integral f a b n)
  (define (add-h x)
    (+ x (h)))
  (define (add-2h x)
    (+ x (* 2 (h))))
  (define (h)
    (/ (- b a) n))
  (* 
    (+ 
      (* (sum f (+ a (h)) add-h b) 2)
      (* (sum f (+ a (h)) add-2h b) 2)
      (f a)
      (- (f (+ a (* b (h))))))
    (/ (h) 3)))
(simpson-integral cube 0 1.0 100)
(simpson-integral cube 0 1.0 1000)


; T1.30
(define (sum term a next b)
  (define (iter a result)
    (if (> a b)
      result
      (iter (next a) (+ (term a) result))))
  (iter a 0))


; T1.31
; 递归计算
(define (product term a next b)
  (if (> a b)
    1
    (* (term a)
       (product term (next a) next b))))
; 迭代计算
(define (product term a next b)
  (define (iter a result)
    (if (> a b)
      result
      (iter (next a) (* (term a) result))))
  (iter a 1))
(define (factorial n)
  (product identity 1 inc n))
(factorial 5)
; 由所给公式计算pi的近似值
; pi/4 = (2*4*4*6*6*8...) / (3*3*5*5*7*7...)
(define (calcu-pi n)
  (define (term k)
    (if (even? k)
      (/ (+ k 2) (+ k 1))
      (/ (+ k 1) (+ k 2))))
  (* (product term 1 inc n) 4.0))
(calcu-pi 10000)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; T1.32~1.33
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


; 1.3.2
(define (p a)
  (define (helper b)
    (* a b))
  (helper (+ a 1)))
(p 10)
(define (p a)
  ((lambda (b) (* a b)) (+ a 1)))
(p 10)
(define (p a)
  (let ((b (+ a 1)))
    (* a b)))
(p 10)
(define (p a)
  (define b (+ a 1))
  (* a b))
(p 10)
; let是λ的语法糖
; (let ((<var1> <exp1>)
;       (<var2> <exp2>)
;       ...
;       (<varn> <expn>))
;   <body>)
; ((lambda (<var1> <var2> ... <varn>)
;    <body>)
;  (<exp1> <exp2> ... <expn>))


; 1.34
(define (f g)
  (g 2))
; (f f)
; 首先写出过程f的lambda形式
; f ~ (lambda (g) (g 2))
; (f f)
; => (f (lambda (g) (g 2)))
; => ((lambda(g) (g 2)) 2)
; => (2 2)
; 2是数值，不是运算符，自然会报错了


; 1.3.3
(define (search f neg-point pos-point)
  (let ((mid-point (average neg-point pos-point)))
    (if (close-enough? neg-point pos-point)
      mid-point
      (let ((test-value (f mid-point)))
        (cond ((positive? test-value)
               (search f neg-point mid-point))
              ((negative? test-value)
               (search f mid-point pos-point))
              (else mid-point))))))
(define (close-enough? x y)
  (< (abs (- x y)) 0.00001))
(define (half-interval-method f a b)
  (let ((a-value (f a))
        (b-value (f b)))
    (cond ((and (negative? a-value) (positive? b-value))
           (search f a b))
          ((and (negative? b-value) (positive? a-value))
           (search f b a))
          (else
            (error "Value are not of opposite sign" a b)))))

(half-interval-method sin 2.0 4.0)
(half-interval-method (lambda(x) (- (* x x x) (* 2 x) 3))
                      1.0
                      2.0)

(define (fix-point f first-guess)
  (define tolerance 0.00001)
  (define (close-enough? x y)
    (< (abs (- x y)) tolerance))
  (define (try guess)
    (let ((next (f guess)))
      (if (close-enough? guess next)
        next
        (try next))))
  (try first-guess))

(fix-point cos 1.0)
(fix-point (lambda(y) (+ (sin y) (cos y)))
           1.0)

(define (sqrt x)
  (fix-point (lambda(y) (average y (/ x y)))
             1.0))
(sqrt 9)


; T1.35
; x^2 = x + 1 => x = 1 + 1/x
(fix-point (lambda(x) (+ 1 (/ 1 x))) 1.0)

; T1.36
(fix-point (lambda(x) (/ (log 1000) (log x)))
                      2.0)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;                     
; T1.37~1.39
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


; 1.3.4
(define (average-damp f)
  (lambda(x) (average x (f x)))) 
(define (sqrt x)
  (fix-point (average-damp (lambda(y) (/ x y)))
             1.0))
(sqrt 9)
