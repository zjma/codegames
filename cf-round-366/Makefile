%.exe: %.cpp
	g++.exe -o $@ $^ -static -DONLINE_JUDGE -s -x c++ -Wl,--stack=268435456 -O2 -std=c++11 -D__USE_MINGW_ANSI_STDIO=0 -U__STRICT_ANSI__ -D__NO_INLINE__

clean:
	rm *.exe *.out -rf
