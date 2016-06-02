#include "stdafx.h"
#include "json_parser.h"
#include <math.h>
#include <iostream>

using namespace std;

char* parseString(char* json, Json* item){
	if(*json != '\"'){
		cout << "parse string error"; 
		return 0; 
	}
	char* out, *ptr = json+1; 
	int length = 0 ; 
	while(*ptr!= '\"' && *ptr || *ptr== '\"'&&*(ptr-1)== '\\'){
		++length;
		++ptr;
	}
	//validate string 
	if(*ptr == 0) {
		return 0 ; 
	}
	out = new char[length+1];
	strncpy(out, json+1, length); 
	out[length] ='\0';
	item->type= String;
	item->stringValue = out; 
	return ptr+1; 
}

char* serializeString(char*str ){
	int size = strlen(str) ; 
	char* out = new char[size +3] ;
	char*ptr = out; 
	out[0] = '\"';
	strncpy(out +1, str, size);  
	out[size +1] ='\"';
	out[size +2] ='\0';
	return out; 
}

char* serializeJsonObject(Json* json ){
	return 0 ; 
}

char* parseNumber(char* json, Json* item) {
	double value = 0; 
	if(*json !='-' && *json< '0' || *json > '9'){
		cout << "parse number error"; 
		return 0; 
	}

	bool isNegative  = *json == '-'; 
	if(isNegative) {
		json++;
	}
	while(*json >= '0' && * json <= '9'){
		value = value*10 + *json-48; 
		++json ; 
	}
	if(*json == '.'){
		++json; 
		if(*json >= '0' && *json < '9') {
			double t = 10; 
			while(*json >= '0' && * json <= '9'){
				value+=(*json -48)/t;
				t*=10;
				++json; 
			}
		}else {
			//invalid rational number 
			return 0 ; 
		}
	}
	//support rational number type 1.234e5, 1.234e+5, 1.234e-5
	if(*json == 'e' || *json == 'E') {
		++json; 
		bool isNegative = false; 
		if(*json == '-'){
			isNegative = true; 
			++json; 
		}else if(*json =='+'){
			++json; 
		} 
		double exp = 0; 
		if(*json>='0' && *json <='9'){
			while (*json>='0' && *json <='9'){
				exp = exp*10 + *json - 48;	 
				++json; 
			}
			exp = isNegative ? exp * -1 : exp;
			value = value*pow(10.0, exp); 
		}else { //invalid json number, eg 1.23e
			return 0; 
		}
	}
	value = isNegative ? value * -1: value; 
	item->type= Number; 
	item->doubleValue = value; 
	item->intValue = int(value);
	return json ; 
}

//functionally, this is not safe operation, for example 1e100 yell an error
char* serializeNumber(double value) {
	
	char tmp[MAX_NUM_SIZE]; 
	char* out; 
	sprintf(tmp, "%f", value); 
	int len = strlen(tmp); 
	out = new char[len+1];
	strncpy(out, tmp, len); 
	out[len] ='\0';
	return out; 
}

char* serializeBoolean(bool value ) {
	if(value) {
		return "true"; 	
	}
	return "false";
}

char* serializeNull () {
	return "null"; 
}

char* parseArray(char* json, Json* item) {
	//must check for valid next token in array [a, b, ]
	if(*json != '['){
		cout << "parse array error"; 
		return 0; 
	}

	json = skipSpace(json+1);
	
	if(*json == ']'){
		item->type= Array; 
		json = skipSpace(json+1);
		return json; 
	}

	Json* child; 
	item->child = child = new Json(); 
	json = parseValue(json, child); 
	json  = skipSpace(json);  
	if(!json ){
		cout << "parse array error"; 
		return 0; 
	}
	while(*json == ','){
		Json* newItem; 
		newItem = new Json(); 
		child->next = newItem; 
		newItem->prevs = child; 
		child = newItem; 
		json = skipSpace(json+1); 
		json = parseValue(json, child);
		//invalid value ["a", ab] or [1,]
		if(json == 0) {
			return 0; 
		}
		json = skipSpace(json);
	}
	if(*json == ']'){
		item->type= Array; 
		return json+1 ;
	}else {
		return 0;
	}
}

