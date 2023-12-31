#pragma once
#include "CityToPlateConversion.h"
#include<iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
namespace graph
{
	struct Entity
	{
		std::string cityName;
		int weight;
	};

	class Vertex
	{
	public:
		Vertex(std::string& City, std::vector<Entity> &a)noexcept;
		void printAdjacents()const;
		static int V; // # of vertex objs
	public:
		std::string CityName;
		std::vector<Entity>adjacents;
	};

	class Graph
	{
	public:
		Graph()noexcept :VertexCount{ 0 }, EdgeCount{ 0 } {};
		Graph(std::vector<Vertex>& vertexList)noexcept;
		int getVsize()const;
		int getEsize();
		void printGraph()const;

	private:
		std::vector<Vertex> vertexList;
		std::unordered_map<std::string, int> DegreeCount;
		int VertexCount; // # of vertices
		int EdgeCount;	// # of edges
	};
}

