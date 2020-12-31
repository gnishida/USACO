#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;


class BinarySearchStack {
public:
	BinarySearchStack() {}

	void push(int val) {
		data.push_back(val);
	}

	int pop() {
		int ret = data.back();
		data.pop_back();
		return ret;
	}

	size_t size() {
		return data.size();
	}

	int upperBound(int query) {
		if (data.size() == 0) return 0;
		return binarySearch(0, data.size() - 1, query);
	}

private:
	int binarySearch(int left, int right, int query) {
		if (left == right) {
			if (query < data[left]) return left;
			else return left + 1;
		}

		int mid = (left + right) / 2;
		if (query <= data[mid]) {
			return binarySearch(left, mid, query);
		} else {
			return binarySearch(mid + 1, right, query);
		}
	}

private:
	vector<int> data;
};


int main() {
	ifstream in("dishes.in");
	int N;
	in >> N;

	vector<stack<int>> soapyDishes;
	BinarySearchStack bottomSoapyDishes;
	int maxCleanedDish = 0;

	int ans = 0;
	for (int i = 0; i < N; i++) {
		int a;
		in >> a;

		if (a < maxCleanedDish) {
			// If the next dirty dish is smaller than the cleaned dish,
			// stop here!
			break;
		}
		
		// Find which stack to place the next dirty dish
		int index = bottomSoapyDishes.upperBound(a);
		if (index >= bottomSoapyDishes.size()) {
			// Add a new stack
			bottomSoapyDishes.push(a);
			soapyDishes.push_back(stack<int>());

			// Place the dirty dish on top of the stack
			soapyDishes[index].push(a);
		} else {
			// Pop the smaller dishes out of the stack
			while (a > soapyDishes[index].top()) {
				maxCleanedDish = soapyDishes[index].top();
				soapyDishes[index].pop();
			}

			// Place the dirty dish on top of the stack
			soapyDishes[index].push(a);
		}

		ans++;
	}

	ofstream out("dishes.out");
	out << ans << endl;

	return 0;
}