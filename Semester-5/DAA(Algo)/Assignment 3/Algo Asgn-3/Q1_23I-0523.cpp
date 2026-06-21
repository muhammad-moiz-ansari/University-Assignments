//#include <iostream>
//#include <string>
//#include <cmath>
//#include <unordered_set>
//#include <vector>
//using namespace std;
//
//#define NAIVE 1
//#define RABINKARP 2
//#define KMP 3
//vector<int> shifts;
//
//bool isPeriodic(const string& T);
//int matcherSelector(const string& T, const string& P, int sigma);
//void naiveStringMatcher(const string& T, const string& P);
//void rabinKarp(const string& T, const string& P, int d, int q);
//int* computePrefixFunction(const string& P);
//void kmpMatcher(const string& T, const string& P);
//void printResultString(const string& T, const string& p);
//void toLowercase(string& str);
//
//int main()
//{
//	string str, str0;
//	string pattern, pat;
//
//	// Input
//	cout << "Enter the text: ";
//	getline(cin, str);
//	cout << "Enter the pattern: ";
//	getline(cin, pattern);
//
//	// Hardcoded input
//	//str = "She sells SEASHELLS by the seashore. HIS sister says SHE has Hershey's";
//	//pattern = "sea";
//
//	str0 = str;
//	pat = pattern;
//	toLowercase(str0);
//	toLowercase(pat);
//
//	const int sigma = unordered_set<char>(str.begin(), str.end()).size();	//Calculate unique number of characters using set
//	const long long q = 1000000007;
//
//	int algo = matcherSelector(str0, pat, sigma);
//
//	cout << "---------- ADVANCED STRING MATCHER ----------\n\n"
//		<< "Text: " << str << endl
//		<< "Pattern: " << pattern << endl << endl
//		<< "Selecting the best string matcher...\n\n";
//
//	if (algo == NAIVE)
//		naiveStringMatcher(str0, pat);
//	else if (algo == RABINKARP)
//		rabinKarp(str0, pat, sigma, q);
//	else
//		kmpMatcher(str0, pat);
//
//	cout << "\nResult String: ";
//	printResultString(str, pattern);
//
//	return 0;
//}
//
//void toLowercase(string& str)
//{
//	for (int i = 0; i < str.length(); ++i)
//	{
//		if (str[i] >= 'A' && str[i] <= 'Z')
//			str[i] += 'a' - 'A';
//	}
//}
//
//bool isPeriodic(const string& T)
//{
//	int n = T.length();
//	if (n <= 1)
//		return false;
//
//	int* pi = computePrefixFunction(T);
//
//	int maxPi = 0;
//	for (int i = 0; i < n; ++i)
//		maxPi = (maxPi < pi[i]) ? pi[i] : maxPi;
//	int blockSize = n - maxPi;;
//	delete[] pi;
//
//	// Zero repetition
//	if (maxPi == 0)
//		return false;
//
//	int periodicLength = n - blockSize;
//
//	// Fully periodic
//	if (n % blockSize == 0)
//		return true;
//
//	// At least half of the text is periodic
//	if (periodicLength >= n / 2)
//		return true;
//
//	return false;
//}
//
//
//
//int matcherSelector(const string& T, const string& P, int sigma)
//{
//	int n = T.length(),
//		m = P.length();
//	bool periodic = isPeriodic(T);
//
//	// Small patterns or small text
//	int max_n = 25;
//	//max_n = 1000;	// for large testcases
//	if (m <= 5 || n <= max_n)
//		return NAIVE;
//
//	// Medium patterns
//	if (m >= 6 && m < 20)
//	{
//		// Repetitive text
//		if (periodic == true)
//			return KMP;
//
//		// Small language size
//		if (sigma <= 6)
//			return KMP;
//
//		// Otherwise rabin karp
//		return RABINKARP;
//	}
//
//	// Long patterns
//	if (m >= 20)
//	{
//		// Small language size
//		if (sigma <= 6)
//			return KMP;
//		else		// large language size
//		{
//			// Repetitive text
//			if (periodic == true)
//				return KMP;
//			else
//				return RABINKARP;
//		}
//	}
//
//    // default
//    return RABINKARP;
//}
//
//void naiveStringMatcher(const string& T, const string& P)
//{
//
//	cout << "--- String Matching Results ---\n\n" 
//		<< "\n> Naive String Matcher <\n";
//
//	int n = T.length(),
//		m = P.length();
//
//	for (int s = 0; s <= n - m; ++s)
//	{
//		if (T.substr(s, m) == P)
//		{
//			cout << "Pattern occurs with shift " << s << endl;
//			shifts.push_back(s);
//		}
//	}
//}
//
//void rabinKarp(const string& T, const string& P, int d, int q)
//{
//	cout << "--- String Matching Results ---\n\n" 
//		<< "\n> Rabin Karp String Matcher <\n";
//
//	int n = T.length(),
//		m = P.length();
//	long long hp = 0, ht = 0;
//	long long h = 1;
//	for (int i = 0; i < m - 1; ++i)
//		h = (h * d) % q;
//
//	for (int i = 0; i < m; ++i)
//	{
//		hp = (d * hp + P[i]) % q;
//		ht = (d * ht + T[i]) % q;
//	}
//
//	for (int s = 0; s <= n - m; ++s)
//	{
//		if (hp == ht)
//		{
//			if (T.substr(s, m) == P)
//			{
//				cout << "Pattern occurs with shift " << s << endl;
//				shifts.push_back(s);
//			}
//			else
//				cout << "- Spurious hit occured at shift " << s << endl;
//		}
//		if (s < n - m)
//		{
//			ht = (d * (ht - T[s] * h) + T[s + m]) % q;
//			if (ht < 0)
//				ht += q;
//		}
//	}
//}
//
//int* computePrefixFunction(const string& P)
//{
//	int m = P.length();
//	int* pi = new int[m];
//	pi[0] = 0;
//	int k = 0;
//
//    for (int q = 1; q < m; q++)
//    {
//        while (k > 0 && P[k] != P[q])
//            k = pi[k - 1];
//
//        if (P[k] == P[q])
//            k++;
//
//        pi[q] = k;
//    }
//
//    return pi;
//}
//
//void kmpMatcher(const string& T, const string& P)
//{
//	cout << "--- String Matching Results ---\n\n"
//		<< "\n> KMP String Matcher <\n";
//
//	int n = T.length();
//	int m = P.length();
//
//	int* pi = computePrefixFunction(P);
//	int q = 0;
//
//	for (int i = 0; i < n; i++)
//	{
//		while (q > 0 && P[q] != T[i])
//			q = pi[q - 1];
//
//		if (P[q] == T[i])
//			q++;
//
//		if (q == m)
//		{
//			cout << "Pattern occurs with shift " << (i - m + 1) << endl;
//			q = pi[q - 1];
//			shifts.push_back(i - m + 1);
//		}
//	}
//}
//
//void printResultString(const string& T, const string& p)
//{
//	int ind = 0;
//	for (int i = 0; i < T.length(); ++i)
//	{
//		if (ind < shifts.size() && i == shifts[ind])
//		{
//			ind++;
//			cout << "\033[31m";
//			int j;
//			for (j = i; j < i + p.length(); ++j)
//			{
//				if (ind < shifts.size() && j == shifts[ind])
//				{
//					--j;
//					break;
//				}
//				cout << T[j];
//			}
//			i = j - 1;
//			cout << "\033[0m";
//		}
//		else
//			cout << T[i];
//	}
//	cout << endl;
//}