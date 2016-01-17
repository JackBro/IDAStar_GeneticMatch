#include <iostream>
#include <utility>
#include <ctime>
#include <vector>
#include <map>
#include <iterator>
#include <cmath>
#include <limits>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

clock_t start;
double time_Limit=0;
map <pair<char,char>, int> MC;
class Nodes{
public:

	int cost;
	int cc_t;
	vector<string> strs;
	int length;
	int pointer;
	vector<int> prev_costs;
	vector<int> prev_;
	vector<int > pres_;
	vector <int> pres_dash;

	Nodes(){
		cost=numeric_limits<int>::max();
		cc_t=numeric_limits<int>::max();
		length=0;
		//prev_costs.resize(length);
		pointer=0;
	}
	void cc_(int a,int t,int c){
		cc_t=c*(a*length-t);
	}
	void mc_(int num_str){
		cost=cc_t;
		for(int i=0;i<num_str-1;i++){

			for(int j=i+1;j<num_str;j++){
				for(int k=0;k<length;k++)
				cost+=MC[make_pair(strs[i][k],strs[j][k])];

			}

		}
	}
	void mc_2(int num_str,int present){
		prev_costs.resize(length);
		pres_.resize(length);
		pres_dash.resize(length);
		prev_.resize(length);
		for(int i=0;i<num_str ;i++){
			if(i== present){continue;}
			for(int k=0;k<length;k++){

				prev_[k]=MC[make_pair(strs[i][k],strs[present][k])];
				this->pres_[k]=prev_[k];
				pres_dash[k]=prev_[k];
				prev_costs[k]=prev_[k];
			}
		}
	}
//	int calc_mc(int num_str,int s,int k){
//		int mc_;
//		for(int i=0;i<num_str-1 && i!=s;i++){
//		mc_+=MC[make_pair(strs[s][k],strs[i][k])];
//		}
//		return mc_;
//	}
	int calc_mc(int num_str,int s,int k,char p){
		int mc_;
		for(int i=0;i<num_str-1;i++){

			mc_=MC[make_pair(p,strs[i][k])];

		}
		return mc_;
	}
	int calc2_mc(int num_str,int s,int k){
		int mc_;
		for(int i=0;i<num_str-1;i++){
			if(i==s){continue;}
			mc_=MC[make_pair('-',strs[i][k])];

		}
		return mc_;
	}

	virtual ~Nodes(){

	}
};

class local{
	public:
	int vocab_size;
	vector<char> vocab;
	int num_strings;
	int total_length;
	int CC;
	int cc_id;
	int Cost_id;
	int mc_id;
	//vector<int> permut;
	int min_test_len;
	vector<string> str_index;
	vector<string> answer;

	vector< vector< vector<int> > > IDAtable;
	vector< vector< vector<int> > > LCStable;

	void Form_node(Nodes* node);
	void Start(Nodes* root,int k);
	void Hill(Nodes* root,int i1,int i2);
	void num();

	vector< vector<int> > lcs( string X_, string Y_ );
	vector< vector<int> > ida( string X, string Y );
	//void create_permut();

};




void local::Start(Nodes* root,int k){
	root->length=min_test_len+rand()%min_test_len;
	//root->length=min_test_len;
	root->cc_(num_strings,total_length,CC);
	root->strs.resize(num_strings);
	int i1=0;
	switch(k){
			case 1  :
				for(vector<string>::iterator it=str_index.begin();it!=str_index.end();it++){
					string s(root->length-(*it).length(),'-');
					string ks=(*it)+s;
					root->strs[i1]=ks;
					i1++;
				}
			   break; //optional
			case  2 :
				for(vector<string>::iterator it=str_index.begin();it!=str_index.end();it++){
					string s(root->length-(*it).length(),'-');
					string ks=(*it);
					for(int i=0;i<(int)(root->length-(*it).length());i++)
					{
						ks.insert(rand()%(ks.length()),1,'-');
					}
					root->strs[i1]=ks.c_str();
					i1++;
				}
			   break; //optional

	}
	root->mc_(num_strings);
//	if(root->cost<=Cost_id){
//		Cost_id=root->cost;
//	}

}
void local::num(){

	while(true){


		Nodes *root=new Nodes();
		Start(root,2);
		//for(int j=0;j<num_strings;j++){

		Hill(root,0,num_strings-1);

		//}
	}
}

