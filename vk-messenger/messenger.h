#ifndef MESSENGER_H
#define MESSENGER_H

#include <QtGui/QMainWindow>
#include "ui_messenger.h"
#include "user.h"
#include <qnetworkaccessmanager.h>
#include <json_parser.h>
#include <QPixmap>

#include <qbuffer.h>

struct Message{
	QString body; 
	long time; 
	int readState; 
	int id; 
	bool incomming;
	int fromId;
};


class Messenger : public QMainWindow
{
	Q_OBJECT

public:
	Messenger(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Messenger();

private:
	Ui::MessengerClass ui;
	QString token; 
	QByteArray GET(QUrl );
	QList<User> users; 
	QTimer* timer; 
	bool isChatting;
	QString currentUid;
	QString currentUsername;

	QString myName;
	QString myId;
	QBuffer* buffer;

	void loadToken(); 
	
	QByteArray imageBytes;

	QString space; 

	void saveToken(); 
	bool isValidToken(QString str); 
	void showFriendList(); 
	QNetworkAccessManager* networkAccessManager ; 
	void  printJsonInQt(Json* item);

	QString getUsername(QString fullName); 
	void markAsRead(QString messageId); 
	void setEnableChatWidgets(bool enable);
	QString constructSpace(int spaceCount);
	QPixmap getImage(QString link);
	void displayPreviousMessage(QString uid);
	QString processRawMessage(char* rawMessage); 
	QMovie* spinner; 

	QList<Message> getChatHistory(QString uid, int count);
	void fetchPreviousMessages(QList<Message> incomming, QList<Message> outcommig); 
	void runSpinner();
	void stopSpinner();

signals :
	void authSuccess(); 

private slots :
	void updateCurrentChatPeer(int, int); 
	void getFriends();
	void urlCheck(QUrl url);
	void afterAuthSuccess();
	void sendMessage();
	void print(); 
	void displayRealtimeMessage();
	void getUnreadMessagesFromFriend(/*QString uid*/);
	void logout(); 
	QByteArray GET(QString url);

};

#endif // MESSENGER_H
