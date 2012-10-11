#include "accessServiceView.h"

AccessServiceView::AccessServiceView( WContainerWidget*parent ):WContainerWidget(parent) 
{
	hbox_ = new WHBoxLayout();
	
	//left
	WContainerWidget* container = new WContainerWidget( );
	navtree_ = new WTreeView( container );
	navtree_->setAttributeValue
      ("oncontextmenu",
       "event.cancelBubble = true; event.returnValue = false; return false;");
	navtree_->resize(200, WLength::Auto);
    navtree_->setSelectionMode(SingleSelection);
    navtree_->expandToDepth(1);
    navtree_->selectionChanged().connect(this, &DataSourceView::navTreeSelectChanged);
	
	container->addWidget( new WBreak( container ) );
	addbtn_ = new WPushButton("增加", container);
	editbtn_ = new WPushButton("修改", container);
	delbtn_ = new WPushButton("删除", container);
	releasebtn_ = new WPushButton("发布", container);

	hbox_->addWidget( container, 0 );
	//right
	contents_ = new WStackedWidget( );
	//服务代码生成下载页面
	bundleCodes_ = new WTable( contents_ );
	contents_->addWidget( bundleCodes_ );
	//访问方法定义页面
	methodDef_ = new WTable( contents_ );
	contents_->addWidget( methodDef_ );
	//数据实体定义页面
	entityDef_ = new WTable( contents_ );
	contents_->addWidget( entityDef_ );
	
	hbox_->addWidget( contents_, 1 );
	
	//data initialize
	basicTypes_["bool"]="bool";
	basicTypes_["byte"]="byte";
	basicTypes_["short"]="i16";
	basicTypes_["int"]="i32";
	basicTypes_["longlong"]="i64";
	basicTypes_["double"]="double";
	basicTypes_["string"]="string";
	//list set map
}

int AccessServiceView::readServiceData()
{
	allServices_.clear();
	map<string,ServiceBundle> 	tmpBundle;
	ServiceBundle				one;
	ServiceMethod				method;
	
	one.name_ = "udas.user56.Sample1";
	one.dsName_ = "QBK";
	
	method.name_ = "getDeptCount";
	method.sql_ = "select count(*) from dept";
	method.argType_ = "";
	method.replyType_ = "int";
	one.methods_.push_back( method );
	
	method.name_ = "execOneWaySQL";
	method.sql_ = "#{value}";
	method.argType_ = "string";
	method.replyType_ = "void";
	one.methods_.push_back( method );
	
	tmpBundle[one.name_] = one;
	allServices_[one.dsName] = tmpBundle;
	//
	DataEntity item;
	item.name_ = "udas.user56.Dept";
	item.fieldTypes_.push_back("int");
	item.fieldNames_.push_back("deptno");
	item.fieldTypes_.push_back("string");
	item.fieldNames_.push_back("name");
	allEntities_[item.name_]=item;
	
	return 0;
}

int AccessServiceView::readClientCodes()
{
	clientLibs_.clear();
	
	GenCodes item;
	item.bundleName_ = "udas.user56.Sample1";
	item.javaCodes_.push_back( "udas.user56.Sample1.jar" );
	item.cppCodes_.push_back( "udas.user56.Sample1.cpp.zip" );
	item.csharpCodes_.push_back( "udas.user56.Sample1.csharp.zip" );
	
	//client call api: udas.user56.Sample1Client client; 
	//client.getDeptCount()
	//client.execOneWaySQL()
	
	return 0;
}

void AccessServiceView::renderCodesSummary(string bundleName )
{
	bundleCodes_->clear();
	
	WTableCell *cell = bundleCodes_->elementAt(0, 0);
	cell->addWidget(new Wt::WText("生成代码"));
	cell->setColumnSpan(2);
	bundleCodes_->elementAt(1, 0)->addWidget(new Wt::WText(" "));
	bundleCodes_->elementAt(1, 1)->addWidget(new Wt::WText(" "));

	map<string,GenCodes>::iterator it;
	it = clientLibs_.find(bundleName);
	
	bundleCodes_->elementAt(2, 0)->addWidget(new Wt::WText("C++语言"));
	bundleCodes_->elementAt(2, 1)->addWidget(new Wt::WPushButton("生成"));
	cell = bundleCodes_->elementAt(3, 0);
	if( it == clientLibs_.end() )
		cell->addWidget(new Wt::WAnchor(WLink(WLink::InternalPath, "/libs/", " "  )));
	else
		cell->addWidget(new Wt::WAnchor(WLink(WLink::InternalPath, "/libs/"+it->second.cppCodes_, it->second.cppCodes_  )));
	cell->setColumnSpan(2);
	bundleCodes_->elementAt(4, 0)->addWidget(new Wt::WText(" "));
	bundleCodes_->elementAt(4, 1)->addWidget(new Wt::WText(" "));
	
	bundleCodes_->elementAt(5, 0)->addWidget(new Wt::WText("Java语言"));
	bundleCodes_->elementAt(5, 1)->addWidget(new Wt::WPushButton("生成"));
	cell = bundleCodes_->elementAt(6, 0);
	if( it == clientLibs_.end() )
		cell->addWidget(new Wt::WAnchor(WLink(WLink::InternalPath, "/libs/", " "  )));
	else
		cell->addWidget(new Wt::WAnchor(WLink(WLink::InternalPath, "/libs/"+it->second.javaCodes_, it->second.javaCodes_  )));
	cell->setColumnSpan(2);
	bundleCodes_->elementAt(7, 0)->addWidget(new Wt::WText(" "));
	bundleCodes_->elementAt(7, 1)->addWidget(new Wt::WText(" "));

	bundleCodes_->elementAt(8, 0)->addWidget(new Wt::WText("C#语言"));
	bundleCodes_->elementAt(8, 1)->addWidget(new Wt::WPushButton("生成"));
	cell = bundleCodes_->elementAt(9, 0);
	if( it == clientLibs_.end() )
		cell->addWidget(new Wt::WAnchor(WLink(WLink::InternalPath, "/libs/", " "  )));
	else
		cell->addWidget(new Wt::WAnchor(WLink(WLink::InternalPath, "/libs/"+it->second.csharpCodes_, it->second.csharpCodes_  )));
	cell->setColumnSpan(2);
}

void AccessServiceView::renderServiceDefine(string bundleName )
{
}

void AccessServiceView::renderEntityDefine(string entityName )
{
}

