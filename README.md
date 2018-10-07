SVSR:a Program to Simulate Structural Variations and Generate Sequence Reads for Multiple Platforms
===================================================================================================

Contents
--------
1.Tools

2.Usage




1.Tools
--------

1.1 gc_content:this tool is used to compute gc content for genome(usage:./gc_content -infile_fa <test.fa>)



2.Usage: sh SVSR.sh
--------------------


2.1 simulation: ./sim [parameter1] [value1].............

parameters:
	-infile_ref(Required)
        -infile_s(Optional Default=0)	##0,1,2,3  0=00=no germline and no somatic,1=01=no germline but with somatic,2=10=germline but no somatic,3=11=germline and somatic
        -infile_i(Optional Default=0)	##0,1,2,3  0=00=no germline and no somatic,1=01=no germline but with somatic,2=10=germline but no somatic,3=11=germline and somatic
        -infile_t(Optional Default=0)	##0,1,2,3  0=00=no germline and no somatic,1=01=no germline but with somatic,2=10=germline but no somatic,3=11=germline and somatic
        -infile_c(Optional Default=0)	##0,1,2,3  0=00=no germline and no somatic,1=01=no germline but with somatic,2=10=germline but no somatic,3=11=germline and somatic
        -infile_I(Optional Default=0)	##0,1,2,3  0=00=no germline and no somatic,1=01=no germline but with somatic,2=10=germline but no somatic,3=11=germline and somatic
        -infile_T(Optional Default=0)	##0,1,2,3  0=00=no germline and no somatic,1=01=no germline but with somatic,2=10=germline but no somatic,3=11=germline and somatic
        -infile_snp_rate(Optional Default="./Datas/SNP_rate.txt")	##you can replace it whit your snp rate file
        -infile_ts(Optional Default=0.5)				##transition rate in snp
        -infile_very_short_rate(Optional Default=0.6)			##rate of very short snp(1~9bp)
        -infile_short_rate(Optional Default=0.3)			##rate of short snp(10~40bp)
        -infile_large_rate(Optional Default=0.1)			##rate of large snp(41~10kbp)
        -infile_hes_rate(Optional Default=0.6)				##rate of heterozygous snp
        -infile_tumor(Optional Default=1)				##whether or not does somatic variations happen(1 is happen and 0 is not happen)
        -infile_Nt(Optional Default=1)					##the number of tumor
example:
	./sim -infile_ref reference.fa -infile_c 2 -infile_ts 0.55 -infile_hes_rate 0.61 -infile_Nt 2

2.2 reads generation
2.2.1 illumina
parameters:
	-infile_norm(Required)		##normal genome
	-infile_tumor(Required)		##tumor genome
	-infile_pe_se(Optional Default="p")	##pair-end or single end("p"|"s")
	-infile_gc_content(Required)		##gc content(it is generated by tools above mentioned)
	-infile_cov(Optional Default=5)		##coverage
	-infile_readlen(Optional Default=100)	##read length
	-infile_erate(Optional Default=1000000)	##error rate
	-infile_trate(Optional Default=1)	##tumor purity(0~1)
	-infile_sloap(Optional Default=3)	##(use coverage=s*gc_content+b to simulate gc bias)
	-infile_bloap(Optional Default=0.1)	##(use coverage=s*gc_content+b to simulate gc bias)
	-iterator(Optional Default=1)		##it is used to achieve the purpose of generating multiple groups of pair-end reads iteratively

example: 
	./illumina -infile_norm germline_cnv1.fa -infile_tumor tumor1_cnv1.fa \
	-infile_pe_se "p" -infile_gc_content "germline_cnv1.fa.gc_content" \
	-infile_cov  5 -infile_readlen 100 -infile_erate 10000000 -infile_trate 1 -iterator 1

2.2.2 solid
parameters:
	-infile_fa(Required)	##genome file
	-infile_pe_se(Optional Default="p")	##pair-end or single end("p"|"s")
	-infile_cov(Optional Default=5)		##coverage
	-infile_readlen(Optional Default=50)	##read length
	-infile_erate(Optional Default=1000000) ##error rate
example:
	./solid -infile_fa ./Datas/a.fa -infile_pe_se p -infile_cov 1 -infile_readlen 50 -infile_erate 1000000
	
2.2.3 ion torrent
parameters:
	-infile_fa(Required)	##genome file	
	-infile_pe_se(Optional Default="p")	##pair-end or single end("p"|"s")
	-infile_cov(Optional Default=5)		##coverage
	-infile_readlen(Optional Default=200)	##read length
	-infile_rstd(Optional Default=10)	##read length:(readlen-std) ~ (readlen+std)
	-infile_erate(Optional Default=1000000) ##error rate
example:
	./ion -infile_fa ./Datas/a.fa -infile_pe_se p -infile_cov 5 -infile_readlen 50 -infile_erate 1000000
2.2.4 454
parameters:
	-infile_fa(Required)	##genome file	
	-infile_pe_se(Optional Default="p")	##pair-end or single end("p"|"s")
	-infile_cov(Optional Default=5)		##coverage
	-infile_readlen(Optional Default=140)	##read length
	-infile_rstd(Optional Default=5)	##read length:(readlen-std) ~ (readlen+std)
	-infile_erate(Optional Default=1000000) ##error rate
example:
	./g454 -infile_fa ./Datas/a.fa -infile_pe_se p -infile_cov 5 -infile_readlen 140 -infile_rstd 5 -infile_erate 1000000
    

