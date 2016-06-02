#include "user.h"


User::User(QString id, QString firstName, QString lastName, int status, QString profileImage/*, QPixmap avatar*/){
	this->id = id; 
	this->firstName = firstName; 
	this->lastName = lastName; 
	this->status = status; 
	this->profileImage = profileImage; 
	this->avatar = avatar;
}

QString User::getId() const{
	return id; 
}

QString User::getFirstName() const{
	return firstName; 
}

QString User::getLastName() const{
	return lastName; 
}

QString User::getFullName() const{
	return firstName +" " + lastName; 
}

int User::getStatus() const{
	return status; 
}

QString User::getProfileImage() const {
	return profileImage;
}

QPixmap User::getAvatar() const {
	return avatar;
}

User::User()
{
}



User::~User()
{
}
