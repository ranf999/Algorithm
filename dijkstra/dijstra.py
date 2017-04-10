import heapq

#pair:(vertex, weight)
adjList = {1:[(2,10),(4,5)], 
		2:[(3,1),(4,2)], 
		3:[(5,4)],
		4:[(2,3),(3,9),(5,2)],
		5:[(1,7),(3,6)]}


heap = []
def decreaseKey(solution, adjList, heap):
    for vertexInSol in solution:
        for pair in adjList[vertexInSol[2]]:
            for vertexInHeap in heap:
                if(vertexInHeap[2] == pair[0]):
                    if(pair[1] + vertexInSol[0] == vertexInHeap[0]):
                        if(vertexInHeap[1] > vertexInSol[1] + 1):
                            vertexInHeap[1] = vertexInSol[1] + 1
                            vertexInHeap[3] = vertexInSol[2]
                    if(pair[1] + vertexInSol[0] < vertexInHeap[0]):
                        vertexInHeap[0] = pair[1] + vertexInSol[0]
                        vertexInHeap[1] = vertexInSol[1] + 1
		        vertexInHeap[3] = vertexInSol[2]


def dijkstra(adjList, source, target):
	#vertex in heap: (distance, pathlen, name, parent)
        solution = []
	heapq.heappush(heap, [0, 0, source, 0])
	for vertex in adjList:
		if(vertex != source):
			heapq.heappush(heap, [float('INF'), float('INF'), vertex, 0])
    
	heapq.heapify(heap)
        currentVertex = [0,0,0,0]
	while currentVertex[2] != target:
		currentVertex = heapq.heappop(heap)
		solution.append(currentVertex)
		decreaseKey(solution, adjList, heap)
                heapq.heapify(heap)
	return solution

def findPath(solution, source):
    size = len(solution)
    path = []
    if size == 0:
        return path
    vertexInSol = solution[size - 1]
    while vertexInSol[2] != source:
        path.append(vertexInSol)
        for vertex in solution:
            if vertex[2] == vertexInSol[3]:
                vertexInSol = vertex
    path.append(vertexInSol)
    return path

result = dijkstra(adjList, 1, 5)

print result
print findPath(result, 1)



