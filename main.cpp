#include <bits/stdc++.h>
using namespace std;

struct TreeNode {

	int character;

	float probability;
	int code[20];
	int top;
} p[256];

typedef struct TreeNode TreeNode;

float Round(float num) {
   float value = (int)(num * 100 + .5);
   return (float)value / 100;
}

void ShannonEncoding(int left, int right, TreeNode p[])
{
	float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0;
	int i, d, k, j;
	if ((left + 1) == right || left == right || left > right) {
		if (left == right || left > right) {
			return;
		}
		p[right].code[++(p[right].top)] = 0;
		p[left].code[++(p[left].top)] = 1;
		return;
	}
	else {
		for (i = left; i <= right - 1; i++)
			pack1 = pack1 + p[i].probability;
		pack2 = pack2 + p[right].probability;
		diff1 = pack1 - pack2;
		if (diff1 < 0)
			diff1 = diff1 * -1;
		j = 2;
		while (j != right - left + 1) {
			k = right - j;
			pack1 = pack2 = 0;
			for (i = left; i <= k; i++)
				pack1 = pack1 + p[i].probability;
			for (i = right; i > k; i--)
				pack2 = pack2 + p[i].probability;
			diff2 = pack1 - pack2;
			if (diff2 < 0)
				diff2 = diff2 * -1;
			if (diff2 >= diff1)
				break;
			diff1 = diff2;
			j++;
		}
		k++;
		for (i = left; i <= k; i++)
			p[i].code[++(p[i].top)] = 1;
		for (i = k + 1; i <= right; i++)
			p[i].code[++(p[i].top)] = 0;

		ShannonEncoding(left, k, p);
		ShannonEncoding(k + 1, right, p);
	}
}


void sortByProbability(int n, TreeNode p[])
{
	int i, j;
	TreeNode temp;
	for (j = 1; j <= n - 1; j++) {
		for (i = 0; i < n - 1; i++) {
			if ((p[i].probability) > (p[i + 1].probability)) {
				temp.probability = p[i].probability;
				temp.character = p[i].character;

				p[i].probability = p[i + 1].probability;
				p[i].character = p[i + 1].character;

				p[i + 1].probability = temp.probability;
				p[i + 1].character = temp.character;
				cout << p[i].probability << endl;
			}
		}
	}
}

void display(int n, TreeNode p[])
{
	int i, j;
	for (i = n - 1; i >= 0; i--) {
	    if (p[i].character == 10) {
	        cout << "NL" << " - ";
		    for (j = 0; j <= p[i].top; j++)
			    cout << p[i].code[j];
		    cout << endl;
	    } else if (p[i].character == 32) {
	        cout << "SPACE" << " - ";
		    for (j = 0; j <= p[i].top; j++)
			    cout << p[i].code[j];
		    cout << endl;
	    } else {
		    cout << char(p[i].character) << " - ";
		    for (j = 0; j <= p[i].top; j++)
			    cout << p[i].code[j];
		    cout << endl;
	    }
	}
}

string ReadFile(string fileName) {
    string result;
    string line;
    ifstream myfile(fileName);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            result = result + line + "\n";
        }
        myfile.close();
    }
    result.pop_back();
    return result;
}

map<int, float> CountProbabilities(string inputString) {
    float oneCharProb = 0.0;
    map <int, float> charProbMap;
    oneCharProb = float(1) / float(inputString.size());
    
    for (int i=0; i<inputString.size(); i++) {
        int currentChar = inputString[i];
        
        map<int, float>::iterator it = charProbMap.find(currentChar);
        if (it != charProbMap.end()) {
            it->second = it->second + oneCharProb;
        } else {
            
            charProbMap.insert(make_pair(int(inputString[i]), oneCharProb));
        }
    }
    
    return charProbMap;
}

void PrintProbabilities(map<int, float> charProbMap) {
    map <int, float>::iterator itr;

    for (itr = charProbMap.begin(); itr != charProbMap.end(); ++itr) {
        if (itr->first == 10) {
            cout << "NL" << " - " << Round(itr->second) << "\n";
        } else if (itr->first == 32) {
            cout << "SPACE" << " - " << Round(itr->second) << "\n";
        } else {
        cout << char(itr->first) << " - " << Round(itr->second) << "\n";
        }
    }
}

string encode(string input, TreeNode p[], int n) {
    string result;
    for (int i=0; i < input.size(); i++) {
        for (int j=0; j < n; j++) {
            if (int(input[i]) == p[j].character) {
                for (int i1 = 0; i1 <= p[j].top; i1++) {
			        result += int(p[j].code[i1] + 48);
                }
            }
        }
    }
    return result;
}

void compRatio(string input, TreeNode p[], int n) {
    int compressed = 0;
    for (int i=0; i < input.size(); i++) {
        for (int j=0; j < n; j++) {
            if (int(input[i]) == p[j].character) {
                for (int i1 = 0; i1 <= p[j].top; i1++) {
			        compressed++;
                }
            }
        }
    }
    float in = float(input.size()*8);
    float comp = float(compressed);
    cout << "Compression ration: " << in/comp << endl;
}

int main()
{
    string fileName = "Text.txt";
    string result;
    map <int, float> charProbMap;
    
    result = ReadFile(fileName);
    
    charProbMap = CountProbabilities(result);
    PrintProbabilities(charProbMap);
    
	int i, j;
	TreeNode temp;
	
	int size = charProbMap.size();
	
	int count = 0;
	
	map <int, float>::iterator itr;
    cout << endl;
    for (itr = charProbMap.begin(); itr != charProbMap.end(); ++itr) {
        int c = itr->first;
        int pb = itr->second;
        p[count].character = c;
        p[count].probability = pb;
        count++;
    }
	

	sortByProbability(size, p);

	for (i = 0; i < size; i++)
		p[i].top = -1;

	ShannonEncoding(0, size - 1, p);

	display(size, p);
	
	string s = encode(result, p, size);
	cout << "Encoded:" << s << endl;
	
	ofstream myfile;
    myfile.open ("new.txt");
    myfile << s << endl;
    myfile.close();
    compRatio(result, p, size);

	
	
	return 0;
}

