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

int num_nodes;
int tot_num_nodes;
long double sys1;
class Node{
public:
	vector<string> strstate_arr;
	pair<pair<int,int>,int> pairs;
	pair<int,int> small;
	int cost;
	vector< int> indices;
	Node(){
		cost=0;
		pairs=make_pair(make_pair(0,0),0);
		small=make_pair(0,0);
		//vector<unsigned int> indices;
	}
	virtual ~Node(){

	}
};

int num_CC=0;
vector< vector< vector<int> > > DPtable;
vector< vector< vector<int> > > LCStable;
vector< vector< vector<int> > > IDAtable;
map <pair<char,char>, int> MC;

class Idastar{
public:
	int vocab_size;
	vector<char> vocab;
	int num_strings;
	vector<string> tests;
	int CC;
	//vector< vector<int> > MC;

	 /// see if possible to use unordered_map in GCL

	vector<int> permut;
	//int max_test_len;

	int heur1(Node &node);
	int heur2(Node &node);
	bool is_goal(Node &node);
	void create_permut();
	vector< vector<int> > lv(string s1,string s2);
	vector< vector<int> > lcs( string X, string Y );
	vector< vector<int> > ida_dp(string s1,string s2);
	void idaSub1();
	Idastar(){
		vocab_size=0;
		num_strings=0;
		CC=0;
	}
	virtual ~Idastar(){

	}
	//Idastar(string s1,string s2);
};
class Idasub{

	int num_strings;
	vector<string> tests;
	int CC;
	Idastar* ids;
	int heur(Node &node);
	bool is_goal(Node &node);

};
int answer;
void print_node(Node &node2,int option){
	//print all strings in node.strstate_arr and cost in it
	//cout<<"(";
	if(option==2){
	for(signed int i=0;i<node2.strstate_arr.size();i++){
		cout<<node2.strstate_arr[i]<<endl;
	}
	//cout<<")"<<endl;
	// answer=node2.cost;
	// cout<<node2.cost;
	// cout<<endl;
	}
}
int Idastar::heur1(Node &nodeh){
	int maxmc_h=0;//numeric_limits<int>::min();

			int counter=0;
			for(int i=0;i<nodeh.pairs.second-1;i++){
				if(i>nodeh.pairs.first.first){
					break;
				}
				for(int j=i+1;j<nodeh.pairs.second;j++){
					if(i>=nodeh.pairs.first.first && j>= nodeh.pairs.first.second){
					counter--;
					}
					counter++;
				}
			}
			int lcs_1=(LCStable[counter][this->tests[0].length()-nodeh.indices[0]][this->tests[1].length()-nodeh.indices[1]]);
			maxmc_h+=max((this->tests[0].length()-nodeh.indices[0]),(this->tests[1].length()-nodeh.indices[1]))-lcs_1;

			//int l2=this->tests[j].length()-nodeh.indices[j]-lcs_1;
			int diff=abs(this->tests[0].length()-nodeh.indices[0]-this->tests[1].length()-nodeh.indices[1]);

	maxmc_h+=this->CC*(diff);
//	for(unsigned int i=0;i<nodeh.indices.size()-1;i++){
//		for(unsigned int j=i+1;j<nodeh.indices.size();j++){
//			if(max_h<(this->DPtable[counter])[this->tests[i].length()-nodeh.indices[i]][this->tests[j].length()-nodeh.indices[j]]){
//				max_h+=(this->DPtable[counter])[this->tests[i].length()-nodeh.indices[i]][this->tests[j].length()-nodeh.indices[j]];
//				//cout<<max_h<<endl;
//			}
//			counter++;
//		}
//	}
	//cout<<maxmc_h<<"maxmc_h\n";
	return maxmc_h;

//	int rmax=0;
//	int counter=0;
//	for(unsigned int i=0;i<nodeh.indices.size()-1;i++){
//		for(unsigned int j=i+1;j<nodeh.indices.size();j++){
//			//if(lmax<(this->LCStable[counter])[this->tests[i].length()-nodeh.indices[i]][this->tests[j].length()-nodeh.indices[j]]){
//				int lmax=(this->LCStable[counter])[this->tests[i].length()-nodeh.indices[i]][this->tests[j].length()-nodeh.indices[j]];
//				//cout<<max_h<<endl;
//			//}
//				int l1=this->tests[i].length()-lmax-nodeh.indices[i]-lmax;
//				int l2=this->tests[j].length()-lmax-nodeh.indices[j]-lmax;
//				rmax+=max(l1,l2)*;
//			counter++;
//		}
//	}

	//cout<<"h:"<<max_h<<endl;
	//return rmax;
}

