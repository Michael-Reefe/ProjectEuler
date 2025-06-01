⍝ Project Euler 2: Even Fibonacci Numbers
⍝ https://projecteuler.net/problem=2

euler2 ← {(⊢+.×0=2|⊢)¯2↓(⊢,(+/¯2↑⊢))⍣(⍵<¯1↑⊢)1 1}
euler2 4e6
