#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <math.h>

using namespace std;

int main(int argc, char * argv[]) //computing the length of each chromosomes for genome
{
	ifstream input;
	char c, abc[100];
	string chr_name[24];
	string fa_name;
	int flag=0;
	int bin=1000;
	for (int i=1; i<argc; i++){
		string token = argv[i];
		if(token.compare("-infile_fa") == 0){
			i++;
			if(i == argc){
				cerr << "Unexpected input fa file." <<endl;
				exit(-1);
			}
			fa_name = argv[i]; 
                }
                else{
			cerr << "Unknow parameter: " << token <<"." <<endl;
                        exit(-1);
		}
	}
	input.open(fa_name.c_str(),ios::in);
	if (!input.is_open())
    	{
		cout<<"Cant't open fa file\n";exit(-1);
     	}

	long int len=0;
	int i=0;
	input.clear();
	input.seekg(ios::beg);
	while(input)
	{
			    c = input.get();
				if( c == '>')
				{
						input.getline(abc, 100);

				}
				//cout<<i<<endl;
				if(isalpha(c))             //Determine if c is a alpha
				{

						len++;
				}
	}
	long int bin_count=ceil(len*1.0/bin);
	cout<<len<<endl;
	cout<<bin_count<<endl;
	float *gc_bin=new float[bin_count];
	input.clear();
	input.seekg(ios::beg);
	len=0;
	int gc_count=0;
	int base_count=0;
	bin_count=0;
	while(input)
	{
		c = input.get();
		if( c == '>')
		{
			input.getline(abc, 100);

		}
		if(isalpha(c))             //Determine if c is a alpha
		{

			len++;
			base_count++;
			if((c=='G')||(c=='g')||(c=='C')||(c=='c')){gc_count++;}
			if((base_count%1000)==0)
			{
				
				gc_bin[bin_count]=gc_count*1.0/base_count;
				//cout<<gc_count<<endl<<base_count<<endl<<bin_count<<endl;
				
				gc_count=0;
				base_count=0;
				bin_count++;
			}
		}
		
	}
	gc_bin[bin_count]=gc_count*1.0/base_count;
	
	ofstream output;
	output.open("gc_bin.txt",ios::out);
	if (!output.is_open())
    	{
		cout<<"Cant't open gc_content file\n";exit(-1);
     	}
	for(int i=0;i<bin_count;i++){output<<gc_bin[i]<<endl;}
	return 0;
}