int Idastar::heur2(Node &nodeh){
	int counter=0;
	int maxmc_h=0;
	int maxl=0;
	int tot_l=0;
	for(int i=0;i<this->num_strings-1;i++){
		if(maxl<(int)this->tests[i].length()-nodeh.indices[i]){
			maxl=this->tests[i].length()-nodeh.indices[i];
		}
		tot_l+=this->tests[i].length()-nodeh.indices[i];

			for(int j=i+1;j<this->num_strings;j++){
				int lcs_1=(IDAtable[counter][nodeh.indices[i]][nodeh.indices[j]]);
				maxmc_h+=lcs_1;
				counter++;

				//int l2=this->tests[j].length()-nodeh.indices[j]-lcs_1;

			}
		}
	if(this->num_strings-1>=0){
	if(maxl<(int)this->tests[this->num_strings-1].length()-nodeh.indices[this->num_strings-1]){
		maxl=this->tests[this->num_strings-1].length()-nodeh.indices[this->num_strings-1];
	}
	    tot_l+=this->tests[this->num_strings-1].length()-nodeh.indices[this->num_strings-1];
	}
	maxl*=num_strings;
	maxl-=tot_l;
	return maxmc_h+CC*maxl;
}
bool Idastar::is_goal(Node &node1){
	bool ans=false;
	for(unsigned int i=0;i<node1.indices.size();i++){
		if((int)this->tests[i].length()==node1.indices[i]){
			ans=true;
		}
		else{
			ans=false;
			break;
		}
	}
	return ans;
}
void Idastar::create_permut(){

	for(int i=0;i<(1<<this->num_strings)-1;i++){
		this->permut.push_back(i);
	}
}
bool bit_at(int num,int index){  //indexing start at 0
	return (num>>index)&1;
}
void printTable(vector< vector<int> > table, string& s1, string& s2) {
	//cout << "\t*";
	for(int i = 0; i < (int)s2.size(); i++) {
		cout << '\t' << s2[i];
	}
	cout << endl;

	//cout << "\t*";
	for(int i = 0; i < (int)s2.size(); i++) {
		cout << '\t' << i;
	}
	cout << endl;

	for(int i = 0; i < (int)s1.size(); i++) {
		cout << s1[i];
		cout << "\t" << i ;

		for(int j = 0; j < (int)s2.size(); j++) {
			cout << '\t' << table[i][j];
		}
		cout << '\n';
	}
}

