import numpy as np

# ---------------- SIZE ----------------
n = 10

# ---------------- CREATE VECTORS ----------------
A = np.arange(n)
B = np.arange(n) * 2

# ---------------- VECTOR ADDITION ----------------
C = A + B

# ---------------- OUTPUT ----------------
print("Vector A:", A)
print("Vector B:", B)
print("Result  :", C)