void printArray(Json* arr) {

	//print arr to json 

	//check for valid next token in array [a, b, ]
	if(arr->child == 0) {
		printf("[]\n");
	} else {
		printf("[\n");
		Json* child = arr->child; 
		while(child != 0){
			printValue(child); 
			child = child->next;
			if(child!= 0){
				printf(",");
			}
		}
		printf("\n]\n");	
	}
}

char* serializeArray(Json* arr) {
	 
	if(arr == 0 ){
		return 0 ; 
	}
	char* out; 
	int entryCount = 0 ;
	Json* ptr = arr->child; 
	int len[MAX_ARR_SIZE];
	char* items[MAX_ARR_SIZE];
	int arr_len  =  3; 
	while(ptr != 0 ){
		entryCount ++;
		int i = entryCount - 1; 
		items[i] = serializeValue(ptr); 
		len[i] = strlen(items[i]);
		arr_len+= len[i];
		if(ptr->next != 0){
			ptr = ptr->next; 	
		}else {
			ptr = 0; 
		}
	}

	if(entryCount == 0) {
		return "[]"; 
	}

	arr_len += entryCount - 1; 
	out = new char[arr_len] ; 
	out[0] ='['; 
	char* currPos = out+1; 
	for( int i = 0 ; i < entryCount; ++ i ) {
		strncpy (currPos, items[i], len[i]); 
		currPos+=len[i]; 
		*currPos = ',';
		++currPos; 
		delete [] items[i];
		items[i] = 0;
	}
	*(currPos - 1)= ']'; 
	*currPos = '\0';
	return out;
}

char* parseObject(char* json, Json* item){
	if(*json != '{'){
		cout << "parse object error"; 
		return 0; 
	}
	json = skipSpace(json+1); 
	if(*json == '}'){ 
		item->type = Object;
		return skipSpace(json+1) ; 		
	}
	Json* child = new Json(); 
	item->child = child; 
	json = skipSpace(json); 
	json = parseString(json, child);
	if(json ==  0) {
		return 0; 
	}
	json = skipSpace(json); 
	if(*json != ':') {
		return 0; 
	}
	child->stringName = child->stringValue;
	child->stringValue  = 0; 
	json = skipSpace(json +1); 
	//???
	json = parseValue(json, child); 
	//check for stringName to ensure that the 
	while(json && *json == ','){
		Json* newItem = new Json(); 
		newItem->prevs = child; 
		child->next = newItem; 
		child  = newItem;
		json = skipSpace(json+1);
		//check for null
		json = parseString(json, child); 
		child->stringName = child->stringValue; 
		child->stringValue = 0; 
		json = skipSpace(json);
		if(*json ==':'){
			json = skipSpace(json+1); 
			//parse value to child
			json = parseValue(json, child);
		}
		skipSpace(json);
	}

	char*tmp = json; 

	json = skipSpace(json); 
	if(json == 0 || *json !='}'){
		return 0; 
	}
	item->type = Object;
	return  json+1;
}

void printObject(Json* object){
	Json* child = object->child;
	printf("\n{\n");
	while(child != 0){
		printString(child->stringName);
		printf(":");
		printValue(child);
		child = child->next;
		if(child != 0){
			printf(",");
		}
	}
	printf("\n}\n"); 
}

