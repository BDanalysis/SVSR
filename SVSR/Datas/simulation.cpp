#include "simulation.h"

void simulate::usage()
{
	cout<<"===============================SVSR============================"<<endl;
	cout<<"Program: SVSR (Tools for variant simulation and reads generation)"<<endl;
	cout<<"Version: 1.0"<<endl<<endl;
	cout<<"Usage:   ./sim [options]"<<endl;
	cout<<"==============================================================="<<endl;
}

long int* simulate::count_genome(ifstream &input) //computing the length of each chromosomes for genome
{

	long int len=0;
	char c, abc[100];
	string chr_name;
	int i=0;
	input.clear();
	input.seekg(ios::beg);
	for(int i=0;i<24;i++){chr_count[i]=0;}
	while(input)
	{
			    c = input.get();
				if( c == '>')
				{
						input.getline(abc, 100);
						chr_name=abc;
						for(int j=1;j<23;j++)
						{
							stringstream s;
							s << j;
							string bb="chr"+  s.str();
							if(chr_name.find(bb)==0)
							{
								i=j-1;
							}
							continue;
						}
						if(chr_name.find("chrX")!=chr_name.npos)
						{
							i=22;
							continue;
						}
						if(chr_name.find("chrY")!=chr_name.npos)
						{
							i=23;
							continue;
						}

				}
				if(isalpha(c))             //Determine if c is a alpha
				{

						chr_count[i]++;
						//cout<<c;

				}
	}
	return chr_count;
}

void simulate::get_parameters(int argc, char** argv, parameters& params)
{
	/*params.infile_ref;
	params.infile_snp_rate;
       	params.infile_ts;
       	params.infile_hes_rate;
       	params.infile_cnv_rate;
       	params.infile_inv_rate1;
       	params.infile_inv_rate2;
      	//params.SNP1,SNP2,INDEL1,INDEL2,INQ,TAND1,TAND2,CNV1,CNV2,INVER1,INVER2,TRANS1,TRANS2;*/
      	params.infile_s=0;params.infile_i=0;params.infile_t=0;params.infile_c=1;params.infile_I=0;params.infile_T=0;
       	params.infile_td_no1=12;params.infile_td_no2=10;params.infile_tumor=1;params.infile_Nt=1;
	for (int i=1; i<argc; i++)
	{
		string token = argv[i];
		if(token.compare("-infile_ref") == 0)
		{
			i++;
			if(i == argc){
				cerr << "Unexpected input ref file." <<endl;
				exit(-1);
			}
			params.infile_ref = argv[i]; 
		}
		else if(token.compare("-infile_s") == 0)
		{
			i++;
			if((i == argc)||((atoi(argv[i])!=0)&&(atoi(argv[i])!=1)&&(atoi(argv[i])!=2)&&(atoi(argv[i])!=3))){
				cerr << "Unexpected input infile_s value<0,1>." <<endl;
				//usage();
				exit(-1);
			}
			params.infile_s = atoi(argv[i]); 
		}
		else if(token.compare("-infile_i") == 0)
		{
			i++;
			if((i == argc)||((atoi(argv[i])!=0)&&(atoi(argv[i])!=1)&&(atoi(argv[i])!=2)&&(atoi(argv[i])!=3))){
				cerr << "Unexpected input infile_i value<0,1>." <<endl;
				exit(-1);
			}
			params.infile_i = atoi(argv[i]);
		}
		else if(token.compare("-infile_t") == 0)
		{
			i++;
			if((i == argc)||((atoi(argv[i])!=0)&&(atoi(argv[i])!=1)&&(atoi(argv[i])!=2)&&(atoi(argv[i])!=3))){
				cerr << "Unexpected input infile_t value<0,1>." <<endl;
				exit(-1);
			}
			params.infile_t = atoi(argv[i]); 
		}
		else if(token.compare("-infile_c") == 0)
		{
			i++;
			if((i == argc)||((atoi(argv[i])!=0)&&(atoi(argv[i])!=1)&&(atoi(argv[i])!=2)&&(atoi(argv[i])!=3))){
				cerr << "Unexpected input infile_c value<0,1>." <<endl;
				exit(-1);
			}
			params.infile_c = atoi(argv[i]);
		}
		else if(token.compare("-infile_I") == 0)
		{
			i++;
			if((i == argc)||((atoi(argv[i])!=0)&&(atoi(argv[i])!=1)&&(atoi(argv[i])!=2)&&(atoi(argv[i])!=3))){
				cerr << "Unexpected input infile_I value<0,1>." <<endl;
				exit(-1);
			}
			params.infile_I = atoi(argv[i]);
		}
		else if(token.compare("-infile_T") == 0)
		{
			i++;
			if((i == argc)||((atoi(argv[i])!=0)&&(atoi(argv[i])!=1)&&(atoi(argv[i])!=2)&&(atoi(argv[i])!=3))){
				cerr << "Unexpected input infile_T value<0,1>." <<endl;
				exit(-1);
			}
			params.infile_T = atoi(argv[i]);
		}
		
		
		
		else if(token.compare("-infile_snp_rate") == 0)
		{
			i++;
			if(i == argc){
				cerr << "Unexpected input snp rate file." <<endl;
				exit(-1);
			}
			params.infile_snp_rate = argv[i]; 
		}
		else if(token.compare("-infile_ts") == 0)
		{
			i++;
			if(i == argc){
				cerr << "Unexpected input snp transition file." <<endl;
				exit(-1);
			}
			params.infile_ts = atof(argv[i]); 
		}
		else if(token.compare("-infile_hes_rate") == 0)
		{
			i++;
			if(i == argc){
				cerr << "Unexpected input snp hes file." <<endl;
				exit(-1);
			}
			params.infile_hes_rate = atof(argv[i]); 
		}
		else if(token.compare("-infile_td_no1") == 0)
		{
			i++;
			if(i == argc){
				cerr << "Unexpected input tandem no1." <<endl;
				exit(-1);
			}
			params.infile_td_no1 = atof(argv[i]); 
		}
		else if(token.compare("-infile_td_no2") == 0)
		{
			i++;
			if(i == argc){
				cerr << "Unexpected input tandem no2" <<endl;
				exit(-1);
			}
			params.infile_td_no2 = atof(argv[i]); 
		}
		else if(token.compare("-infile_tumor") == 0)
		{
			i++;
			if(i == argc){
				cerr << "Unexpected input infile_tumor value<0,1>" <<endl;
				exit(-1);
			}
			params.infile_tumor = atof(argv[i]); 
		}
		else if(token.compare("-infile_Nt") == 0)
		{
			i++;
			if(i == argc){
				cerr << "Unexpected input infile_Nt value<1,2,3...>" <<endl;
				exit(-1);
			}
			params.infile_Nt = atof(argv[i]); 
		}
		else
		{
			cerr << "Unknow parameter: " << token <<"." <<endl;
			//usage();
                        exit(-1);
		}
		
	}	
}


