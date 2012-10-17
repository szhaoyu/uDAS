/*
 * Copyright (C) 2008 Emweb bvba, Heverlee, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include <iostream>
#include <stdlib.h>

#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WEnvironment>
#include <Wt/WLineEdit>
#include <Wt/WGridLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WPushButton>
#include <Wt/WTable>
#include <Wt/WText>
#include <Wt/WTreeView>
#include <Wt/WVBoxLayout>
#include <Wt/WViewWidget>

#inlcude "dataSourceView.h"
#inlcude "accessServiceView.h"
#inlcude "sessionView.h"
#inlcude "logView.h"

using namespace Wt;

/*@{*/

/*! \class UdasViewApplication
 *  \brief A simple application to navigate data access service statuses.
 *
 * This examples demonstrates how to use the custom model use GitModel
 * with a WTreeView.
 */
class UdasViewApplication : public WApplication
{
private:
	WTabWidget		*mainMenu_;
	
	//WWidget			*dsView_, *asView_, *sessionView, *logView;
	WWidget* dataSourceView()
	{
		return new DataSourceView( mainMenu_ );
	}
	WWidget* accessServiceView()
	{
	}
	WWidget* sessionView()
	{
	}
	WWidget* logView()
	{
	}
	WString tr(const char *key)
	{
		return WString::tr(key);
	}
public:
	/*! \brief Constructor.
	*/
	UdasViewApplication(const WEnvironment& env) 
	: WApplication(env)
	{
		useStyleSheet("udasView.css");
		setTitle("数据访问服务平台");
		////
		WContainerWidget *w = root();
		mainMenu_ = new WTabWidget(w);

		WAnimation animation(WAnimation::SlideInFromRight, WAnimation::EaseIn);
		mainMenu_->contentsStack()->setTransitionAnimation(animation, true);

		mainMenu_.addTab( dataSourceView(), tr("data-source") );
		mainMenu_.addTab( accessServiceView(), tr("access-service") );
		mainMenu_.addTab( sessionView(), tr("session-view") )->setPathComponent("");;
		mainMenu_.addTab( logView(), tr("log-view") );
	}

};

WApplication *createApplication(const WEnvironment& env)
{
  return new UdasViewApplication(env);
}

int main(int argc, char **argv)
{
  return WRun(argc, argv, &createApplication);
}

/*@}*/
