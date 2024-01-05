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
	const int n = VertexCount;
	std::vector<int> dist(n, 9999);
	std::vector<int> prev(n, -1);

	int start = Citiy_To_PlateNumber[SourceCity] - 1; // Getting plate id for inputted city. but sub 1 becuase arrays begin with 0
	dist[start] = 0;

	// Create an empty set
	std::set<int> S;
	// Create an empty queue
	std::list<int> Q;

	for (int i = 0; i < n; i++)
		Q.push_back(i);

	while (!Q.empty())
	{
		std::list<int>::iterator it;
		it = std::min_element(Q.begin(), Q.end());
		int u = *it;
		Q.remove(u);
		S.insert(u);
		std::vector<Entity>::iterator i;
		//std::cout << u<<std::endl;
		for (i = vertexList[u].adjacents.begin(); i != vertexList[u].adjacents.end(); i++)
		{
			//std::cout << Citiy_To_PlateNumber[i->cityName] - 1 << std::endl;
			if ((dist[u] + (i->weight)) < dist[Citiy_To_PlateNumber[i->cityName] - 1])
			{
				//std::cout<<"val: "<< Citiy_To_PlateNumber[i->cityName] - 1 <<std::endl;
				dist[Citiy_To_PlateNumber[i->cityName] - 1] = (dist[u] + (i->weight));
				//std::cout << Citiy_To_PlateNumber[i->cityName] - 1 << " : " << dist[Citiy_To_PlateNumber[i->cityName] - 1]<<std::endl;
				prev[Citiy_To_PlateNumber[i->cityName] - 1] = u;
			}
		}
	}

	std::vector<std::pair<int,int>> nodesAndDistances;

	for (int i = 0; i < n; i++)
	{
		if (i != start)
		{
			nodesAndDistances.push_back({ i,dist[i] });
		}
	}
	// Sort the vector to dist

	std::sort(nodesAndDistances.begin(), nodesAndDistances.end(),
		[](const std::pair<int,int>& a, const std::pair<int, int>& b)
		{
			return b.second > a.second;
		}
	);

	if (k > n) { std::cout << "Unvalid number k!!!" << std::endl; return; }

	for (int i = 0; i < k; i++)
	{
		std::cout << vertexList[nodesAndDistances[i].first].CityName<<" , ";
	}
}

void Graph::
FindShortestPath(std::string& SourceCity, std::string& DestCity)
{
	const int n = VertexCount;
	std::vector<int> dist(n, 9999);
	std::vector<int> prev(n, -1);

	int start = Citiy_To_PlateNumber[SourceCity] - 1; // Getting plate id for inputted city. but sub 1 becuase arrays begin with 0
	int dest = Citiy_To_PlateNumber[DestCity] - 1;
	bool flag = false;
	if (start > dest)
	{
		// swap
		flag = true;
		int temp = start;
		start = dest;
		dest = temp;
	}
	dist[start] = 0;

	// Create an empty set
	std::set<int> S;
	// Create an empty queue
	std::list<int> Q;

	for (int i = 0; i < n; i++)
		Q.push_back(i);

	while (!Q.empty())
	{
		std::list<int>::iterator it;
		it = std::min_element(Q.begin(), Q.end());
		int u = *it;
		Q.remove(u);
		S.insert(u);
		std::vector<Entity>::iterator i;
		//std::cout << u<<std::endl;
		for (i = vertexList[u].adjacents.begin(); i != vertexList[u].adjacents.end(); i++)
		{
			//std::cout << Citiy_To_PlateNumber[i->cityName] - 1 << std::endl;
			if ((dist[u] + (i->weight)) < dist[Citiy_To_PlateNumber[i->cityName] - 1])
			{
				//std::cout<<"val: "<< Citiy_To_PlateNumber[i->cityName] - 1 <<std::endl;
				dist[Citiy_To_PlateNumber[i->cityName] - 1] = (dist[u] + (i->weight));
				//std::cout << Citiy_To_PlateNumber[i->cityName] - 1 << " : " << dist[Citiy_To_PlateNumber[i->cityName] - 1]<<std::endl;
				prev[Citiy_To_PlateNumber[i->cityName] - 1] = u;
			}
		}
	}
	printPath(prev,start, dest,flag); 
}

void Graph:: 
FindShortestPath(std::string& SourceCity, int& PlateId)
{
	const int n = VertexCount;
	std::vector<int> dist(n, 9999);
	std::vector<int> prev(n, -1);

	int start = Citiy_To_PlateNumber[SourceCity] - 1; // Getting plate id for inputted city. but sub 1 becuase arrays begin with 0
	int dest = PlateId - 1;
	bool flag = false;
	if (start > dest)
	{
		// swap
		flag = true;
		int temp = start;
		start = dest;
		dest = temp;
	}
	dist[start] = 0;

	// Create an empty set
	std::set<int> S;
	// Create an empty queue
	std::list<int> Q;

	for (int i = 0; i < n; i++)
		Q.push_back(i);

	while (!Q.empty())
	{
		std::list<int>::iterator it;
		it = std::min_element(Q.begin(), Q.end());
		int u = *it;
		Q.remove(u);
		S.insert(u);
		std::vector<Entity>::iterator i;
		//std::cout << u<<std::endl;
		for (i = vertexList[u].adjacents.begin(); i != vertexList[u].adjacents.end(); i++)
		{
			//std::cout << Citiy_To_PlateNumber[i->cityName] - 1 << std::endl;
			if ((dist[u] + (i->weight)) < dist[Citiy_To_PlateNumber[i->cityName] - 1])
			{
				//std::cout<<"val: "<< Citiy_To_PlateNumber[i->cityName] - 1 <<std::endl;
				dist[Citiy_To_PlateNumber[i->cityName] - 1] = (dist[u] + (i->weight));
				//std::cout << Citiy_To_PlateNumber[i->cityName] - 1 << " : " << dist[Citiy_To_PlateNumber[i->cityName] - 1]<<std::endl;
				prev[Citiy_To_PlateNumber[i->cityName] - 1] = u;
			}
		}
	}
	printPath(prev, start, dest, flag);
}

void Graph::printPath(std::vector<int>& prev, int start,int dest, bool& isSwapped)
{
	std::vector<std::string>City_vec;
	std::vector<int> path;
	int current = dest;
	while (current != -1) {
		path.push_back(current);
		current = prev[current];
	}

	for (int i = path.size() - 1; i >= 0; --i) {
		City_vec.push_back(vertexList[path[i]].CityName);
	}
	if (isSwapped)
	{
		std::cout << "Shortest path from " << vertexList[dest].CityName << " to " << vertexList[start].CityName << ": ";
		std::cout << path.size() << " ";
		std::reverse(City_vec.begin(), City_vec.end());
	}
	else {
		std::cout << "Shortest path from " << vertexList[start].CityName << " to " << vertexList[dest].CityName << ": ";
		std::cout << path.size() << " ";
	}
	
	for (const auto& v : City_vec)
	{
		std::cout << v;
		std::cout << " , ";

	}
	std::cout << "\n";
}