

# redis:9067, in FuzzilliCli/TerminalUI.swift and libcoverage/coverage.c
# path recording OptPath in libcoverage/coverage.c:  /home/wjm/paper_optfuzz/data/optfuzz_path


#swift build -c debug -Xlinker='-lrt' -Xlinker='-lhiredis'
swift run -c debug -Xlinker='-lrt' -Xlinker='-lhiredis' FuzzilliCli --jobs=10 --profile=jsc --overwrite --storagePath=./out /home/wjm/paper_optfuzz/target/webkit_for_optfuzz/optfuzz_build/Debug/bin/jsc