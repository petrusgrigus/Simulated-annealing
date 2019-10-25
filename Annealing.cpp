#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <random>
#include <iomanip>
#include <math.h>

using namespace std;
typedef long double ld;
const int ITER = 30000;
const ld TEMP = 100;

vector<int> board;
int n;

int ranking() {
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (j - i == abs(board[j] - board[i])) ++cnt;
		}
	}
	return cnt;
}

int main() {
	cin >> n;

	random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> rnd(0, n - 1);
    uniform_int_distribution<mt19937::result_type> big(0, 1e9);

	for (int i = 0; i < n; ++i) board.push_back(i);

	for (int i = 0; i < ITER; ++i) {
		ld T = TEMP / i;
		int rank = ranking();

		int pos1 = rnd(rng);
		int pos2 = rnd(rng);
		if (pos1 == pos2) continue;

		swap(board[pos1], board[pos2]);
		int new_rank = ranking();
		if (new_rank < rank) continue;

		ld h = exp((rank-new_rank) / T);
		if ((big(rng)) > h * 1e9) {
			swap(board[pos1], board[pos2]);
		}

	}
	for (int i = 0; i < n; ++i) {
		cout << board[i] + 1 << " ";
	}
	cout << "\n";

	/*for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (board[i] == j) cout << "Q";
			else cout << ".";
		}
		cout << "\n";
	}*/
}
