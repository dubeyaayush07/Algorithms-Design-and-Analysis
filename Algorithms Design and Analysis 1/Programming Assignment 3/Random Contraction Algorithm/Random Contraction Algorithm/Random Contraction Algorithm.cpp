// Random Contraction Algorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"




class Edge;

class Vertex {
public:
	//construtors
	Vertex() {}
	Vertex(Edge* e){
		incident.push_back(e);
	}
		
	//data
	int index;
	vector<Edge*> incident;
};

class Edge {
public:

	//constructors
	Edge() {}
	Edge(Vertex*x1, Vertex*x2) : e1{ x1 }, e2{ x2 } {}

	//data
	Vertex* e1;
	Vertex* e2;
};

void fill_index(vector<Vertex>&V) {
	for (int i = 0; i < V.size(); ++i) {
		V[i].index = i;
	}
}

int choose_edge(vector<Edge>&ar) {
	int number = rand() % (ar.size());
	return number;
}

void blueprint_copy(vector<Vertex>& V, vector<Edge>& E, vector<Vertex>& BV, vector<Edge>& BE) {
	V.clear();
	V.resize(BV.size());
	fill_index(V);
	E.clear();

	for (int i = 0; i < BE.size(); ++i) {

		int x1 = BE[i].e1->index, x2 = BE[i].e2->index;
		E.push_back(Edge{ &V[x1], &V[x2] });

		V[x1].incident.push_back(&E[(E.size()) - 1]);
		V[x2].incident.push_back(&E[(E.size()) - 1]);

	}

}

void Union(vector<Vertex>& V, vector<Edge>& E, int edge) {

	//contracted graph
	vector<Vertex>V1(V.size()-1);
	fill_index(V1);
	vector<Edge>E1;

	// index of the vertices that are going to be merged 
	int n1 = min(E[edge].e1->index,E[edge].e2->index);
	int n2 = max(E[edge].e1->index, E[edge].e2->index);
	

	//contract and use fused vertex in place of n1 and n2
	for (int i = 0; i < E.size(); ++i) {
		if (i != edge) {
			int x1 = E[i].e1->index, x2 = E[i].e2->index;
			// if x1 or x2 equal to bigger of the vertices make it equal to the smaller one 
			if (x1 == n2) x1 = n1;
			if (x2 == n2) x2 =n1;
			// if x1 or x2  bigger than n2 decrease their index by 1
			if (x1 > n2) --x1;
			if (x2 > n2) --x2;

			E1.push_back(Edge{ &V1[x1], &V1[x2] });

			V1[x1].incident.push_back(&E1[(E1.size()) - 1]);
			V1[x2].incident.push_back(&E1[(E1.size()) - 1]);
			

		}
	}

	//replace the original graph with the contracted one
	blueprint_copy(V, E, V1, E1);

}

void remove_sloops(vector<Vertex>& V, vector<Edge>& E) {
	//graph without self loops

	vector<Vertex>V1(V.size());
	fill_index(V1);
	vector<Edge>E1;

	for (int i = 0; i < E.size(); i++){
		//if the the edge is not a self loop
		if (E[i].e1->index != E[i].e2->index) {

			int x1 = E[i].e1->index, x2 = E[i].e2->index;
			E1.push_back(Edge{ &V1[x1], &V1[x2] });

			V1[x1].incident.push_back(&E1[(E1.size()) - 1]);
			V1[x2].incident.push_back(&E1[(E1.size()) - 1]);
			
		}

	}

	//replace the original graph with the one without self loops
	blueprint_copy(V, E, V1, E1);

}


int min_cut(vector<Vertex> V, vector<Edge> E) {
	int less = 10000, count = 200;
	for (int i = 0; i < count; ++i) {

		vector<Vertex> V_temp;
		vector<Edge> E_temp;
		blueprint_copy(V_temp, E_temp, V, E);

		while (V_temp.size() > 2) {
			int edge = choose_edge(E_temp);

			//contract the graph 
			Union(V_temp, E_temp, edge);

			//remove self loops
			remove_sloops(V_temp, E_temp);
		}
		if (i == 0) {
			less = V_temp[0].incident.size();
		}
		else {
			if (less > V_temp[0].incident.size()) less = V_temp[0].incident.size();
		}
	}
	return less;
}

int main()
try
{
	srand((unsigned)time(0));//seed

	// represent the values in an adjacency list

	vector<Vertex> V(200);
	fill_index(V);
	vector<Edge> E;

	ifstream ist{ "input.txt" };
	if (!ist) error("Cannot open file");
	string temp;

	while(getline(ist, temp)){
		istringstream is{ temp };
		int x,y;
		is >> x;
		while (is >> y) {
			if (y > x) {
				E.push_back(Edge{ &V[x - 1], &V[y - 1] });

				V[x - 1].incident.push_back(&E[(E.size()) - 1]);
				V[y - 1].incident.push_back(&E[(E.size()) - 1]);
			}
		}

	}

	// calculate and print minimum cut
	cout << min_cut(V, E) << endl;

    return 0;
}
catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}

