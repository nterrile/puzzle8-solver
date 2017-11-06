#include "Puzzle8Solver.h"
#include "Puzzle8State.h"
#include "Puzzle8StateManager.h"
#include <vector>
#include <queue>
#include <iostream>
#include <utility>

using namespace std;

void WeightedAStar(std::string puzzle, double w, int & cost, int & expansions) {
	cost = 0;
	expansions = 0;
	std::vector<Puzzle8State> states;
	Puzzle8StateManager manager;
	auto comp = [](std::pair<int, double> left, std::pair<int, double> right){
		return left.second > right.second;
	};
	std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, 
		decltype(comp)> orderedStates(comp);

	states.push_back(Puzzle8State(puzzle, 0));
	manager.GenerateState(states[0]);
	std::pair<int, double> next(0, w * states[0].GetHeuristic());


	while (!states[next.first].GetHeuristic() == 0) {

		std::vector<std::string> successors = states[next.first].GetSuccessors();
		expansions++;
		for (int i = 0; i < successors.size(); i++) {
			Puzzle8State newState(successors[i], states[next.first].GetG() + 1);
			if (!manager.IsGenerated(newState)) {
				states.push_back(newState);
			}
			int index = manager.GenerateState(newState);
			if (!states[index].IsClosed()) {
				orderedStates.push(std::pair<int, double>(index, 
					newState.GetG() + (w * newState.GetHeuristic())));
			}
		}

		while (states[next.first].IsClosed()) {
			next = orderedStates.top();
			orderedStates.pop();
			//std::cout << next.first << " " << next.second << std::endl;
		}
	}

	cost = states[next.first].GetG();
}

