#ifndef ACCESS_SERVICE_H
#define ACCESS_SERVICE_H

struct ServiceMethod
{
	string  			name_;			//方法名称
	string				sql_;			//SQL语句
	string				argType_;		//输入参数类型	according to mybatis mapper item 
	string				replyType_;		//返回值类型
};

struct ServiceBundle
{
	//string			name_;					//Sample1
	string			name_;					//包括路径名：udas.user56.Sample1
	string			dsName_;				//数据源
	vector<ServiceMethod>	methods_;		//各个服务方法
};

struct DataEntity
{
	string 				name_;				//全路径名称：udas.user56.Dept
	vector<string>		fieldTypes_;			//字段类型
	vector<string>		fieldNames_;			//字段变量名称
};

struct GenCodes
{
	string				bundleName_;
	vector<string>		cppCodes_;
	vector<string>		javaCodes_;
	vector<string>		csharpCodes_;
};

class AccessServiceView : public WContainerWidget
{
public:
	AccessServiceView( WContainerWidget*parent );
	int readServiceData();
	int readClientCodes();
	void renderCodesSummary(string bundleName );
	void renderServiceDefine(string bundleName );
	void renderEntityDefine(string entityName );

private:
	//data
	map<string,string>						basicTypes_;	//int-int32_t....
	map<string,map<string,ServiceBundle>>	allServices_;	//dsName - bundleName - service bundle.
	map<string,DataEntity>					allEntities_;	//all defined data entity
	map<string,vector<string>>				entityServices_;	//entityName - list of service bundles' name.
	map<string,GenCodes>					clientLibs_;	// service bundle name - lib files		
	
	//view layout
	WHBoxLayout			*hbox_;
	//left navigate tree
	WTreeView			*navtree_;							//访问服务+数据实体 两部分
	WPushButton			*addbtn_, *editbtn_, *delbtn_, *releasebtn_;		//根据节点类型激活不同页面，增加访问服务，增加实体
	//right operate panel...
	WStackedWidget		*contents_;
	WTable				*bundleCodes_;						//访问服务代码生成页面
	WTable				*methodDef_;						//访问方法定义页面
	WTable				*entityDef_;						//数据实体定义页面
};

#endif//!ACCESS_SERVICE_H
