(define (average x y)
  (/ (+ x y) 2))

; 2.1.1
; (define (make-rat n d) (cons n d))
(define (make-rat n d)
  (let ((g (gcd n d)))
    (cons (/ n g) (/ d g))))
(define (numer x) (car x))
(define (denom x) (cdr x))

(define (add-rat x y)
  (make-rat (+ (* (numer x) (denom y))
               (* (numer y) (denom x)))
            (* (denom x) (denom y))))
(define (sub-rat x y)
  (make-rat (- (* (numer x) (denom y))
               (* (numer y) (denom x)))
            (* (denom x) (denom y))))
(define (mul-rat x y)
  (make-rat (* (numer x) (numer y))
            (* (denom x) (denom y))))
(define (div-rat x y)
  (make-rat (* (numer x) (denom y))
            (* (denom x) (numer y))))
(define (equal-rat? x y)
  (= (* (numer x) (denom y))
     (* (numer y) (denom x))))

(define (print-rat x)
  (newline)
  (display (numer x))
  (display "/")
  (display (denom x)))

(define one-half
  (make-rat 1 2)))
(define one-third
  (make-rat 1 3))
(print-rat one-half)
(print-rat one-third)
(print-rat (add-rat one-half one-third))
(print-rat (sub-rat one-half one-third))
(print-rat (mul-rat one-half one-third))
(print-rat (div-rat one-half one-third))


; T2.2
(define (make-segment s e)
  (cons s e))
(define (start-segment l)
  (car l))
(define (end-segment l)
  (cdr l))
(define (midpoint-segment l)
  (make-point (average (x-point (start-segment l)) (x-point (end-segment l)))
              (average (y-point (start-segment l)) (y-point (end-segment l)))))
(define (make-point x y)
  (cons x y))
(define (x-point p)
  (car p))
(define (y-point p)
  (cdr p))
(define (print-point p)
  (newline)
  (display "(")
  (display (x-point p))
  (display ",")
  (display (y-point p))
  (display ")"))

(print-point
  (midpoint-segment
    (make-segment
      (make-point 1 2)
      (make-point 3 4))))


; 2.1.3
; 将cons返回的结果定义为过程
; 数据在过程的环境中？很离谱又很合理
; (define (cons x y)
;   (define (dispatch m)
;     (cond ((= m 0) x)
;           ((= m 1) y)
;           (else (error "Argument not 0 or 1 --- cons"))))
;   dispatch)
; (define (car z) (z 0))
; (define (cdr z) (z 1))


