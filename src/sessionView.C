#include "sessionView.h"

SessionView::SessionView( WContainerWidget* parent ):WContainerWidget(parent) 
{
	new WText( WString("Logs view"), this );
}

