#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;


vector<string> splitString(const string &input, const string &seperator)
{
	cout<<"sp";
    vector<string> res;
    size_t pos1, pos2;
    pos1 = 0;
    pos2 = input.find(seperator, pos1);
    while(pos2 != string::npos) {
        res.push_back(input.substr(pos1, pos2 - pos1));
        pos1 = pos2 + seperator.length();
        pos2 = input.find(seperator, pos1);
    }
    if(pos1 != input.length()) 
        res.push_back(input.substr(pos1));
    return res;
}

//convert string to lowercase
void lowercase(string &s)
{
    for(auto &c : s) {
        if(c >= 'A' && c <='Z')
            c += 32;
    }
}

//delete the extra character
void deleteExtra(string &s) 
{
    vector<int> pos; //record the position of extra character
    for(int i = 0; i < s.length(); i++) {
        if((s[i] < 'a' || s[i] > 'z') && s[i] != ' ') {
            if(s[i] < '0' || s[i] > '9')
                pos.push_back(i);
        }
    }
    for(int i = 0; i < pos.size(); i++) {
        s.erase(pos[i] - 1, 1);
    }
}

//delete white space
void deleteWhiteSpace(string &s) 
{
    //erase the leading and trailing whitespace
    if(!s.empty()) {
        int first = 0;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == ' ')
                first++;
            else
                break;
        }
        s.erase(0, first);
        
        int last = s.size()-1;
        for(int i = s.size() - 1; i >= 0; i--) {
            if(s[i] == ' ')
                last--;
            else
                break;
                
        }
        s.erase(last + 1);
    }
    
    //erase contiguous white space
    size_t index;
    index = 0;
    if(s.empty()) {
        while((s.find(" ", index)) != string::npos) {
            if(s[index - 1] == ' ')
                s.erase(index, 1);
            else
                index++;
        }
    }
}

//s1 contains s2?
bool contains(const string &s1, const string &s2)
{
    if(s1.length() < s2.length())
        return false;
    size_t pos = s1.find(s2, 0);
    if(pos != string::npos)
        return true;
    return false;
}

void printLine(const string &s)
{
    if(s.length() == 0) return;
    vector<string> source = splitString(s, "|");
    vector<string> sourceCpy = source;
    
    //pre-process the input string 
    for(auto &str : source) {
        lowercase(str);
        cout<<"lower";
        deleteExtra(str);
        cout<<"delete";
        deleteWhiteSpace(str);
    }
    
    unordered_set<int> posSet;//record the position which should be erased
    unordered_set<int>::const_iterator got;
    for(int i = 0; i < source.size(); i++) {
        got = posSet.find(i);
        if(got != posSet.end())
            continue;
        for(int j = i + 1; j < source.size(); j++) {
            got = posSet.find(j);
            if(got != posSet.end())
                continue;
            
            //source[i] == source[j], then compare the length of original string and the order of appearance
            if(source[i].compare(source[j]) == 0) {
                if(sourceCpy[i].size() > sourceCpy[j].size()) {
                    posSet.emplace(i);
                    break;
                }
                else {
                    posSet.emplace(j);
                    continue;
                }
            }
            
            //contain judgement
            bool contain = false;
            contain = contains(source[j], source[i]);
            if(contain == true) {
                posSet.emplace(i);
                break;
            }
            contain = false;
            contain = contains(source[i], source[j]);
            if(contain == true) {
                posSet.emplace(j);
            }
        }
    }
    
    int cnt = 0;
    
    //display
    for(int i = 0; i < sourceCpy.size(); i++) {
        got = posSet.find(i);
        if(got == posSet.end()) {
            cout<<sourceCpy[i];
            cnt++;
            if(cnt < source.size() - posSet.size())
                cout<<"|";
        }
    }
    cout<<endl;
}
int main(void) {
   	string input;
	while(getline(cin, input)) {
		printLine(input);
		break;
	}
		//cout<<input<<endl;
    
    return 0;
}

