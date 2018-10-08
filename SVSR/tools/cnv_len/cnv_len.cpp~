#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <math.h>

using namespace std;
int main(int argc, char * argv[])
{
	string cnv_name;
	for (int i=1; i<argc; i++){
		string token = argv[i];
		if(token.compare("-infile_cnv") == 0){
			i++;
			if(i == argc){
				cerr << "Unexpected input fa file." <<endl;
				exit(-1);
			}
			cnv_name = argv[i]; 
                }
                else{
			cerr << "Unknow parameter: " << token <<"." <<endl;
                        exit(-1);
		}
	}
	ifstream input;
	ofstream output;
	input.open(cnv_name.c_str(),ios::in);
	if (!input.is_open())
    	{
		cout<<"Cant't open cnv message file\n";exit(-1);
     	}
     	output.open((cnv_name+"_len.txt").c_str(),ios::out);
	if (!output.is_open())
	{
		cout<<"Cant't open cnv len file\n";exit(-1);
	}
     	input.clear();
	input.seekg(ios::beg);
	string str,c;
     	long int pos,cnv_len;
     	int bin_flag=0;
     	//long int start_pos=0;
     	while(input)
     	{
     		
		getline(input,str);//如果没有到达文件的末尾进行读取一行
		istringstream iss(str);
		iss >> c;
		if(c=="chr"){continue;}
		iss >> c;
		iss >> cnv_len;
		if(c==""){continue;}
		else
		output<<cnv_len<<endl;
     	}
     	
}

