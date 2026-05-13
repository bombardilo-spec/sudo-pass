from concurrent.futures import ThreadPoolExecutor


class Node:
    def __init__(self, data):
        self.data = data
        self.neighbors = []


def parallel_dfs(node, visited):

    if node in visited:
        return

    visited.add(node)
    print(node.data, end=" ")

    def work(neigh):
        if neigh not in visited:
            parallel_dfs(neigh, visited)

    with ThreadPoolExecutor() as executor:
        executor.map(work, node.neighbors)


# -------- Example Graph --------
a = Node(0)
b = Node(1)
c = Node(2)
d = Node(3)

a.neighbors = [b, c]
b.neighbors = [a, d]
c.neighbors = [a]
d.neighbors = [b]

print("\nParallel DFS:")
parallel_dfs(a, set())