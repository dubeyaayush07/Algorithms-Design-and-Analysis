
#include "stdafx.h"



class Edge;

class Vertex {
public:
	//construtors
	Vertex() {}
	Vertex(Edge* e) {
		incident.push_back(e);
	}

	int index;
	int dist{ -1 };
	bool in_set{ false };
	vector<Edge*> incident;
};

class Edge {
public:

	//constructors
	Edge() {}
	Edge(Vertex*x1, Vertex*x2, int weight) : e1{ x1 }, e2{ x2 }, e_weight{weight} {}

	Vertex* e1;
	Vertex* e2;
	int e_weight;
};

// gives the index value to edge vertex
void fill_index(vector<Vertex>&V) {
	for (int i = 0; i < V.size(); ++i) {
		V[i].index = i;
	}
}

//Dijkstra's shortest-path algorithm
void shortest_path_fill(vector<Vertex>& V, vector<Edge>& E, int index) {

	V[index].dist = 0;
	V[index].in_set = true;
	vector<Vertex>X{ V[index] };

	while (X.size() != V.size()) {
		int min = -1;
		Vertex* selected = &V[index];
		for (int i = 0; i < E.size(); ++i) {
			if (E[i].e1->in_set && !(E[i].e2->in_set)) {
				int length = E[i].e1->dist + E[i].e_weight;
				if (length < min || min == -1) {
					min = length;
					selected = (E[i].e2);
				}
			}
			else if (E[i].e2->in_set && !(E[i].e1->in_set)) {
				int length = E[i].e2->dist + E[i].e_weight;
				if (length < min || min == -1) {
					min = length;
					selected = (E[i].e1);
				}
			}
		}

		if (min != -1) {
			selected->dist = min;
			selected->in_set = true;
			X.push_back(*selected);
		}

	}
}




int main(){
	//prepare an adjacency list
	vector<Vertex> V(200);
	fill_index(V);
	vector<Edge> E;

	//connect edges to the vertices
	ifstream ist{ "input.txt" };
	if (!ist) error("Cannot open file");
	string temp;

	while (getline(ist, temp)) {
		istringstream is{ temp };
		int x, y, e;
		char ch;
		is >> x;
		while (is >> y >> ch >> e) {
			if (y > x) {
				E.push_back(Edge{ &V[x - 1], &V[y - 1], e });
			}
		}

	}

	//connect vertices to edges
	for (int i = 0; i < E.size(); ++i) {
		E[i].e1->incident.push_back(&E[i]);
		E[i].e2->incident.push_back(&E[i]);
	}


	shortest_path_fill(V, E, 0);

	vector<int> test{ 7,37,59,82,99,115,133,165,188,197 };
	for (int i = 0; i < test.size(); ++i) {
		cout << test[i] << ":  " << V[test[i]-1].dist << endl;
	}

	getchar();

	return 0;
}

