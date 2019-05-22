#include <iostream>
#include <vector>
#include <fstream>
#include <regex>

#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

struct Rssltem
{
    string title;
    string link;
    string description;
    string content;
};

class RssReader
{
public:
    RssReader(){}

    void parseRss();
    void dump(const string & filename);
private:
    vector<Rssltem> _rss;
};

void RssReader::parseRss()
{
    XMLDocument doc;
    doc.LoadFile("coolshell.xml");
    cout<<doc.Error()<<endl;
    XMLElement *rss=doc.RootElement();
    XMLElement *item=rss->FirstChildElement("channel")->FirstChildElement("item");
    cout<<"--------开始处理文件-----"<<endl;
    while(item){
        Rssltem s;
        tinyxml2::XMLElement *itemchild=item->FirstChildElement();
        while(itemchild)
        {
            if(!strcmp(itemchild->Name(),"title")){
                s.title=itemchild->GetText();
            }
            if(!strcmp(itemchild->Name(),"link")){
                s.link=itemchild->GetText();
            }
            if(!strcmp(itemchild->Name(),"description")){
                s.description=itemchild->GetText();
            }
            if(!strcmp(itemchild->Name(),"content:encoded")){
                s.content=itemchild->GetText();
            }
            itemchild=itemchild->NextSiblingElement();
        }
        item=item->NextSiblingElement();
        _rss.push_back(s);
    }
}

void RssReader::dump(const string & filename)
{
    ofstream ofs(filename);
    int cnt=0;
    regex re("<[^>]*>");
    for(auto &it:_rss){
        ++cnt;
        ofs<<"<doc>"<<endl;
        ofs<<"<docid>"<<cnt<<"</docid>"<<endl;
        ofs<<"<title>"<<it.title<<"</title>"<<endl;
        ofs<<"<link>"<<it.link<<"</link>"<<endl;
        ofs<<"<description>"<<regex_replace(it.description,re,"")
            <<"</description>"<<endl;
        ofs<<"<content>"<<regex_replace(it.content,re,"")
            <<"</content>"<<endl;
        ofs<<"</doc>"<<endl;
    }
}

int main()
{
    RssReader rss;
    rss.parseRss();
    rss.dump("pagelib.txt");
    return 0;
}

