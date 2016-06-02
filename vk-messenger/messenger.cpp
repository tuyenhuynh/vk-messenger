#include "messenger.h"
#include <QUrl>
#include <qnetworkproxy.h>
#include < QNetworkReply> 
#include < QSslError>
#include <qdebug.h>
#include < QTimer>
#include <qdatastream.h>
#include <qfile.h>
#include "json.h"
#include <QBitmap>
#include <QSizePolicy>
#include <QtextCursor>
#include <QTime>
#include <QHttp>
#include <QBuffer>
#include <qpixmap.h>
#include <qmovie.h> 
#include <qdatetime.h>
using namespace QtJson; 

Messenger::Messenger(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	QIcon icon("vk_logo.PNG");
	
	this->setWindowIcon(icon); 
	
	networkAccessManager = new QNetworkAccessManager(this);
	timer = new QTimer(); 
	connect(ui.webView, SIGNAL(urlChanged(QUrl)), this, SLOT(urlCheck(QUrl)));
	connect(this, SIGNAL(authSucess()), this, SLOT(afterAuthSuccess()));  
	connect(ui.friendList, SIGNAL(cellClicked ( int, int)), this, SLOT(updateCurrentChatPeer(int, int)));
	//connect(ui.btnLogout, SIGNAL(clicked()), this, SLOT(logout()));
	connect(timer, SIGNAL(timeout()), this, SLOT(displayRealtimeMessage()));
	connect(ui.message, SIGNAL(returnPressed()), this, SLOT(sendMessage()));
	connect(ui.btnSend, SIGNAL(clicked()), this, SLOT(sendMessage()));
	ui.chatContent->setTextInteractionFlags(Qt::TextInteractionFlag::NoTextInteraction | Qt::TextInteractionFlag::TextSelectableByMouse);
	
	setEnableChatWidgets(false);
	ui.friendList->setColumnWidth(0, 200);

	token = "";

	ui.chatFrame->hide(); 
	ui.loginFrame->show();
	ui.webView->load(QUrl("http://oauth.vk.com/authorize?client_id=5108374&scope=offline,friends,messages&redirect_uri=https://oauth.vk.com/blank.html&display=wap&v=5.40&response_type=token"));	

	timer->start(); 

}

void Messenger::logout(){
	timer->stop(); 
	token = "";
	ui.chatFrame->hide(); 
	ui.loginFrame->show(); 
	ui.webView->load(QUrl("http://oauth.vk.com/authorize?client_id=5108374&scope=offline,friends,messages&redirect_uri=https://oauth.vk.com/blank.html&display=wap&v=5.40&response_type=token"));	
}

void Messenger::setEnableChatWidgets(bool enable) {
	ui.message->setEnabled(enable); 
	ui.btnSend->setEnabled(enable);
}

void Messenger::updateCurrentChatPeer(int row, int col) {
	QString  previousUid = currentUid; 
	currentUid = ui.friendList->item(row, 0)->data(Qt::UserRole).toString();
	if(previousUid.compare(currentUid)) {
		currentUsername = users.at(row).getFirstName() + " " + users.at(row).getLastName(); 
		ui.chatContent->clear(); 
		setEnableChatWidgets(true); 
		if(currentUsername.length() > 3) {
			space = constructSpace(currentUsername.length() -1);

		}else {
			space = "";
		}

		ui.partnerName->setText(currentUsername);
		QPixmap avatar = getImage(users.at(row).getProfileImage());

		ui.peerAvatar->setPixmap(avatar); 
		
		runSpinner();
		setEnableChatWidgets(false);
		displayPreviousMessage(currentUid);
		setEnableChatWidgets(true);
		stopSpinner();
	}
}

QString Messenger::getUsername(QString fullName) {
	QStringList names = fullName.split(" "); 
	return names.at(0); 
}

void Messenger::displayRealtimeMessage() {
/*
	if(!currentUid.isEmpty()) {
		getUnreadMessagesFromFriend(currentUid); 
	}
*/

	getUnreadMessagesFromFriend(); 

	/*for(int i = 0 ; i < ui.friendList->rowCount() ;  ++ i) {
		QString uid = ui.friendList->item(i , 0)->data(Qt::UserRole).toString();
		if(uid == currentUid) {
			getUnreadMessagesFromFriend(currentUid); 
		}
	}*/
}



