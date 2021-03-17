import matplotlib.pyplot as plt
import networkx as nx

n = int(input())
graph = [list(map(float, input().split())) for _ in range(n)]
permutation = list(map(int, input().split()))

G = nx.Graph()
plt.figure(figsize=(16, 9))


for i in range(n):
    G.add_node(permutation[i], pos=(graph[permutation[i]][1], graph[permutation[i]][2]))

for i in range(n):
    G.add_edge(permutation[i], permutation[(i + 1) % n])

pos = nx.get_node_attributes(G, 'pos')
nx.draw_networkx_nodes(G, pos, node_color='red')
nx.draw_networkx_edges(G, pos, width=4, edge_color='orange')
plt.title('Graph')
plt.show()
