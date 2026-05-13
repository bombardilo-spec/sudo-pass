from concurrent.futures import ThreadPoolExecutor
import math


# ---------------- INPUT ----------------
n = int(input("Enter number of elements: "))
arr = list(map(int, input("Enter elements: ").split()))


# ---------------- CHUNK FUNCTIONS ----------------
def get_min(chunk):
    return min(chunk)

def get_max(chunk):
    return max(chunk)

def get_sum(chunk):
    return sum(chunk)


# ---------------- PARALLEL REDUCTION ----------------
def parallel_reduction(arr):

    threads = 4
    size = len(arr)
    chunk_size = math.ceil(size / threads)

    chunks = [arr[i:i + chunk_size] for i in range(0, size, chunk_size)]

    with ThreadPoolExecutor() as executor:

        mins = list(executor.map(get_min, chunks))
        maxs = list(executor.map(get_max, chunks))
        sums = list(executor.map(get_sum, chunks))

    min_val = min(mins)
    max_val = max(maxs)
    total = sum(sums)
    avg = total / size

    print("\nMinimum:", min_val)
    print("Maximum:", max_val)
    print("Sum:", total)
    print("Average:", avg)


# ---------------- RUN ----------------
parallel_reduction(arr)