QList<Message> Messenger::getChatHistory(QString uid,  int count){

	QList<Message> messages;

	QUrl url("https://api.vk.com/method/messages.getHistory?");
	url.addQueryItem("v", "5.40");
	url.addQueryItem("access_token", token); 
	url.addQueryItem("user_id", uid);
	url.addQueryItem("rev", 0); 

	url.addQueryItem("count", QString::number(count));

	QByteArray reply = GET(url);
	
	QString text = QString::fromUtf8(reply.data());

	const char* data = text.toStdString().data();

	char* convertedText = text.toAscii().data();

	Json* replyObject = new Json(); 
	parseObject(reply.data(),replyObject);

	Json* response = getFieldOfObject(replyObject, "response");
	Json* items = getFieldOfObject(response, "items");

	if( items != 0) {
		Json* jsonMessage = items->child; 
		while(jsonMessage != 0 ) {
			int date = getFieldOfObject(jsonMessage, "date")->intValue;
			char* messageBody = getFieldOfObject(jsonMessage, "body")->stringValue; 
			int readState = getFieldOfObject(jsonMessage, "read_state")->intValue; 
			int id = getFieldOfObject(jsonMessage, "id")->intValue;
			int fromId = getFieldOfObject(jsonMessage, "from_id")->intValue;
			int out = getFieldOfObject(jsonMessage, "out")->intValue;
			//eliminate messages with attachments
			if(getFieldOfObject(jsonMessage, "attachments") == 0) {
				Message m;
				m.readState = readState;
				m.time = date;
				//QString str = QString::code
				m.body = QString::fromUtf8(messageBody);
				m.id = id; 
				m.incomming = (out ==0); 
				m.fromId= fromId;
				messages.append(m); 	
			}
			jsonMessage = jsonMessage->next; 
		}
	}
	return messages;
}

void Messenger::getUnreadMessagesFromFriend(/*QString uid*/) {

	QUrl url("https://api.vk.com/method/messages.get?");
	url.addQueryItem("v", "5.40");
	url.addQueryItem("access_token", token); 
	//url.addQueryItem("user_id", uid);
	url.addQueryItem("out","0");
	url.addQueryItem("count", "1");

	QByteArray reply = GET(url);

	Json* replyObject = new Json(); 
	parseObject(reply.data(),replyObject);

	Json* response = getFieldOfObject(replyObject, "response");
	Json* items = getFieldOfObject(response, "items");

	char* rawMessage = 0;
	int readState = -1;
	int messageId;
	int senderId;
	if( items != 0) {
		Json* jsonMessage = items->child; 
		if(getFieldOfObject(jsonMessage, "attachments") == 0) {
			rawMessage = getFieldOfObject(jsonMessage, "body")->stringValue; 
			readState = getFieldOfObject(jsonMessage, "read_state")->intValue; 
			messageId = getFieldOfObject(jsonMessage, "id")->intValue; 		
			senderId = getFieldOfObject(jsonMessage, "user_id")->intValue;
		}
	}

	QString senderIdStr = QString::number(senderId); 

	if(rawMessage != 0 && readState == 0 && currentUid.compare(senderIdStr) == 0) {
		ui.chatContent->moveCursor(QTextCursor::End);
		QString time = QTime::currentTime().toString("[hh:mm:ss]");
		ui.chatContent->insertPlainText(currentUsername +  ":" + time + "  " + QString::fromUtf8(rawMessage)/*processRawMessage(rawMessage)*/ + "\n"); 	
		markAsRead(QString::number(messageId)); 
		qDebug() << currentUid;
		//qDebug() << uid;
	}
}

QString  Messenger::processRawMessage(char* rawMessage) {
	QString rawMessageBody = QString(rawMessage);
	QString messageBody; 
	for(int i = 0 ; i < rawMessageBody.length (); ++i ){
		if(rawMessageBody.at(i) != '\\'){
			messageBody.append(rawMessageBody.at(i)); 
		}else {
			i++; 
			if(rawMessageBody.at(i) == 'n'){
				messageBody.append("\n");
			}else if(rawMessageBody.at(i) =='t') {
				messageBody.append('\t');
			}else {
				messageBody.append(rawMessageBody.at(i)); 
			}
		}
	}
	return messageBody;
}

