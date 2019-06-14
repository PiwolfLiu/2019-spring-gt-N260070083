#include <iostream>
#include <string> 
#include <vector> 
#include <fstream>
#include <sstream>
#include <algorithm> 
#include <time.h>
#include <set>
#include <list>
#include <stdlib.h> 
#include <stdio.h> 
#include <queue>
#include <map>
#include <math.h>
#include <limits.h>
#include <cfloat>
#include <stack>
#include <cstdlib>

using namespace std;
class Edg;

class Verte {
	public:
		string name;
		vector<Edg *> conEdge;
};

class Edg {
	public:
		Edg(){};
		Edg(Verte *a, Verte *b, bool f) {
			v1 = a;
			v2 = b;
			extra = f;
			used = false;
		};
		Verte *v1, *v2;
		bool used, extra;
};
