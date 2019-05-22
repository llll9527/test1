#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
using namespace std;
using namespace log4cpp;

enum Pri{
    ERROR,
    WARN,
    INFO,
    DEBUG
};
inline string int2string(int line){
    ostringstream oss;
    oss<<line;
    return oss.str();
}

#define suffix(msg) string(msg).append(" ##")\
    .append(__FILE__).append(":").append(__func__).append(":")\
    .append(int2string(__LINE__)).append("##").c_str()

class Mylog
{
public:
    static Mylog * getInstance()
    {
        if(_plog==nullptr){
            _plog = new Mylog();
        }
        return _plog;
    }

    static void destory()
    {
        if(_plog){
            _plog->_category.info(suffix("Mylog destory"));
            _plog->_category.shutdown();
            delete _plog;
        }
    }

    void setPriority(Pri p);
    void error(const char * msg);
    void warn(const char * msg);
    void info(const char * msg);
    void debug(const char * msg);
private:
    Mylog();
    ~Mylog(){}
private:
    static Mylog * _plog;
    Category & _category;
};

Mylog * Mylog::_plog = nullptr;

Mylog::Mylog()
    : _category(Category::getRoot())
{
    PatternLayout * patternlayout1 = new PatternLayout();
    patternlayout1->setConversionPattern("%d: %p %c %x:%m%n");
    PatternLayout * patternlayout2 = new PatternLayout();
    patternlayout2->setConversionPattern("%d: %p %c %x:%m%n");

    OstreamAppender * ostreamAppender = new OstreamAppender("ostreamAppender",&cout);
    ostreamAppender->setLayout(patternlayout1);

    RollingFileAppender * rollingFileAppender = new RollingFileAppender("rollingFileAppender","my.log",1024,3);
    rollingFileAppender->setLayout(patternlayout2);

    _category.setPriority(Priority::DEBUG);
    _category.setAppender(ostreamAppender);
    _category.addAppender(rollingFileAppender);

    _category.info(suffix("Mylog created!"));
}

void Mylog::setPriority(Pri p){
    switch(p){
    case(ERROR):
        _category.setRootPriority(Priority::ERROR);
        break;
    case(WARN):
        _category.setRootPriority(Priority::WARN);
        break;
    case(INFO):
        _category.setRootPriority(Priority::INFO);
        break;
    case(DEBUG):
        _category.setRootPriority(Priority::DEBUG);
        break;
    default:
        _category.setRootPriority(Priority::ERROR);
        break;     
    }
}

void Mylog::error(const char * msg){
    _category.error(msg);
}
void Mylog::warn(const char * msg){
    _category.warn(msg);
}
void Mylog::info(const char * msg){
    _category.info(msg);
}
void Mylog::debug(const char * msg){
    _category.debug(msg);
}

int main()
{
    Mylog * log = Mylog::getInstance();
    log->error(suffix("this is a error message"));
    log->destory();
    return 0;
}

