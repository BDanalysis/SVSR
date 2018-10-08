#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main(int argc, char * argv[]) //computing the length of each chromosomes for genome
{
	ifstream input;
	ofstream output;
	char c, abc[100];
	string chr_name[24];
	string fa_name;
	int flag=0;
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
	output.open((fa_name+".gc_content").c_str(),ios::out);
	if (!output.is_open())
    	{
		cout<<"Cant't open gc_content file\n";exit(-1);
     	}
	long int len=0;
	int i=0;
	input.clear();
	input.seekg(ios::beg);
	long int*chr_count=new long int[24];
	long int*gc_count=new long int[24];
	for(int k=0;k<24;k++){chr_count[i]=0;}
	while(input)
	{
			    c = input.get();
				if( c == '>')
				{
						input.getline(abc, 100);
						fa_name=abc;
						for(int j=1;j<23;j++)
						{
							stringstream s;
							s << j;
							string bb="chr"+s.str();
							if(fa_name.find(bb)==0)
							{
								i=j-1;
								
							}
							continue;
						}
						if(fa_name.find("chrX")!=fa_name.npos)
						{
							i=22;
							chr_name[i]=fa_name;
							//cout<<chr_name[i]<<"  i="<<i<<endl;
							continue;
						}
						
						if(fa_name.find("chrY")!=fa_name.npos)
						{
							i=23;
							chr_name[i]=fa_name;
							//cout<<chr_name[i]<<"  i="<<i<<endl;
							continue;
						}
						chr_name[i]=fa_name;
						//cout<<chr_name[i]<<"  i="<<i<<endl;

				}
				//cout<<i<<endl;
				if(isalpha(c))             //Determine if c is a alpha
				{

						chr_count[i]++;
						if((c=='G')||(c=='g')||(c=='C')||(c=='c')){gc_count[i]++;}
						//cout<<c;

				}
	}
	output<<"chr\tgc_content"<<endl;
	for(i=0;i<24;i++)
	{
		if(chr_count[i]!=0)
		{
			output<<chr_name[i]<<"\t"<<(gc_count[i]*1.0/(1.0*chr_count[i]))<<endl;
		}
	}
	long int total_count=0,total_gc=0;
	for(i=0;i<24;i++){total_count+=chr_count[i],total_gc+=gc_count[i];}
	output<<"mean_chr\t"<<((total_gc*1.0)/(total_count*1.0))<<endl;
	return 0;
}