void local::Hill(Nodes * root,int i1,int i2){

for(int i11=0;i11<1000;i11++){
		vector<int> find(root->length+1);
		for(int i=i1;i<=i2;i++){
			int find_i=0;
			for(int k=0;k<root->length;k++)
			{
				if(root->strs[i][k]=='-')
				{
					find[find_i]=k;
					find_i++;
				}
			}
			find[find_i]=-1;
			root->mc_2(num_strings,i);
			for(int kf=0;kf<find_i;kf++){
				for(int k=find[kf];k>0;k--){
					if(root->strs[i][k-1]!='-'){
					root->pres_[k]=root->calc_mc(num_strings,i,k,root->strs[i][k-1]);
					continue;
					}
					root->pres_[k]=root->pres_dash[k];
				}
				int pres=0; int min=0; int min_i=find[kf];
				for(int k2=find[kf];k2>0;k2--){
					pres+=root->pres_[k2]+root->pres_dash[k2-1]-root->prev_[k2-1]-root->pres_dash[k2];
					if(pres<min){
						min_i=k2-1;
						min=pres;
					}
				}
				if(min<0){
					string p=root->strs[i].substr(min_i,find[kf]-min_i);
					root->strs[i].replace(min_i,find[kf]-min_i+1,"-"+p);
					root->prev_[min_i]=root->pres_dash[min_i];
					for(int i3=min_i+1;i3<=find[kf];i3++){
						root->prev_[i3]=root->pres_[i3];
					}
				}
			}
			for(int i3=0;i3<root->length;i3++){

			root->cost+=(root->prev_[i3]-root->prev_costs[i3]);
			}




		}
		if(root->cost<Cost_id){
			//<<Cost_id<<"cost1\n";
			Cost_id=root->cost;
			for(int jk=0;jk<num_strings;jk++){
				answer[jk]=root->strs[jk];
			}


		}
		else{
		//<<Cost_id<<"cost1\n";

		}
		float duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

		if(duration > time_Limit*60-5){
			for(int ik=0;ik<num_strings;ik++){


			cout<<answer[ik]<<"\n";

		}
			exit(0);
		}
}




}
//Discrete Space Hill Climbing Algorithm
//   currentNodes = startNodes;
//   loop do
//      L = NEIGHBORS(currentNodes);
//      nextEval = -INF;
//      nextNodes = NULL;
//      for all x in L
//         if (EVAL(x) > nextEval)
//              nextNodes = x;
//              nextEval = EVAL(x);
//      if nextEval <= EVAL(currentNodes)
//         //Return current node since no better neighbors exist
//         return currentNodes;
//      currentNodes = nextNodes


int main(int argc,char** argv){
	///////////////////////////////////////////////   Input Section   /////////////////////////////////////////////////////
	const long double sys1 = time(0);
	start=clock();
	string data;

	ifstream inputfile;
	inputfile.open(argv[1]);

	getline(inputfile,data);
	 time_Limit = atof(data.c_str());

	local *id=new local();
	Nodes *root=new Nodes();
	getline(inputfile,data);
	id->vocab_size=atoi(data.c_str())+1;

	getline(inputfile,data);
	for(int i=0;i<id->vocab_size-1;i++ )
	{
		id->vocab.push_back(data[3*i]);
	}

	id->vocab.push_back('-');
	getline(inputfile,data);
	 id->num_strings=atoi(data.c_str());


//	 for(int i=0;i<id->num_strings;i++){
//		 id->indices.push_back(0);
//	 }
	for(int i=0;i<id->num_strings;i++){
		getline(inputfile,data);

		vector<string>::iterator it=id->str_index.begin();

			id->str_index.push_back(data);



		id->total_length+=data.length()-1;

		if(id->min_test_len<(int)data.length()){
			id->min_test_len=data.length();
		}
		//<<data<<endl;
	}

	id->answer.resize(id->num_strings);


	getline(inputfile,data);
	id->CC=atoi(data.c_str());
	id->cc_id=0; id->mc_id=0; id->Cost_id=numeric_limits<int>::max();

	for(int i=0;i<id->vocab_size;i++){
		getline(inputfile,data);
		for(int j=0;j<id->vocab_size;j++){

			MC.insert(pair<pair<char,char>, int>(make_pair(id->vocab[i],id->vocab[j]),atoi(&data[2*j])));
		}
	}

    getline(inputfile,data);
	inputfile.close();
	//id->Form_node(root);
//	id->Start(root,1);
	id->num();

	//id->Hill();
	const long double sysTime2 = time(0);

	return 0;
}