void print_lcstable(vector< vector<int> > table, string& s1, string& s2){
	cout<<"size";
	cout<<s1;
	cout<<",";
	cout<<s2;
	cout<<",";
	cout<<s1.length();
	cout<<",";
	cout<<s2.length();
	cout<<'\t';
	cout<<'-';
	cout<<'\t';
	//cout<<"nt";
	for(int i=0;i<(int)s2.size();i++){
		cout<<s2[i];
		cout<<"\t";
	}

	cout<<endl;
	//cout<<"nt"<<endl;
//	for(unsigned j = 1; j <= s2.size(); j++) {
//						cout << '\t' << table[0][j];
//					}

	for(int i=0;i<=(int)s1.size();i++){
		if(i>0){cout << s1[i-1];}
		else{cout<<"-";}
		for(int j = 0; j <= s2.size(); j++) {
					cout << '\t' << table[i][j];
				}
		cout<<endl;
	}
}
/////////////////////////////LCS /////////////////
vector< vector<int> > Idastar::lcs( string X, string Y )
{
	int m=X.length();
	int n=Y.length();

//	X = "-" + X;
//	Y = "*" + Y;
	vector< vector<int> > L(m+1, vector<int>(n+1, 0));
   int i, j;

   /* Following steps build L[m+1][n+1] in bottom up fashion. Note
      that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
   for (i=0; i<=m; i++)
   {
     for (j=0; j<=n; j++)
     {
       if (i == 0 || j == 0)
         L[i][j] = 0;



       else if (X[i-1] == Y[j-1])
         L[i][j] = L[i-1][j-1] + 1;

       else
         L[i][j] = max(L[i-1][j], L[i][j-1]);
     }
   }

   /* L[m][n] contains length of LCS for X[0..n-1] and Y[0..m-1] */
   return L;
}


////////////////////////////////	LV ///////////////
vector< vector<int> > Idastar::lv(string s1,string s2){
	s1 = "-" + s1;
	s2 = "-" + s2;
	vector< vector<int> > table(s1.size(), vector<int>(s2.size(), 0));
	for(signed i = 0; i < s1.size(); i++) {
			table[i][0] = this->CC*i;
		}
		for(signed j = 0; j < s2.size(); j++) {
			table[0][j] = this->CC*j;
		}

		for(signed i = 1; i < s1.size(); i++) {
			for(signed j = 1; j < s2.size(); j++) {

					int leftVal = table[i - 1][j] + this->CC;
					int upVal = leftVal;
					int diagVal = table[i - 1][j - 1];
					if(s1[i] != s2[j]) {
						diagVal+=MC[make_pair(s1[i],s2[j])];
						//cout<<diagVal;
					}

					int min = leftVal;
					if(upVal < min) {
						min = upVal;
					}
					if(diagVal < min) {
						min = diagVal;
					}

					table[i][j] = min;

			}
		}
		//printTable(table,s1,s2);
		return table;

}

int bd=0;

