#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <random>
#include <windows.h>
#include "MyJson.h"
using namespace std; 

char* createBigJsonObject();
char* readFile(char* filename);
void writeFile(char*filename, char* data);

int main(int argc, char *argv[])
{	
	char*str ="{\"\":\"sjfhsjdhfjsdf\"}";
	MyJson parser; 
	Json* result  = new Json(); 
	parser.parseObject(str, result); 
	char* serialized = parser.serializeObject(result); 
	Json* value = parser.getFieldOfObject(result, "");
	str = 
		"{	\"students\":\
			[\
			{	\"name\": \"tuyenhm\", \"age\": \"22\", \
					\"school\": \"vstu\", \
					\"courses\": [\"oop\", \"uml\", \"logic\", \"theory of probability\", \"linux\"]	\
				}, \
				{\
					\"name\": \"blackrose\", \
					\"age\":22, \
					\"school\": \"vstu\", \
					\"courses\": [\"oop\", \"uml\", \"logic\", \"theory of probability\", \"linux\"]\
				}	\
			]\
		}";

	cout << "Input text :\n" <<str;

	
	Json* result1 = new Json(); 
	parser.parseObject(str, result1); 

	cout << "\nParsed object to string \n"; 

	parser.printObject(result1);

	system("pause"); 
	
	return 0 ; 
}

char* readFile(char* filename) {
	FILE* fp;
	fp = fopen(filename,"r");
	char c;
	char* text = new char[12*1024*2024];
	int pos = 0 ; 
	while(1)
	{
		c = fgetc(fp);
		
		if(c == '\\') {
			c = fgetc(fp);	
			if(c=='n') {
				c = '\n';
			}else if(c == 't') {
				c = '\t';
			}else if(c == '\\'){
							
			}else if(c =='\"') {
				c = '\'';
			}
		}
		
		text[pos++] = c;

		if( feof(fp))
		{
			break ;
		}
	}
	text[pos] = '\0';
	fclose(fp);
	return text;
}

void writeFile(char*filename, char*data){

	 ofstream myfile;
	 myfile.open (filename);
	 myfile << data;
	 myfile.close();
}

