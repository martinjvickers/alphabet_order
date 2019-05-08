
## alphabet_order

Description of alphabet_order

### Compiling

Getting this to compile on work machine;

```
sudo apt-get install build-essential git cmake
git clone https://github.com/martinjvickers/alphabet_order
git clone https://github.com/seqan/seqan
cd alphabet_order
cmake ../alphabet_order \
   -DCMAKE_MODULE_PATH=../seqan/util/cmake \
   -DSEQAN_INCLUDE_PATH=../seqan/include \
   -DCMAKE_CXX_FLAGS=-std=c++14 \
   -DCMAKE_BUILD_TYPE=Release \
   -DCMAKE_CXX_ARGS="-DSEQAN_DISABLE_VERSION_CHECK=YES" 
make
```


### Running

```
./alphabet_order -i example_data/test.fasta.gz
```

### Output

The output looks like this. For each contig in the fasta file it will calculate each lyndon word for every order of AGCT using the duval algorithm. If the lyndon word is < 101bp then it will print it out, otherwise it will skip it and just show the length of the word.

```
Number of factors new for Chr1 
A < C < G < T <  factors: 6
######### F-0	4
CCCT
######### F-1	99
AAACCCTAAACCCTAAACCCTAAACCTCTGAATCCTTAATCCCTAAATCCCTAAATCTTTAAATCCTACATCCATGAATCCCTAAATACCTAATTCCCT
######### F-2	26
AAACCCGAAACCGGTTTCTCTGGTTG
######### F-3	71
AAAATCATTGTGTATATAATGATAATTTTATCGTTTTTATGTAATTGCTTATTGTTGTGTGTAGATTTTTT
######### F-4	430
```
