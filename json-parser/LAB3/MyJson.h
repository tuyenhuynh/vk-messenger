#ifndef MYJSON_H
#define MYJSON_H
#define MAX_ARR_SIZE 30000
#define MAX_NUM_SIZE 30

enum JsonType {
	Number =0, /*INTEGER, BOOL*/
	True = 1,
	False = 2,
	String = 3, 
	Object =4, 
	Array = 5, 
	None = 6,
	Null = 7

};

struct Json{
	Json* prevs, *next; 
	Json* child; 
	JsonType type;

	char* stringValue; //string in case item is a string
	char* stringName; // key name in case item is subitem of an object  
	int intValue; 
	double doubleValue; 
} ;

class MyJson
{
public:
	
	char* parseString(char* json, Json* item);
	char* parseNumber(char* json, Json* item); 
	char* parseObject(char* json, Json* item); 
	char* parseValue(char* json, Json* item); 
	char* parseArray(char* json, Json* item);
	char* skipSpace(char* json); 
	void printString(char* str);
	void printArray(Json* arr);
	void printObject(Json* obj);
	void printValue(Json* val); 
	void printNumber(Json* num);
	char* serializeString(char* str) ; 
	char* serializeNumber(double value ); 
	char* serializeBoolean(bool value); 
	char* serializeNull ();
	char* serializeArray(Json* arr); 
	char* serializeValue(Json* value);
	char* serializeObject(Json* json); 

	void getArrayValues(Json*  object, Json values[], int& length);
	void getObjectValues(Json* object, Json values[], int& length); 
	Json* getFieldOfObject(Json* object, char* fieldName); 

	MyJson(void);
	~MyJson(void);
};

#endif MYJSON_H