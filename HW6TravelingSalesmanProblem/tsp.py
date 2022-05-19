import string
import sys
from itertools import permutations
from tkinter import Y
import math
from unittest import result


def getLength(coordinates: list, vertex1: int, vertex2: int):
    x1 = coordinates[vertex1][0]
    y1 = coordinates[vertex1][1]
    x2 = coordinates[vertex2][0]
    y2 = coordinates[vertex2][1]

    squarex = (x1-x2)*(x1-x2)
    squarey = (y1-y2)*(y1-y2)

    number = round(math.sqrt(squarex+squarey))

    return number


def getHighestDegree(adjList: list):
    highestLength = 0
    high = -1
    for i in range(0, len(adjList)):
        if len(adjList[i]) > highestLength:
            highestLength = len(adjList[i])
            high = i
    return high


def makeAdjacencyMatrix(coordinates: list):
    # coordinates = list of coordinates, n = number of vertices
    # initialization of adjacency matrix
    n = len(coordinates)
    adjMatrix = []
    for i in range(0, n):
        pointx = ['']*n
        a = len(pointx)
        adjMatrix.append(pointx)

    # make adjacency matrix
    for i in range(0, n):
        for j in range(i, n):
            # hopefully saves time in building matrix
            if adjMatrix[i][j] == '' or adjMatrix[j][i] == '':
                length = getLength(coordinates, i, j)
                adjMatrix[i][j] = length
                adjMatrix[j][i] = length
    return adjMatrix


def MST(adjMatrix: list, n: int):

    discovered = [False]*n

    # initialize adjacency list of the MST
    MSTAdjList = []
    for i in range(0, n):
        list = []
        MSTAdjList.append(list)

    # first lowest edge, nothing is discovered
    counter = 0  # length of minimum spanning tree
    lowestEdge = 10000
    vertex1 = -1
    vertex2 = -1

    for i in range(0, n):  # search for lowest integer
        for j in range(0, n):
            tempLow = adjMatrix[i][j]
            if tempLow < lowestEdge and tempLow != 0:
                lowestEdge = tempLow
                vertex1 = i
                vertex2 = j
    # end search
    counter += lowestEdge
    discovered[vertex1] = True
    discovered[vertex2] = True
    MSTAdjList[vertex2].append(vertex1)
    MSTAdjList[vertex1].append(vertex2)

    # actual MST loop
    for h in range(1, n-1):
        lowestEdge = 1000000
        vertex1 = -1
        vertex2 = -1

        # we want the vertices to be between discovered and undiscovered
        for i in range(0, n):  # search for lowest integer
            if discovered[i] == False:
                continue
            for j in range(0, n):

                if discovered[j] == True:
                    continue

                tempLow = adjMatrix[i][j]
                if tempLow < lowestEdge and tempLow != 0:
                    lowestEdge = tempLow
                    vertex1 = i
                    vertex2 = j
        # end search

        counter += lowestEdge
        discovered[vertex1] = True
        discovered[vertex2] = True
        MSTAdjList[vertex2].append(vertex1)
        MSTAdjList[vertex1].append(vertex2)

    # print(counter)

    return MSTAdjList


def tsp(MST: list, coordinates: int, n: int, adjMatrix: list):
    length = 0
    order = []  # store traversal order
    source = getHighestDegree(MST)

    # initialize color
    visited = [False]*n
    # "white" = not touched, "green" = in queue, "red" = already scanned
    traversalStack = []
    traversalStack.append(source)
    visited[source] = True

    while len(traversalStack) > 0:
        work = traversalStack.pop()
        order.append(work)
        for i in reversed(range(len(MST[work]))):
            if visited[MST[work][i]] == False:
                traversalStack.append(MST[work][i])
                visited[MST[work][i]] = True

    # calculating distance
    # for i in range(0, len(order)-1):
    #     length += getLength(coordinates, order[i], order[i+1])
    # length+= getLength(coordinates, order[n-1], order[0])

    for i in range(0, len(order)-1):
        length += adjMatrix[order[i]][order[i+1]]
    length += adjMatrix[order[n-1]][order[0]]

    result = []
    result.append(str(length))
    for i in range(0, len(order)):
        result.append(str(order[i]))
    return result



def nearestNeighbor(adjMatrix:list, n):
    visited = [False]*n
    start = 0
    node = start
    visited[0] = True
    order = [0]
    length = 0
    tempLow = -1
    for i in range (0,n-1):
        lowest = 100000
        for j in range(0,n):
            if adjMatrix[node][j]<lowest and visited[j]==False:
                lowest = adjMatrix[node][j]
                tempLow = j
        length+=lowest
        node = tempLow
        order.append(node)
        visited[node] = True
    length+=adjMatrix[node][start]
        

    result = []
    result.append(str(length))
    for i in range(0, len(order)):
        result.append(str(order[i]))
    return result

    

def main(argv):

    fileName = str(argv)
    # it's messy but it fixes things
    fileName = fileName.replace('[', '').replace('\'', '').replace(']', '')

    # fileName = 'tsp_example_0.txt'

    input = open(fileName)

    # number of arguments
    n = int(input.readline())

    # initialize point list
    pointList = []

    # receiving input
    for i in range(0, n):
        inputAr = []

        line = input.readline()

        inputAr = line.split(' ')

        # clean input array
        # why did you make me do this
        for i in reversed(range(0, len(inputAr))):
            if inputAr[i] == '' or inputAr[i] == ' ':
                inputAr.pop(i)

        point = (int(inputAr[1]), int(inputAr[2]))

        pointList.append(point)
    # end input loop

    input.close()

    adjMatrix = makeAdjacencyMatrix(pointList)

    # adjList = MST(adjMatrix, n)

    # TSPResult = tsp(adjList, pointList, n, adjMatrix)

    # output = open(fileName+'.tour', 'w')
    # for line in TSPResult:
    #     output.write(line)
    #     output.write('\n')

    # # for i in range(0, len(TSPResult)):
    # #     print(TSPResult[i])

    # output.close()

    nearbyResult = nearestNeighbor(adjMatrix, n)

    output = open(fileName+'.tour', 'w')
    for line in nearbyResult:
        output.write(line)
        output.write('\n')

    # for i in range(0, len(TSPResult)):
    #     print(TSPResult[i])

    output.close()


if __name__ == "__main__":
    main(sys.argv[1:])


# main()

# n = readline()
# for i in range(0,n):    
#     receive inputs in lines as string

#     inputArray = split(input string)

#     adjList = makeAdjacencyList(inputArray)

#     nearestNeighbor(adjList): # actual algorithm
#         node = 0
#         visited = [False]*n
#         visited[startNode] = True
#         length = 0
#         order = []
#         order.push(node)

#         for j in range(n):
#             search for lowestedge connected to node

#             length += getLength(node, lowestEdge)
#             node = lowestEdge
#             order.push(node)

#         result[]
#         result.append(length)
#         result.append(order)
#         return result
#     print(result)
    





