#g++ simulation.cpp -o ../sim -lgsl -lgslcblas
#./sim -infile_ref hs_alt_CHM1_1.1_chr11.fa -infile_snp_rate SNP_rate.txt -infile_ts 0.55 -infile_hes_rate 0.288
#g++ illumina.cpp -o ../illumina -lgsl -lgslcblas -lpthread
#./illumina -infile_ref a.fa -infile_fa ./Results/germline_snp2.fa -infile_pf1 ./Datas/1.pf -infile_pf2 ./Datas/2.pf -infile_pe_se p -infile_cov 5 -infile_readlen 100 -infile_nthreads 4 -infile_erate 10000 -infile_trate 0.8
#g++ solid.cpp -o solid -lgsl -lgslcblas
#g++ ion.cpp -o ion -lgsl -lgslcblas
#g++ g454.cpp -o g454 -lgsl -lgslcblas
#

#parameters
path="/home/gmh/Documents/SVSR_TCBB/SVSR"
cd $path
my_sequencer="illumina"		#illumina,solid,454,ion
my_infile_ref="./Datas/reference.fa"
my_infile_s="3"			#0,1,2,3  0=00=no germline and no somatic,1=01,2=10,3=11=germline and somatic
my_infile_i="3"			#0,1,2,3  00,01,10,11
my_infile_t="3"			#0,1,2,3  00,01,10,11
my_infile_c="3"			#0,1,2,3  00,01,10,11
my_infile_I="3"			#0,1,2,3  00,01,10,11
my_infile_T="3"			#0,1,2,3  00,01,10,11
my_infile_snp_rate="./Datas/SNP_rate.txt"
my_infile_ts="0.55"
my_infile_hes_rate="0.288"
my_infile_cnv_rate=""
my_infile_inv_rate1=""
my_infile_inv_rate2=""
my_infile_td_no1=""
my_infile_td_no2=""
my_infile_tumor=""
my_infile_Nt="2"

my_infile_pe_se="p"
my_infile_readlen="100"
my_infile_cov1="5"
my_infile_cov2="10"
my_infile_cov3="5"
my_infile_cov4="20"
my_infile_erate="10000"
my_infile_nthreads="8"
my_infile_trate="0.8"
my_infile_pf1="./Datas/1.pf"
my_infile_pf2="./Datas/2.pf"
my_infile_gc_content="./Datas/reference.fa.gc_content"


#sequencing function
Illumina(){
for j in $(seq 1 50)
do
echo "iterator ${j}"
./illumina -infile_norm $my_infile_ref -infile_tumor $my_infile_ref -infile_pf1 $my_infile_pf1 -infile_pf2 $my_infile_pf2 -infile_pe_se $my_infile_pe_se -infile_gc_content $my_infile_gc_content -infile_cov $my_infile_cov2 -infile_readlen $my_infile_readlen -infile_nthreads $my_infile_nthreads -infile_erate $my_infile_erate -infile_trate $my_infile_trate -iterator ${j}

done
}

solid(){
for j in $(seq 1 1)
do

./illumina -infile_ref ./Results/germline_trans1.fa -infile_fa ./Results/tumor1_trans1.fa -infile_pf1 ./Datas/1.pf -infile_pf2 ./Datas/2.pf -infile_pe_se p -infile_cov 5 -infile_readlen 100 -infile_nthreads 4 -infile_erate 10000 -infile_trate 0.8 -iterator ${j}

done
}

g454(){
for j in $(seq 1 1)
do

./illumina -infile_ref ./Results/germline_trans1.fa -infile_fa ./Results/tumor1_trans1.fa -infile_pf1 ./Datas/1.pf -infile_pf2 ./Datas/2.pf -infile_pe_se p -infile_cov 5 -infile_readlen 100 -infile_nthreads 4 -infile_erate 10000 -infile_trate 0.8 -iterator ${j}

done
}

ion(){
for j in $(seq 1 1)
do

./illumina -infile_ref ./Results/germline_trans1.fa -infile_fa ./Results/tumor2_trans1.fa -infile_pf1 ./Datas/1.pf -infile_pf2 ./Datas/2.pf -infile_pe_se p -infile_cov 5 -infile_readlen 100 -infile_nthreads 4 -infile_erate 10000 -infile_trate 0.8 -iterator ${j}

done
}




#Main
#1.Simulation
#./sim -infile_ref $my_infile_ref -infile_s $my_infile_s -infile_i $my_infile_i -infile_t $my_infile_t -infile_c $my_infile_c -infile_I $my_infile_I -infile_T $my_infile_T -infile_snp_rate  $my_infile_snp_rate -infile_ts $my_infile_ts -infile_hes_rate $my_infile_hes_rate -infile_Nt $my_infile_Nt

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
