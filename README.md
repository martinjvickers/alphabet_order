
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

