
## alphabet_order

Description of alphabet_order

### Compiling

Getting this to compile on work machine;

```
~/cmake-3.6.0-rc2-Linux-x86_64/bin/cmake ../alphabet_order \
   -DCMAKE_MODULE_PATH=../seqan/util/cmake \
   -DSEQAN_INCLUDE_PATH=../seqan/include \
   -DCMAKE_CXX_FLAGS=-std=c++14 \
   -DCMAKE_BUILD_TYPE=Release \
   -DCMAKE_CXX_ARGS="-DSEQAN_DISABLE_VERSION_CHECK=YES" 
```

### Running

