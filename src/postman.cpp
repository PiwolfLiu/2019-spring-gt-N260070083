#include "network_manager.h"
#include "datatype.h"

vector<vector<Edge *>> avail_paths;
vector<vector<Edge *>>  shortpath;
vector<vector<int>> val_of_shortpath;
vector<int> oddlist;
vector<Verte *> oddlist_vec;
vector<Verte *> verlist;
vector<Edg *> edgelist;

vector<string> ShortPath(string m, string n, Vertex *current);
int minWeightMatching(int w, int start);


int main(int argc, char *argv[]){

/////INPUT NETWORK nm
	NetworkManager *nm,*nm2;
	nm=new NetworkManager();
	nm->interpret(argv[1]);
//	nm->print_all_e();


/////CREATE NEW NETWORK nm2 : ADD VERTEX
	nm2=new NetworkManager();


	Vertex *ver0=nm->get_all_nodes();
	Vertex *ver_head = ver0;

	int num_v =0;
	while(ver0 != NULL){
		nm2->add_switch(ver0->name);
		num_v++;
		ver0 = ver0->next;
	}

	Vertex *ver1 = ver_head;
	Vertex *ver2 = ver1;
	Edge *edge1 = nm->elist;
/////CREATE NEW NETWORK nm2 : CONNECT VERTEX
	while(edge1 != NULL){

		if(nm2->connected(edge1->head->name , edge1->tail->name) == 1){  //not connect yet
			nm2->connect_r(edge1->head->name , edge1->tail->name);
		}		
		edge1= edge1->next;
	}

	Path *path;
	path=new Path();
	path->append(nm2->elist);

////FIND HEAD AND TAIL OF nm2
	Vertex *v = nm2->get_all_nodes();
	Vertex *v2 = v;
	Vertex *nm2_head = v; 
	Vertex *v_tail;

	while(v2!=NULL){
		if(v2->next == NULL)
			v_tail = v2;
		v2 = v2->next;
	}
	v2 = nm2_head;

/////FIND SHORTESTPATH
	while(v != NULL){
		while(v2 != NULL){
			if(v2 == v)
				v2=v2->next;

			if(v2 != NULL){
				avail_paths = path->find_paths(v->name, v2->name);
				v2 = v2->next;
				int shorter = 0;
				if(avail_paths.size() == 0){
					cout<<"*****ERROR:NOT CONNECTED GRAPH : NO SOLUTION*****"<<endl;
						exit(0);
				}
				for(int i=0 ;i < avail_paths.size();i++){
					if(avail_paths[i].size() < avail_paths[shorter].size())
						shorter = i;
				}
				shortpath.push_back(avail_paths[shorter]);
			}
		}
		v = v->next;
		v2 = nm2_head;
	}
	cout<<"CONNECTED GRAPH CHECK"<<endl;
	cout<<"FIND SHORTESTPATH DONE"<<endl;
/*
/////SHOW SHORTESTPATH
	for(int i=0;i<shortpath.size();i++){
		for(int j=0;j<shortpath[i].size();j++){
			cout<<shortpath[i][j]->head->name<<"->"<<shortpath[i][j]->tail->name<<" ";
		}
			cout<<"  end"<<endl;
	}
	cout<< "-------------------"<<endl;
*/

/////CREATE DISTANCE TABLE
	vector<int> val_of_line;
	int count =0;
	for(int i=0;i<shortpath.size();i++){
		for(int j=0;j<shortpath[i].size();j++){
		}	
		count++;

		val_of_line.push_back(shortpath[i].size());
		if(count == num_v-1){
			int pos = (i+1)/count-1;
			val_of_line.insert(val_of_line.begin()+pos,0);

			val_of_shortpath.push_back( val_of_line);
			val_of_line.clear();
			count=0;
		}
	}

/*
/////SHOW DISTANCE TABLE////
	for(int i=0 ;i<val_of_shortpath.size();i++){
		for(int j=0; j<val_of_shortpath[i].size();j++){
			cout<<val_of_shortpath[i][j]<<" ";
		}
		cout<<endl;
	}
*/

/////FIND ODD VERTEX 
	Edge * e= nm->elist;
	map<string ,int> v_deg;
	
	map<string, int>::iterator iter1,iter2;
	while(e != NULL){

		if(verlist.size() == 0){

			if(e->head->name != e->tail->name){
				Edg* e_temp = new Edg;
				Verte* v_temp = new Verte;
				Verte* v_temp2 = new Verte;

				v_temp->name = e->head->name;
				verlist.push_back(v_temp);
				v_temp2->name = e->tail->name;
				verlist.push_back(v_temp2);

				e_temp->v1 = v_temp;
				e_temp->v2 = v_temp2;
				edgelist.push_back(e_temp);
				v_temp->conEdge.push_back(e_temp);
				v_temp2->conEdge.push_back(e_temp);
			}

			else{
				Edg* e_temp = new Edg;
				Verte* v_temp = new Verte;

				v_temp->name = e->head->name;
				verlist.push_back(v_temp);

				e_temp->v1 = v_temp;
				e_temp->v2 = v_temp;
				edgelist.push_back(e_temp);
				v_temp->conEdge.push_back(e_temp);
			
			}
		}

		else{
			Edg* e_temp = new Edg;
			Verte* v_temp = NULL ;
			Verte* v_temp2 = NULL ;
			for(int i=0 ;i<verlist.size() ;i++){
				if(e->head->name == verlist[i]->name){
					v_temp = verlist[i];
				}

				if(e->tail->name == verlist[i]->name){
					v_temp2 = verlist[i];
				}


				if(i == verlist.size()-1){
					if(e->head->name != e->tail->name){

						if(v_temp == NULL){

							v_temp = new Verte;
							v_temp->name = e->head->name;
							verlist.push_back(v_temp);

						}

						if(v_temp2 == NULL){
							v_temp2 = new Verte;
							v_temp2->name = e->tail->name;
							verlist.push_back(v_temp2);
						}
					}

					else{
						if(v_temp == NULL){

							v_temp = new Verte;
							v_temp->name = e->head->name;
							verlist.push_back(v_temp);
							
							v_temp2 = v_temp;
						}

					}
				}
			}
			e_temp->v1 = v_temp;
			e_temp->v2 = v_temp2;
			edgelist.push_back(e_temp);
			v_temp->conEdge.push_back(e_temp);
			v_temp2->conEdge.push_back(e_temp);
		} 
		
		iter1 =  v_deg.find(e->head->name);
		if( iter1 == v_deg.end()){
			v_deg[e->head->name] = 1 ;
		}
		else{
			iter1->second++;

		}

		iter2 =  v_deg.find(e->tail->name);

		if( iter2 == v_deg.end()){
			v_deg[e->tail->name] = 1 ;
		}
		else{
			iter2->second++;
		}

		e= e->next;
	}
	
	int times= 0;

	for(iter1 = v_deg.begin(); iter1 != v_deg.end(); iter1++){
		
		if((iter1->second)%2 != 0){
			oddlist.push_back(times);
		}
		times++;
	}
	
	for(int i= 0 ; i<verlist.size();i++){

	}
	for(int i = 0 ;i<oddlist.size(); i++){
				oddlist_vec.push_back(verlist[oddlist[i]]);
	}
	
	

	cout<<"FIND ODD VERTEX DONE"<<endl;


	if(oddlist.size() != 0){
		int weight = minWeightMatching(0,0);
		cout<<"MIN WEIGHT MATCH DONE"<<endl;

///// ADD MATCHING EDGES	
		for (int i = 0; i < edgelist.size(); i++)
			edgelist[i]->extra = false;

		Edg *add_edge;
		for(int i = 0; i < oddlist_vec.size(); i += 2) {
			add_edge = new Edg(oddlist_vec[i], oddlist_vec[i + 1], true);
			oddlist_vec[i]->conEdge.push_back(add_edge);
			oddlist_vec[i + 1]->conEdge.push_back(add_edge);
			edgelist.push_back(add_edge);
		}
		cout<<"ADD MATCHING EDGES DONE"<<endl;
/////FIND EULERL CIRCLE
		Verte *top;
		stack<Verte *> tmp_path;
		vector<Verte *> eulerlist;

		for (int i = 0; i < edgelist.size(); i++)
			edgelist[i]->used = false;

		if (!verlist.empty())
			tmp_path.push(verlist.front());



		while (!tmp_path.empty()) {
			top = tmp_path.top();
			int index;
			for (index = 0; index < top->conEdge.size(); index++) {
				if (!top->conEdge[index]->used) {
					top->conEdge[index]->used = true;
					if (top->conEdge[index]->v1->name != top->name)
						tmp_path.push(top->conEdge[index]->v1);
					else
						tmp_path.push(top->conEdge[index]->v2);
					break;
				}
			}
			if (index == top->conEdge.size()) {
				tmp_path.pop();
				eulerlist.push_back(top);
			}
		}
		cout<<"FIND EULERL CIRCLE"<<endl;
/////OUTPUT postman.txt
		string outfile = argv[1] ;
		outfile =outfile.assign(outfile, 12, 30) ; 
		outfile = "./output/" + outfile + "_postman.txt";
		cout<<outfile<<endl;

 	string FileName = outfile;
    ofstream out(FileName.c_str()); 
		vector<string> vertex_path;
		out<<"->  : "<< "origin egde "<<endl;
		out<<"->> : "<< "extra edge"<<endl<<endl;
		out<<"Path : "<<endl;
		for (int i = 0; i < eulerlist.size() - 1; i++) {
			for (int j = 0; j < eulerlist[i]->conEdge.size(); j++) {
				if (eulerlist[i]->conEdge[j]->v1->name == eulerlist[i + 1]->name ||
						eulerlist[i]->conEdge[j]->v2->name == eulerlist[i + 1]->name) {
					if (!eulerlist[i]->conEdge[j]->extra)
						out << eulerlist[i]->name << "->";
					else {
						vertex_path = ShortPath(eulerlist[i]->name, eulerlist[i + 1]->name, nm2_head);
						for (int k = 0; k < vertex_path.size()-1; k++)
							out << vertex_path[k] << "->>";
					}
					break;
				}
			}
		}	
		out << eulerlist.back()->name << endl;

		cout<<"OUTPUT FILE DONE"<<endl;
	}

}


