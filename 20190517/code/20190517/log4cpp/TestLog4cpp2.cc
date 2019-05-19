 ///
 /// @file    TestLog4cpp2.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-17 17:22:40
 ///

#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>

#include <iostream>
using std::cout;
using std::endl;
using namespace log4cpp;
 
int main(void)
{
	PatternLayout * patternLayout = new PatternLayout();
	patternLayout->setConversionPattern("%d [%p] %m%n");

	OstreamAppender * ostreamAppender = 
		new OstreamAppender("ostreamAppender", &cout);
	ostreamAppender->setLayout(patternLayout);

	Category & myRecord = Category::getRoot().getInstance("mycategory");
	myRecord.setAppender(ostreamAppender);
	//myRecord.setPriority(Priority::DEBUG);
	myRecord.setPriority(Priority::ERROR);//通过配置文件修改的

	//只有当日志的优先级大于等于日志记录器的优先级时，该条日志才会被记录
	myRecord.emerg("this is an emerg message");//方法本身代表的就是这一条日志的级别
	myRecord.fatal("this is a fatal message");
	myRecord.alert("this is an alert message");
	myRecord.crit("this is a crit message");
	myRecord.warn("this is a warn message");
	myRecord.error("this is an error message");
	myRecord.notice("this is a notice message");
	myRecord.info("this is an info message");
	myRecord.debug("this is a debug message");

	Category::shutdown();//回收各种堆空间的内存
	return 0;
}
