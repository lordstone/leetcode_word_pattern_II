#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
class waysToBuy{

public:
    vector<vector<int>> findWaysToBuy(vector<int>& myList, int n){
        //output the different way to buy n bottles with packages
        //no duplicate allowed
        vector<vector<int>> res;
        if(n == 0) return res;

    }

    void DFS(vector<int>& myList, int n){

    }
};
*/

class wordPattern{
public:

     bool wordPatternMatch(string pattern, string str) {
        unordered_map<char, string> d;
        unordered_map<string, bool> used;
        return match(pattern, str, d, used);
    }

    bool match(string pattern, string str, unordered_map<char, string> &d, unordered_map<string, bool> &used) {
        if(pattern.length() == 0 && str.length() == 0)
            return true;
        if(pattern.length() == 0 || str.length() == 0)
            return false;

        if(pattern.length() == 1) {
            if(d.find(pattern[0]) == d.end()) {
                if(used.find(str) == used.end())
                    return true;
                else
                    return false;
            } else {
                if(d[pattern[0]] == str)
                    return true;
                else
                    return false;
            }
        }

        if(d.find(pattern[0]) != d.end()) {
            if(str.find(d[pattern[0]]) != 0)
                return false;
            else {
                bool result = match(pattern.substr(1), str.substr(d[pattern[0]].length()), d, used);
                if(result)
                    return true;
            }
        } else {
            int length = str.length() - (pattern.length() - 1);
            for(int i = 1; i <= length; i++) {
                string cur = str.substr(0, i);
                d.insert(pair<char, string>(pattern[0], cur));
                used.insert(pair<string, bool>(cur, true));
                bool result = match(pattern.substr(1), str.substr(cur.length()), d, used);
                d.erase(pattern[0]);
                used.erase(cur);
                if(result)
                    return true;
            }
        }
        return false;
    }


//------------
    // s1 is the pattern, s2 is the actual string
    bool isPattern(string& s1, string& s2){
        unordered_map<char,string> myMap;
        unordered_set<string> mySet;
        return recur(s1,s2,myMap, mySet);
    }

    bool recur(string s1, string s2,  unordered_map<char,string> myMap, unordered_set<string> mySet){
        //if(s1.length() > s2.length()) return false;
        //find the pattern first
        if(s1.length() == 0 && s2.length() == 0) return true;
        if(s1.length() == 0 || s2.length() == 0) return false;
        if(s1.length() == 1){
            if(myMap.find(s1[0]) == myMap.end()){
                if(mySet.find(s2) == mySet.end()){
                    return true;
                }else{
                    return false;
                }
            }else{
                if(myMap[s1[0]] == s2){
                    return true;
                }else{
                    return false;
                }
            }
        }
        //end of corner cases

        if(myMap.find(s1[0]) != myMap.end()){
            //if found the definition of the pattern

            string mappedStr = myMap[s1[0]];
            //if(mappedStr.length() > s2.length()) return false; // if not holding the mapped str in the rest s2
            if(mappedStr == s2.substr(0,mappedStr.length())){
                // if there is a match

                if (recur(s1.substr(1), s2.substr(mappedStr.length()), myMap, mySet)){

                    return true;
                }
            }
            return false;
        }
        // if the current pattern is not registered yet
         // the rest can be a whole new pattern and end the search
        // try multiple
        for(int i = 1; i <= s2.length() - s1.length() + 1; i ++){
            string tmp = s2.substr(0,i);
            //if not found
            //register this as the current pattern
            myMap[s1[0]] = tmp;
            mySet.insert(tmp);
            if(recur(s1.substr(1), s2.substr(tmp.length()), myMap, mySet )) return true;
            myMap.erase(s1[0]);
            mySet.erase(tmp);
        }//end for i
        return false;
    }

};//end word Pattern


int main()
{   /*
    int my_list = {12,6,2,1};
    vector<int> myList (my_list, my_list + sizeof(my_list)/sizeof(int));
    waysToBuy myClass = new waysToBuy();

    vector<vector<int>> res = myClass.findWaysToBuy(myList, 10);

    for(int i = 0; i < res.size(); i ++){
        for(int j = 0; j < res[i].size(); j ++){
            cout << res[i][j] << " " ;
        }
        cout << endl;
    }
    */

    string s1 = "aaaaqqqqq";
    string s2 = "jijijijibeibeibeibeibei";

    wordPattern myClass;
    bool res = myClass.isPattern(s1,s2);
    bool res2 = myClass.wordPatternMatch(s1,s2);
    //cout << (bool)("abba" == s1) << endl;
    cout << res << endl;
    s1 = "" ; s2 = "";
    bool res1 = myClass.isPattern(s1,s2);
    cout << res2 << endl;

    return 0;
}
