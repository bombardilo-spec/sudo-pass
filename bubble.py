import time
from concurrent.futures import ThreadPoolExecutor

# ---------------- SEQUENTIAL BUBBLE SORT ----------------
def bubble_sort(arr):
    n = len(arr)

    for i in range(n):
        for j in range(n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]


# ---------------- PARALLEL STYLE BUBBLE SORT ----------------
def parallel_bubble(arr):
    n = len(arr)

    def work(start):
        for i in range(start, n - 1, 2):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]

    for _ in range(n):

        with ThreadPoolExecutor() as t:
            t.submit(work, 0)  # even phase
            t.submit(work, 1)  # odd phase


# ---------------- MAIN ----------------
n = int(input("Enter size: "))
arr = list(map(int, input("Enter elements: ").split()))

a1 = arr.copy()
a2 = arr.copy()

start = time.time()
bubble_sort(a1)
print("\nSequential Bubble Sort Time:", time.time() - start)

start = time.time()
parallel_bubble(a2)
print("Parallel Bubble Sort Time:", time.time() - start)