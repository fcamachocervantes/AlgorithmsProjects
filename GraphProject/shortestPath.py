import networkx as nx
from collections import defaultdict

#this function goes through and connects nodes within the group of nodes together
#essentially this connects different exits from a village center together if they're the
#same line type or color type
def connectGroupNodes(start, targets):
    for i in range(len(targets)):
        for j in range(0, len(targets)):
            first = targets[i].split()
            second = targets[j].split()
            if( (first[0] != second[0]) & ( (first[1] == second[1]) | (first[2] == second[2]) ) ):
                node1 = (start + " "+ first[1] + " " + first[2] + " " + first[0] + " INPUT")
                node2 = (start + " " + second[1] + " " + second[2] + " " + second[0] + " OUTPUT")
                graph.add_edge(node1, node2)

def constructNewNode(headerNode, targetNode, color, type):
    #only creating header nodes if this node hasn't been processed before
    #other wise we're just going to create the group nodes that correspond to 
    #the edges in my graph model

    if(graph.has_node(headerNode) == False):
        #adding header node to graph
        graph.add_node(headerNode + " IN")
        graph.add_node(headerNode + " OUT")

    if(graph.has_node(targetNode) == False):
         #adding target node to graph
        graph.add_node(targetNode + " IN")
        graph.add_node(targetNode + " OUT")

    #creating output node from A -> input node of B
    outputNodeA = headerNode + " " + color + " " + type + " " + targetNode + " OUTPUT"
    inputNodeA = headerNode + " " + color + " " + type + " " + targetNode + " INPUT"

    #adding nodes to graph
    graph.add_node(outputNodeA)
    graph.add_node(inputNodeA)

    #creating output node from A -> input node of B
    outputNodeB = targetNode + " " + color + " " + type + " " + headerNode + " OUTPUT"
    inputNodeB = targetNode + " " + color + " " + type + " " + headerNode + " INPUT"

    #adding nodes to graph
    graph.add_node(outputNodeB)
    graph.add_node(inputNodeB)

    #connecting nodes to their endpoints
    graph.add_edge(inputNodeA, headerNode + " OUT")
    graph.add_edge(inputNodeB, targetNode + " OUT")
    graph.add_edge(headerNode + " IN", outputNodeA)
    graph.add_edge(targetNode + " IN", outputNodeB)
    graph.add_edge(outputNodeA, inputNodeB)
    graph.add_edge(outputNodeB, inputNodeA)   

#creating a dictionary to store which edges are connected
#together need this for connecting input nodes to output nodes 
#within the same group
edgeConnections = defaultdict(list)

#getting file to read from
fileInput = open("input.txt", "r")

#initializing empty graph
graph = nx.DiGraph()

#getting header line of the input
inputHeader = fileInput.readline().split()

#getting start node and end node
startNode = inputHeader[2] + " IN"
endNode = inputHeader[3] + " OUT"

#reading line by line to create the graph
for line in fileInput:
    #splitting line into an array
    line = line.split()

    #adding to dictionary all edge connections
    edgeConnections[line[0]].append(line[1] + " " + line[2] + " " + line[3])
    edgeConnections[line[1]].append(line[0] + " " + line[2] + " " + line[3])
    
    #constructing graph nodes
    constructNewNode(line[0], line[1], line[2], line[3])

#using my dictionary of connections to correctly connect inputs to output within a group
for key in edgeConnections:
    connectGroupNodes(key, edgeConnections[key])

#checking edge cases so I can ensure NO PATH is printed when there isn't a path or 
#a node doesn't exist in the graph
allShortestPathsList = []
if((graph.has_node(endNode) == False) | (graph.has_node(startNode) == False)):
    print("NO PATH")
else:
    if(nx.has_path(graph, startNode, endNode) == False):
        print("NO PATH")
    else:
        #getting all shortest paths
        shortestPath = [shortestPaths for shortestPaths in nx.astar_path(graph, startNode, endNode)]
        #making syntax changes to the shortest path to get rid of extra characters from
        #the label that I used to create the graph but aren't needed for the path
        for path in shortestPath:
            outputShortestPath = ""
            for string in path:
                string = string.split()
                if(len(string) == 2):
                    outputShortestPath = outputShortestPath + " " + str(string[0])
                elif(string[4] == 'INPUT'):
                    outputShortestPath = outputShortestPath + " " + str(string[0])
            #because of how I have my model set up I need to cut off the last station becuase it's basically
            #just repeating the final node. It's kinda messy how I'm having to do this to print the path correctly
            outputShortestPath = outputShortestPath[1:]
            outputShortestPath = list(outputShortestPath.split(" "))
            outputShortestPath.pop()
            outputShortestPath = ' '.join(outputShortestPath)
            allShortestPathsList.append(outputShortestPath)

        #after fixing all the strings for the paths to be formated correctly I get the minimum one out of the
        #list of all the possible shortest paths
        print(min(allShortestPathsList))