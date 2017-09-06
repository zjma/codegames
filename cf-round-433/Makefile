%.exe: %.cpp
	g++.exe -g -o $@ $^ -static -DONLINE_JUDGE -s -x c++ -Wl,--stack=268435456 -O2 -std=c++11 -D__USE_MINGW_ANSI_STDIO=0 -D__NO_INLINE__ -U__STRICT_ANSI__

clean:
	rm *.exe *.out -rf
