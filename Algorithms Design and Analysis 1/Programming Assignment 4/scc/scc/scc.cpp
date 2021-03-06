// scc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int t = 0, total = 0;
int k = 875714;

vector<int> seq(k);


class Edge;

class Vertex {
	public:
	//construtors
	Vertex() {}
	Vertex(Edge* e) {
		incident.push_back(e);
	}

	int index;
	bool is_explored{ false };
	vector<Edge*> incident; // edges for which the vertex acts as tail

};

class Edge {
public:

	//constructors
	Edge() {}
	Edge(Vertex*t, Vertex*h) : tail{ t }, head{ h } {}

	//keeps track of head and tail
	Vertex* tail;
	Vertex* head;
};


void r_dfs(vector<Vertex>& V, vector<Edge>& E, int index) {

	V[index].is_explored = true;
	
	stack<Vertex>Q;
	Q.push(V[index]);
	vector<Vertex>temp;

	//while the stack is not empty
	while (!Q.empty()) {
		// pop the newest vertex and explore its neighbouring ones
		Vertex V1 = Q.top();
		temp.push_back(V1);
		Q.pop();
		for (int i = 0; i<V1.incident.size(); ++i) {
			Vertex* Vptr = V1.incident[i]->head;
			if (!(Vptr->is_explored)) {
				Vptr->is_explored = true;
				Q.push(*Vptr);
				
			}
		}
		++t;
		
	}

	int p = t-1;

	for (int i = 0;  i < temp.size(); ++i) {
		seq[p] = temp[i].index;
		p = p - 1;
	}
}


void dfs(vector<Vertex>& V, vector<Edge>& E, int index) {

	V[index].is_explored = true;
	stack<Vertex>Q;
	Q.push(V[index]);

	//while the stack is not empty
	while (!Q.empty()) {
		// pop the newest vertex and explore its neighbouring ones
		Vertex V1 = Q.top();
		Q.pop();
		for (int i = 0; i<V1.incident.size(); ++i) {
			Vertex* Vptr = V1.incident[i]->head;
			if (!(Vptr->is_explored)) {
				Vptr->is_explored = true;
				Q.push(*Vptr);
			}
		}
		++total;
		
	}
}



// gives the index value to edge vertex
void fill_index(vector<Vertex>&V) {
	for (int i = 0; i < V.size(); ++i) {
		V[i].index = i;
	}
}

//void r_dfs(vector<Vertex>& V, vector<Edge>& E, Vertex& v) {
//	v.is_explored = true;
//	for (int i = 0; i < v.incident.size(); ++i) {
//		if (!(v.incident[i]->head->is_explored)) {
//			r_dfs(V, E, *(v.incident[i]->head));
//		}
//	}
//	++t;
//	seq[t - 1] = v.index;
//}

//void dfs(vector<Vertex>& V, vector<Edge>& E, Vertex& v) {
//	v.is_explored = true;
//	++total;
//	for (int i = 0; i < v.incident.size(); ++i) {
//		if (!(v.incident[i]->head->is_explored)) {
//			dfs(V, E, *(v.incident[i]->head));
//		}
//	}
//}

int main()
{
	//prepare an adjacency list
	vector<Vertex> V(k);
	vector<Vertex> Vrev(k);

	fill_index(V);
	fill_index(Vrev);

	vector<Edge> E;
	vector<Edge> Erev;

	//connect edges to the vertices
	ifstream ist{ "input.txt" };
	if (!ist)error("Cannot open file");

	int x, y;// x is the tail and  y is the head
	while (ist >> x && ist >> y) {
		E.push_back(Edge{ &V[x - 1], &V[y - 1] });
		Erev.push_back(Edge{ &Vrev[y - 1], &Vrev[x - 1] });
	}

	//connect vertices to edges
	for (int i = 0; i < E.size(); ++i) {
		E[i].tail->incident.push_back(&E[i]);
		Erev[i].tail->incident.push_back(&Erev[i]);
	}

	
	// reverse dfs to calculate finishing time
	for (int i = Vrev.size() - 1; i >= 0; --i) {
		if (!(Vrev[i].is_explored)) r_dfs(Vrev, Erev, i);
	}
	

	// dfs according to decreasing finishing time
	vector<int>result;
	for (int i = seq.size() - 1; i >= 0; --i) {
		int j = seq[i];
		if (!(V[j].is_explored)) {
			dfs(V, E, j);
			result.push_back(total);
			total = 0;
		}
	}

	sort(result.begin(),result.end());
	for (int i = 1; i <= 5; ++i) {
		cout << result[result.size() - i] << endl;
	}
	getchar();

    return 0;
}

