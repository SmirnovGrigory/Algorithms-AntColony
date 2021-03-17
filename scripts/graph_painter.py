import matplotlib.pyplot as plt
import networkx as nx
import cv2

n = 5
graph = [
    (1, 2),
    (5, 3),
    (4.3, -2.4),
    (0.43, -3.2),
    (3.45, 8.433),
]

G = nx.Graph()
G.add_node(1, pos=(1, 1))
G.add_node(2, pos=(2, 4))
G.add_node(3, pos=(3, 3))
G.add_edge(1, 2)
G.add_edge(2, 3)
G.add_edge(1, 3)
c = ['#fF5f00']
plt.figure(figsize=(6, 6))
pos = nx.get_node_attributes(G, 'pos')

nx.draw_networkx_nodes(G, pos, node_color=c)
nx.draw_networkx_edges(G, pos, edge_color=['#FF0000', '#00FF00', '#0000FF'], width=[1, 2, 3])
# nx.draw_networkx_edges(G, pos)
# nx.draw(G, pos)
plt.title('Hello')
# plt.show()
plt.savefig('a.png')
nx.draw_networkx_nodes(G, pos, node_color=c)
nx.draw_networkx_edges(G, pos, edge_color=['#FF00FF', '#00FFFF', '#F0F000'], width=[1, 2, 3])
plt.title('World')
plt.savefig('b.png')

# n = int(input())
# graph = [map(int, input().split()) for _ in range(n)]
