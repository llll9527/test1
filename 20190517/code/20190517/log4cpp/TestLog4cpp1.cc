 ///
 /// @file    TestLog4cpp1.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-17 16:12:00
 ///

#include <log4cpp/Category.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>


#include <iostream>
using std::cout;
using std::endl;
 
int main(void)
{
	using namespace log4cpp;
	Category & root = Category::getRoot();

	OstreamAppender * pOstreamAppender = new OstreamAppender("OstreamAppender", &cout);
	pOstreamAppender->setLayout(new BasicLayout());

	root.setAppender(pOstreamAppender);
	root.setPriority(Priority::DEBUG);

	root.debug("this a debug message");

	Category::shutdown();
	return 0;
}
