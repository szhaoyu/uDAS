#ifndef ACCESS_SERVICE_H
#define ACCESS_SERVICE_H

struct ServiceMethod
{
	string  			name_;			//��������
	string				sql_;			//SQL���
	string				argType_;		//�����������	according to mybatis mapper item 
	string				replyType_;		//����ֵ����
};

struct ServiceBundle
{
	//string			name_;					//Sample1
	string			name_;					//����·������udas.user56.Sample1
	string			dsName_;				//����Դ
	vector<ServiceMethod>	methods_;		//�������񷽷�
};

struct DataEntity
{
	string 				name_;				//ȫ·�����ƣ�udas.user56.Dept
	vector<string>		fieldTypes_;			//�ֶ�����
	vector<string>		fieldNames_;			//�ֶα�������
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
	WTreeView			*navtree_;							//���ʷ���+����ʵ�� ������
	WPushButton			*addbtn_, *editbtn_, *delbtn_, *releasebtn_;		//���ݽڵ����ͼ��ͬҳ�棬���ӷ��ʷ�������ʵ��
	//right operate panel...
	WStackedWidget		*contents_;
	WTable				*bundleCodes_;						//���ʷ����������ҳ��
	WTable				*methodDef_;						//���ʷ�������ҳ��
	WTable				*entityDef_;						//����ʵ�嶨��ҳ��
};

#endif//!ACCESS_SERVICE_H
