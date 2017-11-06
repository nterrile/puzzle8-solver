#ifndef STATE_8_PUZZLE_H
#define STATE_8_PUZZLE_H

#include <string>
#include <cassert>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

// Represents an 8-puzzle state as a 3x3 array of chars. Each char can take values in range '0'-'9' (chars, not integers).
// '0' represents the blank tile.
// Provides GetKey to uniquely represent the puzzle as an integer (for hashing).
// You can extend this class to generate successors and get heuristic distance to '012345678', which is always the goal state.

class Puzzle8State {
public:
	Puzzle8State(std::string s = "012345678", int dist = 0) {
		assert(s.length() == 9);
		for (int r = 0; r < 3; r++)
			for (int c = 0; c < 3; c++)
				tiles[r][c] = s[r*3 + c];
		closed = false;
		g = dist;
	}

	// Key generated as an integer for the hash function in Puzzle8StateManager.
	int GetKey() {
		int key = 0;
		for (int r = 0; r < 3; r++)
			for (int c = 0; c < 3; c++)
				key = key*10 + int(tiles[r][c] - '0');
		return key;
	}

	// Return the linearized form as a string. (You don't need to use this.)
	std::string GetLinearizedForm () {
		std::string s = "";
		for (int r = 0; r < 3; r++)
			for (int c = 0; c < 3; c++)
				s += tiles[r][c];
		return s;
	}

	// Print the puzzle in a 3x3 layout. (You don't need to use this.)
	void Print(std::ostream & out = std::cout) {
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				out<<tiles[r][c]<<" ";
			}
			out<<std::endl;
		}
		out<<GetKey()<<std::endl;
	}

	int GetHeuristic() {
		int distance = 0;
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				int tile = int(tiles[r][c] - '0');
				if (tile != 0) {
					int col = tile % 3;
					int row = (tile - col) / 3;
					distance += abs(row - r) + abs(col - c);
				}
			}
		}
		return distance;
	}

	int GetG() {
		return g;
	}

	std::vector<std::string> GetSuccessors() {
		std::vector<std::string> successors;
		int row;
		int col;
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				if (tiles[r][c] == '0') {
					row = r;
					col = c;
				}
			}
		}
		std::string p = GetLinearizedForm();
		if (row != 0) {
			std::string p1 = p;
			std::swap(p1[(3*row)+col], p1[(3*(row-1))+col]);
			successors.push_back(p1);
		}
		if (row != 2) {
			std::string p2 = p;
			std::swap(p2[(3*row)+col], p2[(3*(row+1))+col]);
			successors.push_back(p2);
		}
		if (col != 0) {
			std::string p3 = p;
			std::swap(p3[(3*row)+col], p3[(3*row)+col-1]);
			successors.push_back(p3);
		}
		if (col != 2) {
			std::string p4 = p;
			std::swap(p4[(3*row)+col], p4[(3*row)+col+1]);
			successors.push_back(p4);
		}
		closed = true;
		return successors;
	}

	bool IsClosed() {
		return closed;
	}

private:

	// tiles[r][c] is the tile (or blank) at row r (0-2) and column c (0-2)
	// 0th row is the top row, and 0th column is the leftmost column.
	char tiles[3][3];
	bool closed;
	int g;
};

#endif
