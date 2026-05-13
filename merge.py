import time
from concurrent.futures import ThreadPoolExecutor


# ---------------- MERGE FUNCTION ----------------
def merge(arr, l, m, r):
    left = arr[l:m+1]
    right = arr[m+1:r+1]

    i = j = 0
    k = l

    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            arr[k] = left[i]
            i += 1
        else:
            arr[k] = right[j]
            j += 1
        k += 1

    while i < len(left):
        arr[k] = left[i]
        i += 1
        k += 1

    while j < len(right):
        arr[k] = right[j]
        j += 1
        k += 1


# ---------------- SEQUENTIAL MERGE SORT ----------------
def merge_sort(arr, l, r):
    if l < r:
        m = (l + r) // 2

        merge_sort(arr, l, m)
        merge_sort(arr, m + 1, r)

        merge(arr, l, m, r)


# ---------------- PARALLEL MERGE SORT ----------------
def parallel_merge_sort(arr, l, r, pool=None):

    if l < r:
        m = (l + r) // 2

        if pool:
            left = pool.submit(parallel_merge_sort, arr, l, m, pool)
            right = pool.submit(parallel_merge_sort, arr, m + 1, r, pool)

            left.result()
            right.result()
        else:
            parallel_merge_sort(arr, l, m)
            parallel_merge_sort(arr, m + 1, r)

        merge(arr, l, m, r)


# ---------------- MAIN ----------------
n = int(input("Enter size: "))
arr = list(map(int, input("Enter elements: ").split()))

a1 = arr.copy()
a2 = arr.copy()

start = time.time()
merge_sort(a1, 0, n - 1)
print("\nSequential Merge Sort Time:", time.time() - start)

start = time.time()

with ThreadPoolExecutor() as pool:
    parallel_merge_sort(a2, 0, n - 1, pool)

print("Parallel Merge Sort Time:", time.time() - start)