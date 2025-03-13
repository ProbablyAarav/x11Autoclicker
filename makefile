CXX = g++
CXXFLAGS = -Wall -Wextra -O2
LDFLAGS = -lX11
SRC = autoclick.cpp
OUT = autoclick
all: $(OUT)
$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)
clean:
	rm -f $(OUT)
