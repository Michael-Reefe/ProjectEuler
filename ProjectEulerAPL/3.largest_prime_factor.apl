⍝ Project Euler 3: Largest Prime Factor
⍝ https://projecteuler.net/problem=3

euler3 ← {n0 ← ⍵ ⋄ ⌈/{n←n0÷×/⍵ ⋄ ⍵,⍨(1+⊢)⍣{(2=+⌿0=(⍳⍺)|⍺)∧(0=⍺|n)}1}⍣{1=n0÷×/⍺}1}
euler3 600851475143
