#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> split_string(string);


// Complete the solve function below.
string solve(int x, int y, int r, vector<int> t1, vector<int> t2, vector<int> t3) 
{
	vector<vector<int>> point(3);
	point[0] = t1;
	point[1] = t2;
	point[2] = t3;
	
	for (int i = 0; i < 3; i++)
	{
		point[i][0] -= x;
		point[i][1] -= y;
	}
	for (int i = 0; i < 3; i++)
	{
		long long x1 = point[i][0];
		long long x2 = point[(i + 1) % 3][0];
		long long y1 = point[i][1];
		long long y2 = point[(i + 1) % 3][1];
		long long A = y2 - y1;
		long long B = x1 - x2;
		long long C = y1 * (x2 - x1) - x1 * (y2 - y1);
		if (A != 0)
		{
			long double a = A * A + B * B;
			long double b = 2 * B * C;
			long double c = C * C - A * A * r * r;
			long double discriminant = b * b - 4 * a * c;
			if (discriminant < 0)
				continue;
			double yInter1 = (-b + sqrt(discriminant)) / (2 * a);
			double yInter2 = (-b - sqrt(discriminant)) / (2 * a);
			if ((yInter1 >= y1 && yInter1 <= y2) || (yInter1 >= y2 && yInter1 <= y1))
				return "YES";
			else if((yInter2 >= y1 && yInter2 <= y2) || (yInter2 >= y2 && yInter2 <= y1))
				return "YES";
		}
		else
		{
			long double a = B * B;
			long double c = C * C - B * B * r * r;
			if (c > 0)
				continue;
			double xInter1 = sqrt(- c / a);
			double xInter2 = - sqrt(- c / a);
			if ((xInter1 >= x1 && xInter1 <= x2) || (xInter1 >= x2 && xInter1 <= x1))
				return "YES";
			else if ((xInter2 >= x1 && xInter2 <= x2) || (xInter2 >= x2 && xInter2 <= x1))
				return "YES";
		}
	}
	return "NO";
}

int main()
{
	ofstream fout("OUTPUT_PATH1.txt");
	ifstream fin("input01.txt");
	int t;
	fin >> t;
	fin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int t_itr = 0; t_itr < t; t_itr++) {
		string xyr_temp;
		getline(fin, xyr_temp);

		vector<string> xyr = split_string(xyr_temp);

		int x = stoi(xyr[0]);

		int y = stoi(xyr[1]);

		int r = stoi(xyr[2]);

		string t1_temp_temp;
		getline(fin, t1_temp_temp);

		vector<string> t1_temp = split_string(t1_temp_temp);

		vector<int> t1(2);

		for (int i = 0; i < 2; i++) {
			int t1_item = stoi(t1_temp[i]);

			t1[i] = t1_item;
		}

		string t2_temp_temp;
		getline(fin, t2_temp_temp);

		vector<string> t2_temp = split_string(t2_temp_temp);

		vector<int> t2(2);

		for (int i = 0; i < 2; i++) {
			int t2_item = stoi(t2_temp[i]);

			t2[i] = t2_item;
		}

		string t3_temp_temp;
		getline(fin, t3_temp_temp);

		vector<string> t3_temp = split_string(t3_temp_temp);

		vector<int> t3(2);

		for (int i = 0; i < 2; i++) {
			int t3_item = stoi(t3_temp[i]);

			t3[i] = t3_item;
		}

		string result = solve(x, y, r, t1, t2, t3);

		fout << result << "\n";
	}

	fout.close();

	return 0;
}

vector<string> split_string(string input_string) {
	string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char& x, const char& y) {
		return x == y and x == ' ';
		});

	input_string.erase(new_end, input_string.end());

	while (input_string[input_string.length() - 1] == ' ') {
		input_string.pop_back();
	}

	vector<string> splits;
	char delimiter = ' ';

	size_t i = 0;
	size_t pos = input_string.find(delimiter);

	while (pos != string::npos) {
		splits.push_back(input_string.substr(i, pos - i));

		i = pos + 1;
		pos = input_string.find(delimiter, i);
	}

	splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

	return splits;
}
