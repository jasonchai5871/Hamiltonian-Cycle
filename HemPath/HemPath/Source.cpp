#include <ctime>
#include<iostream>
#include<stdlib.h>

using namespace std;
//int x = 0, d[99][2], y = 0;
int gethem(int e, int v, int edge[500][2]);
int greedysearchHem(int e, int v, int edge[500][2]);
bool findhem(int e, int v, int edge[500][2], int pos, int start, int state, int prev);
bool checknote(int e, int edge[500][2], int pos, int i);
int notestate[100] = {}, notechecked[100], position;
double timecheck = 0;

// A function to generate random graph.
void GenerateRandGraphs(int NOE, int NOV)
{
	int i, j, count;
	int edge[500][2] = {};
	int h[999] = {}, c = 0;
	clock_t start;
	i = 0;
	// Build a connection between two random vertex.

	while (c < NOV) {
		h[c] = rand() % NOV + 1;
		for (int count = 0; count < c; count++) {
			if (h[count] == h[c]) {
				c--;
			}
		}
		c++;
	}
	//for (int g = 0; g < NOV; g++) {
		//cout << h[g] << ",";
	//}
	//cout << endl;

	while (i < NOE)
	{

		if (i < (NOE - NOV)) {
			edge[i][0] = rand() % NOV + 1;
			edge[i][1] = rand() % NOV + 1;
		}
		else {
			int z = i % NOV;

			if (z < (NOV - 1)) {
				edge[i][0] = h[z];
				edge[i][1] = h[z + 1];
			}
			else {
				edge[i][0] = h[z];
				edge[i][1] = h[0];
			}
			for (j = 0; j < i; j++)
			{
				if ((edge[i][0] == edge[j][0] && edge[i][1] == edge[j][1]) || (edge[i][0] == edge[j][1] && edge[i][1] == edge[j][0])) {
					edge[i][0] = rand() % NOV + 1;
					edge[i][1] = rand() % NOV + 1;
				}
			}

		}
		if (edge[i][0] == edge[i][1])
			continue;
		else
		{

			for (j = 0; j < i; j++)
			{
				if ((edge[i][0] == edge[j][0] && edge[i][1] == edge[j][1]) || (edge[i][0] == edge[j][1] && edge[i][1] == edge[j][0]))

					i--;
			}

		}

		i++;
	}

	for (int o = 0; o < NOE; o++) {
		int a, b;
		a = edge[o][0];
		b = edge[o][1];
		if (edge[o][0] > edge[o][1]) {
			edge[o][0] = b;
			edge[o][1] = a;
		}

	}
	/*for (int o = 0; o < NOV; o++) {
		for (int k = 0; k < NOE; k++) {
			if (edge[k][0] == o + 1) {
				cout << edge[k][0] << " ," << edge[k][1] << endl;
			}
		}
	}*/
	start = clock();
	double duration;

	
	//cout << "The local date and time is: " << str << endl;
	
	gethem(NOE, NOV, edge);
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	timecheck += duration;
	cout << "Exhaustive search duration is: " << duration << endl;
	duration = 0;

	start = clock();
	greedysearchHem(NOE, NOV, edge);
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Greedy search duration is: " << duration << endl;
	cout << endl;
	//cout << "The local date and time is: " << str2 << endl;

}
//Check valid path
bool checknote(int e, int edge[500][2], int pos, int i) {
	bool check = false;
	//cout << "Check position:" << pos << endl;
	for (int k = 0; k < pos; k++) {
		//cout << notechecked[k] << ",";
		if (notechecked[k] == edge[i][0]) {
			//cout << k;
			for (int l = 0; l < pos; l++) {
				if (notechecked[l] == edge[i][1]) {
					check = true;
					break;
				}
				else {
				}
			}
		}
	}
	//cout << endl;
	return check;
}
//Exhaustive search
bool findhem(int e, int v, int edge[500][2], int pos, int start, int state, int prev) {

	notechecked[pos - 1] = state;
	//cout << "position: " << pos;
	//cout << " state: "<<state << ",";

	if (pos == v) {
		//cout << endl;
		for (int i = 0; i < e; i++) {
			if (edge[i][0] == state || edge[i][1] == state) {

				if (edge[i][0] == start || edge[i][1] == start) {
					cout << start << ", ";
					return true;
				}
			}
		}
		return false;
	}
	for (int i = 0; i < e; i++) {
		//cout  <<" no:" << i << endl;
		if ((edge[i][0] == state || edge[i][1] == state)) {
			if (checknote(e, edge, pos, i)) {
				continue;
			}
			pos++;
			prev = state;
			if (edge[i][0] == state) {
				state = edge[i][1];
			}
			else if (edge[i][1] == state) {
				state = edge[i][0];
			}
			if (findhem(e, v, edge, pos, start, state, prev)) {
				cout << state << ", ";
				return true;
			}
			else {
				pos = pos - 1;
				state = prev;
				//cout << "Position:" << pos << "current checked:" << notechecked[pos-1] << " state:" << state << endl;
				continue;
			}

		}
	}
	return false;

}
//Get Start point for exhausive search
int gethem(int e, int v, int edge[500][2]) {
	int start = 0, p[99], l[99], s = 0;

	for (int a = 0; a < v; a++) {
		start = a + 1;
		//cout << "Start as : " << start << endl;
		if (findhem(e, v, edge, 1, start, start, -1)) {
			cout << start << endl;
			cout << "Exhaustive search found the solution." << endl;
			break;
		}
		else {
			cout << "Exhaustive search did not found the solution." << endl;
		}
	}

	return 0;
}
//Greedy Search
void arangestate(int p, int size, int node) {
	int temp, temp2;

	for (int i = 0; i < size; i++) {
		if (i == p) {
			notestate[size+1] = notestate[i+1];
			notestate[i+1] = node;
		}
		int a, b;
		if (i > p) {
			a = notestate[i+1];
			b = notestate[size + 1];
			notestate[i+1] = b;
			notestate[size+1] = a;
		}
	}
	/*for (int i = 0; i < size + 1; i++) {
		cout << notestate[i] << " , ";
	}
	cout << endl;*/
}

