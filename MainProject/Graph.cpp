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
		std::cout << v.cityName << " , ";
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
