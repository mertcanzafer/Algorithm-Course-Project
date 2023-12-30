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
}
