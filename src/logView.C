#include "logView.h"

LogView::LogView( WContainerWidget* parent ):WContainerWidget(parent) 
{
	new WText( WString("Logs view"), this );
}

