from collections import deque
from concurrent.futures import ThreadPoolExecutor


class Node:
    def __init__(self, data):
        self.data = data
        self.neighbors = []


def parallel_bfs(start):

    visited = set()
    q = deque()

    q.append(start)
    visited.add(start)

    while q:

        level_size = len(q)
        nodes = []

        # take one level
        for _ in range(level_size):
            nodes.append(q.popleft())

        def process(node):
            print(node.data, end=" ")

            for neigh in node.neighbors:
                if neigh not in visited:
                    visited.add(neigh)
                    q.append(neigh)

        with ThreadPoolExecutor() as executor:
            executor.map(process, nodes)


# -------- Example Graph --------
a = Node(0)
b = Node(1)
c = Node(2)
d = Node(3)

a.neighbors = [b, c]
b.neighbors = [a, d]
c.neighbors = [a]
d.neighbors = [b]

print("Parallel BFS:")
parallel_bfs(a)