; T2.4
; (define (cons x y)
;   (lambda(m) (m x y)))
; (define (car z)
;   (z (lambda(p q) p)))
; (define (cdr z)
;   (z (lambda(p q) q)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; T2.5~2.6
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


; 2.1.4
(define (add-interval x y)
  (make-interval (+ (lower-bound x) (lower-bound y))
                 (+ (upper-bound x) (upper-bound y))))

(define (mul-interval x y)
  (let ((p1 (* (lower-bound x) (lower-bound y)))
        (p2 (* (lower-bound x) (upper-bound y)))
        (p3 (* (upper-bound x) (lower-bound y)))
        (p4 (* (upper-bound x) (upper-bound y))))
    (make-interval (min p1 p2 p3 p4)
                   (max p1 p2 p3 p4))))

(define (div-interval x y)
  (mul-interval x
                (make-interval (/ 1.0 (upper-bound y))
                               (/ 1.0 (lower-bound y)))))


; T2.7
(define (make-interval a b)
  (cons a b))

(define (upper-bound x)
  (cdr x))

(define (lower-bound x)
  (car x))


; T2.8
(define (sub-interval x y)
  (let ((p1 (- (lower-bound x) (lower-bound y)))
        (p2 (- (lower-bound x) (upper-bound y)))
        (p3 (- (upper-bound x) (upper-bound y)))
        (p4 (- (upper-bound x) (upper-bound y))))
    (make-interval (min p1 p2 p3 p4)
                   (max p1 p2 p3 p4))))


; T2.10
(define (div-interval x y)
  (if (and (< (lower-bound y) 0) (> (upper-bound y) 0))
    (error "0 is in y")
    (mul-interval x
                  (make-interval (/ 1.0 (upper-bound y))
                                 (/ 1.0 (lower-bound y))))))


; T2.11
; [_, a1, _, b1, _]
; [_, a2, _, b2, _]
; 插空法及乘法原理，一共有3*3=9种可能


; T2.12
(define (make-center-width c w)
  (make-interval (- c w) (+ c w)))

(define (center i)
  (/ (+ (lower-bound i) (upper-bound i)) 2))

(define (width i)
  (/ (- (upper-bound i) (lower-bound i)) 2))

(define (make-center-percent c p)
  (make-interval (* c (- 1 p)) (* c (+ 1 p))))

(define (center i)
  (/ (+ (lower-bound i) (upper-bound i)) 2))

(define (percent i)
  (/ (- (upper-bound i) (center i)) (center i)))


; T2.13
; (p1+p2) / (1+p1p2)


; T2.14
(define (par1 r1 r2)
  (div-interval (mul-interval r1 r2)
                (add-interval r1 r2)))

(define (par2 r1 r2)
  (let ((one (make-interval 1 1)))
    (div-interval one
                  (add-interval (div-interval one r1)
                                (div-interval one r2)))))
; par1和par2分别表示计算并联电阻的两个等式
; R = r1r2 / (r1+r2)     R = 1 / ((1/r1) + (1/r2))
; par1和par2的计算结果是不相同的
; 我觉得原因是这样的，这里的interval是在一个可能的区间
; 也就是在误差范围内震荡，而每次区间操作都会影响到震荡
; 先不说加减乘除对震荡的影响程度是否相同
; 但就运算次数，par1是3次，par2是4次
; 这就已经不相同了


; 2.2.1
(define (list-ref items n)
  (if (= n 0)
    (car items)
    (list-ref (cdr items) (- n 1))))

(list-ref (list 2 4 2 5 0) 3)

(define (length l)
  (if (null? l)
    0
    (+ 1 (length (cdr items)))))

(define (length l)
  (define (iter a count)
    (if (null? a)
      count
      (iter (cdr a) (+ 1 count))))
  (iter l 0))

; (define (append l1 l2)
;   (if (null? l1)
;     l2
;     (cons (car l1) (append (cdr l1) l2))))
; 
; (append (list 2 4 5) (list 8 9 7 6))


; T2.17
; 迭代计算过程
(define (last-pair l)
  (if (null? (cdr l))
    l
    (last-pair (cdr l))))

(last-pair (list 3 2 5 4 8))


; T2.18
(define (reverse items)
  (if (null? items)
    '()
    (append (reverse (cdr items)) (list (car items)))))

(reverse (list 2 4 5 6 9))


; T2.19
(define (cc amount coin-values)
  (cond ((= amount 0) 1)
        ((or (< amount 0) (no-more? coin-values)) 0)
        (else
          (+ (cc amount
                 (except-first-denomination coin-values))
             (cc (- amount (first-denomination coin-values))
                 coin-values)))))
(define us-coins (list 50 25 10 5 1))
(define uk-coins (list 100 50 20 10 5 2 1 0.5))
(define (first-denomination coins)
  (car coins))
(define (except-first-denomination coins)
  (cdr coins))
(define (no-more? coins)
  (null? coins))
(cc 100 us-coins)
(cc 50 uk-coins)
; coins-values的排序不同并不会影响到最后的计算结果


; T2.20
; 偷鸡写法
(define (same-parity one . others)
  (filter (if (even? one) even? odd?) (cons one others)))

(define (same-parity one . others)
  (define (iter result l)
    (if (null? l)
      result
      (if (= (remainder one 2) (remainder (car l) 2))
        ; (append result (list (car l)))
        ; (iter result (cdr l)))))   ;; 问题出在这儿，如何让append和iter一起执行呢
        ; 啊啊啊，我悟啦
        (iter (append result (list (car l))) (cdr l))
        (iter result (cdr l)))))
  (iter (list one) others))

(same-parity 4 1 2 3 4 5 6)


; map并不是其他语言里的数据结构map，而是一个处理表结构的高层抽象过程
; 将实现表变换的过程的实现，与如何提取表中元素以及组合结果的细节隔离开来
(define (scale-list items factor)
  (if (null? items)
    '()
    (cons (* (car items) factor)
          (scale-list (cdr items) factor))))
(scale-list (list 2 4 8 9) 10)

; 抽象出一般的模式，即对列表中的每一个元素进行操作
(define (map proc items)
  (if (null? items)
    '()
    (cons (proc (car items))
          (map proc (cdr items)))))