//////////////////////////////////////////////////////
int search(Idastar *id,Node* node,int &bound,int option,bool &touch){
	int f;
	num_nodes++;
	tot_num_nodes++;
	if(option==1){
	 f=node->cost+id->heur1(*node);
	}
	else{
		f=node->cost+id->heur2(*node);
	}
	//cout<<"f:"<<f<<",bound:"<<bound<<endl;
	if (f>bound){
		return f;
	}
	if (id->is_goal(*node)){
		//cout<<"printing goal"<<endl;
		print_node(*node,option);    ///////////////// answer is printed here
		//cout<<time(0)-sys1<<"time\n";
		//t=-2;
		return -node->cost;
	}


	int min=numeric_limits<int>::max();  //change here to int.max

//////////////////////succesor function       don't dare to interpret it because i also got scared after writing these :)  //////////////////////
	for(int i=0;i<(1<<id->num_strings)-1;i++){
		bool bloop=false;

		for(int j=0;(j<id->num_strings)   ;j++)
		{
			if(node->indices[j]>=(int)id->tests[j].length() && (!bit_at(i,j)) )
			{
				bloop=true;
				break;
			}

		}
		if(bloop)
		{
			continue;
		}
		Node* succ=new Node();
		succ->pairs=node->pairs;
		succ->small=node->small;
		succ->indices.resize(node->indices.size());
		succ->indices=(node->indices);




		for(int j=0;j<id->num_strings;j++)
		{

			succ->strstate_arr.push_back(node->strstate_arr[j]+ (bit_at(i,j) ? '-' : (id->tests[j].at(succ->indices[j])) ));
			if(!bit_at(i,j)){
				succ->indices[j]++;
			}
			else{
				succ->cost+=id->CC;
			}

		}

		int diff=0;

		for(int ione=0;ione<id->num_strings-1;ione++)
		{
			for(int jone=ione+1;jone<id->num_strings;jone++)
			{
				diff+=MC[make_pair(succ->strstate_arr[ione].at(succ->strstate_arr[ione].length()-1),succ->strstate_arr[jone].at(succ->strstate_arr[jone].length()-1))];
			}
		}
		succ->cost+=node->cost+diff;
		//print_node(*succ);cout<<"from"<<endl;print_node(node);
		int t = search(id,succ,bound,option,touch);

		if (t <0){return t;}
	    if (t < min) {min = t;}

	    //cout<<"\ndeleting"<<endl;print_node(*succ);
	    delete succ;
	}

return min;
}
////////////////////////////////////////// ida sub
int IDA_Star_fun(Idastar *id,Node *root,int option){
	int bound;
	int bd=3;
	if(option==1){
		bound=(id->heur1(*root));
	}
	else{
		bound=(id->heur2(*root));
	}

	//cout<<"boundroot:"<<bound<<endl;
	int jk=0;
	int answ=0;
	bool touch=false;
	while(true){
		num_nodes=0;
		int t=search(id,root,bound,option,touch);
		if(t<=0){answ=-t;break;}
		{bound=t;}
		
		//cout<<time(0)-sys1<<"time  max"<<bound  <<endl;//<<"bound:///////////////////////////////////////////////////////////////////////////////////"<<bound<<"  it:"<<jk++<<endl;
	}
	return answ;
}


//////////////////////////////////////////////////ida_dp///////////////////
vector< vector<int> > Idastar::ida_dp(string X_,string Y_){
	int m=X_.length();
	int n=Y_.length();
	string X;
	reverse_copy(X_.begin(),X_.end(),back_inserter(X));
	string Y;
	reverse_copy(Y_.begin(),Y_.end(),back_inserter(Y));
	vector< vector<int> > Tbl(m+1, vector<int>(n+1, 0));
	int i,j;
	for (i=0; i<=m; i++)
	   {
	     for (j=0; j<=n; j++)
	     {
	       if (i == 0){
	         Tbl[i][j] = j*this->CC;
	       }
	       else if(i!=0&&j == 0){
	    	   Tbl[i][j] = i*this->CC;
	       }

	       else{
	    	   //Tbl[i][j]=;
	       }
	     }
	   }
	return Tbl;
}