char* serializeObject(Json* object) {
	if(!object) {
		return 0 ; 
	}

	char* out; 
	int entryCount = 0 ; 
	Json * ptr = object->child; 
	char* items[MAX_ARR_SIZE] ;  
	int len[MAX_ARR_SIZE];
	int objectLen =  3; 

	while (ptr != 0 ) {
		entryCount++ ; 
		int i = entryCount - 1; 
		char* key = serializeString(ptr->stringName); 
		
		char* value = serializeValue(ptr); 
		int keyLen  = strlen(key); 
		int valLen = strlen(value ); 
		len[i]  = keyLen  + valLen  + 2; 
		items[i] = new char[len[i]] ; 
		char* pos = items[i]; 
		
		strncpy (pos, key, keyLen); 
		delete [] key;
		pos+= keyLen ; 
		*pos = ':'; 
		++pos; 
		strncpy ( pos, value, valLen );

		delete [] value;

		pos += valLen; 
		*pos = '\0';
		objectLen+= len[i]; // ,  
		ptr = ptr->next ; 
	}

	if(entryCount == 0) {
		return "{}"; 
	}
	objectLen+= entryCount - 1; 

	out = new char[objectLen];
	out[0] = '{'; 
	char* pos = out+1; 
	for( int i =  0 ; i < entryCount ;  ++ i  ) {
		
		strncpy(pos, items[i], len[i]); 
		//TODO why len[i] -1, not len[i] ??????
		pos += len[i]-1; 
		*pos = ',';
		++pos; 
		delete [] items[i];
		items[i] = 0;
	}
	*(pos -1) ='}'; 
	*(pos) = '\0'; 
	return out; 
}


char* parseValue(char* json, Json* item){
	switch(*json){
	case '[':
		return parseArray(json, item); 
	case '{':
		return parseObject(json, item); 
	case '\"':
		return parseString(json, item);
	case '-':case '0':case '1': case '2': case '3': case '4':case '5':
	case '6': case '7': case '8': case '9':
		return parseNumber(json, item); 
	case 't':
		if(strlen(json) >=4 && *(json+1) =='r' && *(json+2) =='u' && *(json+3) =='e'){
			item->type = True;
			return json+4;
		} 
	case 'f':
		if(strlen(json) >= 5 && *(json+1) =='a' && *(json+2) =='l' && *(json+3) =='s' && *(json+4) =='e'){
			item->type = False; 
			return json + 5; 
		}
	case 'n':
		if(strlen(json) > 4 && *(json+1)=='u' && *(json+2) =='l' && *(json+3) == 'l'){
			item->type = Null;
			return json+4;
		} 
	default:
		return 0; 
	}
}

void printString(char* str){
	printf("\"%s\"", str); 
}

void printNumber(Json* number){
	printf("%f", number->doubleValue);
}

void printValue(Json* value){
	switch(value->type){
	case Number:
		printNumber(value); 
		return ; 
	case String:
		printString(value->stringValue); 
		return ; 
	case True:
		printf("true");
		return ; 
	case  False:
		printf("false");
		return ; 
	case Array:
		printArray(value); 
		return ; 
	case Object:
		printObject(value);
		return ; 
	case Null:
		printf("null");
		return ; 
	}
}

char* serializeValue (Json* value) {
	switch(value->type) {
	case Number: 
		return serializeNumber(value->doubleValue); 
	case String:
		return serializeString(value->stringValue); 
	case True:
		return serializeBoolean(true); 
	case False: 
		return serializeBoolean(false ); 
	case Array:
		return serializeArray(value ); 
	case Object:
		return serializeObject(value); 
	case Null:
		return serializeNull();
	default:return 0 ; 
	}
}



void getArrayValues(Json*  array, Json values[], int& length){
	length= 0 ; 
	Json* child = array->child; 
	while(child !=  0){
		values[length++] =*child; 
		child = child->next; 
	}
}

void getObjectValues(Json*  object, Json values[], int& length){
	length= 0 ; 
	Json* child = object->child; 
	while(child !=  0){
		values[length++] =*child; 
		if(child->next != 0 ){
			child = child->next; 	
		}else {
			child = 0 ; 
		}
	}
}

Json* getFieldOfObject(Json* object, char* fieldName){
	if(object != 0) {
		Json* child = object->child; 
		while(child != 0 && strcmp(child->stringName, fieldName)){
			child = child->next; 
		}

		if(child != 0 && strcmp(child->stringName, fieldName) == 0) {
			return child;
		}
		return 0;	
	}
	return 0;
}

char* skipSpace(char* json){
	while(json != 0 && (*json == ' ' || *json == '\t' || *json == '\n')){
		json ++; 
	}
	return json; 
}
