CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2
TARGETS  = FA_best_fit FA_first_fit FA_next_fit FA_worst_fit \
           PS_FIFO PS_Shortest_Job_first PS_Roundrobin \
           PS_Shortest_remaining

all: $(TARGETS)

.PHONY: all clean pdf

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

pdf:
	tectonic os_lab_report.tex

clean:
	rm -f $(TARGETS)