int main(){
	///////////////////////////////////////////////   Input Section   /////////////////////////////////////////////////////
	num_nodes=0;tot_num_nodes=0;
	//cout<<"running\n";
	sys1=time(0);
	string data;
	ifstream inputfile("input.txt");

	getline(inputfile,data);
	double time_Limit = atof(data.c_str());

	Idastar *id=new Idastar();

	getline(inputfile,data);
	id->vocab_size=atoi(data.c_str())+1;


	string buf;
	getline(inputfile,data);
	stringstream ss(data);
	getline(ss,buf, ',');
	id->vocab.push_back(buf.at(0));
	while( getline(ss,buf, ',')){
		buf=buf.substr(1,1); //// to remove the space as input is given as "A, C, T, G"
		//cout<<buf<<endl;
		id->vocab.push_back(buf.at(0));

	}
	id->vocab.push_back('-');
	getline(inputfile,data);
	 id->num_strings=atoi(data.c_str());

	for(int i=0;i<(int)id->num_strings;i++){
		getline(inputfile,data);
		id->tests.push_back(data.substr(0,data.length()-1));
		// cout<<"tests";
		// cout<<id->tests.back();
		// cout<<",";
		// cout<<id->tests.back().length();
//		if(id->max_test_len<(int)data.length()){
//			id->max_test_len=data.length();
//		}

	}

	id->create_permut();

	getline(inputfile,data);
	id->CC=atoi(data.c_str());


	for(int i=0;i<id->vocab_size;i++){
		getline(inputfile,data);
		stringstream ss1(data);

		for(int j=0;j<id->vocab_size;j++){
			getline(ss1,buf, ' ');
			//cout<<buf<<endl;
			MC.insert(pair<pair<char,char>, int>(make_pair(id->vocab[i],id->vocab[j]),atoi(buf.c_str())));
		}
	}

		for(int i=0;i<id->num_strings-1;i++){
			for(int j=i+1;j<id->num_strings;j++){
				//id->DPtable.push_back(id->lv(rev_string[i],rev_string[j]));
				string X(id->tests[i]);
				//cout<<id->tests[i].length();
				//cout<<id->tests[i];
				string s1="davdfav";
				//cout<<",";
				//cout<<s1.length();

				//cout<<",length";
				//cout<<X.length();
				reverse(X.begin(),X.end());
				string Y(id->tests[j]);
				reverse(Y.begin(),Y.end());

				LCStable.push_back(id->lcs(X,Y));
				//string a='-'+rev_string[i];string b='-'+rev_string[j];
				//print_lcstable(LCStable.back(),X,Y);
				//cout<<"sai"<<id->LCStable.back()[id->tests[i].length()][id->tests[j].length()];
			}
		}

		for(int i=0;i<id->num_strings-1;i++){

			for(int j=i+1;j<id->num_strings;j++){


				//cout<<time(0)-sys1<<"time i,j "<<i<<","<<j<<endl;
				vector<vector<int> > ida_t(id->tests[i].length()+1, vector<int> (id->tests[j].length()+1,0));
				ida_t[id->tests[i].length()][id->tests[j].length()]=0;
				for(int p=0;p<(int)id->tests[i].length();p++){
					ida_t[p][id->tests[j].length()]=+MC[make_pair(id->tests[i].at(p),'-')];
				}

				for(int k=0;k<(int)id->tests[j].length();k++){
					ida_t[id->tests[i].length()][k]=+MC[make_pair(id->tests[j].at(k),'-')];
				}
				//(id->tests[j].length()-k )*id->CC

				for(int p=0;p<(int)id->tests[i].length();p++){
					//string p=id->tests[j];

					for(int k=0;k<(int)id->tests[j].length();k++){
						Idastar *ids=new Idastar();
						Node* root1=new Node();
						root1->pairs=make_pair(make_pair(i,j),id->num_strings);
						ids->tests.push_back(id->tests[i].substr(p));
						ids->tests.push_back(id->tests[j].substr(k));
						ids->num_strings=2;
						ids->vocab_size=id->vocab_size;
						ids->vocab=id->vocab;
						root1->cost=0;
						root1->small=make_pair(p,k);
						root1->indices.resize(2,0);
						root1->strstate_arr.resize(2,"");


						ida_t[p][k]=(IDA_Star_fun(ids,root1,1));
						if(num_CC<root1->strstate_arr[0].length()){
							num_CC=root1->strstate_arr[0].length();
						}
						delete ids;
						delete root1;
					}
				}
				IDAtable.push_back(ida_t);


			}
		}
		Node* root=new Node();
		root->cost=0;
		root->indices.resize(id->num_strings,0);
		root->strstate_arr.resize(id->num_strings,"");
	getline(inputfile,data);
	inputfile.close();
	num_CC*=id->num_strings;
	for(int i=0;i<id->num_strings;i++){
		num_CC+=(-1*id->tests[i].length());
	}
	num_CC=id->CC*num_CC;
	IDA_Star_fun(id,root,2);
	//cout<<time(0)*1000-sys1*1000<<"time-end\n";
	//cout<<num_nodes<<"nodes\n";
	//cout<<tot_num_nodes<<"tot_nodes\n";
	return 0;
}