char* createBigJsonObject() {
	
	char* enjoySubjects[] = {"Mathematical", "Physic", "Informatical", "Music", "Chemistry", "Socialogy", "Phylosophy", "Literature", "Network", "Big data"};
	char* firstNames[] ={"Huynh", "Nguyen", "Pham", "Phan", "Do", "Le", "Duong", "Vo", "Ho", "Hoang"};
	char* lastNames[]= {"Tuyen", "Thang", "Duc", "Ngoc", "Quoc", "Dao", "Dien", "Truong", "Tam", "Quy"};
	char* quotes[] = {
			"I'm selfish, impatient and a little insecure. I make mistakes, \nI am out of control and at times hard to handle. But if you can't handle me at my worst, then you sure as hell don't deserve me at my best. A friend is someone who knows all \nabout you and still loves you", 
			"A friend is someone who knows all \nabout you and still loves you. You only live once, but if you do it right, \nonce is enough", 
			"Two things are infinite: the universe and human\n stupidity; and I'm not sure about the universe.", 
			"You only live once, but if you do it right, \nonce is enough. I love deadlines. I love the whooshing \nnoise they make as they go by.", 
			"Insanity is doing the same thing, over and \nover again, but expecting different results.I'm selfish, impatient and a little insecure. I make mistakes, \nI am out of control and at times hard to handle. But if you can't handle me at my worst, then you sure as hell don't deserve me at my best. A friend is someone who knows all \nabout you and still loves you", 
			"The person, be it gentleman or lady, who has \nnot pleasure in a good novel, must be intolerably stupid.", 
			"A day without sunshine is like, you know, night.The trouble with having an open mind, of course, is that people\n will insist on coming along and trying to put things in it.", 
			"I love deadlines. I love the whooshing \nnoise they make as they go by.I love deadlines. I love the whooshing \nnoise they make as they go by.", 
			"I'm not afraid of death; I just don't \nwant to be there when it happens. A day without sunshine is like, you know, night.", 
			"The trouble with having an open mind, of course, is that people\n will insist on coming along and trying to put things in it."
		};
	char* countries[] = {"Vietnam", "Korea", "Russia", "England", "American", "Ukraina", "France", "Sweden", "Spain", "German"};
	double weights[] = {40.5, 56.5, 60.0, 50.5, 48.0 , 44.3, 98.1, 65.2, 40.8, 78.5};

	char* text = new char[11*1024*2024];
	
	char* objects[] = { "{\"field1\":3, \"field2\": \"string1\", \"field3\": [4,2,1,23.1]}", 
						"{\"field1\":4, \"field2\": \"string2\", \"field3\": [14,2,1,23.1]}", 
						"{\"field1\":6, \"field2\": \"string3\", \"field3\": [324,23.1]}"};

	char*ptr = text; 
	strcpy(ptr, "{\"students\":["); 
	ptr+= strlen(text);
	for(int i = 0 ; i < MAX_ARR_SIZE; ++i ){
		*ptr = '{';
		ptr++; 
		//subject
		strcpy(ptr, "\"");
		ptr++;
		strcpy(ptr, "subject"); 
		ptr+=strlen("subject"); 
		strcpy(ptr, "\":"); 
		ptr+=2;
		strcpy(ptr, "\"");
		ptr++; 
		char* subject = enjoySubjects[rand()%10];
		strcpy(ptr, subject); 
		ptr+=strlen(subject); 
		strcpy(ptr, "\"");
		ptr +=1;
		*ptr=',';
		ptr++;
		//firstname
		strcpy(ptr, "\""); 
		ptr++;
		strcpy(ptr, "firstName"); 
		ptr+=strlen("firstName"); 
		strcpy(ptr, "\":"); 
		ptr+=2;
		strcpy(ptr, "\"");
		ptr++; 
		char* firstName = firstNames[rand()%10];
		strcpy(ptr, firstName); 
		ptr+=strlen(firstName); 
		strcpy(ptr, "\"");
		ptr +=1;
		*ptr=',';
		ptr++;
		//lastname
		strcpy(ptr, "\""); 
		ptr++;
		strcpy(ptr, "lastName"); 
		ptr+=strlen("lastName"); 
		strcpy(ptr, "\":"); 
		ptr += 2;
		strcpy(ptr, "\"");
		ptr++; 
		char* lastName = lastNames[rand()%10];
		strcpy(ptr, lastName); 
		ptr+=strlen(lastName); 
		strcpy(ptr, "\"");
		ptr += 1;
		*ptr=',';
		ptr++;
		//quote
		strcpy(ptr, "\""); 
		ptr++;
		strcpy(ptr, "quote"); 
		ptr+=strlen("quote"); 
		strcpy(ptr, "\":"); 
		ptr += 2;
		strcpy(ptr, "\"");
		ptr++; 
		char* quote = quotes[rand()%10];
		strcpy(ptr, quote); 
		ptr+=strlen(quote); 
		strcpy(ptr, "\"");
		ptr +=1;
		*ptr=',';
		ptr++;
		//country
		strcpy(ptr, "\""); 
		ptr++;
		strcpy(ptr, "country"); 
		ptr+=strlen("country"); 
		strcpy(ptr, "\":"); 
		ptr += 2;
		strcpy(ptr, "\"");
		ptr++; 
		char* country = countries[rand()%10];
		strcpy(ptr, country); 
		ptr+=strlen(country); 
		strcpy(ptr, "\"");
		ptr +=1;
		*ptr=',';
		ptr++;
		//object
		strcpy(ptr, "\""); 
		ptr++;
		strcpy(ptr, "object"); 
		ptr+=strlen("object"); 
		strcpy(ptr, "\":"); 
		ptr += 2; 
		char* object = objects[rand()%3];
		strcpy(ptr, object); 
		ptr+=strlen(object); 
		*ptr=',';
		ptr++;
		//weight
		strcpy(ptr, "\""); 
		ptr++;
		strcpy(ptr, "weight"); 
		ptr+=strlen("weight"); 
		strcpy(ptr, "\":"); 
		ptr += 2;
		strcpy(ptr, "50.5"); 
		ptr+=strlen("50.5"); 
		*ptr=',';
		ptr++;
		strcpy(ptr, "\""); 
		ptr++;
		strcpy(ptr, "age"); 
		ptr+=strlen("age"); 
		strcpy(ptr, "\":"); 
		ptr+=2;
		char age[3];
		sprintf(age, "%2d", rand()%10 +20);
		strcpy(ptr, "20"); 
		ptr+=strlen("20"); 
		*ptr = '}';
		ptr++;
		*ptr =',';
		ptr++;
	}
	ptr--;
	strcpy(ptr, "]}");
	return text; 
}

