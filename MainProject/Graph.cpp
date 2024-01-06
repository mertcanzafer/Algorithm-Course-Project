#include "Graph.h"
using namespace graph;

int Vertex::V = 0;

Vertex::Vertex(std::string& City, std::vector<Entity>& a) noexcept
	:CityName{City},adjacents{a}
{
	V++;
}

void Vertex::printAdjacents()const
{
	for (auto& v : adjacents)
	{
		std::cout << v.cityName<<"("<<v.weight<<")" << " , ";
	}
}

Graph::Graph(std::vector<Vertex>& vertexList) noexcept
	:vertexList{vertexList},VertexCount{Vertex::V},EdgeCount{0}
{
	for (const auto& v : vertexList)
	{
		DegreeCount[v.CityName] = v.adjacents.size();
	}
}

int Graph::getVsize() const
{
	return VertexCount;
}

int Graph::getEsize()
{
	EdgeCount = 0;
	for (auto& d : DegreeCount)
	{
		EdgeCount += d.second;
	}
	EdgeCount = EdgeCount / 2;
	return EdgeCount;
}

void Graph::printGraph() const
{
	for (auto& v : vertexList)
	{
		std::cout << v.CityName << ": ";
		v.printAdjacents();
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Graph::ConstructDistanceTable(const char* fileLoc)
{
	std::fstream file;
	std::string SkipFirstLine; // Discard first line from the text file
	file.open(fileLoc,std::ios::in);

	if (!file) { std::cout << "No such a file exits." << std::endl; return; }

	std::string line;
	std::getline(file, SkipFirstLine); // Read the first line and jump to newline 2

	while (!file.eof())
	{
		std::getline(file, line);
		std::vector<int> row;
		std::string value; // The values that will be reading

		std::istringstream iss(line);
		// Skip the first two columns
		std::getline(iss, value, ';');
		std::getline(iss, value, ';');

		while (std::getline(iss, value, ';'))
		{
			row.push_back(std::stoi(value)); // Convert string to int
		}
		DistanceTable.push_back(row);
	}
	file.close();
}

void Graph::printDistanceTable() const
{
	for (const auto& row : DistanceTable)
	{
		for (auto val : row)
		{
			std::cout << val << " , ";
		}
		std::cout << std::endl;
	}
}

void Graph::SetWeights()
{
	int col = 0;

	// Traverse the table
	for (size_t i = 0; i < DistanceTable.size(); i++)
	{
		for (size_t j = 0; j < DistanceTable.size(); j++)
		{
			col = j + 1;
			// set weight
			for (auto& a : vertexList[i].adjacents)
			{
				if (Citiy_To_PlateNumber[a.cityName] == col)
				{
					a.weight = DistanceTable[i][j];
				}
			}
		}
	}
}

void
Graph::findKClosestCities(std::string& SourceCity, int k)
{

	/*
	   Create two array prev and dist with fixed size as numOfvertex
	   set dist array as Infinite num
	   set prev array as -1
	   Create a priaroty queue that will hold dist and vertex
	*/
	const int n = VertexCount;
	std::vector<int> dist(n, 9999);
	std::vector<int> prev(n, -1);
	int start = Citiy_To_PlateNumber[SourceCity] - 1;  // Sub 1 because Because if vertex = 0, then plate num = 1
	dist[start] = 0;

	std::priority_queue<std::pair<int, int>,
	std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pQ;
	pQ.push({ 0,start });

	while (!pQ.empty())
	{
		int u = pQ.top().second;
		pQ.pop();

		// Traverse adjacents with related to number u coming from queue
		std::vector<Entity>::iterator i;
		for (i = vertexList[u].adjacents.begin(); i != vertexList[u].adjacents.end(); i++)
		{
			if ((dist[u] + (i->weight)) < dist[Citiy_To_PlateNumber[i->cityName] - 1])
			{
				dist[Citiy_To_PlateNumber[i->cityName] - 1] = (dist[u] + (i->weight));
				prev[Citiy_To_PlateNumber[i->cityName] - 1] = u;
				pQ.push({ dist[Citiy_To_PlateNumber[i->cityName] - 1],Citiy_To_PlateNumber[i->cityName] - 1 });
			}
		}
	}

	// Sort the dist vector
	std::vector<std::pair<int, int>> distances;
	for (int i = 0; i < n; i++) {
		distances.push_back({ dist[i], i });
	}
	std::sort(distances.begin(), distances.end());

	if (k > n) { std::cout << "Invalid number k!!!\n"; return; }

	for (int i = 0; i < k + 1; i++)
	{
		int v = distances[i].second;
		std::cout << vertexList[v].CityName << " - ";
	}
	std::cout << "\n";
}

void Graph::
FindShortestPath(std::string& SourceCity, std::string& DestCity)
{
	/*
	   This func will use the same alg Djikstra's method
	   and it will print out the whole path
	*/
	const int n = VertexCount;
	std::vector<int> dist(n, 9999);
	std::vector<int> prev(n, -1);

	int start = Citiy_To_PlateNumber[SourceCity] - 1;
	int dest = Citiy_To_PlateNumber[DestCity] - 1;
	dist[start] = 0;

	std::priority_queue<std::pair<int, int>, 
	std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pQ;
	pQ.push({ 0,start });

	while (!pQ.empty())
	{
		int u = pQ.top().second;
		pQ.pop();

		std::vector<Entity>::iterator i;
		for (i = vertexList[u].adjacents.begin(); i != vertexList[u].adjacents.end(); i++)
		{
			if ((dist[u] + (i->weight)) < dist[Citiy_To_PlateNumber[i->cityName] - 1])
			{
				dist[Citiy_To_PlateNumber[i->cityName] - 1] = (dist[u] + (i->weight));
				prev[Citiy_To_PlateNumber[i->cityName] - 1] = u;
				pQ.push({ dist[Citiy_To_PlateNumber[i->cityName] - 1],Citiy_To_PlateNumber[i->cityName] - 1 });
			}
		}
	}
	printPath(prev, dist, start, dest);
}

void Graph:: 
FindShortestPath(std::string& SourceCity, int& PlateId)
{
	const int n = VertexCount;
	std::vector<int> dist(n, 9999);
	std::vector<int> prev(n, -1);

	int start = Citiy_To_PlateNumber[SourceCity] - 1; // Getting plate id for inputted city. but sub 1 becuase arrays begin with 0
	int dest = PlateId - 1;
	dist[start] = 0;

	std::priority_queue<std::pair<int, int>,
		std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pQ;
	pQ.push({ 0,start });

	while (!pQ.empty())
	{
		int u = pQ.top().second;
		pQ.pop();

		std::vector<Entity>::iterator i;
		for (i = vertexList[u].adjacents.begin(); i != vertexList[u].adjacents.end(); i++)
		{
			if ((dist[u] + (i->weight)) < dist[Citiy_To_PlateNumber[i->cityName] - 1])
			{
				dist[Citiy_To_PlateNumber[i->cityName] - 1] = (dist[u] + (i->weight));
				prev[Citiy_To_PlateNumber[i->cityName] - 1] = u;
				pQ.push({ dist[Citiy_To_PlateNumber[i->cityName] - 1],Citiy_To_PlateNumber[i->cityName] - 1 });
			}
		}
	}
	printPath(prev, dist, start, dest);
}

void Graph::printPath(std::vector<int>& prev, std::vector<int>& dist, int start, int dest)
{
	std::cout << "Shorters Distance from "<<vertexList[start].CityName<<" to "<<vertexList[dest].CityName<<": ";

	// print path
	printCities(prev, start, dest);
	std::cout << "\n";
}

void Graph::
printCities(std::vector<int>& prev, int start, int dest)
{
	if (dest == -1 || dest == start)
	{
		std::cout << vertexList[start].CityName;
		return;
	}

	printCities(prev, start, prev[dest]);
	std::cout << " - "<<vertexList[dest].CityName;
}