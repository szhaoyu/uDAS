#ifndef OBJECT_SET_H
#define OBJECT_SET_H

struct ObjectFieldDef
{
	string			fname_;
	enum DataType  	ftype_;
};

struct ObjectItem
{
	string					objectID_;
	map<string, string>		objectFields_;	//field label-每个字段值的二进制字符串
	
	string getStringValue();
	int getIntValue();
	short getShortValue();
	bool getBoolValue();
	...
	ObjectSet getObjectSetValue();
};

class ObjectSet 
{
public:
	string						name_;
	string						alias_;
	map<string,ObjectFieldDef>		fieldsMeta_;
	//data items
	vector<ObjectItem>				objs_;
};

class DataAcessClietn
{
public:
	bool login( string sever, string user, string passwd );
	void logout( );
	//query: birthdate>='1990-09-10' && (height > 170 || weight<65 ) ... later provide a WhereBuilder.and( .... ) 
	int query( string objectName, string whereStr, ObjectSet &result );
	//insert
	int insert( ObjectSet &datas );
	int insert( string objectName, ObjectItem &itemData );
	int insert( string objectName, vector<ObjectItem> &itemDatas );
	//update
	int update( string objectName, ObjectItem data, string whereStr );
	int save( ObjectSet &datas );
};


#endif //!OBJECT_SET_H