bool checkgreedy( int e, int edge[500][2], int note, int pos) {

	bool checkhead = false;
	bool checktail = false;

	for (int i = 0; i <= pos; i++) {
		if (i < pos) {
			//check head
			for (int j = 0; j < e; j++) {

				if (edge[j][0] == notestate[i]) {
					if (edge[j][1] == note) {
						checkhead = true;
						//cout << "check: " << edge[j][0] << " , " << edge[j][1] << endl;
						j = e;
					}
					else {
						checkhead = false;
					}
				}
				else if (edge[j][1] == notestate[i]) {
					if (edge[j][0] == note) {
						checkhead = true;
						//cout << "check: " << edge[j][0] << " , " << edge[j][1] << endl;
						j = e;
					}
					else {
						checkhead = false;
					}
				}
			}
			if (checkhead) {
				//check tail
				for (int j = 0; j < e; j++) {
					if (edge[j][0] == notestate[i + 1]) {
						if (edge[j][1] == note) {
							checktail = true;
							//cout << "check: " << edge[j][0] << " , " << edge[j][1] << endl;
							j = e;
						}
						else {
							checktail = false;
						}
					}
					else if (edge[j][1] == notestate[i + 1]) {
						if (edge[j][0] == note) {
							checktail = true;
							//cout << "check: " << edge[j][0] << " , " << edge[j][1] << endl;
							j = e;
						}
						else {
							checktail = false;
						}
					}
				}
			}
			if (checkhead && checktail) {
				position = i;
				//arangestate(i, pos, note);
				return true;
			}
		}
		else {
			for (int j = 0; j < e; j++) {

				if (edge[j][0] == notestate[i]) {
					if (edge[j][1] == note) {
						checkhead = true;
						//cout << "check: " << edge[j][0] << " , " << edge[j][1] << endl;
						j = e;
					}
					else {
						checkhead = false;
					}
				}
				else if (edge[j][1] == notestate[i]) {
					if (edge[j][0] == note) {
						checkhead = true;
						//cout << "check: " << edge[j][0] << " , " << edge[j][1] << endl;
						j = e;
					}
					else {
						checkhead = false;
					}
				}
			}
			if (checkhead) {
				//check tail
				for (int j = 0; j < e; j++) {
					if (edge[j][0] == notestate[0]) {
						if (edge[j][1] == note) {
							checktail = true;
							//cout << "check: " << edge[j][0] << " , " << edge[j][1] << endl;
							j = e;
						}
						else {
							checktail = false;
						}
					}
					else if (edge[j][1] == notestate[0]) {
						if (edge[j][0] == note) {
							checktail = true;
							//cout << "check: " << edge[j][0] << " , " << edge[j][1] << endl;
							j = e;
						}
						else {
							checktail = false;
						}
					}
				}
			}
			if (checkhead && checktail) {
				position = i;
				//arangestate(i, pos, note);
				return true;
			}
		}
		if (checkhead && checktail) {
			position = i;
			//arangestate(i, pos, note);
			return true;
		}
	}

		return false;


}
int greedyfindHem(int e, int v, int edge[500][2], int pos) {

	bool check = false;
	for (int i = 0; i < v; i++) {
		for (int j = 0; j <= pos; j++) {
			if (notestate[j] == i + 1) {
				check = true;
				break;
			}
			check = false;
		}
		if (check == true) {
			continue;
		}
		if (checkgreedy(e, edge, i + 1, pos)) {
			//cout << "No" << i << "in" << sizeof(state); 
			pos++;
			//notestate[pos] = i + 1;
			//cout <<notestate[pos] << " ,";
			arangestate(position, pos, i + 1);

			i = 0;
		}
		//cout << "add " << pos +1;

	}
	return pos;
}
int greedysearchHem(int e, int v, int edge[500][2]) {
	int pos = 1;
	int result, best = 0, n;
	cout << endl;
	//cout << "_____________"<< endl;
	//cout << "Greedy search" << endl;
	//cout << "_____________" << endl;
	for (int i = 0; i < e; i++) {
		notestate[100] = {};
		notestate[0] = edge[i][0];
		notestate[1] = edge[i][1];
		//cout << "Start as : " << notestate[0] << " , " << notestate[1] << endl;
		//cout << "Result " << i + 1 << " : ";
		result = greedyfindHem(e, v, edge, pos);
		//cout << endl;
		if (result > best) {
			best = result;
			n = i + 1;
		}
		//cout << endl;
	}
	cout << "The best result is Result " << n << " which checked " << best + 1 << " nodes." << endl;

	return 0;
}
//Main
int main()
{
	srand(time(NULL));
	int n, i, e, v;
	cout << "Random graph generation: ";
	// Randomly assign vertex and edges of the graph.
	v = 30;
	cout << "\nThe graph has " << v << " vertexes.";
	e = 150;
	cout << "\nThe graph has " << e << " edges." << endl;
	// A function to generate a random undirected graph with e edges and v vertexes.

	int a;
	a = (v*(v - 1)) / 2;
	if (a == e) {
		cout << "There is a solution for hemiltonian cycle because of all vertex are connneting to each others." << endl;
	}
	else if (e < v) {
		cout << "There is no solution for hemiltonian cycle because of the edges are less than vertex." << endl;
	}
	else {
		//time_t timek;

		for (int k = 0; k < 20; k++) {
			//timek = k;
			
			GenerateRandGraphs(e, v);
			
		}
		cout << "Total time: " << timecheck << endl;
	}
	cout << endl;
	system("PAUSE");
}