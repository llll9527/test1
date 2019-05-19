#include <iostream>
#include <string.h>
#include <ctype.h>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

class Dictionary
{
public:
    void read(const std::string & filename)
    {
        ifstream ifs(filename);
        if(!ifs){
            cout << ">> ifstream open file " << filename << " error!" << endl;
            return ;
        }
        string line;
        while(getline (ifs, line)){
            istringstream iss(line);
            string key;
            while(!iss.eof()){
                iss >> key;
                for(int i=0;i<key.size();i++)
                    key[i]=tolower(key[i]);
                if(!m.count(key)){
                    m.insert(make_pair(key,1));
                }else{
                    m[key]++;
                }
            }
        }
    }
    //void store(const std::string & filename);
    //void sort();
    void print()
    {
        for(auto & it :m){
            cout << it.first << " : " << it.second <<endl;
        }
    }
private:
    map<string,int> m;
};
int main()
{
    Dictionary dic;
    dic.read("The_Holy_Bible.txt");
    dic.print();
    return 0;
}

