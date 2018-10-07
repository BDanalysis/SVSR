#parameters
path="/home/gmh/Documents/SVSR_TCBB/SVSR"		#this is your software's dictionary and you should change it
cd $path
my_sequencer="illumina"		#illumina,solid,454,ion
my_infile_ref="./Datas/reference.fa"
my_infile_s="0"			#0,1,2,3  0=00=no germline and no somatic,1=01,2=10,3=11=germline and somatic
my_infile_i="0"			#0,1,2,3  00,01,10,11
my_infile_t="0"			#0,1,2,3  00,01,10,11
my_infile_c="3"			#0,1,2,3  00,01,10,11
my_infile_I="0"			#0,1,2,3  00,01,10,11
my_infile_T="0"			#0,1,2,3  00,01,10,11
my_infile_ts="0.55"
my_infile_hes_rate="0.288"
my_infile_Nt="2"

my_infile_pe_se="p"
my_infile_readlen="100"
my_infile_cov1="5"
my_infile_cov2="10"
my_infile_cov3="20"
my_infile_cov4="40"
my_infile_erate="10000"
my_infile_nthreads="1"
my_infile_trate="0.8"
my_infile_gc_content="./Datas/reference.fa.gc_content"


#sequencing function
Illumina(){
for j in $(seq 1 1)
do
echo "iterator ${j}"
./illumina -infile_norm $my_infile_ref -infile_tumor $my_infile_ref \
-infile_pe_se $my_infile_pe_se -infile_gc_content $my_infile_gc_content \
-infile_cov  $my_infile_cov1 -infile_readlen $my_infile_readlen -infile_nthreads \
$my_infile_nthreads -infile_erate $my_infile_erate -infile_trate $my_infile_trate -iterator ${j}

done
}

solid(){
./solid -infile_fa ./Datas/a.fa -infile_pe_se p -infile_cov 1 -infile_readlen 50 -infile_erate 1000000
}

ion(){
./ion -infile_fa ./Datas/a.fa -infile_pe_se p -infile_cov 5 -infile_readlen 50 -infile_erate 1000000
}

g454()
{
./g454 -infile_fa ./Datas/a.fa -infile_pe_se p -infile_cov 5 -infile_readlen 140 -infile_rstd 5 -infile_erate 1000000
}



#Main
#1.Simulation
./sim -infile_ref $my_infile_ref -infile_s $my_infile_s -infile_i \
$my_infile_i -infile_t $my_infile_t -infile_c $my_infile_c -infile_I \
$my_infile_I -infile_T $my_infile_T  -infile_ts $my_infile_ts \
-infile_hes_rate $my_infile_hes_rate -infile_Nt $my_infile_Nt

#2.Sequencing
echo "\n**************************Sequencing************************************\n"
if [ $my_sequencer = "illumina" ]; then
Illumina
elif [ $my_sequencer = "solid" ]; then
solid
elif [ $my_sequencer = "ion" ]; then
ion
elif [ $my_sequencer = "454" ]; then
g454
else
echo "????????????Abnormal sequencing platform! "
exit
fi
echo "\n************************************************************************"
