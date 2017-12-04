from collections import heapq
#pair:(vertex, weight)
adjList = {1:[(2,10),(4,5)], 
		2:[(3,1),(4,2)], 
		3:[(5,4)],
		4:[(2,3),(3,9),(5,2)],
		5:[(1,7),(3,6)]}


solution = []
heap = heapq()

def dijkstra(adjList, source, target):
	#vertex in heap: (distance, pathlen, name, parent)
	heappush(heap, [0, 0, source, 0])
	for vertex in adjList:
		if(vertex != source):
			heappush(heap, [float('INF'), float('INF'), vertex, 0])
	
	while currentVertex[2] != target:
		currentVertex = heappop(heap)
		solution.append(currentVertex)
		decreaseKey(solution, adjList, heap)

	return solution

def decreaseKey(solution, adjList, heap)
	for vertexInSol in solution:
		for pair in adjList[vertex[2]]:
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

result = dijkstra(adjList, 1, 5)
print result



