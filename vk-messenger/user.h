#ifndef USER_H
#define USER_H
#include <qstring.h>
#include <QPixmap>
class User
{
private :
	QString id; 
	QString firstName; 
	QString lastName; 
	int status; 
	QString profileImage;
	QPixmap avatar;
public:
	User(QString id, QString firstname, QString lastName, int status, QString profileImage/*, QPixmap pixmap*/) ;
	QString getId() const ; 
	QString getFirstName() const ; 
	QString getLastName() const ; 
	int getStatus() const ; 
	QString getFullName() const ; 
	QString getProfileImage() const; 
	QPixmap getAvatar () const;

	User();
	~User();
};
#endif ///USER_H
