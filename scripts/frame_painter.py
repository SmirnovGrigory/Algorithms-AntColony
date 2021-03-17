import matplotlib.pyplot as plt
import networkx as nx
import math

path = '/home/toliman/Projects/Algorithms-AntColony/tmp/frames/'

s = '123456789abcdefffffffffffffffffffffffffffffffffff'

frame_number, n = map(int, input().split())

G = nx.Graph()
plt.figure(figsize=(16, 9))

graph = [list(map(float, input().split())) for _ in range(n)]
ph_matrix = [[x ** .4 for x in list(map(float, input().split()))] for _ in range(n)]

permutation = list(map(int, input().split()))

pairs = set()

for i in range(n):
    pairs.add((permutation[i], permutation[(i + 1) % n]))
    pairs.add((permutation[(i + 1) % n], permutation[i]))

ph_max_value = max([max(x) for x in ph_matrix])
ph_min_value = min([min(x) for x in ph_matrix])


def get_color(val) -> str:
    n_color = (val / ph_max_value) * 255
    fi, se = int(n_color / 16), int(n_color) % 16
    return f'#ff{s[16 - fi]}{s[16 - se]}{s[16 - fi]}{s[16 - se]}'


for i in range(n):
    G.add_node(i, pos=(graph[i][1], graph[i][2]))

edge_colors = []
edges = []

for i in range(n):
    for j in range(i + 1, n, 1):
        # if (i, j) in pairs:
        edges.append((i, j, get_color(ph_matrix[i][j])))
        # G.add_edge(i, j)
        edge_colors.append(get_color(ph_matrix[i][j]))

# edges.sort(key=lambda x: x[2], reverse=True)
for e in edges:
    G.add_edge(e[0], e[1])

# edge_colors.sort(reverse=False)
pos = nx.get_node_attributes(G, 'pos')

nx.draw_networkx_nodes(G, pos, node_color='darkred')
nx.draw_networkx_edges(G, pos, width=4, edge_color=edge_colors)

plt.title(f'Iteration: {frame_number}')
# plt.savefig(f'{path}frame_{frame_number}.png')
plt.show()