(map abs (list -10 2 -4 5 -9))

(define (scale-list items factor)
  (map (lambda(x) (* x factor))
       items))
(scale-list (list 2 4 8 9) 10)


; T2.21
(define (square-list items)
  (if (null? items)
    '()
    (cons (square (car items))
          (square-list (cdr items)))))

(square-list (list 2 4 5 6))

(define (square-list items)
  (map (lambda(x) (square x)) items))

(square-list (list 2 4 5 6))


; T2.22
; cons把result放后面的当然不行啦，得到的是逆序的，可以reverse一下
(define (square-list items)
  (define (iter result things)
    (if (null? things)
      result
      (iter (cons (square (car things)) result)
            (cdr things))))
  (iter '() items))

; 至于cons把result放在前面，结果会奇奇怪怪的，因为每次会与nil复合并不是append
(define (square-list items)
  (define (iter result things)
    (if (null? things)
      result
      (iter (cons result (square (car things)))
            (cdr things))))
  (iter '() items))

(square-list (list 2 4 5 6))

(define (square-list items)
  (define (iter result things)
    (if (null? things)
      result
      (iter (append result (list (square (car things))))
            (cdr things))))
  (iter '() items))

(square-list (list 2 4 5 6))


;T2.23
(define (for-each proc items)
  (if (not (null? items))
    (begin ; if只能接单条语句，因而用特殊形式begin包裹一下
      (proc (car items))
      (for-each proc (cdr items)))))

(define (for-each proc items)
  ; cond后面可以接多条语句，因而更方便
  (cond ((not (null? items))
         (proc (car items))
         (for-each proc (cdr items)))))

(for-each (lambda(x) (newline) (display x))
          (list 2 4 5 9 7 9))


; 2.2.2
(define (count-leaves x)
  (cond ((null? x) 0)
        ((not (pair? x)) 1)
        (else
          (+ (count-leaves (car x))
             (count-leaves (cdr x))))))

(count-leaves (cons 2 (cons (list 1 2) (list 3 5))))


; T2.24
(list 1 (list 2 (list 3 4)))


; T2.25
(car (cdaddr (list 1 3 (list 5 7) 9)))

(caar (list (list 7)))

(cadadr (cadadr (cadadr (list 1 (list 2 (list 3 (list 4 (list 5 (list 6 7)))))))))


; T2.26
(define x (list 1 2 3))
(define y (list 4 5 6))

(append x y)

(cons x y)

(list x y)


; T2.27
(define (reverse items)
  (if (null? items)
    '()
    (append (reverse (cdr items))
            (list (car items)))))

(define (deep-reverse items)
  (if (null? items)
    '()
    (append (deep-reverse (cdr items)) 
            ; 区别仅在此处是否要递归的reverse pair
            (if (pair? (car items))
              (list (reverse (car items)))
              (list (car items))))))

(deep-reverse (list (list 1 2) (list 3 4)))


; T2.28
; flatten
(define (fringe tree)
  (if (null? tree)
    '()
    (append (if (pair? (car tree))
              (fringe (car tree))
              (list (car tree)))
            (fringe (cdr tree)))))

(fringe (list (list 9 8) (list 0 7) 1 2 3 4))


; T2.29
; 刚疑惑cons和list的区别，这题就涉及到了
; sicp牛啊
(define (make-mobile left right)
  (list left right))

(define (make-branch len structure)
  (list len structure))

; a) selector process
(define (left-branch mobile)
  (car mobile))

(define (right-branch mobile)
  (cadr mobile))    ; 区别在这里，list的cdr部分仍然是一个cons，需要再car取一下

(define (branch-len branch)
  (car branch))

(define (branch-structure branch)
  (cadr branch))    ; 同理

; b) total weight
(define (total-weight mobile)
  (let ((lb (left-branch mobile))
        (rb (right-branch mobile)))
    (+
      (if (pair? (branch-structure lb))
        (total-weight (branch-structure lb))
        (branch-structure lb))
      (if (pair? (branch-structure rb))
        (total-weight (branch-structure rb))
        (branch-structure rb)))))

(define (branch-weight branch)
  (if (pair? (branch-structure branch))
    (total-weight (branch-structure branch))
    (branch-structure branch)))

(define (total-weight mobile)
  (+ (branch-weight (left-branch mobile))
     (branch-weight (right-branch mobile))))

(total-weight (make-mobile (make-branch 1 100) (make-branch 2 200)))

; c) judge banance
(define (balanced? mobile)
  (let ((lb (left-branch mobile))
        (rb (right-branch mobile)))
    (and
      (=
        (if (pair? (branch-structure lb))
          (* (total-weight (branch-structure lb)) (branch-len lb))
          (* (branch-structure lb) (branch-len lb)))
        (if (pair? (branch-structure rb))
          (* (total-weight (branch-structure rb)) (branch-len rb))
          (* (branch-structure rb) (branch-len rb))))
      (if (pair? (branch-structure lb))
        (balanced? (branch-structure lb))
        true)
      (if (pair? (branch-structure rb))
        (balanced? (branch-structure rb))
        true))))

(balanced? (make-mobile (make-branch 1 100) (make-branch 2 200)))

; d) cons 和 list 的区别
; list 末尾一定是一个nil
; 因而和cons有很大的区别
(define (make-mobile left right)
  (cons left right))

(define (make-branch len structure)
  (cons len structure))

(define (left-branch mobile)
  (car mobile))

(define (right-branch mobile)
  (cdr mobile))

(define (branch-len branch)
  (car branch))

(define (branch-structure branch)
  (cdr branch))

(balanced? (make-mobile (make-branch 1 100) (make-branch 2 200)))


; 2.2.2
(define (scale-tree tree factor)
  (cond ((null? tree) '())
        ((not (pair? tree))
         (* tree factor))
        (else
          (cons (scale-tree (car tree) factor)
                (scale-tree (cdr tree) factor)))))

(scale-tree (list 1 (list 2 (list 3 4) 5) (list 6 7))
            10)

; 也可以将树看作是子树的序列
(define (scale-tree tree factor)
  (map
    (lambda(sub-tree)
      (if (pair? sub-tree)
        (scale-tree sub-tree factor)
        (* sub-tree factor)))
    tree))

(scale-tree (list 1 (list 2 (list 3 4) 5) (list 6 7))
            10)


; T2.30
(define (square-tree tree)
  (map
    (lambda(sub-tree)
      (if (pair? sub-tree)
        (square-tree sub-tree)
        (square sub-tree)))
    tree))

(square-tree (list 1 (list 2 (list 3 4) 5) (list 6 7)))

(define (square-tree tree)
  (cond ((null? tree) '())
        ((not (pair? tree))
         (square tree))
        (else
          (cons (square-tree (car tree))
                (square-tree (cdr tree))))))

(square-tree (list 1 (list 2 (list 3 4) 5) (list 6 7)))


; T2.31
; 来了来了，tree-map
(define (tree-map proc tree)
  (cond ((null? tree) '())
        ; ((not (pair? tree)) proc tree)    ; 哈哈哈哈哈，缩进括号什么的都容易出问题
        ((not (pair? tree)) (proc tree))
        (else
          (cons
            (tree-map proc (car tree))
            (tree-map proc (cdr tree))))))

(define (square-tree tree)
  (tree-map square tree))

(square-tree (list 1 (list 2 (list 3 4) 5) (list 6 7)))


; T2.32
(define (subsets s)
  (if (null? s)
    (list '())
    (let ((rest (subsets (cdr s))))
      (append rest (map
                     (lambda(x) (cons (car s) x))
                     rest)))))

(subsets (list 1 2 3))


; 2.2.3
;; 枚举每一棵子树
;; 过滤它们，选出其中的奇树
;; 对选中的数字取平方
;; 用+累积得到的结果，从0开始
(define (sum-odd-squares tree)
  (cond ((null? tree) 0)
        ((not (pair? tree))
         (if (odd? tree) (square tree) 0))
        (else
          (+ (sum-odd-squares (car tree))
             (sum-odd-squares (cdr tree))))))

;; 枚举从0到n的整数
;; 对每个整数计算相应的斐波那契数
;; 过滤它们，选出其中的偶数
;; 用cons累积得到的结果，从空表开始
(define (even-fibs n)
  (define (next k)
    (if (> k n)
      '()
      (let ((f (fib k)))
        (if (even? f)
          (cons f (next (+ k 1)))
          (next (+ k 1))))))
  (next 0))

;; sum-odd-squares:  enumerate -> filter -> map -> accumulate
;; even-fibs      :  enumerate -> map -> filter -> accumulate


; filter
(define (filter predicate sequence)
  (cond ((null? sequence) '())
        ((predicate (car sequence))
         (cons (car sequence)
               (filter predicate (cdr sequence))))
        (else
          (filter predicate (cdr sequence)))))

(filter odd? (list 2 3 5 2 9 8 0))

; accumulate
(define (accumulate op initial sequence)
  (if (null? sequence)
    initial
    (op (car sequence)
        (accumulate op initial (cdr sequence)))))

(accumulate + 0 (list 1 2 3 4 5))
(accumulate * 1 (list 1 2 3 4 5))
(accumulate cons (list 1 2 3) (list 4 5 6))

; enumerate
(define (enumerate-interval low high)
  (if (> low high)
    '()
    (cons low (enumerate-interval (+ low 1) high))))

(enumerate-interval 3 7)

(define (enumerate-tree tree)
  (cond ((null? tree) '())
        ((not (pair? tree)) (list tree))
        (else
          (append (enumerate-tree (car tree))
                  (enumerate-tree (cdr tree))))))

(enumerate-tree (list 1 (list 2 (list 3 4))))


; 前面的两个过程可以被如下组合
(define (sum-odd-squares tree)
  (accumulate +
              0
              (map square
                   (filter odd?
                           (enumerate-tree tree)))))

(define (even-fibs n)
  (accumulate cons
              '()
              (filter even?
                      (map fib
                           (enumerate-interval 0 n)))))


; 2.2.4 跳


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; T2.33~2.52
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


; 2.3.1
(define (memq item x)
  (cond ((null? x) false)
        ((eq? item (car x)) x)
        (else
          (memq item (cdr x)))))

(memq 'apple '(pear appl banana prune))
(memq 'apple '(pear apple banana prune))


; T2.53
(list 'a 'b 'c)
(list (list 'george))
(cdr '((x1 x2) (y1 y2)))
(cadr '((x1 x2) (y1 y2)))   ; 注意区别cons和list的区别
(cdr (cons '(x1 x2) '(y1 y2)))
(pair? (car '(a short list)))
(memq 'red '((red shoes) (blue socks)))
(memq 'red '(red shoes blue socks))


; T2.54
(define (equal? x y)
  (cond ((and (symbol? x) (symbol? y))
         (eq? x y))
        ((and (list? x) (list? y))
         (list-equal? x y))
        (else
          (error "not equal" x y))))

(define (list-equal? x y)
  (cond ((and (null? x) (null? y))
         true)
        ((or (null? x) (null? y))
         false)
        ((equal? (car x) (car y))
         (equal? (cdr x) (cdr y)))
        (else
          false)))

(equal? '(this is a short list) '(this is a short list))
(equal? '(this is a short list) '(this is a short 1ist))


; T2.55
(car '' abracadabra)
; 写出等价形式
(car (quote (quote abracadabra)))


; 2.3.2
; 采用前缀表达式书写
; 如 (+ (* a x) b)
(define (variable? x)
  (symbol? x))

(define (same-variable? v1 v2)
  (and (variable? v1) (variable? v2) (eq? v1 v2)))

(define (make-sum a1 a2)
  (list '+ a1 a2))

(define (make-product m1 m2)
  (list '* m1 m2))

(define (sum? x)
  (and (pair? x) (eq? (car x) '+)))

(define (addend s)
  (cadr s))

(define (augend s)
  (caddr s))

(define (product? x)
  (and (pair? x) (eq? (car x) '*)))

(define (multiplier p)
  (cadr p))

(define (multiplicand p)
  (caddr p))

; 基于上面定义的过程，就可以写符号求导了
(define (deriv exp var)
  (cond ((number? exp) 0)
        ((variable? exp)
         (if (same-variable? exp var) 1 0))
        ((sum? exp)
         (make-sum (deriv (addend exp) var)
                   (deriv (augend exp) var)))
        ((product? exp)
         (make-sum
           (make-product (multiplier exp)
                         (deriv (multiplicand exp) var))
           (make-product (deriv (multiplier exp) var)
                         (multiplicand exp))))
        (else
          (error "unkonw expression type -- DERIVE" exp))))

(deriv '(+ x 3) 'x)
(deriv '(* x y) 'x)

(define (=number? exp num)
  (and (number? exp) (= exp num)))

(define (make-sum a1 a2)
  (cond ((=number? a1 0) a2)
        ((=number? a2 0) a1)
        ((and (number? a1) (number? a2)) (+ a1 a2))
        (else
          (list ('+ a1 a2)))))

(define (make-product m1 m2)
  (cond ((or (=number? m1 0) (=number? m2 0)) 0)
        ((=number? m1 1) m2)
        ((=number? m2 1) m1)
        ((and (number? m1) (number? m2)) (* m1 m2))
        (else
          (list '* m1 m2))))

(deriv '(+ x 3) 'x)
(deriv '(* x y) 'x)


; T2.56
(define (fast-expt b n)
  (cond ((= n 0) 1)
        ((even? n) (square (fast-expt b (/ n 2))))
        (else (* b (fast-expt b (- n 1))))))
(fast-expt 2 4)

(define (exponentiation? x)
  (and (pair? x) (eq? (car x) '**)))

(define (base s)
  (cadr s))

(define (exponent s)
  (caddr s))

(define (make-exponentiation e1 e2)
  (cond ((=number? e1 0) 0)
        ((=number? e2 0) 1)
        ((=number? e2 1) e1)
        ((and (number? e1) (number? e2) (fast-pow e1 e2)))
        ((and (exponentiation? e1) (exponentiation? e2) (same-variable? (base e1) (base e2)))
         (list '** (base e1) (+ (exponent e1) (exponent e2))))
        (else
          (list '** e1 e2))))

(define (deriv exp var)
  (cond ((number? exp) 0)
        ((variable? exp)
         (if (same-variable? exp var) 1 0))
        ((sum? exp)
         (make-sum (deriv (addend exp) var)
                   (deriv (augend exp) var)))
        ((product? exp)
         (make-sum
           (make-product (multiplier exp)
                         (deriv (multiplicand exp) var))
           (make-product (deriv (multiplier exp) var)
                         (multiplicand exp))))
        ((exponentiation? exp)
         (make-product
           (make-product (exponent exp)
                         (make-exponentiation (base exp) (- (exponent exp) 1)))
           (deriv (base exp) var)))
        (else
          (error "unkonw expression type -- DERIVE" exp))))

(deriv '(** x 2) 'x)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; T2.57~2.58
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


; 2.3.3
; 用到的equal需要扩展一下都为数字的判等
(define (equal? x y)
  (cond ((and (number? x) (number? y))
         (= x y))
        ((and (symbol? x) (symbol? y))
         (eq? x y))
        ((and (list? x) (list? y))
         (list-equal? x y))
        (else
          ; (error "not equal" x y))))
          false)))

(define (list-equal? x y)
  (cond ((and (null? x) (null? y))
         true)
        ((or (null? x) (null? y))
         false)
        ((equal? (car x) (car y))
         (equal? (cdr x) (cdr y)))
        (else
          false)))
(define (element-of-set? x set)
  (cond ((null? set) false)
        ((equal? x (car set)) true)
        (else
          (element-of-set? x (cdr set)))))

(define (adjoin x set)
  (if (element-of-set? x set)
    set
    (cons x set)))

(define (intersection-set set1 set2)
  (cond ((or (null? set1) (null? set2)) '())
        ((element-of-set? (car set1) set2)
         (cons (car set1)
               (intersection-set (cdr set1) set2)))
        (else (intersection-set (cdr set1) set2))))

(define (union-set set1 set2)
  (cond ((null? set1) set2)
        ((null? set2) set1)
        ((element-of-set? (car set1) set2)
         (union-set (cdr set1) set2))
        (else
          (cons (car set1)
                (union-set (cdr set1) set2)))))


(element-of-set? 4 (list 2 3 4))

(adjoin 3 (list 1 2 4))

(intersection-set '(a a p p l e) '(b a n a n a))

(union-set '(a p p l e) '(b a n a n a))

; T2.60
(intersection-set '(a a p p l e) '(b a n a n a))

(union-set '(a p p l e) '(b a n a n a))
; 可重复元素的集合表示，意思是做一下集合化简？
; element-of-set不需要修改
; intersection-set
(define (unique-set set)
  (cond ((null? set) '())
        ((null? (cdr set)) set)
        ((element-of-set? (car set) (cdr set))
         (unique-set (cdr set)))
        (else
          (cons (car set) (unique-set (cdr set))))))

(unique-set (list 2 3 4 5 2 3 4 2))

(define (intersection-multiset set1 set2)
  (let ((us1 (unique-set set1))
        (us2 (unique-set set2)))
    (intersection-set us1 us2)))

(define (union-multiset set1 set2)
  (let ((us1 (unique-set set1))
        (us2 (unique-set set2)))
    (union-set us1 us2)))

(intersection-multiset '(a a p p l e) '(b a n a n a))

(union-multiset '(a p p l e) '(b a n a n a))


; 2.3.4 Huffman Tree
(define (make-leaf symbol weight)
  (list 'leaf symbol weight))

(define (leaf? object)
  (eq? (car object) 'leaf))

(define (symbol-leaf x)
  (cadr x))

(define (weight-leaf x)
  (caddr x))

(define (make-code-tree left right)
  (list left
        right
        ; (append (list (symbols left)) (list (symbols right)))
        (append (symbols left) (symbols right))
        (+ (weight left) (weight right))))

(define (left-branch tree)
  (car tree))

(define (right-branch tree)
  (cadr tree))

(define (symbols tree)
  (if (leaf? tree)
    (list (symbol-leaf tree))
    (caddr tree)))

(define (weight tree)
  (if (leaf? tree)
    (weight-leaf tree)
    (cadddr tree)))

(define (decode bits tree)
  (define (decode-1 bits current-branch)
    (if (null? bits)
      '()
      (let ((next-branch (choose-branch (car bits) current-branch)))
        (if (leaf? next-branch)
          (cons (symbol-leaf next-branch)
                (decode-1 (cdr bits) tree))
          (decode-1 (cdr bits) next-branch)))))
  (decode-1 bits tree))

(define (choose-branch bit branch)
  (cond ((= bit 0) (left-branch branch))
        ((= bit 1) (right-branch branch))
        (else (error "bad bit -- CHOOSE-BRANCH" bit))))

(define (adjoin-set x set)
  (cond ((null? set) (list x))
        ((< (weight x) (weight (car set))) (cons x set))
        (else (cons (car set)
                    (adjoin-set x (cdr set))))))

; T2.67
(define (make-leaf-set pairs)
  (if (null? pairs)
    '()
    (let ((pair (car pairs))) (adjoin-set (make-leaf (car pair) (cadr pair))
                  (make-leaf-set (cdr pairs))))))

(define sample-tree
  (make-code-tree (make-leaf 'A 4)
                  (make-code-tree
                    (make-leaf 'B 2)
                    (make-code-tree
                      (make-leaf 'C 1)
                      (make-leaf 'D 1)))))

(define sample-message
  '(0 1 1 0 0 1 0 1 0 1 1 1 0))

(decode sample-message sample-tree)

; T2.68
(define (encode message tree)
  (if (null? message)
    '()
    (append (encode-symbol (car message) tree)
            (encode (cdr message) tree))))

; (define (encode-symbol symbol tree)
;   (let ((result (list '())))
;     (define (encode-symbol-iter symbol tree)
;       (let ((lb (left-branch tree))
;             (rb (right-branch tree)))
;         (cond ((leaf? lb)
;                (if (eq? symbol (symbol-leaf lb))
;                  (append result (list 0))
;                  (begin (append result (list 1))
;                         (encode-symbol-iter symbol rb))))
;               ((leaf? rb)
;                (if (eq? symbol (symbol-leaf rb))
;                  (append result (list 1))
;                  (error "error")))
;               (else (encode-symbol-iter symbol rb)))))
;     (encode-symbol-iter symbol tree)
;     result))

(define (symbol-in-tree? given-symbol tree)
  (not
    (false?
      (find (lambda(s) (eq? s given-symbol))
            (symbols tree)))))

(define (encode-symbol symbol tree)
  (cond ((leaf? tree)
         '())
        ((symbol-in-tree? symbol (left-branch tree))
         (cons 0 (encode-symbol symbol (left-branch tree))))
        ((symbol-in-tree? symbol (right-branch tree))
         (cons 1 (encode-symbol symbol (right-branch tree))))
        (else
          (error "Invaild Symbol -- " symbol))))

(encode-symbol 'B sample-tree)

(encode (decode sample-message sample-tree) sample-tree)
