export WEBKIT_OUTPUTDIR=optfuzz_build
rm -rf optfuzz_build
./Tools/Scripts/build-jsc --jsc-only --debug --cmakeargs="-DENABLE_STATIC_JSC=ON -DCMAKE_C_COMPILER='/home/wjm/llvm-project-14.0.1.src/modified-build/bin/clang' -DCMAKE_CXX_COMPILER='/home/wjm/llvm-project-14.0.1.src/modified-build/bin/clang++' -DCMAKE_CXX_FLAGS='-fsanitize-coverage=trace-pc-guard  -std=c++17   -O0'"