void Messenger::displayPreviousMessage(QString uid) {
	
	QList<Message> messages = getChatHistory(uid, 10); 
	for( int i =  messages.size() -1  ; i >= 0 ; --i ){
		ui.chatContent->moveCursor(QTextCursor::End);
		if(messages.at(i).incomming) {
			QString time = QTime::currentTime().toString("[hh:mm:ss]");
			ui.chatContent->insertPlainText(currentUsername +  ":" + time + "  " + messages.at(i).body + "\n"); 	
		}else {
			QDateTime date;
			date.setTime_t(messages.at(i).time); 
			QString time = date.toString("[hh:mm:ss]");
			ui.chatContent->insertPlainText("me: " +  space  +  time + "  " + messages.at(i).body + "\n"); 	
		}
	}
}


void Messenger::markAsRead( QString messageId) {
	QUrl url = QUrl("https://api.vk.com/method/messages.markAsRead?"); 
	url.addQueryItem("v", "5.40");
	url.addQueryItem("access_token", token); 
	url.addQueryItem("peer_id", currentUid);
	url.addQueryItem("message_ids", messageId);
	QByteArray reply = GET(url);
}

QString Messenger::constructSpace(int spaceCount ){
	QString spaceStr; 
	for(int i = 0 ; i < spaceCount ; ++ i ) {
		spaceStr += " "; 
	}
	return spaceStr;
}

void Messenger::sendMessage() {
	if(currentUid != "" ) {
		QString message = ui.message->text();
		if(!message.isEmpty()) {
			
			//display message
			ui.chatContent->moveCursor(QTextCursor::End);
			QTime time = QTime::currentTime();
			QString timeStr = time.toString("[hh:mm:ss]");
			ui.chatContent->insertPlainText("me: " + space + timeStr + "  " + message +"\n");
			ui.message->setText("");
			
			QUrl url = QUrl("https://api.vk.com/method/messages.send?"); 
			url.addQueryItem("v", "5.40");
			url.addQueryItem("access_token", token); 
			url.addQueryItem("user_id", currentUid);
			url.addQueryItem("message", message);

			QByteArray reply = GET(url);

			Json* replyObject = new Json(); 
			parseObject(reply.data(),replyObject );

			if(replyObject != 0 && getFieldOfObject(replyObject, "error") == 0) {
				/*ui.chatContent->moveCursor(QTextCursor::End);
				QTime time = QTime::currentTime();
				QString timeStr = time.toString("[hh:mm:ss]");
				u`i.chatContent->insertPlainText("me: " + space + timeStr + "  " + message +"\n");
				ui.message->setText("");*/ 
			}
		}	
	}
}

void Messenger::print() {
	qDebug() << "a"; 
}

void Messenger::urlCheck(QUrl url){
	url = url.toString().replace("#", "?"); 
	
	if(!url.toString().contains("access_token")){
		return; 
	}

	token = url.queryItemValue("access_token"); 
	myId = url.queryItemValue("user_id");
	//myName = url.queryItems("");


	QUrl myUrl("https://api.vk.com/method/users.get?");
	myUrl.addQueryItem("user_ids", myId); 
	myUrl.addQueryItem("fields", "first_name, last_name,photo"); 
	QByteArray reply = GET(myUrl);
	Json* jsonObject = new Json(); 
	parseObject(reply.data(), jsonObject);
	Json* response = getFieldOfObject(jsonObject, "response"); 
	Json* me = response->child; 
	QString myAvatarLink = QString(getFieldOfObject(me, "photo")->stringValue).remove("\\");

	myName = QString(getFieldOfObject(me, "first_name")->stringValue)  +" " + QString(getFieldOfObject(me, "last_name")->stringValue);

	QPixmap myAvatar = getImage(myAvatarLink);
	ui.myAvatar->setPixmap(myAvatar); 
	ui.loginFrame->hide();
	ui.chatFrame->show();

	ui.myName->setText(myName);

	runSpinner();
	getFriends();
	stopSpinner();
	timer->start(); 
}

void Messenger::runSpinner() {
	spinner = new QMovie("spinner.GIF");
	QSize size (50, 50); 
	spinner->setScaledSize(size); 
	ui.gif->setMovie(spinner); 
	spinner->start(); 
}


void Messenger::stopSpinner(){
	spinner->stop(); 
	spinner = new QMovie();
	ui.gif->setMovie(spinner);

}

void Messenger::afterAuthSuccess() {
	ui.loginFrame->hide();
	ui.chatFrame->show(); 
	ui.chatContent->clear();
	getFriends();
}