void simulate::germline_SNP(parameters& params)   //generate SNP variations
{
	ifstream input,SNP_rate;;
	cout<<"Germline SNP..."<<endl;
	long int *SNP_LOC,snp_made=0,*genome_count,snp_count[25],total_snp=0,meanDistance=0;
	char* SNP_flag;
	float snp_rate[24];
	float hot_degree=0.75;
	int Nh=5,m=0;  //m=0,2,.....23 instead of 24 chromosomes
	long int region_hot[24][Nh];
	long int hot_count=0;
	ofstream SNP_LOC1,SNP1,SNP2,SNP_LOC2;
	params.SNP1="./Results/germline_snp1.fa";
	params.SNP2="./Results/germline_snp2.fa";
	input.open(params.infile_ref.c_str(),ios::in);
	if (!input.is_open())
    	{
		cout<<"Cant't open reference file\n";exit(-1);
     	}
	SNP_LOC1.open("./Results/germlinr_snp_messaeg1.txt",ios::out);
	if (!SNP_LOC1.is_open())
    	{
		cout<<"Cant't open file for SNP message1 writing\n";exit(-1);
     	}
	SNP1.open(params.SNP1.c_str(),ios::out);
	if (!SNP1.is_open())
    	{
		cout<<"Cant't open file for SNP1 writing\n";exit(-1);
     	}
	SNP_LOC2.open("./Results/germlinr_snp_messaeg2.txt",ios::out);
	if (!SNP_LOC2.is_open())
    	{
		cout<<"Cant't open file for SNP message2 writing\n";exit(-1);
     	}
	SNP2.open(params.SNP2.c_str(),ios::out);
	if (!SNP2.is_open())
    	{
		cout<<"Cant't open file for SNP2 writing\n";exit(-1);
     	}
	SNP_rate.open(params.infile_snp_rate.c_str(),ios::in);
	if (!SNP_rate.is_open())
    	{
		cout<<"Cant't open snp rate file\n";exit(-1);
     	}
	genome_count=count_genome(input);//compute the length of chromosome 
	long int i=0; //i =1,2.....22,X,Y
	while(SNP_rate)    //compute snp count
	{
		string str,c;
		getline(SNP_rate,str);//如果没有到达文件的末尾进行读取一行
		istringstream iss(str);
		iss >> c;
		if(c=="Chromosome")
		{
			continue;
		}
		else
		{
			iss >> c;
			iss >> c;
			iss >> snp_rate[i];
                        //(r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
			snp_count[i]=genome_count[i]/(snp_rate[i]*1000);
			//cout<<"genome_count[chr"<<i+1<<"]: "<<genome_count[i]<<endl;
			i++;
		}
	}
	for(int l=0;l<24;l++)
	{
		total_snp+=snp_count[l];
	}
	SNP_LOC=(long int*) calloc (total_snp,sizeof(long int));
	SNP_flag=(char*) calloc (total_snp,sizeof(char));

	long int snp_num=0;   //snp tumber
	long int total_count=0;  //Base number
	gsl_rng_env_setup();
	T = gsl_rng_default;//T is const gsl_rng_type *
	r = gsl_rng_alloc (T);//r point at T，r is gsl_rng *
	region_hot[0][0]=genome_count[0]/40;
	long int total=0;
	for(m=0;m<24;m++)    //compute hot region
	{ 
		region_hot[m][0]=total+genome_count[i]/40;
		total+=genome_count[m];	
		if(genome_count[m]!=0)
		{
			for(int h=1;h<Nh;h++)
			{
				region_hot[m][h]=region_hot[m][h-1]+(genome_count[m]*7/80+rand()%(genome_count[m])/80);//cout<<"region: "<<region_hot[m][h]<<endl;
			}
		}

	}
	m=0;
	int h=0;
	while(snp_made<total_snp)  	//generate location for germline SNP
	{
		float temp_ran=0.75+gsl_rng_uniform(r)*0.25;//gsl_ran_ugaussian(r);
		float snp_rate_hot;
		while((snp_made==snp_num)&&(m<24))
		{
			if(snp_count[m]==0){total_count+=genome_count[m];m++;continue;}
			snp_rate_hot=snp_rate[m]*(20-Nh)/10;  //not in  hot region
			SNP_LOC[snp_made]=total_count+(int)(snp_rate_hot*1000*temp_ran);
			SNP_flag[snp_made]='n';
			total_count+=genome_count[m];
			snp_made++;
			snp_num+=snp_count[m];
			float step=abs((int)(snp_rate[m]*1000*temp_ran));
			//cout<<"chrrr"<<m+1<<"  loc:"<<SNP_LOC[snp_made-1]<<"  total_count:"<<total_count<<" step:"<<step<<" rate: "<<snp_rate[m]<<endl;
			m++;
			h=0;
		}
			float step=abs((int)(snp_rate[m-1]*1000*temp_ran));

		//judge if it is in hot region
		if(h<=Nh)
		{
			long int temp_length;
			//if((temp_length>=(-snp_rate[m-1]*1000))&&(temp_length<=(genome_count[m-1]/20-snp_rate[m-1]*1000))&&(SNP_flag[snp_made-1]=='n'))
			if((SNP_flag[snp_made-1]=='n'))
				{temp_length=SNP_LOC[snp_made-1]-region_hot[m-1][h];}
			else
				{temp_length=SNP_LOC[snp_made-1]-region_hot[m-1][h-1];}
			if((temp_length>=(-snp_rate[m-1]*1000))&&(temp_length<=(genome_count[m-1]/20-snp_rate[m-1]*1000)))
			{
				if(SNP_flag[snp_made-1]=='n'){h++;//cout<<"h "<<h<<endl;
				}//
				snp_rate_hot=snp_rate[m-1]*Nh/10;
				SNP_flag[snp_made]='h';
			}
			else{	snp_rate_hot=snp_rate[m-1]*(20-Nh)/10;SNP_flag[snp_made]='n';}

		}
		else{	snp_rate_hot=snp_rate[m-1]*(20-Nh)/10;SNP_flag[snp_made]='n';}	
		

		SNP_LOC[snp_made]=SNP_LOC[snp_made-1]+(int)(snp_rate_hot*1000*temp_ran);
				//cout<<"snp_rate_hot "<<snp_rate_hot<<"loc:"<<SNP_LOC[snp_made]<<"region_hot[m-1][h-1] "<<region_hot[m-1][h-1]<<endl;	
		
		snp_made++;
	}
	//Germline snp variation

	long int kk=0;
	for(i=1;i<=total_snp; i++)//Removing duplicates SNPs 
	{
		if(SNP_LOC[i]!=SNP_LOC[kk])
			{
				kk++;
				SNP_LOC[kk]=SNP_LOC[i];
			}
	}

	char c,name[100];
	i=0;
	float Ts_rate=params.infile_ts;
	float Tr_rate=1.0/Ts_rate;
	float Het_rate=params.infile_hes_rate;

	//cout<<"*****"<<Ts_rate<<" "<<Het_rate<<endl;
	input.clear();
	input.seekg(ios::beg);
	//for(long int kk=0;kk<total_snp;kk++)cout<<SNP_LOC[kk]<<endl;
	SNP_LOC1<<"chr"<<"\t"<<"loc"<<"\t\t"<<"ref"<<"\t\talter"<<"\n";
	SNP_LOC2<<"chr"<<"\t"<<"loc"<<"\t\t"<<"ref"<<"\t\talter"<<"\n";
	for(long int pos=0;(c=input.get())!=EOF;pos++)//input is reference file
	{
			if(c=='>')
			{
					input.getline(name,100);
					SNP1<<">"<<name<<"\n";
					SNP2<<">"<<name<<"\n";
					//cout<<name<<" "<<pos<<endl;
					pos--;
					continue;
			}

			if(c=='\n')
			{
					pos--;
			}
			if(c=='a')
			{
				c='A';
			}
			if(c=='t')
			{
				c='T';
			}
			if(c=='g')
			{
				c='G';
			}
			if(c=='c')
			{
				c='C';
			}
			if(pos==(SNP_LOC[i]-1))	//loc is the location for germline SNP
			{
				//cout<<name<<SNP_LOC[i]<<endl;
string aaa=name;
				//if(aaa.find("chr8")){				cout<<"mytest"<<name<<SNP_LOC[i]<<endl;cout<<name<<SNP_LOC[i+1]<<endl;cout<<name<<SNP_LOC[i+2]<<endl;cout<<name<<SNP_LOC[i+3]<<endl;}
				i++;//i is eaquals to snp_made;   //execute snp variation  1.print information 2.change nueclitide

				if(c=='N'||c=='n'){	//N Region
					int nucli=rand()%4; //0=='A',1==='T',2=='G',3=='c'
					switch(nucli)
					{
						case 0: {
								SNP1.put('A');
								SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA"<<"\n";
								if((rand()%100)<(Het_rate*100))  //Heterozigous
								{
									int het_a=rand()%3;
									if(het_a==0){SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT"<<"\n";}
									else if(het_a==1){SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG"<<"\n";}
									else{SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC"<<"\n";}
								}
							   	else //Homogenous
								{SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA"<<"\n";}

							  };
						break;
						case 1: {
								SNP1.put('T');
								SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT"<<"\n";
								if((rand()%100)<(Het_rate*100))//Hetero
								{
									int het_a=rand()%3;
									if(het_a==0){SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA"<<"\n";}
									else if(het_a==1){SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG"<<"\n";}
									else{SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC"<<"\n";}
								}
							   	else{SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT"<<"\n";}

								//continue;
							  };
						break;
						case 2: {
								SNP1.put('G');
								SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG"<<"\n";
								if((rand()%100)<(Het_rate*100))//Hetero
								{
									int het_a=rand()%3;
									if(het_a==0){SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA"<<"\n";}
									else if(het_a==1){SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT"<<"\n";}
									else{SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC"<<"\n";}
								}
							   	else{SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG"<<"\n";}

							  };
						break;
						case 3: {
								SNP1.put('C');
								SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC"<<"\n";
								if((rand()%100)<(Het_rate*100))//Hetero
								{
									int het_a=rand()%3;
									if(het_a==0){SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA"<<"\n";}
									else if(het_a==1){SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT"<<"\n";}
									else if(het_a==2){SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG"<<"\n";}
								}
							   	else{SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC"<<"\n";}

							  };
						break;
						default:cout<<"error"<<nucli<<endl;
					}
					continue;  //complete this  for circulation
				}

				if(rand()%(int)((Ts_rate+1.0)*100)<(Ts_rate*100))   ////Transtion
				{
					if(c=='A'||c=='a')
					{
						SNP1.put('G');
						SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";
						if((rand()%100)<(Het_rate*100))  //Hetero
						{SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";}
						else  //Homo
						{SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";}

					}
					else if(c=='T'||c=='t')
					{
						SNP1.put('C');
						SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC\n";
						if((rand()%100)<(Het_rate*100))  //Hetero
						{SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";}
						else  //Homo
						{SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC\n";}
					}
					else if(c=='G'||c=='g')
					{
						SNP1.put('A');
						SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
						if((rand()%100)<(Het_rate*100))  //Hetero
						{SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";}
						else  //Homo
						{SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";}
					}
					else if(c=='C'||c=='c')
					{
						SNP1.put('G');
						SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";
						if((rand()%100)<(Het_rate*100))  //Hetero
						{SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";}
						else  //Homo
						{SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";}
					}
					continue;
				}
				else        //Transvertion
				{
					if(c=='A'||c=='a')
					{
						if(rand()%2)   //Transvertion A->C
						{
							SNP1.put('C');
							SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC\n";
							if((rand()%100)<(Het_rate*100))  //Hetero
							{SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";}
							else  //Homo
							{SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC\n";}

						}
						else   //Transvertion A->T
						{
							SNP1.put('T');
							SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							if((rand()%100)<(Het_rate*100))  //Hetero
							{SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";}
							else  //Homo
							{SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";}
						}
					}
					else if(c=='T'||c=='t')
					{
						if(rand()%2)   //Transvertion T->A
						{
							SNP1.put('A');
							SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
							if((rand()%100)<(Het_rate*100))  //Hetero
							{SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";}
							else  //Homo
							{SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";}

						}
						else   //Transvertion T->G
						{
							SNP1.put('G');
							SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";
							if((rand()%(int)((Het_rate+1)*100))<(Het_rate*100))  //Hetero
							{SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";}
							else  //Homo
							{SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";}
						}
					}
					else if(c=='G'||c=='g')
					{
						if(rand()%2)   //Transvertion G->C
						{
							SNP1.put('C');
							SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC\n";
							if((rand()%100)<(Het_rate*100))  //Hetero
							{SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";}
							else  //Homo
							{SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC\n";}

						}
						else   //Transvertion G->T
						{
							SNP1.put('T');
							SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							if((rand()%100)<(Het_rate*100))  //Hetero
							{SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";}
							else  //Homo
							{SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";}
						}
					}
					else if(c=='C'||c=='c')
					{
						if(rand()%2)   //Transvertion C->A
						{
							SNP1.put('A');
							SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
							if((rand()%100)<(Het_rate*100))  //Hetero
							{SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC\n";}
							else  //Homo
							{SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";}

						}
						else   //Transvertion C->G
						{
							SNP1.put('G');
							SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";
							if((rand()%100)<(Het_rate*100))  //Hetero
							{SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC\n";}
							else  //Homo
							{SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";}
						}
					}
					continue;
				}

			}

			SNP1.put(c);
			SNP2.put(c);
			//SNP_LOC1<<"";
			//SNP_LOC2<<"";


	}

	SNP_LOC=(long int *) realloc (SNP_LOC, 0*(sizeof (long int)));
	SNP_flag=(char *) realloc (SNP_flag, 0*(sizeof (char)));
	SNP1.close();
	SNP2.close();
	SNP_LOC1.close();
	SNP_LOC2.close();
	SNP1.clear();
	SNP2.clear();
	SNP_LOC1.clear();
	SNP_LOC2.clear();
	//cout<<"Germline SNP simulation complete"<<endl;
}

void simulate::somatic_SNP(parameters& params)   //generate SNP variations
{
	ifstream input,SNP_rate,SNP_IN1,SNP_IN2;
	cout<<"somatic SNP..."<<endl;
	long int *SNP_LOC,snp_made=0,*genome_count,snp_count[25],total_snp=0,meanDistance=0;
	char* SNP_flag;
	float snp_rate[24];
	float hot_degree=0.75;
	int Nh=5,m=0;  //m=0,2,.....23 instead of 24 chromosomes
	long int region_hot[24][Nh];
	long int hot_count=0;
	ofstream SNP_LOC1,SNP1,SNP2,SNP_LOC2;
	char somatic_snp_name[300];
	sprintf(somatic_snp_name,"./Results/tumor%d_snp1.fa",tumor_flag);
     	params.SNP1=somatic_snp_name;
     	sprintf(somatic_snp_name,"./Results/tumor%d_snp2.fa",tumor_flag);
     	params.SNP2=somatic_snp_name;
     	sprintf(somatic_snp_name,"./Results/tumor%d_snp_message1.txt",tumor_flag);
     	SNP_LOC1.open(somatic_snp_name,ios::out);
     	sprintf(somatic_snp_name,"./Results/tumor%d_snp_message2.txt",tumor_flag);
     	SNP_LOC2.open(somatic_snp_name,ios::out);
	input.open(params.infile_ref.c_str(),ios::in);
	if (!input.is_open())
    	{
		cout<<"Cant't open reference file\n";exit(-1);
     	}
	
	if (!SNP_LOC1.is_open())
    	{
		cout<<"Cant't open file for SNP message1 writing\n";exit(-1);
     	}
	SNP1.open(params.SNP1.c_str(),ios::out);
	if (!SNP1.is_open())
    	{
		cout<<"Cant't open file for SNP1 writing\n";exit(-1);
     	}

	if (!SNP_LOC2.is_open())
    	{
		cout<<"Cant't open file for SNP message2 writing\n";exit(-1);
     	}
	SNP2.open(params.SNP2.c_str(),ios::out);
	if (!SNP2.is_open())
    	{
		cout<<"Cant't open file for SNP2 writing\n";exit(-1);
     	}
	SNP_rate.open(params.infile_snp_rate.c_str(),ios::in);
	if (!SNP_rate.is_open())
    	{
		cout<<"Cant't open snp rate file\n";exit(-1);
     	}
     	SNP_IN1.open(somatic_ref1.c_str(),ios::in);
	if (!SNP_IN1.is_open())
	{
		cout<<"Cant't open somatic_ref1 for SNP1 reading\n";exit(-1);
	}
	SNP_IN2.open(somatic_ref2.c_str(),ios::in);
	if (!SNP_IN2.is_open())
	{
		cout<<"Cant't open somatic_ref2 for SNP2 reading\n";exit(-1);
	}
	genome_count=count_genome(SNP_IN1);//compute the length of chromosome 
	long int i=0; //i =1,2.....22,X,Y
	while(SNP_rate)    //compute snp count
	{
		string str,c;
		getline(SNP_rate,str);//如果没有到达文件的末尾进行读取一行
		istringstream iss(str);
		iss >> c;
		if(c=="Chromosome")
		{
			continue;
		}
		else
		{
			iss >> c;
			iss >> c;
			iss >> snp_rate[i];
                        //(r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
			snp_count[i]=genome_count[i]/(snp_rate[i]*1000);
			//cout<<"genome_count[chr"<<i+1<<"]: "<<genome_count[i]<<endl;
			i++;
		}
	}
	for(int l=0;l<24;l++)
	{
		total_snp+=snp_count[l];
	}
	SNP_LOC=(long int*) calloc (total_snp,sizeof(long int));
	SNP_flag=(char*) calloc (total_snp,sizeof(char));

	long int snp_num=0;   //snp tumber
	long int total_count=0;  //Base number
	gsl_rng_env_setup();
	T = gsl_rng_default;//T is const gsl_rng_type *
	r = gsl_rng_alloc (T);//r point at T，r is gsl_rng *
	region_hot[0][0]=genome_count[0]/40;
	long int total=0;
	for(m=0;m<24;m++)    //compute hot region
	{ 
		region_hot[m][0]=total+genome_count[i]/40;
		total+=genome_count[m];	
		if(genome_count[m]!=0)
		{
			for(int h=1;h<Nh;h++)
			{
				region_hot[m][h]=region_hot[m][h-1]+(genome_count[m]*7/80+rand()%(genome_count[m])/80);//cout<<"region: "<<region_hot[m][h]<<endl;
			}
		}

	}
	m=0;
	int h=0;
	while(snp_made<total_snp)  	//generate location for germline SNP
	{
		float temp_ran=0.75+gsl_rng_uniform(r)*0.25;//gsl_ran_ugaussian(r);
		float snp_rate_hot;
		while((snp_made==snp_num)&&(m<24))
		{
			if(snp_count[m]==0){total_count+=genome_count[m];m++;continue;}
			snp_rate_hot=snp_rate[m]*(20-Nh)/10;  //not in  hot region
			SNP_LOC[snp_made]=total_count+(int)(snp_rate_hot*1000*temp_ran);
			SNP_flag[snp_made]='n';
			total_count+=genome_count[m];
			snp_made++;
			snp_num+=snp_count[m];
			float step=abs((int)(snp_rate[m]*1000*temp_ran));
			//cout<<"chrrr"<<m+1<<"  loc:"<<SNP_LOC[snp_made-1]<<"  total_count:"<<total_count<<" step:"<<step<<" rate: "<<snp_rate[m]<<endl;
			m++;
			h=0;
		}
			float step=abs((int)(snp_rate[m-1]*1000*temp_ran));

		//judge if it is in hot region
		if(h<=Nh)
		{
			long int temp_length;
			//if((temp_length>=(-snp_rate[m-1]*1000))&&(temp_length<=(genome_count[m-1]/20-snp_rate[m-1]*1000))&&(SNP_flag[snp_made-1]=='n'))
			if((SNP_flag[snp_made-1]=='n'))
				{temp_length=SNP_LOC[snp_made-1]-region_hot[m-1][h];}
			else
				{temp_length=SNP_LOC[snp_made-1]-region_hot[m-1][h-1];}
			if((temp_length>=(-snp_rate[m-1]*1000))&&(temp_length<=(genome_count[m-1]/20-snp_rate[m-1]*1000)))
			{
				if(SNP_flag[snp_made-1]=='n'){h++;//cout<<"h "<<h<<endl;
				}//
				snp_rate_hot=snp_rate[m-1]*Nh/10;
				SNP_flag[snp_made]='h';
			}
			else{	snp_rate_hot=snp_rate[m-1]*(20-Nh)/10;SNP_flag[snp_made]='n';}

		}
		else{	snp_rate_hot=snp_rate[m-1]*(20-Nh)/10;SNP_flag[snp_made]='n';}	
		

		SNP_LOC[snp_made]=SNP_LOC[snp_made-1]+(int)(snp_rate_hot*1000*temp_ran);
				//cout<<"snp_rate_hot "<<snp_rate_hot<<"loc:"<<SNP_LOC[snp_made]<<"region_hot[m-1][h-1] "<<region_hot[m-1][h-1]<<endl;	
		
		snp_made++;
	}
	//Germline snp variation

	long int kk=0;
	for(i=1;i<=total_snp; i++)//Removing duplicates SNPs 
	{
		if(SNP_LOC[i]!=SNP_LOC[kk])
			{
				kk++;
				SNP_LOC[kk]=SNP_LOC[i];
			}
	}

	char c,c2,name[100];
	i=0;
	float Ts_rate=params.infile_ts;
	float Tr_rate=1.0/Ts_rate;
	float Het_rate=params.infile_hes_rate;

	//cout<<"*****"<<Ts_rate<<" "<<Het_rate<<endl;
	SNP_IN1.clear();
	SNP_IN1.seekg(ios::beg);
	SNP_IN2.clear();
	SNP_IN2.seekg(ios::beg);
	//for(long int kk=0;kk<total_snp;kk++)cout<<SNP_LOC[kk]<<endl;
	SNP_LOC1<<"chr"<<"\t"<<"loc"<<"\t\t"<<"ref"<<"\t\talter"<<"\n";
	SNP_LOC2<<"chr"<<"\t"<<"loc"<<"\t\t"<<"ref"<<"\t\talter"<<"\n";
	int snp_in1_flag=1,snp_in2_flag=1;
	for(long int pos=0;;pos++)//input is reference file
	{
		if(snp_in1_flag==1){if((c=SNP_IN1.get())!=EOF){} else{break;}}
		if(snp_in2_flag==1){if((c2=SNP_IN2.get())!=EOF){} else{break;}}
		//if(pos<100)cout<<c<<c2<<endl;			
		if((c=='>')||(c=='\n'))
		{
			pos--;
			if(c=='>')
			{
				SNP_IN1.getline(name,100);
				SNP1<<">"<<name<<"\n";
				//cout<<name<<"  "<<pos<<endl;
				snp_in1_flag=1;
				snp_in2_flag=0;
				continue;
			}
			
			
		}
		if((c2=='>')||(c2=='\n'))
		{
			pos--;	
			if(c2=='>')
			{
				SNP_IN2.getline(name,100);
				SNP2<<">"<<name<<"\n";
				//cout<<name<<"  "<<pos<<endl;
				snp_in2_flag=1;
				snp_in1_flag=0;
				continue;

			}
			
		}
		snp_in1_flag=1;snp_in2_flag=1;
		if(pos==(SNP_LOC[i]-1))	//loc is the location for somatic SNP
		{
			i++;//i is eaquals to snp_made;   //execute snp variation  1.print information 2.change nueclitide

			if(c=='N'||c=='n')
			{	//N Region
				int nucli=rand()%4; //0=='A',1==='T',2=='G',3=='c'
				switch(nucli)
				{
						case 0: {
								SNP1.put('A');
								SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA"<<"\n";
								if((rand()%100)<(Het_rate*100))  //Heterozigous
								{
									int het_a=rand()%3;
									if(het_a==0){SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT"<<"\n";}
									else if(het_a==1){SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG"<<"\n";}
									else{SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC"<<"\n";}
								}
							   	else //Homogenous
								{SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA"<<"\n";}

							  };
						break;
						case 1: {
								SNP1.put('T');
								SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT"<<"\n";
								if((rand()%100)<(Het_rate*100))//Hetero
								{
									int het_a=rand()%3;
									if(het_a==0){SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA"<<"\n";}
									else if(het_a==1){SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG"<<"\n";}
									else{SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC"<<"\n";}
								}
							   	else{SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT"<<"\n";}

								//continue;
							  };
						break;
						case 2: {
								SNP1.put('G');
								SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG"<<"\n";
								if((rand()%100)<(Het_rate*100))//Hetero
								{
									int het_a=rand()%3;
									if(het_a==0){SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA"<<"\n";}
									else if(het_a==1){SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT"<<"\n";}
									else{SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC"<<"\n";}
								}
							   	else{SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG"<<"\n";}

							  };
						break;
						case 3: {
								SNP1.put('C');
								SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC"<<"\n";
								if((rand()%100)<(Het_rate*100))//Hetero
								{
									int het_a=rand()%3;
									if(het_a==0){SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA"<<"\n";}
									else if(het_a==1){SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT"<<"\n";}
									else if(het_a==2){SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG"<<"\n";}
								}
							   	else{SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC"<<"\n";}

							  };
						break;
						default:cout<<"error"<<nucli<<endl;
				}
				continue;  //complete this  for circulation
			}

			if(rand()%(int)((Ts_rate+1.0)*100)<(Ts_rate*100))   ////Transition
			{
				if(c=='A'||c=='a')
				{
					if(c2=='A'||c2=='a')
					{
						if((rand()%100)<(Het_rate*100))  //Hetero
						{
							if(rand()%2)
							{
								SNP1.put('G');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";
								SNP2.put('A');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
							}
							else
							{
								SNP1.put('A');//SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
								SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tG\n";
							}
							
						}
						else  //Homo
						{
							SNP1.put('G');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";
							SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tG\n";
						}
					}
					if(c2=='T'||c2=='t')
					{
						if((rand()%100)<(Het_rate*100))  //Hetero
						{
							if(rand()%2)
							{
								SNP1.put('G');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";
								SNP2.put('T');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
							}
							else
							{
								SNP1.put('A');//SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
								SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tC\n";
							}
							
						}
						else  //Homo
						{
							SNP1.put('G');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";
							SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tC\n";
						}
					}
					if(c2=='G'||c2=='g')
					{
						if((rand()%100)<(Het_rate*100))  //Hetero
						{
							if(rand()%2)
							{
								SNP1.put('G');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";
								SNP2.put('G');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
							}
							else
							{
								SNP1.put('A');//SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
								SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tA\n";
							}
							
						}
						else  //Homo
						{
							SNP1.put('G');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";
							SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tA\n";
						}
					}
					if(c2=='C'||c2=='c')
					{
						if((rand()%100)<(Het_rate*100))  //Hetero
						{
							if(rand()%2)
							{
								SNP1.put('G');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";
								SNP2.put('C');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
							}
							else
							{
								SNP1.put('A');//SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
								SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tT\n";
							}
							
						}
						else  //Homo
						{
							SNP1.put('G');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";
							SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tT\n";
						}
					}	

				}
				else if(c=='T'||c=='t')
				{
					if(c2=='A'||c2=='a')
					{
						if((rand()%100)<(Het_rate*100))  //Hetero
						{
							if(rand()%2)
							{
								SNP1.put('C');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC\n";
								SNP2.put('A');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							}
							else
							{
								SNP1.put('T');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
								SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tG\n";
							}
							
						}
						else  //Homo
						{
							SNP1.put('C');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC\n";
							SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tG\n";
						}
					}
					if(c2=='T'||c2=='t')
					{
						if((rand()%100)<(Het_rate*100))  //Hetero
						{
							if(rand()%2)
							{
								SNP1.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC\n";
								SNP2.put('T');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							}
							else
							{
								SNP1.put('T');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
								SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tC\n";
							}
							
						}
						else  //Homo
						{
							SNP1.put('C');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC\n";
							SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tC\n";
						}
					}
					if(c2=='G'||c2=='g')
					{
						if((rand()%100)<(Het_rate*100))  //Hetero
						{
							if(rand()%2)
							{
								SNP1.put('C');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC\n";
								SNP2.put('G');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							}
							else
							{
								SNP1.put('T');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
								SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tA\n";
							}
							
						}
						else  //Homo
						{
							SNP1.put('C');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC\n";
							SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tA\n";
						}
					}
					if(c2=='C'||c2=='c')
					{
						if((rand()%100)<(Het_rate*100))  //Hetero
						{
							if(rand()%2)
							{
								SNP1.put('C');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC\n";
								SNP2.put('C');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							}
							else
							{
								SNP1.put('T');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
								SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tT\n";
							}
							
						}
						else  //Homo
						{
							SNP1.put('C');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC\n";
							SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tT\n";
						}
					}
				}
				else if(c=='G'||c=='g')
				{						
					if(c2=='A'||c2=='a')
					{
						if((rand()%100)<(Het_rate*100))  //Hetero
						{
							if(rand()%2)
							{
								SNP1.put('A');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
								SNP2.put('A');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							}
							else
							{
								SNP1.put('G');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
								SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tG\n";
							}
							
						}
						else  //Homo
						{
							SNP1.put('A');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
							SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tG\n";
						}
					}
					if(c2=='T'||c2=='t')
					{
						if((rand()%100)<(Het_rate*100))  //Hetero
						{
							if(rand()%2)
							{
								SNP1.put('A');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
								SNP2.put('T');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							}
							else
							{
								SNP1.put('G');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
								SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tC\n";
							}
							
						}
						else  //Homo
						{
							SNP1.put('A');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
							SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tC\n";
						}
					}
					if(c2=='G'||c2=='g')
					{
						if((rand()%100)<(Het_rate*100))  //Hetero
						{
							if(rand()%2)
							{
								SNP1.put('A');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
								SNP2.put('G');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							}
							else
							{
								SNP1.put('G');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
								SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tA\n";
							}
							
						}
						else  //Homo
						{
							SNP1.put('A');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
							SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tA\n";
						}
					}
					if(c2=='C'||c2=='c')
					{
						if((rand()%100)<(Het_rate*100))  //Hetero
						{
							if(rand()%2)
							{
								SNP1.put('A');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
								SNP2.put('C');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							}
							else
							{
								SNP1.put('G');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
								SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tT\n";
							}
							
						}
						else  //Homo
						{
							SNP1.put('A');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
							SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tT\n";
						}
					}
				}
				else if(c=='C'||c=='c')
				{
					if(c2=='A'||c2=='a')
					{
						if((rand()%100)<(Het_rate*100))  //Hetero
						{
							if(rand()%2)
							{
								SNP1.put('T');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
								SNP2.put('A');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							}
							else
							{
								SNP1.put('C');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
								SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tG\n";
							}
							
						}
						else  //Homo
						{
							SNP1.put('T');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tG\n";
						}
					}
					if(c2=='T'||c2=='t')
					{
						if((rand()%100)<(Het_rate*100))  //Hetero
						{
							if(rand()%2)
							{
								SNP1.put('T');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
								SNP2.put('T');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							}
							else
							{
								SNP1.put('C');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
								SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tC\n";
							}
							
						}
						else  //Homo
						{
							SNP1.put('T');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tC\n";
						}
					}
					if(c2=='G'||c2=='g')
					{
						if((rand()%100)<(Het_rate*100))  //Hetero
						{
							if(rand()%2)
							{
								SNP1.put('T');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
								SNP2.put('G');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							}
							else
							{
								SNP1.put('C');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
								SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tA\n";
							}
							
						}
						else  //Homo
						{
							SNP1.put('T');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tA\n";
						}
					}
					if(c2=='C'||c2=='c')
					{
						if((rand()%100)<(Het_rate*100))  //Hetero
						{
							if(rand()%2)
							{
								SNP1.put('T');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
								SNP2.put('C');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							}
							else
							{
								SNP1.put('C');//SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
								SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tT\n";
							}
							
						}
						else  //Homo
						{
							SNP1.put('T');SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tT\n";
						}
					}
				}
				continue;
			}
			else        //Transvertion
			{
				if(c=='A'||c=='a')
				{
						if(rand()%2)   //Transvertion A->C
						{
							SNP1.put('C');
							SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC\n";
							if((rand()%100)<(Het_rate*100))  //Hetero
							{SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tA\n";}
							else  //Homo
							{SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tC\n";}

						}
						else   //Transvertion A->T
						{
							SNP1.put('T');
							SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							if((rand()%100)<(Het_rate*100))  //Hetero
							{SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tA\n";}
							else  //Homo
							{SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tT\n";}
						}
				}
				else if(c=='T'||c=='t')
				{
						if(rand()%2)   //Transvertion T->A
						{
							SNP1.put('A');
							SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
							if((rand()%100)<(Het_rate*100))  //Hetero
							{SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tT\n";}
							else  //Homo
							{SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tA\n";}

						}
						else   //Transvertion T->G
						{
							SNP1.put('G');
							SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";
							if((rand()%(int)((Het_rate+1)*100))<(Het_rate*100))  //Hetero
							{SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tT\n";}
							else  //Homo
							{SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tG\n";}
						}
				}
				else if(c=='G'||c=='g')
				{
						if(rand()%2)   //Transvertion G->C
						{
							SNP1.put('C');
							SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tC\n";
							if((rand()%100)<(Het_rate*100))  //Hetero
							{SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tG\n";}
							else  //Homo
							{SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tC\n";}

						}
						else   //Transvertion G->T
						{
							SNP1.put('T');
							SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tT\n";
							if((rand()%100)<(Het_rate*100))  //Hetero
							{SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tG\n";}
							else  //Homo
							{SNP2.put('T');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tT\n";}
						}
				}
				else if(c=='C'||c=='c')
				{
						if(rand()%2)   //Transvertion C->A
						{
							SNP1.put('A');
							SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tA\n";
							if((rand()%100)<(Het_rate*100))  //Hetero
							{SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tC\n";}
							else  //Homo
							{SNP2.put('A');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tA\n";}

						}
						else   //Transvertion C->G
						{
							SNP1.put('G');
							SNP_LOC1<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c<<"\t\tG\n";
							if((rand()%100)<(Het_rate*100))  //Hetero
							{SNP2.put('C');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tC\n";}
							else  //Homo
							{SNP2.put('G');SNP_LOC2<<name<<"\t"<<SNP_LOC[i-1]<<"\t\t"<<c2<<"\t\tG\n";}
						}
				}
				continue;
			}

		}

		SNP1.put(c);
		SNP2.put(c2);
		//SNP_LOC1<<"";
		//SNP_LOC2<<"";


	}

	SNP_LOC=(long int *) realloc (SNP_LOC, 0*(sizeof (long int)));
	SNP_flag=(char *) realloc (SNP_flag, 0*(sizeof (char)));
	SNP1.close();
	SNP2.close();
	SNP_LOC1.close();
	SNP_LOC2.close();
	SNP1.clear();
	SNP2.clear();
	SNP_LOC1.clear();
	SNP_LOC2.clear();
	//cout<<"Germline SNP simulation complete"<<endl;
}


void simulate::Indels(parameters & params)
{
	
	float indel_rate=7.2;          //7.2base per indel
	float het_rate=3.0/5;
	float very_short_rate=7.0/10;
	float short_rate=2.0/10;
	float large_rate=1-very_short_rate-short_rate;
	float ins_rate=0.47;//?
	int Nh=5,m=0/*,flag_indel[24]*/;//?
	long int *INDEL_LOC,indel_count[24],total_indel=0,region_hot[24][Nh],indel_made=0,indel_made_length=0;
	int* INDEL_LEN;
	char *INDEL_flag;
	
     	
     	if((params.infile_tumor==1)&&(somatic_flag==1))
     	{
     		cout<<"Somatic Indel..."<<endl;
     		char somatic_indel_name[300];
     		sprintf(somatic_indel_name,"./Results/tumor%d_indel1.fa",tumor_flag);
     		params.INDEL1=somatic_indel_name;
     		sprintf(somatic_indel_name,"./Results/tumor%d_indel2.fa",tumor_flag);
     		params.INDEL2=somatic_indel_name;
     		sprintf(somatic_indel_name,"./Results/tumor%d_indel_message1.fa",tumor_flag);
     		INDEL_LOC1.open(somatic_indel_name,ios::out);
     		sprintf(somatic_indel_name,"./Results/tumor%d_indel_message2.fa",tumor_flag);
     		INDEL_LOC2.open(somatic_indel_name,ios::out);
     		//cout<<params.SNP1.c_str()<<endl<<params.SNP2.c_str()<<endl;
		
     	}
     	else
     	{
     		cout<<"Germline Indel..."<<endl;
     		params.INDEL1="./Results/germline_indel1.fa";
		params.INDEL2="./Results/germline_indel2.fa";
		//for(m=0;m<24;m++){flag_indel[m]=0;}
		INDEL_LOC1.open("./Results/indel_messaeg_1.txt",ios::out);
		INDEL_LOC2.open("./Results/indel_messaeg_2.txt",ios::out);
     	}
     	if (!INDEL_LOC1.is_open())
     	{
		cout<<"Cant't open file for INDEL message1 writing\n";exit(-1);
	}
	INDEL1.open(params.INDEL1.c_str(),ios::out);
	if (!INDEL1.is_open())
	{
		cout<<"Cant't open file for INDEL1 writing\n";exit(-1);
	}
		
	if (!INDEL_LOC2.is_open())
	{
		cout<<"Cant't open file for INDEL message2 writing\n";exit(-1);
	}
	INDEL2.open(params.INDEL2.c_str(),ios::out);
	if (!INDEL2.is_open())
	{
		cout<<"Cant't open file for INDEL2 writing\n";exit(-1);
	}
	INDEL_IN1.open(params.SNP1.c_str(),ios::in);
	if (!INDEL_IN1.is_open())
	{
		cout<<"Cant't open SNP1 for INDEL1 reading\n";exit(-1);
	}
	INDEL_IN2.open(params.SNP2.c_str(),ios::in);
	if (!INDEL_IN2.is_open())
	{
		cout<<"Cant't open SNP2 for INDEL2 reading\n";exit(-1);
	}
	INQ.open("./Datas/inq_life_micro_database.txt",ios::in);
	if (!INQ.is_open())
	{
		cout<<"Cant't open inq_life_micro_database.txt for indel\n";exit(-1);
	}
     	
	int inq_no=0;
	string indel_str,indel_str2;
	while(getline(INQ,indel_str))    //indel insertion database
	{
		istringstream iss(indel_str);
		iss >> indel_str2;
		iss >> INQS[inq_no];
		inq_no++;
	}

	//compute count and hot region for germline INDEL
	if(params.infile_s==0){long int *indel_genome_count=count_genome(INDEL_IN1);}
	for(int i=0;i<24;i++)
	{
		indel_count[i]=chr_count[i]/(indel_rate*1000);
		total_indel+=indel_count[i];
	}

	//region_hot[0][0]=chr_count[0]/40;
	//long int total=0;
	for(int i=0;i<24;i++)    //compute hot region
	{ 
		region_hot[i][0]=total+chr_count[i]/40;
		total+=chr_count[i];	
		if(chr_count[i]!=0)
		{
			for(int h=1;h<Nh;h++)
			{
				region_hot[i][h]=region_hot[i][h-1]+(chr_count[i]*7/80+rand()%(chr_count[i])/80);
			}
		}

	}
	INDEL_LOC=(long int*) calloc (0,sizeof(long int));
	INDEL_flag=(char*) calloc (0,sizeof(char));
	INDEL_LEN=(int*) calloc (1,sizeof(int));
	
	long int indel_num=0;   //indel number
	long int total_count=0;  //Base number
	m=0;
	int h=0;
	gsl_rng_env_setup();
	T = gsl_rng_default;//T is const gsl_rng_type *
	r = gsl_rng_alloc (T);//r point at T，r is gsl_rng *
	INDEL_LEN[0]=rand()%9+1;
	while(indel_made_length<=total_indel)
	{
		
		float temp_ran=0.55+gsl_rng_uniform(r)*0.15;
		float indel_rate_hot;
		while(((indel_num-indel_made_length)>=0)&&((indel_num-indel_made_length-INDEL_LEN[indel_made])<0)&&(m<24)/*&&(flag_indel[m]==0)*/)
		{
			if(indel_count[m]==0){total_count+=chr_count[m];m++;continue;}
			INDEL_LOC=(long int*) realloc (INDEL_LOC,(indel_made+1)*sizeof(long int));
			INDEL_flag=(char*) realloc (INDEL_flag,(indel_made+1)*sizeof(char));
			INDEL_LEN=(int*) realloc (INDEL_LEN,(indel_made+2)*sizeof(int));
			indel_rate_hot=indel_rate*(20-Nh)/10;  //not in  hot region
			int indel_lt=rand()%100;  //indel_lt is indel length type: 
			if(indel_lt>(100-very_short_rate*100))   //The probability of a very short indel is 70%. very shot=1~9bp.
			{
				INDEL_LEN[indel_made+1]=rand()%9+1;
			}
			else if(indel_lt>(100*(1-very_short_rate-short_rate)))//The probability of a short indel is 20%. short=10~40bp.
			{
					INDEL_LEN[indel_made+1]=rand()%31+10;
			}
			else//The probability of a large indel is 10%. large=40~10kbp.??????????????????????41~10?
			{
					INDEL_LEN[indel_made+1]=rand()%9960+40;
			}
			INDEL_LOC[indel_made]=total_count+(0.55+gsl_rng_uniform(r)*0.15)*INDEL_LEN[indel_made]*((int)(indel_rate_hot*1000*temp_ran));
			int INDEL_LEN_T=INDEL_LEN[indel_made];
			while(INDEL_LOC[indel_made]>(total_count+chr_count[m]-INDEL_LEN[indel_made]))
			{
				INDEL_LEN_T--;
				INDEL_LOC[indel_made]=total_count+(0.55+gsl_rng_uniform(r)*0.15)*INDEL_LEN_T*((int)(indel_rate_hot*1000*temp_ran));
			}
			INDEL_flag[indel_made]='n';
			total_count+=chr_count[m];
			indel_made_length+=INDEL_LEN[indel_made];
			indel_made++;
			indel_num+=indel_count[m];
			float step=abs((int)(indel_rate*1000*temp_ran));
			//cout<<"chrrr"<<m+1<<"  loc:"<<INDEL_LOC[indel_made-1]<<"  total_count:"<<total_count<<" step:"<<step<<" rate: "<<indel_rate<<endl;
			//flag_indel[m]==1;
			m++;
			h=0;
		}
		//judge if it is in hot region
		INDEL_LOC=(long int*) realloc (INDEL_LOC,(indel_made+1)*sizeof(long int));
		INDEL_flag=(char*) realloc (INDEL_flag,(indel_made+1)*sizeof(char));
		INDEL_LEN=(int*) realloc (INDEL_LEN,(indel_made+2)*sizeof(int));
		if(h<=Nh)
		{
			long int temp_length;
			//if((temp_length>=(-indel_rate*1000))&&(temp_length<=(chr_count[m-1]/20-indel_rate*1000))&&(INDEL_flag[snp_made-1]=='n'))
			if((INDEL_flag[indel_made-1]=='n'))
				{temp_length=INDEL_LOC[indel_made-1]-region_hot[m-1][h];}
			else
				{temp_length=INDEL_LOC[indel_made-1]-region_hot[m-1][h-1];}
			if((temp_length>=(-indel_rate*1000))&&(temp_length<=(chr_count[m-1]/20-indel_rate*1000)))
			{
				if(INDEL_flag[indel_made-1]=='n'){h++;//cout<<"h "<<h<<endl;
				}//
				indel_rate_hot=indel_rate*Nh/10;
				INDEL_flag[indel_made]='h';
			}
			else{	indel_rate_hot=indel_rate*(20-Nh)/10;INDEL_flag[indel_made]='n';}

		}
		else{	indel_rate_hot=indel_rate*(20-Nh)/10;INDEL_flag[indel_made]='n';}
		int indel_lt=rand()%100;  //indel_lt is indel length type: 
		if(indel_lt>(100-very_short_rate*100))   //The probability of a very short indel is 70%. very shot=1~9bp.
		{
			INDEL_LEN[indel_made+1]=rand()%9+1;
		}
		else if(indel_lt>(100*(1-very_short_rate-short_rate)))//The probability of a short indel is 20%. short=10~40bp.
		{
			INDEL_LEN[indel_made+1]=rand()%31+10;
		}
		else//The probability of a large indel is 10%. large=40~10kbp.??????????????????????41~10?
		{
			INDEL_LEN[indel_made+1]=rand()%9960+40;
		}
		INDEL_LOC[indel_made]=INDEL_LOC[indel_made-1]+(0.55+gsl_rng_uniform(r)*0.15)*INDEL_LEN[indel_made]*((int)(indel_rate_hot*1000*temp_ran));
		//INDEL_LOC[indel_made]=total_count+INDEL_LEN[indel_made]*((int)(indel_rate_hot*1000*temp_ran));
		int INDEL_LEN_T=INDEL_LEN[indel_made];
		while(INDEL_LOC[indel_made]>(total_count-INDEL_LEN[indel_made]))
		{
			INDEL_LEN_T--;
			INDEL_LOC[indel_made]=INDEL_LOC[indel_made-1]+(0.55+gsl_rng_uniform(r)*0.15)*INDEL_LEN_T*((int)(indel_rate_hot*1000*temp_ran));
		}
		indel_made_length+=INDEL_LEN[indel_made];
		//cout<<"indel_rate_hot "<<indel_rate_hot<<"loc:"<<INDEL_LOC[indel_made]<<"region_hot[m-1][h-1] "<<region_hot[m-1][h-1]<<endl;	
		indel_made++;
	}
	/*cout<<"indel_made is "<<indel_made<<endl;
	cout<<"indel_made_length is "<<indel_made_length<<endl;
	cout<<"total_indel is "<<total_indel<<endl;
	cout<<"total_count is "<<total<<endl;
	for(int test=0;test<indel_made;test++)
	cout<<INDEL_LEN[test]<<endl;*/
	
	//Germline indel variation

	long int kk=0;
	long int i;
	for(i=1;i<indel_made; i++)//Removing duplicates indels 
	{
		if(INDEL_LOC[i]!=INDEL_LOC[kk])
			{
				kk++;
				INDEL_LOC[kk]=INDEL_LOC[i];
				//cout<<INDEL_LOC[kk]<<endl;
			}
	}
	//indelmap1=new long int[total+indel_made_length];
	//indelmap2=new long int[total+indel_made_length];
	char c,c2,name[200];
	i=0;
	//float Het_rate=params.infile_hes_rate;
	INDEL_IN1.clear();
	INDEL_IN1.seekg(ios::beg);
	INDEL_LOC1<<"chr"<<"\t"<<"loc\t"<<"ref"<<"\talter"<<"\n";
	INDEL_IN2.clear();
	INDEL_IN2.seekg(ios::beg);
	INDEL_LOC2<<"chr"<<"\t"<<"loc"<<"\t"<<"ref"<<"\talter"<<"\n";
	indel_no1=0;indel_no2=0;indel_var_no1=0;indel_var_no2=0;indel_no11=0;indel_no22=0;
	int flag=0; //assure the first time not insert '\n';
	//cout<<"begin..."<<endl;
	int indel_in1_flag=1,indel_in2_flag=1;
	for(long int pos=0;;pos++)//input is SNP file
	{      
		if(indel_in1_flag==1){if((c=INDEL_IN1.get())!=EOF){} else{break;}}
		if(indel_in2_flag==1){if((c2=INDEL_IN2.get())!=EOF){} else{break;}}
		//if(pos<100)cout<<c<<c2<<endl;			
		if((c=='>')||(c=='\n'))
		{
			if(c=='>')
			{
				if(flag==1)
				{
					INDEL1<<"\n";
					INDEL_IN1.getline(name,100);
					INDEL1<<">"<<name;
					//cout<<name<<"  "<<pos<<endl;
				}
				else
				{
					INDEL_IN1.getline(name,100);
					INDEL1<<">"<<name<<"\n";
					//cout<<name<<"   "<<pos<<endl;
				}
				indel_no11+=50-(pos+indel_no1+indel_no11)%50;
			}
			
			indel_in1_flag=1;
			indel_in2_flag=0;
			pos--;	continue;
		}
		if((c2=='>')||(c2=='\n'))
		{
			if(c2=='>')
			{
				if(flag==1)
				{
					INDEL2<<"\n"; 
					INDEL_IN2.getline(name,100);
					INDEL2<<">"<<name;
					//cout<<name<<"  "<<pos<<endl;
				}
				else
				{
					INDEL_IN2.getline(name,100);
					INDEL2<<">"<<name<<"\n";
					//cout<<name<<"   "<<pos<<endl;
				}
				indel_no22+=50-(pos+indel_no2+indel_no22)%50;
			}
			indel_in2_flag=1;
			indel_in1_flag=0;
			pos--;	continue;
		}
		indel_in1_flag=1;indel_in2_flag=1;
		if(flag==1)
		{ 
			if((pos+indel_no1+indel_no11)%50==0){INDEL1<<"\n";}  
			if((pos+indel_no2+indel_no22)%50==0){INDEL2<<"\n";}
		}
		flag=1;
		
		if((pos==(INDEL_LOC[i]-1))&&(i<indel_made))	//INDEL_LOC is the location for germline indel
		{
			i++;
			int type=rand()%100;
			if(type>(100-100*ins_rate))  //insertion
			{
				//cout<<"ins..."<<pos<<endl;
				//indel_ins(INDEL_LEN[i],het_rate,pos,name);
					
			}
			else    //deletion
			{
				//INDEL_LEN[i]=500000;
				//cout<<"del..."<<INDEL_LEN[i]<<endl;
				indel_del(INDEL_LEN[i],het_rate,pos,name);
				pos+=INDEL_LEN[i];
			}
		}
				INDEL1.put(c);
				INDEL2.put(c2);
				//indelmap1[pos+indel_var_no1]=pos+1;
				//indelmap2[pos+indel_var_no2]=pos+1;
				//cout<<pos+indel_var_no1<<endl;

	}
	INDEL1.put('\n');
	INDEL2.put('\n');
	/*ofstream INDELMAP1,INDELMAP2;
	INDELMAP1.open("./Results/indel_map1.txt",ios::out);
	if (!INDELMAP1.is_open())
    	{
		cout<<"Cant't open map1 for indel writing\n";exit(-1);
     	}
     	INDELMAP2.open("./Results/indel_map2.txt",ios::out);
	if (!INDELMAP2.is_open())
    	{
		cout<<"Cant't open map2 for indel writing\n";exit(-1);
     	}*/
     	//cout<<(total+indel_made_length)<<endl;
	/*for(long int map_s=0;map_s<(total+indel_made_length);map_s++){
		if((map_s!=0)&&(indelmap1[map_s]==0)){continue;}
		INDELMAP1<<indelmap1[map_s]<<endl;
		//cout<<indelmap1[map_s]<<endl;
	}
	for(long int map_s=0;map_s<(total+indel_made_length);map_s++){
		if((map_s!=0)&&(indelmap2[map_s]==0)){continue;}
		INDELMAP2<<indelmap2[map_s]<<endl;
	}*/
	/*INDELMAP1.close();
	INDELMAP1.clear();
	INDELMAP2.close();
	INDELMAP2.clear();*/
	INDEL_LOC=(long int *) realloc (INDEL_LOC, 0*(sizeof (long int)));
	INDEL_flag=(char *) realloc (INDEL_flag, 0*(sizeof (char)));
	INDEL_LEN=(int *) realloc (INDEL_LOC, 0*(sizeof (int)));
	INDEL1.close();
	INDEL2.close();
	INDEL_LOC1.close();
	INDEL_LOC2.close();
	INDEL_IN1.close();
	INDEL_IN2.close();
	INDEL1.clear();
	INDEL2.clear();
	INDEL_LOC1.clear();
	INDEL_LOC2.clear();
	INDEL_IN1.clear();
	INDEL_IN2.clear();
}
void simulate::indel_ins(int indel_lt,float het_rate,long int pos,string name)
{
	pos=pos+1;
	ios::pos_type position_i1,position_i2;
	position_i1=INDEL_IN1.tellg();
	position_i2=INDEL_IN2.tellg();
	int indel_hoht=rand()%100;
	char name_indel_ins[100];
	if(indel_hoht>(100*het_rate))//homegeneous  germline indel insertion
	{
		for(int imap=0;imap<=indel_lt;imap++)
		{
			//indelmap1[pos+indel_var_no1+imap-1]=pos;
			//indelmap2[pos+indel_var_no2+imap-1]=pos;
		}
		INDEL_LOC1<<name<<"\t"<<pos<<"\t-\t";
		INDEL_LOC2<<name<<"\t"<<pos<<"\t-\t";
		int ins_type=rand()%3;
		//cout<<"ins_type "<<ins_type<<endl;
		if(ins_type==0) //random germline indel insertion
		{
			for(int sub=0;sub<indel_lt;sub++)
			{
				int ins_base=rand()%4;
				if(ins_base==0){INDEL1<<"A";INDEL2<<"A";INDEL_LOC1<<"A";INDEL_LOC2<<"A";}
				else if(ins_base==1){INDEL1<<"T";INDEL2<<"T";INDEL_LOC1<<"T";INDEL_LOC2<<"T";}
				else if(ins_base==2){INDEL1<<"G";INDEL2<<"G";INDEL_LOC1<<"G";INDEL_LOC2<<"G";}
				else{INDEL1<<"C";INDEL2<<"C";INDEL_LOC1<<"C";INDEL_LOC2<<"C";}
				//if((pos+indel_no1+sub)%50==0){INDEL1<<"\n";}pos+indel_no1+indel_no11
				//if((pos+indel_no2+sub)%50==0){INDEL2<<"\n";}
				if((pos+indel_no1+indel_no11+sub)%50==0){INDEL1<<"\n";}
				if((pos+indel_no2+indel_no22+sub)%50==0){INDEL2<<"\n";}
			}
		}
		else if(ins_type==1) //indel internal expansion
		{
			long int ins_move=rand()%1000+1;
			INDEL_IN1.seekg(ins_move,ios::cur);
			INDEL_IN2.seekg(ins_move,ios::cur);
			for(int sub=0;sub<indel_lt;sub++)
			{
				char ins_c1;
				ins_c1=INDEL_IN1.get();
				if(ins_c1=='\n'){sub--;continue;}
				if((ins_c1=='N')||(ins_c1=='n'))
				{int ins_c1_base=rand()%4;if(ins_c1_base==0){ins_c1='A';} else if(ins_c1_base==1){ins_c1='T';} else if(ins_c1_base==2){ins_c1='G';} else{ins_c1='C';}}
				if(ins_c1=='>'){INDEL_IN1.getline(name_indel_ins,100);sub--;continue;}
				INDEL1<<ins_c1;INDEL_LOC1<<ins_c1;
				if((pos+indel_no1+indel_no11+sub)%50==0){INDEL1<<"\n";}	    
			}
			for(int sub=0;sub<indel_lt;sub++)
			{
				char ins_c2;
				ins_c2=INDEL_IN2.get();
				if(ins_c2=='\n'){sub--;continue;}
				if((ins_c2=='N')||(ins_c2=='n'))
				{int ins_c2_base=rand()%4;if(ins_c2_base==0){ins_c2='A';} else if(ins_c2_base==1){ins_c2='T';} else if(ins_c2_base==2){ins_c2='G';} else{ins_c2='C';}}
				if(ins_c2=='>'){INDEL_IN2.getline(name_indel_ins,100);sub--;continue;}
				INDEL2<<ins_c2;INDEL_LOC2<<ins_c2;
				if((pos+indel_no2+indel_no22+sub)%50==0){INDEL2<<"\n";}
			}
		}
		else ////indel external insertion from micro database
		{
			int inq=rand()%217;
			if(indel_lt<=INQS[inq].length())
			{
				//cout<<indel_no1<<endl;
				string temp_inq=INQS[inq].substr(0,indel_lt);
				for (int sub=0; sub<temp_inq.length(); sub++)  
				{  
				    if ((temp_inq[sub] == 'U')||(temp_inq[sub] == 'u')){temp_inq[sub] = 'T';}
				    INDEL1<<temp_inq[sub];INDEL2<<temp_inq[sub];INDEL_LOC1<<temp_inq[sub];INDEL_LOC2<<temp_inq[sub];
				    if((pos+indel_no1+indel_no11+sub)%50==0){INDEL1<<"\n";}
				    if((pos+indel_no2+indel_no22+sub)%50==0){INDEL2<<"\n";}
				} 
			}
			else
			{
				for(int sub=0;sub<indel_lt;sub++)
				{
					int ins_base=rand()%4;
					if(ins_base==0){INDEL1<<"A";INDEL2<<"A";INDEL_LOC1<<"A";INDEL_LOC2<<"A";}
					else if(ins_base==1){INDEL1<<"T";INDEL2<<"T";INDEL_LOC1<<"T";INDEL_LOC2<<"T";}
					else if(ins_base==2){INDEL1<<"G";INDEL2<<"G";INDEL_LOC1<<"G";INDEL_LOC2<<"G";}
					else{INDEL1<<"C";INDEL2<<"C";INDEL_LOC1<<"C";INDEL_LOC2<<"C";}
					if((pos+indel_no1+indel_no11+sub)%50==0){INDEL1<<"\n";}
				    	if((pos+indel_no2+indel_no22+sub)%50==0){INDEL2<<"\n";}

				}
			}


		}
		INDEL_LOC1<<"\n";
		INDEL_LOC2<<"\n";
		indel_no1+=indel_lt;
		indel_no2+=indel_lt;
		indel_var_no1+=indel_lt;
		indel_var_no2+=indel_lt;
	}
	else //heterozygous  germline indel insertion
	{
		int indel_allel_choose=rand()%2;
		if(indel_allel_choose==0)      //diploid 1
		{
			for(int imap=0;imap<=indel_lt;imap++)
			{
				//indelmap1[pos+indel_var_no1+imap-1]=pos;
			}
			INDEL_LOC1<<name<<"\t"<<pos<<"\t-\t";
			int ins_type=rand()%3;
			//cout<<"ins_type het "<<ins_type<<endl;
			if(ins_type==0) //random germline indel insertion
			{
				for(int sub=0;sub<indel_lt;sub++)
				{
					int ins_base=rand()%4;
					if(ins_base==0){INDEL1<<"A";INDEL_LOC1<<"A";}
					else if(ins_base==1){INDEL1<<"T";INDEL_LOC1<<"T";}
					else if(ins_base==2){INDEL1<<"G";INDEL_LOC1<<"G";}
					else{INDEL1<<"C";INDEL_LOC1<<"C";}
					if((pos+indel_no1+indel_no11+sub)%50==0){INDEL1<<"\n";}

				}

			}
			else if(ins_type==1) //indel internal expansion
			{
				long int ins_move=rand()%1000+1;
				INDEL_IN1.seekg(ins_move,ios::cur);
				for(int sub=0;sub<indel_lt;sub++)
				{
					char ins_c1;
					ins_c1=INDEL_IN1.get();//ins_c2=INDEL_IN2.get();
					if(ins_c1=='\n'){sub--;continue;}
					if((ins_c1=='N')||(ins_c1=='n'))
					{int ins_c1_base=rand()%4;if(ins_c1_base==0){ins_c1='A';} else if(ins_c1_base==1){ins_c1='T';} else if(ins_c1_base==2){ins_c1='G';} else{ins_c1='C';}}
					if(ins_c1=='>'){INDEL_IN1.getline(name_indel_ins,100);sub--;continue;}
					INDEL1<<ins_c1;INDEL_LOC1<<ins_c1;
					if((pos+indel_no1+indel_no11+sub)%50==0){INDEL1<<"\n";}
				}
			}
			else ////indel external insertion from database
			{
				int inq=rand()%217;
				if(indel_lt<=INQS[inq].length())
				{
					string temp_inq=INQS[inq].substr(0,indel_lt);
					for (int sub=0; sub<temp_inq.length(); sub++)  
					{  
					    if ((temp_inq[sub] == 'U')||(temp_inq[sub] == 'u')){temp_inq[sub] = 'T';}
					    INDEL1<<temp_inq[sub];INDEL_LOC1<<temp_inq[sub];
					    if((pos+indel_no1+indel_no11+sub)%50==0){INDEL1<<"\n";}
					}
				}
				else
				{
					for(int sub=0;sub<indel_lt;sub++)
					{
						int ins_base=rand()%4;
						if(ins_base==0){INDEL1<<"A";INDEL_LOC1<<"A";}
						else if(ins_base==1){INDEL1<<"T";INDEL_LOC1<<"T";}
						else if(ins_base==2){INDEL1<<"G";INDEL_LOC1<<"G";}
						else{INDEL1<<"C";INDEL_LOC1<<"C";}
						if((pos+indel_no1+indel_no11+sub)%50==0){INDEL1<<"\n";}
					}	
				}
			}
			INDEL_LOC1<<"\n";
			indel_no1+=indel_lt;
			indel_var_no1+=indel_lt;
		}
		else      //diploid 2
		{
			for(int imap=0;imap<=indel_lt;imap++)
			{
				//indelmap2[pos+indel_var_no2+imap-1]=pos;
			}
			INDEL_LOC2<<name<<"\t"<<pos<<"\t-\t";
			int ins_type=rand()%3;
			if(ins_type==0) //random germline indel insertion
			{
				for(int sub=0;sub<indel_lt;sub++)
				{
					int ins_base=rand()%4;
					if(ins_base==0){INDEL2<<"A";INDEL_LOC2<<"A";}
					else if(ins_base==1){INDEL2<<"T";INDEL_LOC2<<"T";}
					else if(ins_base==2){INDEL2<<"G";INDEL_LOC2<<"G";}
					else{INDEL2<<"C";INDEL_LOC2<<"C";}
					if((pos+indel_no2+indel_no22+sub)%50==0){INDEL2<<"\n";}

				}

			}
			else if(ins_type==1) //indel internal expansion
			{
				long int ins_move=rand()%1000+1;
				INDEL_IN2.seekg(ins_move,ios::cur);
				for(int sub=0;sub<indel_lt;sub++)
				{
					char ins_c2;
					ins_c2=INDEL_IN2.get();
					if(ins_c2=='\n'){sub--;continue;}
					if((ins_c2=='N')||(ins_c2=='n'))
					{int ins_c2_base=rand()%4;if(ins_c2_base==0){ins_c2='A';} else if(ins_c2_base==1){ins_c2='T';} else if(ins_c2_base==2){ins_c2='G';} else{ins_c2='C';}}
					if(ins_c2=='>'){INDEL_IN2.getline(name_indel_ins,100);sub--;continue;}
					INDEL2<<ins_c2;INDEL_LOC2<<ins_c2;
					if((pos+indel_no2+indel_no22+sub)%50==0){INDEL2<<"\n";}
				}
			}
			else ////indel external insertion from database
			{
				int inq=rand()%217;
				if(indel_lt<=INQS[inq].length())
				{
					string temp_inq=INQS[inq].substr(0,indel_lt);
					//INDEL2<<temp_inq;
					//INDEL_LOC2<<temp_inq;
					for (int sub=0; sub<temp_inq.length(); sub++)  
					{  
					    if ((temp_inq[sub] == 'U')||(temp_inq[sub] == 'u')){temp_inq[sub] = 'T';}
					    INDEL2<<temp_inq[sub];INDEL_LOC2<<temp_inq[sub];
					    if((pos+indel_no2+indel_no22+sub)%50==0){INDEL2<<"\n";}
					}
				}
				else
				{
					for(int sub=0;sub<indel_lt;sub++)
					{
						int ins_base=rand()%4;
						if(ins_base==0){INDEL2<<"A";INDEL_LOC2<<"A";}
						else if(ins_base==1){INDEL2<<"T";INDEL_LOC2<<"T";}
						else if(ins_base==2){INDEL2<<"G";INDEL_LOC2<<"G";}
						else{INDEL2<<"C";INDEL_LOC2<<"C";}
						if((pos+indel_no2+indel_no22+sub)%50==0){INDEL2<<"\n";}
					}
				}
			}
			INDEL_LOC2<<"\n";
			indel_no2+=indel_lt;
			indel_var_no2+=indel_lt;
		}


	}
	INDEL_IN1.seekg(position_i1);
	INDEL_IN2.seekg(position_i2);
}
void simulate::indel_del(int indel_lt,float het_rate,long int pos,string name)
{	
	pos=pos+1;
	int indel_hoht=rand()%100;
	char name_indel_del[100];
	if(indel_hoht>(100*het_rate))//homegeneous  germline indel deletion
	{
		INDEL_LOC1<<name<<"\t"<<pos<<"\t";
		INDEL_LOC2<<name<<"\t"<<pos<<"\t";
		for(int sub=0;sub<indel_lt;sub++)
		{
			char del_c1=INDEL_IN1.get();
			if(del_c1=='\n'){sub--;continue;}
			if(del_c1=='>'){indel_no11+=50-(pos-1+indel_no1+indel_no11)%50;INDEL_IN1.getline(name_indel_del,100);INDEL1<<"\n>"<<name_indel_del<<"\n";sub--;continue;}
			INDEL_LOC1<<del_c1;
		}
		for(int sub=0;sub<indel_lt;sub++)
		{
			char del_c2=INDEL_IN2.get();
			if(del_c2=='\n'){sub--;continue;}
			if(del_c2=='>'){indel_no22+=50-(pos-1+indel_no2+indel_no22)%50;INDEL_IN2.getline(name_indel_del,100);INDEL2<<"\n>"<<name_indel_del<<"\n";sub--;continue;}
			INDEL_LOC2<<del_c2;
		}
		INDEL_LOC1<<"\t-\n";
		INDEL_LOC2<<"\t-\n";
		indel_no1-=indel_lt;
		indel_no2-=indel_lt;
		indel_var_no1-=indel_lt;
		indel_var_no2-=indel_lt;
	}
	else //heterozygous  germline indel deletion
	{
		int indel_allel_choose=rand()%2;
		if(indel_allel_choose==0)      //diploid 1
		{
			INDEL_LOC1<<name<<"\t"<<pos<<"\t";
			for(int sub=0;sub<indel_lt;sub++)
			{
				char del_c1=INDEL_IN1.get();
				char del_c2=INDEL_IN2.get();
				if(del_c1=='\n'){sub--;continue;}
				if(del_c1=='>'){indel_no11+=50-(pos-1+indel_no1+indel_no11)%50;INDEL_IN1.getline(name_indel_del,100);INDEL1<<"\n>"<<name_indel_del<<"\n";sub--;continue;}
				INDEL_LOC1<<del_c1;
				INDEL2.put(del_c2);
				if((pos+indel_no2+indel_no22+sub)%50==0){INDEL2<<"\n";}
			}
			INDEL_LOC1<<"\t-\n";
			indel_no1-=indel_lt;
			indel_var_no1-=indel_lt;
			
		}
		else      //diploid 2
		{
			INDEL_LOC2<<name<<"\t"<<pos<<"\t";
			for(int sub=0;sub<indel_lt;sub++)
			{
				char del_c1=INDEL_IN1.get();
				char del_c2=INDEL_IN2.get();
				if(del_c2=='\n'){sub--;continue;}
				if(del_c2=='>'){indel_no22+=50-(pos-1+indel_no2+indel_no22)%50;INDEL_IN2.getline(name_indel_del,100);INDEL2<<"\n>"<<name_indel_del<<"\n";sub--;continue;}
				INDEL1.put(del_c1);
				INDEL_LOC2<<del_c2;
				if((pos+indel_no1+indel_no11+sub)%50==0){INDEL1<<"\n";}

			}
			INDEL_LOC2<<"\t-\n";
			indel_no2-=indel_lt;
			indel_var_no2-=indel_lt;
		}
	}


}

void simulate::tanddup(parameters & params)
{
	//cout<<"Germline Tandem duplication..."<<endl;
	ofstream TAND_LOC1,TAND1,TAND2,TAND_LOC2;
	ifstream TAND_IN1,TAND_IN2;
	
	if((params.infile_tumor==1)&&(somatic_flag==1))
     	{
     		cout<<"Somatic Tandem duplication..."<<endl;
     		//params.TAND1="./Results/somatic_tand1.fa";
		//params.TAND2="./Results/somatic_tand2.fa";
		char somatic_tand_name[300];
     		sprintf(somatic_tand_name,"./Results/tumor%d_tand1.fa",tumor_flag);
     		params.TAND1=somatic_tand_name;
     		sprintf(somatic_tand_name,"./Results/tumor%d_tand2.fa",tumor_flag);
     		params.TAND2=somatic_tand_name;
		sprintf(somatic_tand_name,"./Results/tumor%d_tand_message1.fa",tumor_flag);
     		TAND_LOC1.open(somatic_tand_name,ios::out);
     		sprintf(somatic_tand_name,"./Results/tumor%d_tand_message2.fa",tumor_flag);
     		TAND_LOC2.open(somatic_tand_name,ios::out);
     	}
     	else
     	{
     		cout<<"Germline Tandem duplication..."<<endl;
     		params.TAND1="./Results/germline_tand1.fa";
		params.TAND2="./Results/germline_tand2.fa";
     		
		//for(m=0;m<24;m++){flag_indel[m]=0;}
		TAND_LOC1.open("./Results/tand_messaeg_1.txt",ios::out);
		TAND_LOC2.open("./Results/tand_messaeg_2.txt",ios::out);
     	}
	
	
	
	if (!TAND_LOC1.is_open())
    	{
		cout<<"Cant't open file for TAND message1 writing\n";exit(-1);
     	}
	TAND1.open(params.TAND1.c_str(),ios::out);
	if (!TAND1.is_open())
    	{
		cout<<"Cant't open file for TAND1 writing\n";exit(-1);
     	}
     	
	if (!TAND_LOC2.is_open())
    	{
		cout<<"Cant't open file for TAND message2 writing\n";exit(-1);
     	}
     	TAND2.open(params.TAND2.c_str(),ios::out);
	if (!TAND2.is_open())
    	{
		cout<<"Cant't open file for TAND2 writing\n";exit(-1);
     	}
	TAND_IN1.open(params.INDEL1.c_str(),ios::in);
	if (!TAND_IN1.is_open())
    	{
		cout<<"Cant't open INDEL1 for TAND1 reading\n";exit(-1);
     	}
     	TAND_IN2.open(params.INDEL2.c_str(),ios::in);
	if (!TAND_IN2.is_open())
    	{
		cout<<"Cant't open INDEL2 for TAND2 reading\n";exit(-1);
     	}
     	//long int* TAND_LOC=new long int[24];
     	//------------1.first  tand: no=infile_td_no1(user define) length=100~200(Gaussion distribution) repeat times:1~10(random number)-------------------------
     	//------------2.second tand: no=infile_td_no2(user define)  sequence:(CTG.CAG)n   repeat times:n(17~175unit)----------------------------------------------
     	gsl_rng_env_setup();
	T = gsl_rng_default;//T is const gsl_rng_type *
	r = gsl_rng_alloc (T);//r point at T，r is gsl_rng *
     	
     	int td_mu=150,td_sigma=50;
     	int *td_length1=new int[params.infile_td_no1];
     	for(int td=0;td<params.infile_td_no1;td++)
     	{
     		td_length1[td]=gsl_ran_gaussian(r,td_sigma)+td_mu;
     		if(td_length1[td]>=200||td_length1[td]<=100){td--;continue;}
     		//cout<<td_length1[td]<<endl;
     		
     	}
     	int td_no=params.infile_td_no1+params.infile_td_no2;
     	long int *TAND_LOC=new long int[td_no];
     	//cout<<"td_no is:"<<td_no<<endl;
     	int td_made=0;
     	long int total_length1,total_length2;
     	long int *total_tand1=count_genome(TAND_IN1);
     	for(int td_chr=0;td_chr<24;td_chr++){total_length1+=chr_count[td_chr];}
     	long int *total_tand2=count_genome(TAND_IN1);
     	for(int td_chr=0;td_chr<24;td_chr++){total_length2+=chr_count[td_chr];}
     	total=total_length1<total_length2?total_length1:total_length2;
     	int td_mean=total/td_no;
     	float up=0.75,low=0.95;
     	TAND_LOC[0]=td_mean*(low+gsl_rng_uniform(r)*(up-low));
     	//cout<<"TAND_LOC[0]:"<<TAND_LOC[0]<<endl;
     	while((td_made) < (td_no-1)){
     		td_made++;
     		TAND_LOC[td_made]=TAND_LOC[td_made-1]+td_mean*(low+gsl_rng_uniform(r)*(up-low));
     		//cout<<"TAND_LOC: "<<TAND_LOC[td_made]<<endl;
     	}
     	//tandem duplication variation
     	char c,c2;
     	char name[200];
     	tand_no1=tand_no2=tand_var_no1=tand_var_no2=0;
     	int flag=0;
     	int i=0;
     	TAND_IN1.clear();
	TAND_IN1.seekg(ios::beg);
	TAND_LOC1<<"chr"<<"\t"<<"loc\t"<<"len(-)"<<"\trep"<<"\n";
	TAND_IN2.clear();
	TAND_IN2.seekg(ios::beg);
	TAND_LOC2<<"chr"<<"\t"<<"loc"<<"\t"<<"len(-)"<<"\trep"<<"\n";
	int td_var1=0,td_var2=0;
	ios::pos_type position_i1,position_i2;
	//cout<<"1 begin"<<endl;
     	for(long int pos=0;((c=TAND_IN1.get())!=EOF);pos++)//input is INDEL file output is TAND file
	{               			
		if(c=='>')
		{
			if(flag==1)
			{
				TAND1<<"\n"; 
				TAND_IN1.getline(name,100);
				TAND1<<">"<<name;
				//cout<<name<<" "<<pos<<endl;
			}
			else
			{
				TAND_IN1.getline(name,100);
				TAND1<<">"<<name<<"\n";
				//cout<<name<<"  "<<pos<<endl;
			}
			tand_no1+=50-(pos+tand_no1)%50;pos--;	continue;
		}
		if(c=='\n')
		{
			pos--;	continue;
		}
		if(flag==1)
		{ 
			if((pos+tand_no1)%50==0){TAND1<<"\n";}  
		}
		flag=1;
		
		if((pos==(TAND_LOC[i]-1))&&(i<td_no))	//TAND_LOC is the location for germline tandem duplication INDEL
		{
			i++;
			int td_type=rand()%2;
			if(td_var1==params.infile_td_no1){td_type=1;}
			if(td_var2==params.infile_td_no2){td_type=0;}
			position_i1=TAND_IN1.tellg();
			if(td_type==0) //---------------kind 1 tand
			{
				int td_rep1=rand()%10+1;
				TAND_LOC1<<name<<"\t"<<(pos+1)<<"\t"<<td_length1[td_var1]<<"\t"<<td_rep1<<endl;
				for(int sub_td=0;sub_td<td_rep1;sub_td++)
				{
					for(int sub_lt=0;sub_lt<td_length1[td_var1];sub_lt++)
					{
						char td_c1=TAND_IN1.get();
						if(td_c1=='\n'){sub_lt--;continue;}
						if(td_c1=='>'){TAND_IN1.getline(name,100);sub_lt--;continue;}
						TAND1<<td_c1;
						if((pos+tand_no1+sub_lt+1)%50==0){TAND1<<"\n";}
					}
					TAND_IN1.seekg(position_i1);
					tand_no1+=td_length1[td_var1];
				}
				td_var1++;
			}
			else         //---------------kind 2 tand
			{
				int td_rep2=rand()%158+17;             //td_rep2=17~175
				TAND_LOC1<<name<<"\t"<<(pos+1)<<"\t"<<"-"<<"\t"<<td_rep2<<endl;
				for(int sub_td=0;sub_td<td_rep2;sub_td++)
				{
					TAND1<<"C";tand_no1++;
					if((pos+tand_no1)%50==0){TAND1<<"\n";}
					TAND1<<"T";tand_no1++;
					if((pos+tand_no1)%50==0){TAND1<<"\n";}
					TAND1<<"G";tand_no1++;
					if((pos+tand_no1)%50==0){TAND1<<"\n";}
					TAND1<<"C";tand_no1++;
					if((pos+tand_no1)%50==0){TAND1<<"\n";}
					TAND1<<"A";tand_no1++;
					if((pos+tand_no1)%50==0){TAND1<<"\n";}
					TAND1<<"G";tand_no1++;
					if((pos+tand_no1)%50==0){TAND1<<"\n";}
				}
				td_var2++;
			}
		}
		TAND1.put(c);
	}
	i=flag=0;
	td_var1=td_var2=0;
	//cout<<"2 begin"<<endl;
	for(long int pos=0;((c2=TAND_IN2.get())!=EOF);pos++)//input is INDEL file output is TAND file
	{               			
		if(c2=='>')
		{
			if(flag==1)
			{
				TAND2<<"\n"; 
				TAND_IN2.getline(name,100);
				TAND2<<">"<<name;
				//cout<<name<<" "<<pos<<endl;
			}
			else
			{
				TAND_IN2.getline(name,100);
				TAND2<<">"<<name<<"\n";
				//cout<<name<<"  "<<pos<<endl;
			}
			//tand_no2=50-pos%50;pos--;	continue;
			tand_no2+=50-(pos+tand_no2)%50;pos--;	continue;
		}
		if(c2=='\n')
		{
			pos--;	continue;
		}
		if(flag==1)
		{ 
			if((pos+tand_no2)%50==0){TAND2<<"\n";}  
		}
		flag=1;
		
		if((pos==(TAND_LOC[i]-1))&&(i<td_no))	//TAND_LOC is the location for germline tandem duplication
		{
			i++;
			int td_type=rand()%2;
			if(td_var1==params.infile_td_no1){td_type=1;}
			if(td_var2==params.infile_td_no2){td_type=0;}
			position_i2=TAND_IN2.tellg();
			if(td_type==0) //---------------kind 1 tand
			{
				
				int td_rep1=rand()%10+1;
				TAND_LOC2<<name<<"\t"<<(pos+1)<<"\t"<<td_length1[td_var1]<<"\t"<<td_rep1<<endl;
				//cout<<td_var1<<" ---td_length1[td_var1]"<<td_length1[td_var1]<<endl;
				for(int sub_td=0;sub_td<td_rep1;sub_td++)
				{
					for(int sub_lt=0;sub_lt<td_length1[td_var1];sub_lt++)
					{
						char td_c2=TAND_IN2.get();
						if(td_c2=='\n'){sub_lt--;continue;}
						if(td_c2=='>'){TAND_IN2.getline(name,100);sub_lt--;continue;}
						TAND2<<td_c2;
						if((pos+tand_no2+sub_lt+1)%50==0){TAND2<<"\n";}
					}
					TAND_IN2.seekg(position_i2);
					tand_no2+=td_length1[td_var1];
				}
				td_var1++;			
			}
			else         //---------------kind 2 tand
			{
				int td_rep2=rand()%158+17;             //td_rep2=17~175
				TAND_LOC2<<name<<"\t"<<(pos+1)<<"\t"<<"-"<<"\t"<<td_rep2<<endl;
				for(int sub_td=0;sub_td<td_rep2;sub_td++)
				{
					TAND2<<"C";tand_no2++;
					if((pos+tand_no2)%50==0){TAND2<<"\n";}
					TAND2<<"T";tand_no2++;
					if((pos+tand_no2)%50==0){TAND2<<"\n";}
					TAND2<<"G";tand_no2++;
					if((pos+tand_no2)%50==0){TAND2<<"\n";}
					TAND2<<"C";tand_no2++;
					if((pos+tand_no2)%50==0){TAND2<<"\n";}
					TAND2<<"A";tand_no2++;
					if((pos+tand_no2)%50==0){TAND2<<"\n";}
					TAND2<<"G";tand_no2++;
					if((pos+tand_no2)%50==0){TAND2<<"\n";}
				}
				td_var2++;
			}
		}
		TAND2.put(c2);
	}
	TAND1.put('\n');
	TAND2.put('\n');
	TAND1.close();
	TAND2.close();
	TAND1.clear();
	TAND2.clear();
	TAND_LOC1.close();
	TAND_LOC2.close();
	TAND_IN1.close();
	TAND_IN2.close();
	TAND_LOC1.clear();
	TAND_LOC2.clear();
	TAND_IN1.clear();
	TAND_IN2.clear();
	
     	
}
void simulate::copy_no_variation(parameters & params)
{
					/* Transtion model*/
	//---------------------------------------------------------------------------------------------
	//Pa->b(d)=P((T(xk)=b)|(T(xk-1)=a))  Transtion model
	//a,b:		{0,1,2}  three states
	//xk:		marker a k-th position
	//k:		2~L(L is genome length)
	//T(xk):	the status of marker xk
	//Pa->b(d):	donote the transtion propobility from a to b,d is the distance from xk-1 to xk
	
	/*以三个状态产生概率，取最大的进行执行，如果有到1，2状态之间的转变，则发生了相对的变异

	N:0(initial state)
	P(0->0)=0.98
	P(0->1)=0.01
	P(0->2)=0.01

	A:1
	P(1->0)=0.01
	P(1->1)=0.98
	P(2->2)=0.01

	B:2
	P(2->0)=0.01
	P(2->1)=0.01
	P(2->2)=0.98*/
	//---------------------------------------------------------------------------------------------
	//cout<<"Germline CNV..."<<endl;
	if((params.infile_tumor==1)&&(somatic_flag==1))
     	{
     		cout<<"Somatic CNV..."<<endl;
     		//params.CNV1="./Results/somatic_cnv1.fa";
		//params.CNV2="./Results/somatic_cnv2.fa";
		//for(m=0;m<24;m++){flag_indel[m]=0;}
		char somatic_cnv_name[300];
     		sprintf(somatic_cnv_name,"./Results/tumor%d_cnv1.fa",tumor_flag);
     		params.CNV1=somatic_cnv_name;
     		sprintf(somatic_cnv_name,"./Results/tumor%d_cnv2.fa",tumor_flag);
     		params.CNV2=somatic_cnv_name;
		sprintf(somatic_cnv_name,"./Results/tumor%d_cnv_message1.fa",tumor_flag);
     		CNV_LOC1.open(somatic_cnv_name,ios::out);
     		sprintf(somatic_cnv_name,"./Results/tumor%d_cnv_message2.fa",tumor_flag);
     		CNV_LOC2.open(somatic_cnv_name,ios::out);
     	}
     	else
     	{
     		cout<<"Germline CNV..."<<endl;
     		params.CNV1="./Results/germline_cnv1.fa";
		params.CNV2="./Results/germline_cnv2.fa";
     		
		//for(m=0;m<24;m++){flag_indel[m]=0;}
		CNV_LOC1.open("./Results/cnv_messaeg_1.txt",ios::out);
		CNV_LOC2.open("./Results/cnv_messaeg_2.txt",ios::out);
     	}
	
	
	
	if (!CNV_LOC1.is_open())
    	{
		cout<<"Cant't open file for CNV message1 writing\n";exit(-1);
     	}
	CNV1.open(params.CNV1.c_str(),ios::out);
	if (!CNV1.is_open())
    	{
		cout<<"Cant't open file for CNV1 writing\n";exit(-1);
     	}
     	
	if (!CNV_LOC2.is_open())
    	{
		cout<<"Cant't open file for CNV message2 writing\n";exit(-1);
     	}
     	CNV2.open(params.CNV2.c_str(),ios::out);
	if (!CNV2.is_open())
    	{
		cout<<"Cant't open file for CNV2 writing\n";exit(-1);
     	}
	CNV_IN1.open(params.TAND1.c_str(),ios::in);
	if (!CNV_IN1.is_open())
    	{
		cout<<"Cant't open INDEL1 for CNV1 reading\n";exit(-1);
     	}
     	CNV_IN2.open(params.TAND2.c_str(),ios::in);
	if (!CNV_IN2.is_open())
    	{
		cout<<"Cant't open INDEL2 for CNV2 reading\n";exit(-1);
     	}
	//float Pnn=0.999993,Pna=0.000003,Pnd=0.000004,Pan=0.0001,Paa=0.9999,Pad=0,Pdn=0.0001,Pda=0,Pdd=0.9999;
	float Pnn=0.999993,Pna=0.000003,Pnd=0.000004,Pan=0.0001,Paa=0.9999,Pad=0,Pdn=0.0001,Pda=0,Pdd=0.9999;
	//float Pnn=0.98,Pna=0.01,Pnd=0.01,Pan=0.02,Paa=0.98,Pad=0,Pdn=0.02,Pda=0.0,Pdd=0.98;
	long int cnvlen1=0,cnvlen2=0;
	long int* cnvlens1=count_genome(CNV_IN1); for(int kk=0;kk<24;kk++){cnvlen1+=cnvlens1[kk];}
	long int* cnvlens2=count_genome(CNV_IN2); for(int kk=0;kk<24;kk++){cnvlen2+=cnvlens2[kk];}
	long int cnvlen=cnvlen1<cnvlen2?cnvlen1:cnvlen2;
	
	int state=0;
	long int cnv_made=0;
	long int*CNV_LOC;
	int* CNV_LEN;
	int* CNV_CP1;
	int* CNV_CP2;
	char* CNV_TYPE;
	CNV_LOC = (long int *)calloc(cnv_made, sizeof(long int));
   	CNV_LEN = (int *)calloc(cnv_made, sizeof(int));
   	CNV_CP1 = (int *)calloc(cnv_made, sizeof(int));
   	CNV_CP2 = (int *)calloc(cnv_made, sizeof(int));
   	CNV_TYPE = (char *)calloc(cnv_made, sizeof(char));
   	

	
	for(long int kk=0;kk<cnvlen;kk++)
	{
		kk++;
	   	if(state==0)//Norm
   		{
			float s_type=rand()%1000000/(double)1000001;
			//cout<<"s_type:"<<s_type<<endl;	
			//cout<<s_type<<endl;
	   		if(s_type>(1-Pnn))  //Norm-->Norm
	   		{
	   			//cout<<"Norm-->Norm"<<endl;
	   			state=0;continue;
	   		}
	   		else if(s_type>(Pnd))  //Norm-->Amp
	   		{
	   			/*cout<<"s_type:"<<s_type<<endl;	
	   			cout<<"Norm-->Amp"<<endl;
	   			cout<<"kk:"<<kk<<endl;
   				cout<<"cnv_made:"<<cnv_made<<endl;*/		
	   			state=1;
	   			cnv_made++;
	   			//cout<<"cnv_made:"<<cnv_made<<endl;
   				CNV_LOC = (long int *)realloc(CNV_LOC, (cnv_made) * sizeof(long int));
   				CNV_LEN = (int *)realloc(CNV_LEN, (cnv_made) * sizeof(int));
   				CNV_CP1 = (int *)realloc(CNV_CP1, (cnv_made) * sizeof(int));
   				CNV_CP2 = (int *)realloc(CNV_CP2, (cnv_made) * sizeof(int));
   				CNV_TYPE = (char *)realloc(CNV_TYPE, (cnv_made) * sizeof(char));
   				CNV_LOC[cnv_made-1]=kk;
   				CNV_LEN[cnv_made-1]=1;
   				CNV_CP1[cnv_made-1]=rand()%8+3;
   				CNV_CP2[cnv_made-1]=rand()%8+3;
   				CNV_TYPE[cnv_made-1]='a';
   				//cout<<"Norm-->Amp end"<<endl;
	   			continue;
	   		}
	   		else  //Norm-->Del
	   		{
	   			/*cout<<"s_type:"<<s_type<<endl;
	   			cout<<"Norm-->Del"<<endl;
	   			cout<<"kk:"<<kk<<endl;
   				cout<<"cnv_made:"<<cnv_made<<endl;*/	
	   			state=2;
	   			cnv_made++;
	   			//cout<<"cnv_made:"<<cnv_made<<endl;
   				CNV_LOC = (long int *)realloc(CNV_LOC, (cnv_made) * sizeof(long int));
   				CNV_LEN = (int *)realloc(CNV_LEN, (cnv_made) * sizeof(int));
   				CNV_CP1 = (int *)realloc(CNV_CP1, (cnv_made) * sizeof(int));
   				CNV_CP2 = (int *)realloc(CNV_CP2, (cnv_made) * sizeof(int));
   				CNV_TYPE = (char *)realloc(CNV_TYPE, (cnv_made) * sizeof(char));
   				CNV_LOC[cnv_made-1]=kk;
   				CNV_LEN[cnv_made-1]=1;
   				CNV_CP1[cnv_made-1]=rand()%2;
   				if((CNV_CP1[cnv_made-1])==1){CNV_CP2[cnv_made-1]=0;}
   				else{CNV_CP2[cnv_made-1]=rand()%2;}
				CNV_TYPE[cnv_made-1]='d';
				//cout<<"Norm-->Del end"<<endl;
	   			continue;
	   		}
		}
		if(state==1)//Amp
   		{		
   			float s_type=rand()%1000000/(double)1000001;
   			//cout<<s_type<<endl;
   			if(s_type>(1-Pan))  //Amp-->Norm
   			{
   				//cout<<"Amp-->Norm（Amp end）"<<endl;
   				state=0;continue;
   			}
   			else if(s_type>(Pad))  //Amp-->Amp
   			{
   				//cout<<"Amp-->Amp"<<endl;
   				CNV_LEN[cnv_made-1]++;
   				state=1;continue;
   			}
   			else  //Amp-->Del
   			{
   				/*cout<<"Amp-->Del（Amp end）"<<endl;
   				cout<<kk<<endl;
   				cout<<cnv_made<<endl;*/
   				cnv_made++;
   				CNV_LOC = (long int *)realloc(CNV_LOC, (cnv_made) * sizeof(long int));
   				CNV_LEN = (int *)realloc(CNV_LEN, (cnv_made) * sizeof(int));
   				CNV_CP1 = (int *)realloc(CNV_CP1, (cnv_made) * sizeof(int));
   				CNV_CP2 = (int *)realloc(CNV_CP2, (cnv_made) * sizeof(int));
   				CNV_TYPE = (char *)realloc(CNV_TYPE, (cnv_made) * sizeof(char));
   				CNV_LOC[cnv_made-1]=kk;
   				CNV_LEN[cnv_made-1]=1; 
   				CNV_CP1[cnv_made-1]=rand()%2;
   				if((CNV_CP1[cnv_made-1])==1){CNV_CP2[cnv_made-1]=0;}
   				else{CNV_CP2[cnv_made-1]=rand()%2;}
				CNV_TYPE[cnv_made-1]='d';
   				state=2;continue;
   			}
   		}
   		if(state==2)//Del
   		{
   		   	float s_type=rand()%1000000/(double)1000001;
   		   	//cout<<s_type<<endl;
   			if(s_type>(1-Pdn))  //Del-->Norm
   			{
   				//cout<<"Del-->Norm()end"<<endl;
   				state=0;continue;
   			}
   			else if(s_type>(Pdd))  //Del-->Amp
   			{
   				/*cout<<"Del-->Amp(end)"<<endl;
   				cout<<kk<<endl;
   				cout<<cnv_made<<endl;*/
   				cnv_made++;
   				CNV_LOC = (long int *)realloc(CNV_LOC, (cnv_made) * sizeof(long int));
   				CNV_LEN = (int *)realloc(CNV_LEN, (cnv_made) * sizeof(int));
   				CNV_CP1 = (int *)realloc(CNV_CP1, (cnv_made) * sizeof(int));
   				CNV_CP2 = (int *)realloc(CNV_CP2, (cnv_made) * sizeof(int));
   				CNV_TYPE = (char *)realloc(CNV_TYPE, (cnv_made) * sizeof(char));
   				CNV_LOC[cnv_made-1]=kk;
   				CNV_LEN[cnv_made-1]=1;
   				CNV_CP1[cnv_made-1]=rand()%8+3;
   				CNV_CP2[cnv_made-1]=rand()%8+3;
   				CNV_TYPE[cnv_made-1]='a';
   				state=1;continue;
   			}
   			else  //Del-->Del
   			{
   				//cout<<"Del-->Del"<<endl;
   				CNV_LEN[cnv_made-1]++;
   				state=2;continue;
   			}
   		}
	}
	
	
	
	
	/*for(int kks=0;kks<cnv_made;kks++)
	{
		cout<<CNV_LOC[kks]<<"\t"<<CNV_LEN[kks]<<"\t"<<CNV_TYPE[kks]<<"\t"<<CNV_CP1[kks]<<"\t"<<CNV_CP2[kks]<<endl;
	}*/
	
	//cout<<"begin variation"<<endl;
	
	//Variant simulation
	char chr,chr2;
     	char name[200];

     	cnv_no1=0,cnv_no2=0;
	CNV_IN1.clear();
	CNV_IN1.seekg(ios::beg);
	CNV_LOC1<<"chr\tloc\tlen\ttype\tcopy\n";
	CNV_IN2.clear();
	CNV_IN2.seekg(ios::beg);
	CNV_LOC2<<"chr\tloc\tlen\ttype\tcopy\n";

	int flag=0;
	int i=0;
     	for(long int pos=0;((chr=CNV_IN1.get())!=EOF);pos++)//input is Tandem dupilcation file output is CNV file
	{               			
		if(chr=='>')
		{
			if(flag==1)
			{
				CNV1<<"\n"; 
				CNV_IN1.getline(name,100);
				//cout<<name<<"  "<<pos<<endl;
				CNV1<<">"<<name;
				//cout<<name<<" "<<pos<<endl;
			}
			else
			{
				CNV_IN1.getline(name,200);
				//cout<<name<<"  "<<pos<<endl;
				CNV1<<">"<<name<<"\n";	
				//cout<<name<<"  "<<pos<<endl;
			}	
			cnv_no1+=50-(pos+cnv_no1)%50;	pos--;continue;	
		}
		if(chr=='\n')
		{
			pos--;	continue;
		}
		if(flag==1)
		{ 
			if((pos+cnv_no1)%50==0){CNV1<<"\n";}  
		}
		flag=1;
		
		if((pos==(CNV_LOC[i]-1)))	//CNV_LOC is the location for germline CNV
		{
			if(CNV_TYPE[i]=='a')
			{
				cnv_amp(CNV_LEN[i],CNV_CP1[i],pos,1);	//name
				CNV_LOC1<<name<<"\t"<<CNV_LOC[i]<<"\t"<<CNV_LEN[i]<<"\tamp\t"<<CNV_CP1[i]<<endl;
			}
			else
			{
				if(CNV_CP1[i]==0)
				{
					cnv_del(CNV_LEN[i],pos,1);
					pos=pos+CNV_LEN[i];
					CNV_LOC1<<name<<"\t"<<CNV_LOC[i]<<"\t"<<CNV_LEN[i]<<"\tdel\t"<<CNV_CP1[i]<<endl;
				}
				
			}
			i++;
		}
		CNV1.put(chr);
	}
	
	flag=0;
	i=0;
	for(long int pos=0;((chr2=CNV_IN2.get())!=EOF);pos++)//input is Tandem dupilcation file output is CNV file
	{               			
		if(chr2=='>')
		{
			if(flag==1)
			{
				CNV2<<"\n"; 
				CNV_IN2.getline(name,100);
				//cout<<name<<"  "<<pos<<endl;
				CNV2<<">"<<name;
				//cout<<name<<" "<<pos<<endl;
			}
			else
			{
				CNV_IN2.getline(name,200);
				//cout<<name<<"  "<<pos<<endl;
				CNV2<<">"<<name<<"\n";	
				//cout<<name<<"  "<<pos<<endl;
			}	
			cnv_no2+=50-(pos+cnv_no2)%50;	pos--;continue;	
		}
		if(chr2=='\n')
		{
			pos--;	continue;
		}
		if(flag==1)
		{ 
			if((pos+cnv_no2)%50==0){CNV2<<"\n";}  
		}
		flag=1;
		
		if((pos==(CNV_LOC[i]-1)))	//CNV_LOC is the location for germline CNV
		{
			if(CNV_TYPE[i]=='a')
			{
				cnv_amp(CNV_LEN[i],CNV_CP2[i],pos,2);	//name
				CNV_LOC2<<name<<"\t"<<CNV_LOC[i]<<"\t"<<CNV_LEN[i]<<"\tamp\t"<<CNV_CP2[i]<<endl;
			}
			else
			{
				if(CNV_CP2[i]==0)
				{
					cnv_del(CNV_LEN[i],pos,2);
					pos=pos+CNV_LEN[i];
					CNV_LOC2<<name<<"\t"<<CNV_LOC[i]<<"\t"<<CNV_LEN[i]<<"\tdel\t"<<CNV_CP2[i]<<endl;
				}	
			}
			i++;
		}
		CNV2.put(chr2);
	}
	
	CNV1.close();
	CNV2.close();
	CNV1.clear();
	CNV2.clear();
	CNV_LOC1.close();
	CNV_LOC2.close();
	CNV_IN1.close();
	CNV_IN2.close();
	CNV_LOC1.clear();
	CNV_LOC2.clear();
	CNV_IN1.clear();
	CNV_IN2.clear();
}

void simulate::cnv_amp(long int cnv_len,int cnv_cp,long int pos,int tag)
{
	ios::pos_type position_cnv;
	cnv_len=cnv_len/cnv_cp;
	char name_cnv_amp[100];
	if(tag==1)
	{
		position_cnv=CNV_IN1.tellg();
		while(cnv_cp>1)
	    	{
			cnv_cp--;
			for(long int amp=0;amp<cnv_len;amp++)
		    	{
				char amp_nuc=CNV_IN1.get();
				if(amp_nuc=='\n'){amp--;continue;}
				if(amp_nuc=='>'){amp--;CNV_IN1.getline(name_cnv_amp,100);continue;}
				CNV1.put(amp_nuc);
				cnv_no1++;
				if((pos+cnv_no1)%50==0)
				{CNV1.put('\n');}
		    	}
		    	CNV_IN1.seekg(position_cnv);
	    	}
	}
	else
	{
		position_cnv=CNV_IN2.tellg();
		while(cnv_cp>1)
	    	{
			cnv_cp--;
			for(long int amp=0;amp<cnv_len;amp++)
		    	{
				char amp_nuc=CNV_IN2.get();
				if(amp_nuc=='\n'){amp--;continue;}
				if(amp_nuc=='>'){amp--;CNV_IN2.getline(name_cnv_amp,100);continue;}
				CNV2.put(amp_nuc);
				cnv_no2++;
				if((pos+cnv_no2)%50==0)
				{CNV2.put('\n');}
		    	}
		    	CNV_IN2.seekg(position_cnv);
	    	}
	}
	
}
void simulate::cnv_del(long int cnv_len,long int pos,int tag)
{
	//ios::pos_type position_cnv;	
	char name_cnv_del[100];
	long int cnv_no_temp1=cnv_no1;
	long int cnv_no_temp2=cnv_no2;
	if(tag==1)
	{
	    	for(long int del=0;del<cnv_len;del++)
	    	{
			char del_nuc=CNV_IN1.get();
			if(del_nuc=='>'){del--;CNV_IN1.getline(name_cnv_del,100);CNV1<<"\n>"<<name_cnv_del<<"\n";cnv_no1+=50-(pos+cnv_no_temp1)%50;continue;}
			if(!isalpha(del_nuc)){del--;continue;}
			cnv_no1--;
		}
	}
	else
	{
		for(long int del=0;del<cnv_len;del++)
	    	{
			char del_nuc=CNV_IN2.get();
			if(del_nuc=='>'){del--;CNV_IN2.getline(name_cnv_del,100);CNV2<<"\n>"<<name_cnv_del<<"\n";cnv_no2+=50-(pos+cnv_no_temp2)%50;continue;}
			if(!isalpha(del_nuc)){del--;continue;}
			cnv_no2--;
		}
	}

}

long int simulate::rands(long int GENOME_SIZE_INV)
{
	if(GENOME_SIZE_INV<= RAND_MAX){          //RAND_MAX为随机数可产生的最大数
		return rand()%GENOME_SIZE_INV+1;
	}
	else{
		if(rand()/(double)RAND_MAX <= (RAND_MAX/(double)GENOME_SIZE_INV)){
				return rand()%(GENOME_SIZE_INV)+1;
			}else{
				return RAND_MAX+(rand()%(GENOME_SIZE_INV-RAND_MAX))+1;
		}
	}
}
void simulate::invertions(parameters & params)
{
	//cout<<"Germline Inversion..."<<endl;
	ofstream INVER_LOC1,INVER1,INVER2,INVER_LOC2;
	ifstream INVER_IN1,INVER_IN2;
	long int* INVER_LOC=NULL,*INVER_SIZE=NULL;
	if((params.infile_tumor==1)&&(somatic_flag==1))
     	{
     		cout<<"Somatic Inversion..."<<endl;
     		//params.INVER1="./Results/somatic_inver1.fa";
		//params.INVER2="./Results/somatic_inver2.fa";
		char somatic_inver_name[300];
     		sprintf(somatic_inver_name,"./Results/tumor%d_inver1.fa",tumor_flag);
     		params.INVER1=somatic_inver_name;
     		sprintf(somatic_inver_name,"./Results/tumor%d_inver2.fa",tumor_flag);
     		params.INVER2=somatic_inver_name;
		sprintf(somatic_inver_name,"./Results/tumor%d_inver_message1.fa",tumor_flag);
     		INVER_LOC1.open(somatic_inver_name,ios::out);
     		sprintf(somatic_inver_name,"./Results/tumor%d_inver_message2.fa",tumor_flag);
     		INVER_LOC2.open(somatic_inver_name,ios::out);
     	}
     	else
     	{
     		cout<<"Germline Inversion..."<<endl;
     		params.INVER1="./Results/germline_inver1.fa";
		params.INVER2="./Results/germline_inver2.fa";
     		
		//for(m=0;m<24;m++){flag_indel[m]=0;}
		INVER_LOC1.open("./Results/inver_messaeg_1.txt",ios::out);
		INVER_LOC2.open("./Results/inver_messaeg_2.txt",ios::out);
     	}
	
	
	
	if (!INVER_LOC1.is_open())
    	{
		cout<<"Cant't open file for inversion message1 writing\n";exit(-1);
     	}
	INVER1.open(params.INVER1.c_str(),ios::out);
	if (!INVER1.is_open())
    	{
		cout<<"Cant't open file for INVER1 writing\n";exit(-1);
     	}
     	
	if (!INVER_LOC2.is_open())
    	{
		cout<<"Cant't open file for inversion message2 writing\n";exit(-1);
     	}
     	INVER2.open(params.INVER2.c_str(),ios::out);
	if (!INVER2.is_open())
    	{
		cout<<"Cant't open file for INVER2 writing\n";exit(-1);
     	}
	INVER_IN1.open(params.CNV1.c_str(),ios::in);
	if (!INVER_IN1.is_open())
    	{
		cout<<"Cant't open CNV1 for INVER1 reading\n";exit(-1);
     	}
     	INVER_IN2.open(params.CNV2.c_str(),ios::in);
	if (!INVER_IN2.is_open())
    	{
		cout<<"Cant't open CNV2 for INVER2 reading\n";exit(-1);
     	}
	
	int inv_made=0;
	long int* inv_len1=count_genome(INVER_IN1);
     	for(int i=0;i<24;i++){inv_len11+=chr_count[i];
     		//cout<<chr_count[i]<<endl;
     		//cout<<inv_len1[i]<<endl;
     	}
    	//long int* inv_len2=count_genome(INVER_IN2);
    	for(int i=0;i<24;i++){inv_len22+=chr_count[i];
    		//cout<<chr_count[i]<<endl;
    		//cout<<inv_len2[i]<<endl;
    	}
	//long int inv7_q22=98865645,inv7_q31=121068299,inv7_q36=157866463,inv9_p11=40714548,inv9_q12=46222769,inv9_q13=62291150;
       	//for(int i = 0; i< 24; i++){cout<<inv_len1[i]<<endl;}
       	long int inv7_q22=203,inv7_q31=223,inv7_q36=245,inv9_p11=100,inv9_q12=150,inv9_q13=170;
       	
	if(inv_len1[6]>inv7_q31)
       	{
       		INVER_LOC = (long int *)realloc(INVER_LOC, (inv_made+1) * sizeof(long int));
		INVER_SIZE = (long int *)realloc(INVER_SIZE, (inv_made+1) * sizeof(long int));
		
		INVER_LOC[inv_made]=inv_len1[0]+inv_len1[1]+inv_len1[2]+inv_len1[3]+inv_len1[4]+inv_len1[5]+inv7_q22;
		//cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
		INVER_SIZE[inv_made]=inv7_q31-inv7_q22;
		//cout<<INVER_LOC[inv_made]<<endl;
		//for(int ii=0;ii<24;ii++){
     		//cout<<chr_count[i]<<endl;
     		//cout<<inv_len1[ii]<<endl;
     		//}
		//cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
		inv_made++;
       	}
       	if(inv_len1[6]>inv7_q36)
       	{
       		INVER_LOC = (long int *)realloc(INVER_LOC, (inv_made+1) * sizeof(long int));
		INVER_SIZE = (long int *)realloc(INVER_SIZE, (inv_made+1) * sizeof(long int));
		INVER_LOC[inv_made]=inv_len1[0]+inv_len1[1]+inv_len1[2]+inv_len1[3]+inv_len1[4]+inv_len1[5]+inv7_q22;
		INVER_SIZE[inv_made]=inv7_q36-inv7_q22;
		//cout<<INVER_LOC[inv_made]<<endl;
		inv_made++;
       	}
	if(inv_len1[8]>inv9_q12)
       	{
       		INVER_LOC = (long int *)realloc(INVER_LOC, (inv_made+1) * sizeof(long int));
		INVER_SIZE = (long int *)realloc(INVER_SIZE, (inv_made+1) * sizeof(long int));
		INVER_LOC[inv_made]=inv_len1[0]+inv_len1[1]+inv_len1[2]+inv_len1[3]+inv_len1[4]+inv_len1[5]+inv_len1[6]+inv_len1[7]+inv9_p11;
		INVER_SIZE[inv_made]=inv9_q12-inv9_p11;
		//cout<<INVER_LOC[inv_made]<<endl;
		inv_made++;
       	}
	if(inv_len1[8]>inv9_q13)
       	{
       		INVER_LOC = (long int *)realloc(INVER_LOC, (inv_made+1) * sizeof(long int));
		INVER_SIZE = (long int *)realloc(INVER_SIZE, (inv_made+1) * sizeof(long int));
		INVER_LOC[inv_made]=inv_len1[0]+inv_len1[1]+inv_len1[2]+inv_len1[3]+inv_len1[4]+inv_len1[5]+inv_len1[6]+inv_len1[7]+inv9_p11;
		//cout<<INVER_LOC[inv_made]<<endl;
		INVER_SIZE[inv_made]=inv9_q13-inv9_p11;
		inv_made++;
       	}
       	
       	
        //for(int i = 0; i< 4; i++){cout<<INVER_LOC[i]<<endl;}
       	char chr_i;
	char name_inver[100];	
	INVER_IN1.clear();
	INVER_IN1.seekg(0,ios::beg);
	INVER_LOC1<<"name"<<"\t"<<"inv_s"<<"\t"<<"inv_e"<<"\t"<<"inv_size"<<'\n';
	int a1=0;
	long int inv_no=0;
	for(long int pos_i=0;(chr_i=INVER_IN1.get())!=EOF;pos_i++)
	{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	    	if(chr_i=='>')
	    	{
	    		inv_no=50-pos_i%50;
			pos_i--;
			INVER_IN1.getline(name_inver,100);
			INVER1<<">"<<name_inver<<"\n";
			//cout<<name_inver<<": "<<(pos_i+1)<<"\n";				
			continue;
	    	}
	    	if(chr_i=='\n')
	   	{
			pos_i--;//continue;
	    	}
	    	if(((pos_i+1)==INVER_LOC[a1])&&(a1<inv_made))
	    	{
	    		//if(chr_i=='\n'){INVER1<<'\n';}
	    		//cout<<INVER_LOC[a1]<<endl;
			a1++;
			//if(a1> inv_made){return;}
			INVER_LOC1<<name_inver<<"\t\t"<<INVER_LOC[a1-1]<<"\t\t"<<INVER_LOC[a1-1]+INVER_SIZE[a1-1]<<"\t\t"<<INVER_SIZE[a1-1]<<'\n';
			//cout<<name_inver<<"  "<<INVER_LOC[a1]<<endl;
			a1++;
			INVER_LOC1<<name_inver<<"\t\t"<<INVER_LOC[a1-1]<<"\t\t"<<INVER_LOC[a1-1]+INVER_SIZE[a1-1]<<"\t\t"<<INVER_SIZE[a1-1]<<'\n';
			stack<char> s1;
			stack<char> s11;
			
			for( int in_vert1=0; in_vert1 < INVER_SIZE[a1-2]; in_vert1++ )
			{
			    chr_i=INVER_IN1.get();
			    if(chr_i=='\n'){in_vert1--;continue;}
			    s1.push(chr_i);
			}
			//position_inv=INVER_IN1.tellg();
	      		while(!s1.empty())
			{
				  chr_i=s1.top();
				  //INVER1.put(chr_i);
				  s11.push(chr_i);
				  s1.pop();
				  //pos_i++;
			}
			while(!s11.empty())
			{
				  chr_i=s11.top();
				  INVER1.put(chr_i);
				  s11.pop();
				  pos_i++;
				  if((pos_i+inv_no)%50==0){INVER1<<'\n';}
			}
			
					
		}
		INVER1.put(chr_i);
	}
	
	
	
     	long int* inv_len2=count_genome(INVER_IN2);
     	for(int i=0;i<24;i++){inv_len22+=chr_count[i];
    		//cout<<chr_count[i]<<endl;
    		//cout<<inv_len2[i]<<endl;
    	}
	inv_made=0;
	if(inv_len2[6]>inv7_q31)
       	{
       		INVER_LOC = (long int *)realloc(INVER_LOC, (inv_made+1) * sizeof(long int));
		INVER_SIZE = (long int *)realloc(INVER_SIZE, (inv_made+1) * sizeof(long int));
		INVER_LOC[inv_made]=inv_len2[0]+inv_len2[1]+inv_len2[2]+inv_len2[3]+inv_len2[4]+inv_len2[5]+inv7_q22;
		INVER_SIZE[inv_made]=inv7_q31-inv7_q22;
		inv_made++;
       	}
       	if(inv_len2[6]>inv7_q36)
       	{
       		INVER_LOC = (long int *)realloc(INVER_LOC, (inv_made+1) * sizeof(long int));
		INVER_SIZE = (long int *)realloc(INVER_SIZE, (inv_made+1) * sizeof(long int));
		INVER_LOC[inv_made]=inv_len2[0]+inv_len2[1]+inv_len2[2]+inv_len2[3]+inv_len2[4]+inv_len2[5]+inv7_q22;
		INVER_SIZE[inv_made]=inv7_q36-inv7_q22;
		inv_made++;
       	}
	if(inv_len2[8]>inv9_q12)
       	{
       		INVER_LOC = (long int *)realloc(INVER_LOC, (inv_made+1) * sizeof(long int));
		INVER_SIZE = (long int *)realloc(INVER_SIZE, (inv_made+1) * sizeof(long int));
		INVER_LOC[inv_made]=inv_len2[0]+inv_len2[1]+inv_len2[2]+inv_len2[3]+inv_len2[4]+inv_len2[5]+inv_len2[6]+inv_len2[7]+inv9_p11;
		INVER_SIZE[inv_made]=inv9_q12-inv9_p11;
		inv_made++;
       	}
	if(inv_len2[8]>inv9_q13)
       	{
       		INVER_LOC = (long int *)realloc(INVER_LOC, (inv_made+1) * sizeof(long int));
		INVER_SIZE = (long int *)realloc(INVER_SIZE, (inv_made+1) * sizeof(long int));
		INVER_LOC[inv_made]=inv_len2[0]+inv_len2[1]+inv_len2[2]+inv_len2[3]+inv_len2[4]+inv_len2[5]+inv_len2[6]+inv_len2[7]+inv9_p11;
		INVER_SIZE[inv_made]=inv9_q13-inv9_p11;
		inv_made++;
       	}
	
	a1=0;
	inv_no=0;
	INVER_IN2.clear();
	INVER_IN2.seekg(0,ios::beg);
	INVER_LOC2<<"name"<<"\t"<<"inv_s"<<"\t"<<"inv_e"<<"\t"<<"inv_size"<<'\n';
	for(long int pos_i=0;(chr_i=INVER_IN2.get())!=EOF;pos_i++)
	{
	    	if(chr_i=='>')
	    	{
		    	inv_no=50-pos_i%50;
			pos_i--;
			INVER_IN2.getline(name_inver,100);
			INVER2<<">"<<name_inver<<"\n";
			//cout<<name_inver<<"\n";
			continue;
	    	}
	    	if(chr_i=='\n')
	    	{
			pos_i--;
	    	}
	    	if((pos_i==INVER_LOC[a1])&&(a1<inv_made))
	    	{
	    		//cout<<INVER_LOC[a1]<<endl;			
		    	a1++;
		    	INVER_LOC2<<name_inver<<"\t\t"<<INVER_LOC[a1-1]<<"\t\t"<<INVER_LOC[a1-1]+INVER_SIZE[a1-1]<<"\t\t"<<INVER_SIZE[a1-1]<<'\n';
		    	a1++;
		    	INVER_LOC2<<name_inver<<"\t\t"<<INVER_LOC[a1-1]<<"\t\t"<<INVER_LOC[a1-1]+INVER_SIZE[a1-1]<<"\t\t"<<INVER_SIZE[a1-1]<<'\n';
			//if(a1>inv_made) {return;}
			stack<char> s2;
			stack<char> s22;
			for( int in_vert2=0; in_vert2 < INVER_SIZE[a1-2]; in_vert2++ )
			{				
			    	chr_i=INVER_IN2.get();
			    	if(chr_i=='\n'){in_vert2--;continue; }
			    	s2.push(chr_i);
			}
		      	while(!s2.empty())
		      	{		
			  	chr_i=s2.top();
			  	s22.push(chr_i);
			  	s2.pop();
			}
			
			
			for( int in_vert2=0; in_vert2 < (INVER_SIZE[a1-1]-INVER_SIZE[a1-2]); in_vert2++ )
			{				
			    	chr_i=INVER_IN2.get();
			    	if(chr_i=='\n'){in_vert2--;continue; }
			    	s22.push(chr_i);
			}
			while(!s22.empty())
			{
				  chr_i=s22.top();
				  INVER2.put(chr_i);
				  s22.pop();
				  pos_i++;
				  if((pos_i+inv_no)%50==0){INVER2<<'\n';}
			}
			
	    	}
	    INVER2.put(chr_i);
	}
	
	/*//对INVER_LOC进行排序(冒泡排序)；
	for(int i = 0; i< inv_made; i++)
	{
		for(int j = 1; j < inv_made - i; j++)
		{	
		    	if(INVER_LOC[j] < INVER_LOC[j - 1])
		    	{
				long int temp_i=INVER_LOC[j-1];
				INVER_LOC[j-1]=INVER_LOC[j];
				INVER_LOC[j]=temp_i;
		    	}
		}
	 }
	*/
     	INVER1.close();
	INVER2.close();
	INVER1.clear();
	INVER2.clear();
	INVER_LOC1.close();
	INVER_LOC2.close();
	INVER_IN1.close();
	INVER_IN2.close();
	INVER_LOC1.clear();
	INVER_LOC2.clear();
	INVER_IN1.clear();
	INVER_IN2.clear();
}
void simulate::translocation(parameters & params)
{
	//cout<<"Germline Translocation..."<<endl;
	ofstream TRANS_LOC1,TRANS1,TRANS2,TRANS_LOC2;
	ifstream TRANS_IN1,TRANS_IN2,TRANS_INFO;
	
	if((params.infile_tumor==1)&&(somatic_flag==1))
     	{
     		cout<<"Somatic Translocation..."<<endl;
		char somatic_trans_name[300];
     		sprintf(somatic_trans_name,"./Results/tumor%d_trans1.fa",tumor_flag);
     		params.TRANS1=somatic_trans_name;
     		sprintf(somatic_trans_name,"./Results/tumor%d_trans2.fa",tumor_flag);
     		params.TRANS2=somatic_trans_name;
		sprintf(somatic_trans_name,"./Results/tumor%d_trans_message1.fa",tumor_flag);
     		TRANS_LOC1.open(somatic_trans_name,ios::out);
     		sprintf(somatic_trans_name,"./Results/tumor%d_trans_message2.fa",tumor_flag);
     		TRANS_LOC2.open(somatic_trans_name,ios::out);
     	}
     	else
     	{
     		cout<<"Germline Translocation..."<<endl;
     		params.TRANS1="./Results/germline_trans1.fa";
		params.TRANS2="./Results/germline_trans2.fa";
     		
		//for(m=0;m<24;m++){flag_indel[m]=0;}
		TRANS_LOC1.open("./Results/trans_messaeg_1.txt",ios::out);
		TRANS_LOC2.open("./Results/trans_messaeg_2.txt",ios::out);
     	}
	

	TRANS_INFO.open("./Datas/trans.txt",ios::in);
	if (!TRANS_INFO.is_open())
    	{
		cout<<"Cant't open trans.txt file for translocation\n";exit(-1);
     	}
	
	if (!TRANS_LOC1.is_open())
    	{
		cout<<"Cant't open file for translocation message1 writing\n";exit(-1);
     	}
	TRANS1.open(params.TRANS1.c_str(),ios::out);
	if (!TRANS1.is_open())
    	{
		cout<<"Cant't open file for TRANS1 writing\n";exit(-1);
     	}
     	
	if (!TRANS_LOC2.is_open())
    	{
		cout<<"Cant't open file for translocation message2 writing\n";exit(-1);
     	}
     	TRANS2.open(params.TRANS2.c_str(),ios::out);
	if (!TRANS2.is_open())
    	{
		cout<<"Cant't open file for TRANS2 writing\n";exit(-1);
     	}
	TRANS_IN1.open(params.INVER1.c_str(),ios::in);
	if (!TRANS_IN1.is_open())
    	{
		cout<<"Cant't open INVER1 for TRANS1 reading\n";exit(-1);
     	}
     	TRANS_IN2.open(params.INVER2.c_str(),ios::in);
	if (!TRANS_IN2.is_open())
    	{
		cout<<"Cant't open INVER2 for TRANS2 reading\n";exit(-1);
     	}
     	long int *Start_p=NULL,*Trans_size_p=NULL,*Start_q=NULL,*Trans_size_q=NULL,trans_made=0;
     	long int *len_trans1=count_genome(TRANS_IN1);
     	int *chrp=NULL,*chrq=NULL;
     	while(TRANS_INFO)    //compute snp count
	{
		string str,c;
		getline(TRANS_INFO,str);//如果没有到达文件的末尾进行读取一行
		istringstream iss(str);
		iss >> c;
		if(c=="translocation")
		{
			continue;
		}
		else if(c!="")	//first	first_loc	first_length	second	second_loc	second_length
		{
			chrp=(int *) realloc (chrp, (trans_made+1)*(sizeof (int)));
			Start_p=(long int *) realloc (Start_p, (trans_made+1)*(sizeof (long int)));
			Trans_size_p=(long int *) realloc (Trans_size_p, (trans_made+1)*(sizeof (long int)));
			chrq=(int *) realloc (chrq, (trans_made+1)*(sizeof (int)));
			Start_q=(long int *) realloc (Start_q, (trans_made+1)*(sizeof (long int)));
			Trans_size_q=(long int *) realloc (Trans_size_q, (trans_made+1)*(sizeof (long int)));
			//INVER_SIZE = (long int *)realloc(INVER_SIZE, (inv_made+1) * sizeof(long int));
			iss >> chrp[trans_made];
			iss >> Start_p[trans_made];
			iss >> Trans_size_p[trans_made];
			for(int trans_pos=0;trans_pos<(chrp[trans_made]-1);trans_pos++){Start_p[trans_made]+=len_trans1[trans_pos];}
			iss >> chrq[trans_made];
			iss >> Start_q[trans_made];
			iss >> Trans_size_q[trans_made];
			for(int trans_pos=0;trans_pos<(chrq[trans_made]-1);trans_pos++){Start_q[trans_made]+=len_trans1[trans_pos];}
			//cout<<chrp[trans_made]<<endl<<Start_p[trans_made]<<endl<<Trans_size_p[trans_made]<<endl<<chrq[trans_made]<<endl<<Start_q[trans_made]<<endl<<Trans_size_q[trans_made]<<endl;
			trans_made++;
		}	
	}
     	TRANS_LOC1<<"chr_p\tstart_p\tsize_p\tchr_q\tstart_q\tsize_q\n";

     	
	int max_flag=1;
	long int max_post=Start_q[0],max_size=Trans_size_q[0];
	for(int i=1;i<trans_made;i++)
	{
		if(Start_q[i]>max_post)
		{
			max_post=Start_q[i];
			max_size=Trans_size_q[i];
			max_flag=chrq[trans_made];
		}
	}
	/*char trans_col[max_post+max_size+1-Start_p[0]];
	*/
	string trans_col="";
	int trans_a;
	long int pos_t;
       	char chr_t;
       	char name_trans[100];
       	int trans_no=0;
       	//TRANS_IN1.clear();
	//TRANS_IN1.seekg(0,ios::beg);
	ios::pos_type position_trans;
	queue<char> p;
	queue<char> q;
	queue<char> o;
	int trans_flag=0;
	int trans_flag2=0;
//first	first_loc	first_length	second	second_loc	second_length

	//TRANS1
	for(trans_a=0;trans_a<trans_made;trans_a++)
	{
		TRANS_LOC1<<"chr"<<chrp[trans_a]<<"\t"<<Start_p[trans_a]<<"\t"<<Trans_size_p[trans_a]<<"\t"<<"chr"<<chrq[trans_a]<<"\t"<<Start_q[trans_a]<<"\t"<<Trans_size_q[trans_a]<<'\n';
		if(trans_a>0)
		{
			TRANS_IN1.open("./Results/germline_trans_temp1.fa",ios::in);
			if (!TRANS_IN1.is_open())
		    	{
				cout<<"Cant't open germline_trans_temp1 for TRANS1 reading\n";exit(-1);
		     	}
			TRANS1.open(params.TRANS1.c_str(),ios::out);
			if (!TRANS1.is_open())
		    	{
				cout<<"Cant't open file for TRANS1 writing\n";exit(-1);
		     	}
		}
		TRANS_IN1.clear();
		TRANS_IN1.seekg(0,ios::beg);
		for(pos_t=0;(chr_t=TRANS_IN1.get())!=EOF;pos_t++)
		{
			trans_flag2=0;
		    	if(chr_t=='>')
		    	{
		    		if(trans_flag==1){TRANS1<<"\n";}
		    		trans_no=50-pos_t%50;
				pos_t--;
				TRANS_IN1.getline(name_trans,100);
				TRANS1<<">"<<name_trans;
				
				continue;
		    	}
		    	trans_flag=1;
		    	if(chr_t=='\n')
		    	{	
				pos_t--;
				continue;
				//cout<<"nnnmm"<<endl;
		    	}
		    	if((trans_flag==1)&&((pos_t+trans_no)%50==0))
			{
				TRANS1<<'\n';
				
			}
			
		    	if((pos_t+1)==Start_p[trans_a])
		    	{
		    		trans_flag2=1;
		    		//cout<<"pos_t:"<<pos_t<<endl;
		    		long int pos_transt=pos_t;
		        	position_trans=TRANS_IN1.tellg();
				
				for( int trans_p=0; trans_p < Trans_size_p[trans_a]; trans_p++)
			    	{
					chr_t=TRANS_IN1.get();
					pos_transt++;
					if(chr_t=='\n')
				    	{
						trans_p--;
						pos_transt--;
						continue;
				    	}
				   	p.push(chr_t);
				   	
			    	}
			    	//cout<<"pos_t:"<<pos_t<<endl;
				while(pos_transt<Start_q[trans_a])
				{	
					chr_t=TRANS_IN1.get();
					pos_transt++;
					if(chr_t=='>')
					{
						pos_transt--;
						TRANS_IN1.getline(name_trans,100);
						o.push('>');
						string temp_name_trans=name_trans;
						for(int trans_p=0; trans_p < temp_name_trans.length(); trans_p++){o.push(name_trans[trans_p]);}
						o.push('\n');
						//cout<<"trans_col: "<<trans_col<<endl;
						continue;
					}
					if(chr_t=='\n')
				    	{
						pos_transt--;	continue;
				    	}
				    	o.push(chr_t);
				}
				//cout<<"pos_t:"<<pos_t<<endl;
				for( int trans_p=0; trans_p < Trans_size_q[trans_a]; trans_p++)
				{	
					chr_t=TRANS_IN1.get();
					//pos_transt++;
					
					if(chr_t=='\n')
				    	{
						trans_p--;
						//pos_transt--;	
						continue;
				    	}
				    	q.push(chr_t);
				}
				//TRANS1<<"begin";
				//cout<<"pos_t:"<<pos_t<<endl;
				while(!q.empty())
				{	
				  	chr_t=q.front();
				  	TRANS1.put(chr_t);
				  	
				  	
				  	q.pop();
				  	trans_no++;
				  	if((pos_t+trans_no)%50==0)
				  	{
				      		TRANS1<<'\n';
				      		
				  	}
				 }
				 //TRANS1<<"p_end";
				//cout<<"pos_t:"<<pos_t<<endl;
		  		TRANS_IN1.seekg(position_trans+(1+Trans_size_p[trans_a]));
		  		pos_t+=Trans_size_p[trans_a];
		  		trans_no-=Trans_size_p[trans_a];
	    		}
	    		if((pos_t)==Start_q[trans_a])
	    		{
	    			//TRANS1<<"q_start";
	    			trans_flag2=2;
	    			position_trans=TRANS_IN1.tellg();
	    			while(!p.empty())
				{	
				  	chr_t=p.front();
				  	TRANS1.put(chr_t);
				  	
				  	p.pop();
				  	trans_no++;
				  	if((pos_t+trans_no)%50==0)
				  	{
				      		TRANS1<<'\n';
				      	
				  	}
				 }
				TRANS_IN1.seekg(position_trans+(1+Trans_size_q[trans_a]));
				pos_t+=Trans_size_q[trans_a];
		  		trans_no-=Trans_size_q[trans_a];
				//TRANS1<<"end";
	    		}
	    		if(trans_flag2>0)
	    		{
	    			trans_no--;
		    		continue;	
		    		//cout<<">>0"<<chr_t<<endl;
		    		//TRANS1<<"trans_flag2=1"<<endl;
	    		}
	    		TRANS1.put(chr_t);
	    		
			
		}
		if(trans_a==(trans_made-1)){TRANS1.clear();TRANS1.close();}
		system("cp ./Results/germline_trans1.fa ./Results/germline_trans_temp1.fa");
		//trans_a++;
	}
	system("rm ./Results/germline_trans_temp1.fa");
	
	
	
	long int *len_trans2=count_genome(TRANS_IN2);
	trans_made=0;
	TRANS_INFO.clear();
	TRANS_INFO.seekg(0,ios::beg);
     	while(TRANS_INFO)    //compute snp count
	{
		string str,c;
		getline(TRANS_INFO,str);//如果没有到达文件的末尾进行读取一行
		istringstream iss(str);
		iss >> c;
		if(c=="translocation")
		{
			continue;
		}
		else if(c!="")	//first	first_loc	first_length	second	second_loc	second_length
		{
			chrp=(int *) realloc (chrp, (trans_made+1)*(sizeof (int)));
			Start_p=(long int *) realloc (Start_p, (trans_made+1)*(sizeof (long int)));
			Trans_size_p=(long int *) realloc (Trans_size_p, (trans_made+1)*(sizeof (long int)));
			chrq=(int *) realloc (chrq, (trans_made+1)*(sizeof (int)));
			Start_q=(long int *) realloc (Start_q, (trans_made+1)*(sizeof (long int)));
			Trans_size_q=(long int *) realloc (Trans_size_q, (trans_made+1)*(sizeof (long int)));
			//INVER_SIZE = (long int *)realloc(INVER_SIZE, (inv_made+1) * sizeof(long int));
			iss >> chrp[trans_made];
			iss >> Start_p[trans_made];
			iss >> Trans_size_p[trans_made];
			for(int trans_pos=0;trans_pos<(chrp[trans_made]-1);trans_pos++){Start_p[trans_made]+=len_trans2[trans_pos];}
			iss >> chrq[trans_made];
			iss >> Start_q[trans_made];
			iss >> Trans_size_q[trans_made];
			for(int trans_pos=0;trans_pos<(chrq[trans_made]-1);trans_pos++){Start_q[trans_made]+=len_trans2[trans_pos];}
			//cout<<chrp[trans_made]<<endl<<Start_p[trans_made]<<endl<<Trans_size_p[trans_made]<<endl<<chrq[trans_made]<<endl<<Start_q[trans_made]<<endl<<Trans_size_q[trans_made]<<endl;
			trans_made++;
		}	
	}
     	TRANS_LOC2<<"chr_p\tstart_p\tsize_p\tchr_q\tstart_q\tsize_q\n";
	max_flag=1;
	max_post=Start_q[0];
	max_size=Trans_size_q[0];
	for(int i=1;i<trans_made;i++)
	{
		if(Start_q[i]>max_post)
		{
			max_post=Start_q[i];
			max_size=Trans_size_q[i];
			max_flag=chrq[trans_made];
		}
	}


	trans_no=0;
	trans_flag=0;
	trans_flag2=0;

	//TRANS2
	for(trans_a=0;trans_a<trans_made;trans_a++)
	{
		TRANS_LOC2<<"chr"<<chrp[trans_a]<<"\t"<<Start_p[trans_a]<<"\t"<<Trans_size_p[trans_a]<<"\t"<<"chr"<<chrq[trans_a]<<"\t"<<Start_q[trans_a]<<"\t"<<Trans_size_q[trans_a]<<'\n';
		if(trans_a>0)
		{
			TRANS_IN2.open("./Results/germline_trans_temp2.fa",ios::in);
			if (!TRANS_IN2.is_open())
		    	{
				cout<<"Cant't open germline_trans_temp2 for TRANS2 reading\n";exit(-1);
		     	}
			TRANS2.open(params.TRANS2.c_str(),ios::out);
			if (!TRANS2.is_open())
		    	{
				cout<<"Cant't open file for TRANS2 writing\n";exit(-1);
		     	}
		}
		TRANS_IN2.clear();
		TRANS_IN2.seekg(0,ios::beg);
		for(pos_t=0;(chr_t=TRANS_IN2.get())!=EOF;pos_t++)
		{
			trans_flag2=0;
		    	if(chr_t=='>')
		    	{
		    		if(trans_flag==1){TRANS2<<"\n";}
		    		trans_no=50-pos_t%50;
				pos_t--;
				TRANS_IN2.getline(name_trans,100);
				TRANS2<<">"<<name_trans;
				continue;
		    	}
		    	trans_flag=1;
		    	if(chr_t=='\n')
		    	{	
				pos_t--;
				continue;
				//cout<<"nnnmm"<<endl;
		    	}
		    	if((trans_flag==1)&&((pos_t+trans_no)%50==0))
			{
				TRANS2<<'\n';
			}
			
		    	if((pos_t+1)==Start_p[trans_a])
		    	{
		    		trans_flag2=1;
		    		//cout<<"pos_t:"<<pos_t<<endl;
		    		long int pos_transt=pos_t;
		        	position_trans=TRANS_IN2.tellg();
				
				for( int trans_p=0; trans_p < Trans_size_p[trans_a]; trans_p++)
			    	{
					chr_t=TRANS_IN2.get();
					pos_transt++;
					if(chr_t=='\n')
				    	{
						trans_p--;
						pos_transt--;
						continue;
				    	}
				   	p.push(chr_t);
				   	
			    	}
			    	//cout<<"pos_t:"<<pos_t<<endl;
				while(pos_transt<Start_q[trans_a])
				{	
					chr_t=TRANS_IN2.get();
					pos_transt++;
					if(chr_t=='>')
					{
						pos_transt--;
						TRANS_IN2.getline(name_trans,100);
						//o.push('>');
						//string temp_name_trans=name_trans;
						//for(int trans_p=0; trans_p < temp_name_trans.length(); trans_p++){o.push(name_trans[trans_p]);}
						//o.push('\n');
						//cout<<"trans_col: "<<trans_col<<endl;
						continue;
					}
					if(chr_t=='\n')
				    	{
						pos_transt--;	continue;
				    	}
				    	//o.push(chr_t);
				}
				//cout<<"pos_t:"<<pos_t<<endl;
				for( int trans_p=0; trans_p < Trans_size_q[trans_a]; trans_p++)
				{	
					chr_t=TRANS_IN2.get();
					//pos_transt++;
					
					if(chr_t=='\n')
				    	{
						trans_p--;
						//pos_transt--;	
						continue;
				    	}
				    	q.push(chr_t);
				}
				//TRANS2<<"begin";
				//cout<<"pos_t:"<<pos_t<<endl;
				while(!q.empty())
				{	
				  	chr_t=q.front();
				  	TRANS2.put(chr_t);
				  	
				  	q.pop();
				  	trans_no++;
				  	if((pos_t+trans_no)%50==0)
				  	{
				      		TRANS2<<'\n';
				  	}
				 }
				 //TRANS2<<"p_end";
				//cout<<"pos_t:"<<pos_t<<endl;
		  		TRANS_IN2.seekg(position_trans+(1+Trans_size_p[trans_a]));
		  		pos_t+=Trans_size_p[trans_a];
		  		trans_no-=Trans_size_p[trans_a];
	    		}
	    		if((pos_t)==Start_q[trans_a])
	    		{
	    			//TRANS2<<"q_start";
	    			trans_flag2=2;
	    			position_trans=TRANS_IN2.tellg();
	    			while(!p.empty())
				{	
				  	chr_t=p.front();
				  	TRANS2.put(chr_t);
				  	p.pop();
				  	trans_no++;
				  	if((pos_t+trans_no)%50==0)
				  	{
				      		TRANS2<<'\n';
				  	}
				 }
				TRANS_IN2.seekg(position_trans+(1+Trans_size_q[trans_a]));
				pos_t+=Trans_size_q[trans_a];
		  		trans_no-=Trans_size_q[trans_a];
				//TRANS2<<"end";
	    		}
	    		if(trans_flag2>0)
	    		{
	    			trans_no--;
		    		continue;	
		    		//cout<<">>0"<<chr_t<<endl;
		    		//TRANS2<<"trans_flag2=1"<<endl;
	    		}
	    		TRANS2.put(chr_t);
	    		
			
		}
		if(trans_a==(trans_made-1)){TRANS2.clear();TRANS2.close();}
		system("cp ./Results/germline_trans2.fa ./Results/germline_trans_temp2.fa");
		//trans_a++;
	}
	system("rm ./Results/germline_trans_temp2.fa");
       	/*for(pos_t=0;(chr_t=TRANS_IN1.get())!=EOF;pos_t++)
	{
	    	if(chr_t=='>')
	    	{
	    		trans_no=50-pos_t%50;
			pos_t--;
			TRANS_IN1.getline(name_trans,100);
			TRANS1<<">"<<name_trans<<"\n";
			continue;
	    	}
	    	if(chr_t=='\n')
	    	{	
			pos_t--;
			//cout<<"nnnmm"<<endl;
	    	}
	    	if((pos_t+1)==Start_p[0])
	    	{
	    		//cout<<sizeof(trans_col)<<endl<<(max_post+max_size+1-Start_p[0])<<endl;
	    		long int pos_transt=pos_t;
	    		//TRANS_LOC1<<Start_p[trans_a]<<"\t"<<Trans_size_p[trans_a]<<'\t'<<Start_q[trans_a]<<"\t"<<Trans_size_q[trans_a]<<'\n';
			while(pos_transt < (max_post+max_size))
			{
				chr_t=TRANS_IN1.get();
				pos_transt++;
				if(chr_t=='>')
				{
					pos_transt--;
					TRANS_IN1.getline(name_trans,100);
					trans_col+=">";
					trans_col+=name_trans;
					trans_col+="\n";
					//cout<<"trans_col: "<<trans_col<<endl;
					continue;
				}
				if(chr_t=='\n')
			    	{
					//trans_p--;
					pos_transt--;
					continue;
			    	}
			    	trans_col+=chr_t;
				//trans_col[trans_p]=chr_t;
			}
			while(trans_a<trans_made)
			{
				//1.befor start_p[trans_a]
				for(long int trans_p=0; trans_p < (start_p[trans_a]-pos_t-1); trans_p++)
				{
					trans_temp[trans_p]=trans_col[trans_p];
				}
				
				//2.q
				for(long int trans_p=0; trans_p <Trans_size_q[trans_a]; trans_p++)
				{
					trans_temp[start_p[trans_a]-pos_t-1+trans_p]=trans_col[start_q[trans_a]-pos_t-1+trans_p];
				}
				//3.p----q
				for(long int trans_p=0; trans_p <(start_q[trans_a]-start_p[trans_a]-Trans_size_p[trans_a]); trans_p++)
				{
					trans_temp[start_p[trans_a]-pos_t-1+Trans_size_q[trans_a]+trans_p]=trans_col[start_p[trans_a]+Trans_size_p[trans_a]-pos_t-1+trans_p];
				}
				//4.p
				for(long int trans_p=0; trans_p <Trans_size_p[trans_a]; trans_p++)
				{
					trans_temp[start_q[trans_a]+Trans_size_q[trans_a]-pos_t-1-Trans_size_p[trans_a]+trans_p]=trans_col[start_p[trans_a]-pos_t-1+trans_p];
				}
				trans_col=trans_temp;
				trans_a++;
			}
			//cout<<sizeof(trans_col)<<endl<<(max_post+max_size+1-Start_p[0])<<endl;
			for(long int trans_p=0; trans_p < trans_col.length(); trans_p++)
			{
				//cout<<trans_col[trans_p]<<endl;
				if(trans_col[trans_p]=='>'){TRANS1<<'\n';trans_p--;continue;}
				TRANS1.put(trans_col[trans_p]);
				pos_t++;
			  	if(pos_t%50==0)
			  	{
			      		TRANS1<<'\n';
			  	}
			}
          		//cout<<"pos_t:"<<pos_t<<endl;
          		//cout<<"pos_transt:"<<pos_transt<<endl;
          		
    		}
		TRANS1.put(chr_t);
	}
     	
     	long int Start_p,Trans_size_p,Start_q,Trans_size_q;
     	TRANS_LOC1<<"start_p"<<"\t"<<"end_p"<<"\t"<<"size_p\t"<<"start_q"<<"\t"<<"end_q\t"<<"size_q"<<'\n';
     	TRANS_LOC2<<"start_p"<<"\t"<<"end_p"<<"\t"<<"size_p\t"<<"start_q"<<"\t"<<"end_q\t"<<"size_q"<<'\n';
     	//inv_len11=0,inv_len22
     	Start_p=rand()%(inv_len11*8/10);
     	Start_q=Start_p+inv_len11*0.1;
     	params.trans_size_p=100;
     	params.trans_size_q=50;
     	Trans_size_p=gsl_ran_gaussian(r,10)+params.trans_size_p;
     	Trans_size_q=gsl_ran_gaussian(r,10)+params.trans_size_q;
       	TRANS_LOC1<<Start_p<<"\t"<<Start_p+Trans_size_p<<"\t"<<Trans_size_p<<'\t'<<Start_q<<"\t"<<Start_q+Trans_size_q<<"\t"<<Trans_size_q<<'\n';
       	long int pos_t;
       	char chr_t;
       	char name_trans[100];
       	int trans_no=0;
        for(pos_t=0;(chr_t=TRANS_IN1.get())!=EOF;pos_t++)
	{
	    	if(chr_t=='>')
	    	{
	    		trans_no=50-pos_t%50;
			pos_t--;
			TRANS_IN1.getline(name_trans,100);
			TRANS1<<">"<<name_trans<<"\n";
			continue;
	    	}
	    	if(chr_t=='\n')
	    	{	
			pos_t--;
			//cout<<"nnnmm"<<endl;
	    	}
	    	if(pos_t==Start_p)
	    	{
			long int pos_transt=pos_t;
	//        	position_i1=in1.tellg();
			queue<char> p;
			queue<char> q;
			queue<char> o;
			for( int trans_p=0; trans_p < Trans_size_p; trans_p++)
		    	{
				chr_t=TRANS_IN1.get();
				pos_transt++;
				if(chr_t=='\n')
			    	{
					trans_p--;
					pos_transt--;
					continue;
			    	}
			   	p.push(chr_t);
		    	}
			while(pos_transt<Start_q)
			{	
				chr_t=TRANS_IN1.get();
				pos_transt++;
				if(chr_t=='\n')
			    	{
					pos_transt--;	continue;
			    	}
			    	o.push(chr_t);
			}
			for( int trans_p=0; trans_p < Trans_size_q; trans_p++)
			{	
				chr_t=TRANS_IN1.get();
				if(chr_t=='\n')
			    	{
				trans_p--;	continue;
			    	}
			    	q.push(chr_t);
			}
			while(!q.empty())
			{	
			  	chr_t=q.front();
			  	TRANS1.put(chr_t);
			  	q.pop();
			  	pos_t++;
			  	if((pos_t)%50==0)
			  	{
			      		TRANS1<<'\n';
			  	}
			 }
			 while(!o.empty())
			 {	
			 	chr_t=o.front();
			  	TRANS1.put(chr_t);
			  	o.pop();
			  	pos_t++;
			  	if(pos_t%50==0)
			  	{
			      		TRANS1<<'\n';
			  	}
			  }
			  while(!p.empty())
			  {	
			  	chr_t=p.front();
			  	TRANS1.put(chr_t);
			  	p.pop();
			  	pos_t++;
			  	if(pos_t%50==0)
			  	{
			      		TRANS1<<'\n';
			  	}
          		  }
    		}
		TRANS1.put(chr_t);
	}
	Start_p=rand()%(inv_len22*8/10);
     	Start_q=Start_p+inv_len22*0.1;
	Trans_size_p=gsl_ran_gaussian(r,10)+params.trans_size_p;
     	Trans_size_q=gsl_ran_gaussian(r,10)+params.trans_size_q;
       	TRANS_LOC2<<Start_p<<"\t"<<Start_p+Trans_size_p<<"\t"<<Trans_size_p<<'\t'<<Start_q<<"\t"<<Start_q+Trans_size_q<<"\t"<<Trans_size_q<<'\n';
 	for(pos_t=0;(chr_t=TRANS_IN2.get())!=EOF;pos_t++)
	{	
    		if(chr_t=='>')
    		{
			pos_t--;
			TRANS_IN2.getline(name_trans,100);
			TRANS2<<">"<<name_trans<<"\n";
			continue;
    		}
    		if(chr_t=='\n')
    		{
			pos_t--;
		}
    		if(pos_t==Start_p)
    		{
			long int pos_transt=pos_t;
			queue<char> p;
			queue<char> q;
			queue<char> o;
        		for( int trans_p=0; trans_p < Trans_size_p; trans_p++)
        		{
				chr_t=TRANS_IN2.get();
				pos_transt++;
				if(chr_t=='\n')
			    	{
					trans_p--;
					pos_transt--;
					//pos_i++;
			    	}
            			else {p.push(chr_t);}
            		}
        		while(pos_transt<Start_q)
        		{
				chr_t=TRANS_IN2.get();
				pos_transt++;
				if(chr_t=='\n')
				    {
					pos_transt--;
				    }
			    	else {o.push(chr_t);}
            		}
        		for( int trans_p=0; trans_p < Trans_size_q; trans_p++)
        		{
		        	chr_t=TRANS_IN2.get();
		        	if(chr_t=='\n')
		    		{
		        		trans_p--;
		    		}
            			else {q.push(chr_t);}
        		}
         		while(!q.empty())
         		{
          			chr_t=q.front();
          			TRANS2.put(chr_t);
          			q.pop();
          			pos_t++;
          			if(pos_t%50==0)
				  {
				      TRANS2<<'\n';
				  }
          		}
           		while(!o.empty())
           		{
		       		chr_t=o.front();
			  	TRANS2.put(chr_t);
			  	o.pop();
			  	pos_t++;
			  	if(pos_t%50==0)
			  	{
			      		TRANS2<<'\n';
			  	}
           		}
		  	while(!p.empty())
		 	{
		  		chr_t=p.front();
		  		TRANS2.put(chr_t);
		  		p.pop();
		  		pos_t++;
		  		if(pos_t%50==0)
		  		{
		      			TRANS2<<'\n';
		  		}
		  	}
    		}
		TRANS2.put(chr_t);
	}*/
     	TRANS1.close();
	TRANS2.close();
	TRANS1.clear();
	TRANS2.clear();
	TRANS_LOC1.close();
	TRANS_LOC2.close();
	TRANS_IN1.close();
	TRANS_IN2.close();
	TRANS_LOC1.clear();
	TRANS_LOC2.clear();
	TRANS_IN1.clear();
	TRANS_IN2.clear();
}

int main(int   argc, char*   argv[])
{
	srand((unsigned int)time(0));
	ifstream reference;
	simulate simulate1;
	parameters parameter1;
	char buffer[1024] = { 0 };
	
	
	//get parameters
	simulate1.get_parameters(argc, argv, parameter1);
	somatic_ref1="./Results/somatic_ref1.fa";
	somatic_ref2="./Results/somatic_ref2.fa";
	if(((parameter1.infile_s==0)||(parameter1.infile_s==1))&&((parameter1.infile_i==0)||(parameter1.infile_i==1))&&((parameter1.infile_t==0)||(parameter1.infile_t==1))&&((parameter1.infile_c==0)||(parameter1.infile_c==1))&&((parameter1.infile_I==0)||(parameter1.infile_I==1))&&((parameter1.infile_T==0)||(parameter1.infile_T==1)))
	{
		sprintf(buffer,"cp %s %s",parameter1.infile_ref.c_str(),somatic_ref1.c_str());system(buffer);
		sprintf(buffer,"cp %s %s",parameter1.infile_ref.c_str(),somatic_ref2.c_str());system(buffer);
	}
	//cout<<parameter1.infile_s<<parameter1.infile_i<<parameter1.infile_t<<parameter1.infile_c<<parameter1.infile_I<<parameter1.infile_T<<endl;
	
	//germline simulation
	cout<<"**************************Germline simulation**************************"<<endl<<endl;
	if((parameter1.infile_s==0)||(parameter1.infile_s==1))
	{
		parameter1.SNP1="./Results/germline_snp1.fa";
		parameter1.SNP2="./Results/germline_snp2.fa";
		sprintf(buffer,"cp %s ./Results/germline_snp1.fa",parameter1.infile_ref.c_str());
		system(buffer);
		sprintf(buffer,"cp %s ./Results/germline_snp2.fa",parameter1.infile_ref.c_str());
		system(buffer);
	}
	else
	{
		simulate1.germline_SNP(parameter1);	//Genome OK
		somatic_ref1=parameter1.SNP1;somatic_ref2=parameter1.SNP2;
	}
	if((parameter1.infile_i==0)||(parameter1.infile_i==1))
	{
		parameter1.INDEL1="./Results/germline_indel1.fa";
		parameter1.INDEL2="./Results/germline_indel2.fa";
		sprintf(buffer,"cp %s %s",parameter1.SNP1.c_str(),parameter1.INDEL1.c_str());
		system(buffer);
		sprintf(buffer,"cp %s %s",parameter1.SNP2.c_str(),parameter1.INDEL2.c_str());
		system(buffer);
	}
	else
	{
		simulate1.Indels(parameter1);	//Genome OK
		somatic_ref1=parameter1.INDEL1;somatic_ref2=parameter1.INDEL2;
	}
	if((parameter1.infile_s==0)||(parameter1.infile_s==1)){system("rm ./Results/germline_snp1.fa");system("rm ./Results/germline_snp2.fa");}
	if((parameter1.infile_t==0)||(parameter1.infile_t==1))
	{
		parameter1.TAND1="./Results/germline_tand1.fa";
		parameter1.TAND2="./Results/germline_tand2.fa";
		sprintf(buffer,"cp %s %s",parameter1.INDEL1.c_str(),parameter1.TAND1.c_str());
		system(buffer);
		sprintf(buffer,"cp %s %s",parameter1.INDEL2.c_str(),parameter1.TAND2.c_str());
		system(buffer);
	}
	else
	{
		simulate1.tanddup(parameter1);	//Genome OK
		somatic_ref1=parameter1.TAND1;somatic_ref2=parameter1.TAND2;
	}
	if((parameter1.infile_i==0)||(parameter1.infile_i==1)){system("rm ./Results/germline_indel1.fa");system("rm ./Results/germline_indel2.fa");}
	if((parameter1.infile_c==0)||(parameter1.infile_c==1))
	{
		parameter1.CNV1="./Results/germline_cnv1.fa";
		parameter1.CNV2="./Results/germline_cnv2.fa";
		sprintf(buffer,"cp %s %s",parameter1.TAND1.c_str(),parameter1.CNV1.c_str());
		system(buffer);
		sprintf(buffer,"cp %s %s",parameter1.TAND2.c_str(),parameter1.CNV2.c_str());
		system(buffer);
	}
	else
	{
		simulate1.copy_no_variation(parameter1);	//Genome OK
		somatic_ref1=parameter1.CNV1;somatic_ref2=parameter1.CNV2;
	}
	if((parameter1.infile_t==0)||(parameter1.infile_t==1)){system("rm ./Results/germline_tand1.fa");system("rm ./Results/germline_tand2.fa");}
	if((parameter1.infile_I==0)||(parameter1.infile_I==1))
	{
		parameter1.INVER1="./Results/germline_inver1.fa";
		parameter1.INVER2="./Results/germline_inver2.fa";
		sprintf(buffer,"cp %s %s",parameter1.CNV1.c_str(),parameter1.INVER1.c_str());
		system(buffer);
		sprintf(buffer,"cp %s %s",parameter1.CNV2.c_str(),parameter1.INVER2.c_str());
		system(buffer);
	}
	else
	{
		simulate1.invertions(parameter1);	//Genome OK
		somatic_ref1=parameter1.INVER1;somatic_ref2=parameter1.INVER2;
	}
	if((parameter1.infile_c==0)||(parameter1.infile_c==1)){system("rm ./Results/germline_cnv1.fa");system("rm ./Results/germline_cnv2.fa");}
	if((parameter1.infile_T==0)||(parameter1.infile_T==1)){}
	else
	{
		simulate1.translocation(parameter1);
		somatic_ref1=parameter1.TRANS1;somatic_ref2=parameter1.TRANS2;
	}
	if((parameter1.infile_I==0)||(parameter1.infile_I==1)){system("rm ./Results/germline_inver1.fa");system("rm ./Results/germline_inver2.fa");}
	
	//somatic simulation
	for(int nt=0;nt<parameter1.infile_Nt;nt++)
	{
		cout<<endl<<"**************************Tumor"<<(nt+1)<<" simulation****************************"<<endl<<endl;
		somatic_flag=1;
		tumor_flag=nt+1;
		if((parameter1.infile_s==0)||(parameter1.infile_s==2))
		{
			sprintf(buffer,"./Results/tumor%d_snp1.fa",tumor_flag);
			parameter1.SNP1=buffer;
			sprintf(buffer,"./Results/tumor%d_snp2.fa",tumor_flag);
			parameter1.SNP2=buffer;
			sprintf(buffer,"cp %s %s",somatic_ref1.c_str(),parameter1.SNP1.c_str());
			system(buffer);
			sprintf(buffer,"cp %s %s",somatic_ref2.c_str(),parameter1.SNP2.c_str());
			system(buffer);
		}
		else
		{
			simulate1.somatic_SNP(parameter1);	//Genome OK
		}
		//cout<<somatic_ref1<<endl<<parameter1.SNP1<<endl<<somatic_ref2<<endl<<parameter1.SNP2<<endl;
		
		if((parameter1.infile_i==0)||(parameter1.infile_i==2))
		{
			sprintf(buffer,"./Results/tumor%d_indel1.fa",tumor_flag);
			parameter1.INDEL1=buffer;
			sprintf(buffer,"./Results/tumor%d_indel2.fa",tumor_flag);
			parameter1.INDEL2=buffer;
			sprintf(buffer,"cp %s %s",parameter1.SNP1.c_str(),parameter1.INDEL1.c_str());
			system(buffer);
			sprintf(buffer,"cp %s %s",parameter1.SNP2.c_str(),parameter1.INDEL2.c_str());
			system(buffer);
		}
		else
		{
			simulate1.Indels(parameter1);	//Genome OK
		}
		if((parameter1.infile_s==0)||(parameter1.infile_s==2)){sprintf(buffer,"rm ./Results/tumor%d_snp1.fa",tumor_flag);system(buffer);sprintf(buffer,"rm ./Results/tumor%d_snp2.fa",tumor_flag);system(buffer);}
		if((parameter1.infile_t==0)||(parameter1.infile_t==2))
		{
			sprintf(buffer,"./Results/tumor%d_tand1.fa",tumor_flag);
			parameter1.TAND1=buffer;
			sprintf(buffer,"./Results/tumor%d_tand2.fa",tumor_flag);
			parameter1.TAND2=buffer;
			sprintf(buffer,"cp %s %s",parameter1.INDEL1.c_str(),parameter1.TAND1.c_str());
			system(buffer);
			sprintf(buffer,"cp %s %s",parameter1.INDEL2.c_str(),parameter1.TAND2.c_str());
			system(buffer);
		}
		else
		{
			simulate1.tanddup(parameter1);	//Genome OK
		}
		if((parameter1.infile_i==0)||(parameter1.infile_i==2)){sprintf(buffer,"rm ./Results/tumor%d_indel1.fa",tumor_flag);system(buffer);sprintf(buffer,"rm ./Results/tumor%d_indel2.fa",tumor_flag);system(buffer);}
		if((parameter1.infile_c==0)||(parameter1.infile_c==2))
		{
			sprintf(buffer,"./Results/tumor%d_cnv1.fa",tumor_flag);
			parameter1.CNV1=buffer;
			sprintf(buffer,"./Results/tumor%d_cnv2.fa",tumor_flag);
			parameter1.CNV2=buffer;
			sprintf(buffer,"cp %s %s",parameter1.TAND1.c_str(),parameter1.CNV1.c_str());
			system(buffer);
			sprintf(buffer,"cp %s %s",parameter1.TAND2.c_str(),parameter1.CNV2.c_str());
			system(buffer);
		}
		else
		{
			simulate1.copy_no_variation(parameter1);	//Genome OK
		}
		//if(parameter1.infile_t==0){system("rm ./Results/somatic_tand1.fa");system("rm ./Results/somatic_tand2.fa");}
		if((parameter1.infile_t==0)||(parameter1.infile_t==2)){sprintf(buffer,"rm ./Results/tumor%d_tand1.fa",tumor_flag);system(buffer);sprintf(buffer,"rm ./Results/tumor%d_tand2.fa",tumor_flag);system(buffer);}
		if((parameter1.infile_I==0)||(parameter1.infile_I==2))
		{
			sprintf(buffer,"./Results/tumor%d_inver1.fa",tumor_flag);
			parameter1.INVER1=buffer;
			sprintf(buffer,"./Results/tumor%d_inver2.fa",tumor_flag);
			parameter1.INVER2=buffer;
			sprintf(buffer,"cp %s %s",parameter1.CNV1.c_str(),parameter1.INVER1.c_str());
			system(buffer);
			sprintf(buffer,"cp %s %s",parameter1.CNV2.c_str(),parameter1.INVER2.c_str());
			system(buffer);
		}
		else
		{
			simulate1.invertions(parameter1);	//Genome OK
		}
		//if(parameter1.infile_c==0){system("rm ./Results/somatic_cnv1.fa");system("rm ./Results/somatic_cnv2.fa");}
		if((parameter1.infile_c==0)||(parameter1.infile_c==2)){sprintf(buffer,"rm ./Results/tumor%d_cnv1.fa",tumor_flag);system(buffer);sprintf(buffer,"rm ./Results/tumor%d_cnv2.fa",tumor_flag);system(buffer);}
		if((parameter1.infile_T==0)||(parameter1.infile_T==2)){}
		else
		{
			simulate1.translocation(parameter1);
		}
		//if(parameter1.infile_I==0){system("rm ./Results/somatic_inver1.fa");system("rm ./Results/somatic_inver2.fa");}
		if((parameter1.infile_I==0)||(parameter1.infile_I==2)){sprintf(buffer,"rm ./Results/tumor%d_inver1.fa",tumor_flag);system(buffer);sprintf(buffer,"rm ./Results/tumor%d_inver2.fa",tumor_flag);system(buffer);}
	}
	if(((parameter1.infile_s==0)||(parameter1.infile_s==1))&&((parameter1.infile_i==0)||(parameter1.infile_i==1))&&((parameter1.infile_t==0)||(parameter1.infile_t==1))&&((parameter1.infile_c==0)||(parameter1.infile_c==1))&&((parameter1.infile_I==0)||(parameter1.infile_I==1))&&((parameter1.infile_T==0)||(parameter1.infile_T==1)))
		{
			system("rm ./Results/somatic_ref1.fa");
			system("rm ./Results/somatic_ref2.fa");
		}

	return 0;
}


