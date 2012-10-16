#ifndef OBJECT_SET_H
#define OBJECT_SET_H

//basic data type...
/*
 bool 	[ default value ]
 number [ default value, range ]
 date   [ default value, range ]
 string [ default value, max length, index type ]
 text   [ default value, max length, index type ]
 blob
 file   [ index type ]
 docx	[ word docx file  just full with text && image, saved in FILE && CLOB ]
 enum   [ default value, embed type( ex: string, bool, ...), values( ex: 1, 10, 1000 ... ) ]
 list   [ embed type ]
 ...........................................
 list<string>	[ string max length, index type]
 list<file>		[ index type ]
 
 keywords	[ size ] 		string
 abstract	[ length ]			string
 catalog	[ xml classfy tree ] string
 
 Example:
 CREATE (DIRECTORY|OBJECT) <英文ID> [AS <中文名称>]
 {
	<英文字段名称> [AS <中文名>] FieldType [NOT NULL],
 }
 
 FieldType ::=  BOOL   [ DEFAULT <val> ]
			  | NUMBER [ DEFAULT <val> ] [ RANGE '(' (<min>|'-') ',' (<max>|'-') ')' ] [ UNIQUE ]
			  | DATE   [ DEFAULT <val> ] [ RANGE '(' (<min>|'-') ',' (<max>|'-') ')' ] [ UNIQUE ]
			  | STRING ['('<len>')'] [ DEFAULT <val> ] [ RANGE '(' (<min>|'-') ',' (<max>|'-') ')' ] [ UNIQUE ] [ INDEX (PLAIN|FULL-TEXT|NONE) ]
			  | TEXT   ['('<len>')'] [ RANGE '(' (<min>|'-') ',' (<max>|'-') ')' ] [ INDEX (PLAIN|FULL-TEXT|NONE) ]
			  | BLOB
			  | DOCX   
			  | FILE   [ INDEX (FULL-TEXT|NONE) ]
			  | LIST '<' BOOL|NUMBER|DATE|STRING['('<len>')']|TEXT['('<len>')']|BLOB|DOCX|FILE [INDEX NONE] '>'
			  | ENUM '<' NUMBER|DATE|STRING '>' VALUES '(' 120,200,300|'2012-09-21 12:23:32','2012-09-21 12:23:32'|'ONE','TWO' ')'
			  | KEYWORDS ['('12')']
			  | ABSTRACT ['('256')']
			  | CATALOG
			  ;
 
 EName 		::= ('a'-'z'|'A'-'Z')('a'-'z'|'A'-'Z'|'_'|'0'-'9')*
 ZHName		::= .*
 
 
 ----unique, nullable, range, default value----
 create OBJECT /MingRenYiShi as 名人轶事
 {
	title AS 标题 STRING(256) UNIQUE NOT NULL,
	content AS 正文 DOCX,
	files AS 附件 LIST<FILE>,
	author AS 作者 STRING(128),
	editTime as 时间 DATE DEFAULT SYSDATE
 }

about read allow: only self, group, every one


DIRECTORY&OBJECT entry:
NO	Name		Parent		flag	Owner		readAllow		writeAllow
1	'/'			''			0		system		E				E
2	'/部门1'	'/'			0		body1		G(group1),U(lisan)	G(group1)
3	'/部门1/李三' '/部门1'	0		lisan		S				S	
4	'/部门1/考勤' '/部门1'  1		body1		G(group1)		S
...

GROUP ENTRY:
-Name-			-Parent-		-members-
group1							system,one,two
group11			group1			one110,two110...
group12			group1

USER ENTRY:
-Name-		-passwd-		-registeDate-
system		MD5('admin')	2012-10-14 10:53:00
...

 */
//author, time, desc, keywords,

class TypeBool
{
public:
	string toString( bool var );
	bool   parseString( string var );
};
class TypeDate
{
public:
	string toString();
	int fromString();
};

struct ObjectFieldDef
{
	string			fname_;
	enum DataType  	ftype_;
};

enum ObjectStatus { InitRead, NewData, DeleteData, UpdateData, WriteFailed };

struct ObjectItem
{
	enum ObjectStatus		flag_;			//status
	string					objectID_;		//object id
	map<string, string>		objectFields_;	//field label-每个字段值的二进制字符串
	
	string getStringValue();
	int getIntValue();
	short getShortValue();
	bool getBoolValue();
	...
	ObjectSet getObjectSetValue();
	//update
	int setStringValue();
	...
	//delete
	int deleteData();
};

class ObjectMeta
{
public:
	string							name_;		//full path name as: '公开资料.人民日报.政治人物'
	string							alias_;
	map<string,ObjectFieldDef>		fieldsMeta_;
};

class ObjectSet 
{
public:
	//object define information
	ObjectMeta						meta_;
	//data items
	vector<ObjectItem>				objs_;
	
	int addObject( ObjectItem &item );
	int deleteLocal( ObjectItem &item );
	int deleteObject( ObjectItem &item );
	ObjectItem* nextObject();
	ObjectItem* prevObject();
	ObjectItem* currentObject();
};

class DataAcessClietn
{
public:
	bool login( string sever, string user, string passwd );
	void logout( );
	//create object storage
	
	//create group
	
	//create user
	
	//drop object storage
	
	//read object define...

	//read directory
	
	//read all objects
	
	//query: birthdate>='1990-09-10' && (height > 170 || weight<65 ) ... later provide a WhereBuilder.and( .... ) 
	int query( string objectName, string selectFields, string whereStr, ObjectSet &result );
	//insert
	int insert( ObjectSet &datas );
	int insert( string objectName, ObjectItem &itemData );
	int insert( string objectName, vector<ObjectItem> &itemDatas );
	//update
	int update( string objectName, ObjectItem &data, string whereStr );
	int update( string objectName, ObjectItem &data );
	int update( ObjectSet &datas );
	//delete
	int deleteObject( string objectName, string whereStr );
	int deleteObject( string objectName, ObjectItem &data );
	int deleteObject( ObjectSet &datas );
};


#endif //!OBJECT_SET_H
