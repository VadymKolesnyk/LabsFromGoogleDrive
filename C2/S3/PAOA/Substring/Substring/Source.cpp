#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

vector<string> findStrings(vector<string> w, vector<int> queries) 
{
	vector<string> result(queries.size());
	int size = 0;
	for (int i = 0; i < w.size(); i++)
	{
		size += (w[i].length() + 1);
	}
	vector<string> suffix(size);
	int k = 0;
	for (string word: w)
	{
		word += '$';
		vector<string> substrings(word.length());
		for (int i = 0; i < word.length(); i++)
		{
			for (int j = 0; j < word.length() - i; j++)
			{
				suffix[k] += word[i + j];
			}
			k++;
		}
	}
	sort(suffix.begin(), suffix.end());
	suffix.erase(unique(suffix.begin(), suffix.end()),suffix.end());
	vector<int> lcp(suffix.size(), 0);
	for (int i = 0; i < suffix.size() - 1; i++)
	{
		int j = 0;
		while (suffix[i][j] == suffix[i + 1][j])
		{
			j++;
			lcp[i]++;
		}
	}
	int sizesub = 1 - suffix.size() ;
	for (int i = 1; i < suffix.size(); i++)
	{
		sizesub += suffix[i].length();
		sizesub -= lcp[i - 1];
	}
	for (int j = 0; j < queries.size(); j++)
	{
		if (queries[j] > sizesub)
		{
			result[j] = "INVALID";
			continue;
		}
		int index = 0;
		int i = 1;
		while (index + suffix[i].length() - 1 - lcp[i - 1] < queries[j])
		{
			index += (suffix[i].length() - 1 - lcp[i - 1]);
			i++;
		}
		result[j] = suffix[i].substr(0, queries[j] - index + lcp[i - 1]);
	}
	return result;
}

int main()
{
	ofstream fout("OUTPUT_PATH.txt");


	int w_count;
	cin >> w_count;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	vector<string> w(w_count);

	for (int w_itr = 0; w_itr < w_count; w_itr++) {
		string w_item;
		getline(cin, w_item);

		w[w_itr] = w_item;
	}

	int queries_count;
	cin >> queries_count;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	vector<int> queries(queries_count);

	for (int queries_itr = 0; queries_itr < queries_count; queries_itr++) {
		int queries_item;
		cin >> queries_item;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		queries[queries_itr] = queries_item;
	}

	vector<string> result = findStrings(w, queries);

	for (int result_itr = 0; result_itr < result.size(); result_itr++) {
		fout << result[result_itr];

		if (result_itr != result.size() - 1) {
			fout << "\n";
		}
	}

	fout << "\n";

	fout.close();

	return 0;
}