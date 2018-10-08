#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <math.h>

using namespace std;
int main(int argc, char * argv[])
{
	string depth_name;
	for (int i=1; i<argc; i++){
		string token = argv[i];
		if(token.compare("-infile_depth") == 0){
			i++;
			if(i == argc){
				cerr << "Unexpected input fa file." <<endl;
				exit(-1);
			}
			depth_name = argv[i]; 
                }
                else{
			cerr << "Unknow parameter: " << token <<"." <<endl;
                        exit(-1);
		}
	}
	ifstream input;
	ofstream output;
	input.open(depth_name.c_str(),ios::in);
	if (!input.is_open())
    	{
		cout<<"Cant't open fa file\n";exit(-1);
     	}
     	output.open((depth_name+".bin").c_str(),ios::out);
	if (!output.is_open())
	{
		cout<<"Cant't open gc_content file\n";exit(-1);
	}
     	input.clear();
	input.seekg(ios::beg);
	string str,c;
     	long int pos,depths;
     	int bin_flag=0;
     	//long int start_pos=0;
     	while(input)
     	{
     		
		getline(input,str);//如果没有到达文件的末尾进行读取一行
		istringstream iss(str);
		iss >> c;
		iss >> pos;
		//if(bin_flag==0){bin_flag=1;start_pos=pos;}
		iss >> depths;
		//cout<<depths<<endl;
     	}
     	cout<<pos<<endl;
     	int *depth_pos=new int[pos];
     	for(int i=0;i<pos;i++){depth_pos[i]=0;}
     	input.clear();
	input.seekg(ios::beg);
     	while(input)
     	{
     		
		getline(input,str);//如果没有到达文件的末尾进行读取一行
		istringstream iss(str);
		iss >> c;
		iss >> pos;
		iss >> depths;
		depth_pos[pos-1]=depths;
     	}
     	//for(int i=0;i<pos;i++){output<<depth_pos[i]<<endl;}
	
	//for(int i=0;i<pos;i++){cout<<depth_pos[i];}
	int bin_size=1000;
	int bin_count=ceil(pos*1.0/bin_size);
	float *depth_bin=new float[bin_count];
	long int depth_total=0;
	bin_count=0;
	int bin_size2=0;
	for(int i=0;i<pos;i++)
	{
		depth_total+=depth_pos[i];
		bin_size2++;
		if(((i+1)%bin_size)==0)
			{
				
				depth_bin[bin_count]=depth_total*1.0/bin_size2;
				
				depth_total=0;
				bin_size2=0;
				output<<depth_bin[bin_count]<<endl;
				bin_count++;
			}
		
	}
	depth_bin[bin_count]=depth_total*1.0/bin_size2;
	output<<depth_bin[bin_count]<<endl;
}

