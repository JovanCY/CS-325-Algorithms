import math
from queue import PriorityQueue


def main(file: str):

    lines = read_file(file)
    test_case = 1
    vertices = 0 # number of vertices in the test case

    for count in range(1, len(lines)):
        if vertices == 0:
            coordinates = [] # contains tuples (x,y)
            vertices = lines[count][0]
            continue

        coordinates.append((lines[count][0],lines[count][1]))
        vertices -= 1

        if vertices == 0:
            G = create_matrix(coordinates)
            print("Test case", test_case, end='')
            print(": MST weight", mst(G, coordinates), '\n') # Get the MST weight

            test_case += 1



def read_file(file:str):
    arrays = []
    with open(file, 'r') as f: # read the data
        for line in f.readlines():
            arrays.append(line.split(' ')) # store the data in a 2D array
    f.close()

    lines = []
    for line in arrays:
        try:
            line = [int(item) for item in line] # make all input integers instead of strings
            lines.append(line)
        except:
            continue

    return lines

def calculate_edge(x1: int, y1: int, x2: int, y2: int):
    distance = (x1 - x2)**2 + (y1 - y2)**2
    distance = math.sqrt(distance)

    return round(distance)

def create_matrix(coordinates: list): # input: list of all our coordinates
    matrix = []

    for i in range(len(coordinates)):
        matrix.append([])
        for j in range(len(coordinates)):
            if i != j: # the nodes are not the same. Since this is a perfect graph, they are connected.
                # Get the edge weight between node i and node j
                matrix[i].append(calculate_edge(coordinates[i][0], coordinates[i][1], coordinates[j][0], coordinates[j][1]))
            else:
                matrix[i].append(0)

    return matrix

def mst(G: list, coordinates: list):
    weight = 0
    edgeCount = 0
    pq = PriorityQueue()
    visited = [False]

    edges = []
    for i in range(len(coordinates)-1):
        edges.append(-1) # -1 means it's uninitialized
        visited.append(False)

    # Add first edge to mst
    visited[0] = True

    # Add all adjacent nodes to the queue
    for i in range(len(G[0])):
        if G[0][i] != 0 and not visited[i]: # so it is connected
            pq.put((G[0][i], 0, i)) # Add (weight, from, to) to the queue

    while (not pq.empty() and edgeCount != len(coordinates) - 1):
        edge = pq.get() # get the edge with the lowest weight from the priority queue
        vertex = edge[2] # to_vertex

        if visited[vertex]:
            continue

        edges[edgeCount] = edge 
        edgeCount += 1 
        weight += edge[0] 

        # Add all adjacent nodes to the queue
        visited[vertex] = True 
        for i in range(len(G)):
            if G[vertex][i] != 0 and not visited[i]:
                pq.put((G[vertex][i], vertex, i)) # Add (weight, from, to) to the queue
    
    # There should be V-1 edges, if there are not, this is not a minimum spanning tree since it cannot reach all vertices.
    #if edgeCount != len(coordinates) - 1:
        #return -1 # No MST exisits
    
    return weight

main("graph.txt")