void Messenger::getFriends() {
	QUrl url = QUrl("https://api.vk.com/method/friends.get?"); 
	url.addQueryItem("access_token", token); 
	url.addQueryItem("v", "5.40");
	url.addQueryItem("fields", "first_name,last_name,uid,photo");
	QByteArray reply = GET(url);
	char* jsondata = reply.data();
	
	Json* item = new Json();

	parseObject(jsondata, item); 

	bool ok = true;
	Json* response = getFieldOfObject(item, "response");
	if(response != 0){
		Json* items = getFieldOfObject(response, "items"); 
		int length;	
		users.clear(); 
		Json values[1000];
		getObjectValues(items, values, length); 
		for( int i = 0 ; i < length ; ++i){
			QString id = QString::number(getFieldOfObject(values+i, "id")->intValue);
			QString firstName = QString::fromAscii(getFieldOfObject(values+i, "first_name")->stringValue); 
			QString lastName = QString::fromAscii(getFieldOfObject(values+i ,"last_name")->stringValue); 
			QString rawProfileImagePath  = QString::fromAscii(getFieldOfObject(values+i, "photo")->stringValue);
			QString profileImagePath = rawProfileImagePath.replace('\\', ""); 

			qDebug() << "Profile image : " + profileImagePath;
			int status = getFieldOfObject(values+i, "online")->intValue; 
			//QPixmap avatar = getImage(profileImagePath);
			users.append(User(id, firstName, lastName, status, profileImagePath/*, avatar*/)); 
		}
		showFriendList();
		
	}
}



QPixmap Messenger::getImage(QString link) {
	QUrl url(link); 
	QPixmap image;
	image.loadFromData(GET(link)); 
	return image;
}

void Messenger::showFriendList(){
	for( int i  = ui.friendList->rowCount()-1  ; i >= 0; --i){
		ui.friendList->removeRow(i); 
	} 
	for(int i = 0; i<users.size() ; ++i){
		ui.friendList->insertRow(i);
		QTableWidgetItem* item;
		item = new QTableWidgetItem(/*QIcon(users.at(i).getProfileImage()), */users.at(i).getFullName());
		ui.friendList->setItem(i, 0, item); 
		/*QString status = users.at(i).getStatus() == 0 ? "Offline" : "Online";
		item = new QTableWidgetItem(status);
		ui.friendList->setItem(i, 1, item);*/
		QString id = users.at(i).getId(); 
		
		ui.friendList->item(i, 0)->setData(Qt::UserRole, id);
		
		/*QString profileImageUrl  = users.at(i).getProfileImage(); 
		
		QUrl url (profileImageUrl);
		
		qDebug() << url.toString();

		QPixmap avatar = getImage(profileImageUrl);*/
	}
}

bool Messenger::isValidToken(QString str) {
	bool isValid = false;
	QUrl url = QUrl("https://api.vk.com/method/users.get?"); 
	url.addQueryItem("access_token", str); 
	url.addQueryItem("v", "5.40");
	url.addQueryItem("user_ids", "1");
	QByteArray reply = GET(url);
	if(reply.contains("response")){
		isValid = true;
	}
	return isValid; 
}

QByteArray Messenger::GET(QString url){

	QNetworkAccessManager* manager = new QNetworkAccessManager(this);
	QNetworkReply* reply = manager->get(QNetworkRequest(url)); 
	QEventLoop wait; 
	connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
	QTimer::singleShot(20000, &wait, SLOT(quit()));
	wait.exec(); 
	
	QByteArray answer = reply->readAll(); 

	QString type = reply->header(QNetworkRequest::ContentTypeHeader).toString();
	
	reply->deleteLater();
	return answer; 	
}

QByteArray Messenger::GET(QUrl url){
	
	QNetworkAccessManager* manager = new QNetworkAccessManager(this);
	
	QNetworkReply* reply = manager->get(QNetworkRequest(url)); 
	QEventLoop wait; 
	connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
	QTimer::singleShot(20000, &wait, SLOT(quit()));
	wait.exec(); 
	
	QByteArray answer = reply->readAll(); 

	reply->deleteLater();
	return answer; 
}

void Messenger::loadToken(){
	QFile file("setting.ini");
	if(file.open(QIODevice::ReadOnly)){
		QDataStream stream(&file);
		stream>>token;
	}
}

void Messenger::saveToken(){
	QFile file("setting.ini"); 
	if(file.open(QIODevice::WriteOnly| QIODevice::Truncate)){
		QDataStream stream(&file); 
		stream<< token; 
	}
}

void Messenger::printJsonInQt(Json* item){
	
}

Messenger::~Messenger()
{

}