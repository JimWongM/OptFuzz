# OptFuzz
OptFuzz: Optimization Path Guided Fuzzing for JavaScript JIT Compilers (Usenix Security 2024)

## 1.Compile Clang-14

Download [LLVM-14 source code](https://releases.llvm.org/download.html).

Replace ```llvm/lib/Transforms/Instrumentation/SanitizerCoverage.cpp``` with ```llvm-14/SanitizerCoverage.cpp``` in this repository. 

Modify the path of ```sancov.txt``` in ```llvm-14/SanitizerCoverage.cpp```.

Compile LLVM, you can use the shell commands in ```llvm-14/run.sh```. 

## 2.Install hiredis

Optfuzz use ```redis``` to record the number of OptPath, so we need install ```hiredis``` before run OptFuzz. 

```
# install redis-server
sudo apt install redis

# install hiredis
git clone git@github.com:redis/hiredis.git
cd hiredis
make 
make install
cp libhiredis.so /usr/lib64 /usr/lib 
/sbin/ldconfig
```

Redis is used in ```optfuzz/FuzzilliCli/TerminalUI.swift``` and ```optfuzz/libcoverage/coverage.c```.

## 3.Build JavaScritCore

Build JSC with ```webkit_for_optfuzz/run.sh```, specify the clang path to the path compiled in the first step.

> JSC commit id: 7e485991f408cd0d38734297936fc449c260fc2f


## 4.Build OptFuzz

Build:
```
swift build -c debug -Xlinker='-lrt' -Xlinker='-lhiredis'
```

Please Modify the path of ```data/optfuzz_path``` in ```optfuzz/libcoverage/coverage.c``` and ```webkit_for_optfuzz/Source/JavaScriptCore/jsc.cpp```

Run:
```
swift run -c debug -Xlinker='-lrt' -Xlinker='-lhiredis' FuzzilliCli --jobs=10 --profile=jsc --overwrite --storagePath=./out ../webkit_for_optfuzz/optfuzz_build/Debug/bin/jsc
```