vector<string> ShortPath(string m, string n, Vertex *current){
	vector<string> vertex_path;
	int order_m = 0;
	int order_n = 0;
	int count = 0;
	int num = 0;

	while(current != NULL){
		num++;
		if(n == current->name){
			order_n = count;
		}

		if(m == current->name){
			order_m = count;
		}
		current = current->next;
		count++;
	}
	int order_in_path =0;

	if(order_m > order_n)
		order_in_path = order_m*(num-1) + order_n ;

	if(order_m < order_n)
		order_in_path = order_m*(num-1) + order_n -1;

	vertex_path.push_back(m);
	for(int i = 0; 	i < shortpath[order_in_path].size() ;i++){
		vertex_path.push_back(shortpath[order_in_path][i]->tail->name);
	}
	return vertex_path;
}

int minWeightMatching(int w, int start)
{
	int min_w = INT_MAX;

	if (start == oddlist.size() - 2) {
		int weight = val_of_shortpath[oddlist[start]][oddlist[start + 1]];

		if (w + weight < min_w) {
			min_w = w + weight;
		}
		return weight;
	}

	for (int i = start + 1; i < oddlist.size(); i++) {
		int weight = val_of_shortpath[oddlist[start]][oddlist[i]];
		int tmp = oddlist[start + 1];
		oddlist[start + 1] = oddlist[i];
		oddlist[i] = tmp;
		weight += minWeightMatching(w + weight, start + 2);
		tmp = oddlist[start + 1];
		oddlist[start + 1] = oddlist[i];
		oddlist[i] = tmp;
		if (weight < min_w)
			min_w = weight;
	}
	return min_w;;
}


