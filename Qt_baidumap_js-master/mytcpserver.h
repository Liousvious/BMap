#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H


#include <QTcpSocket>
#include <QTcpServer>

class MyTCPServer : public QTcpServer
{
    Q_OBJECT
  public:
    explicit MyTCPServer(QObject *parent = nullptr);
    bool listen(QHostAddress addr, quint16 port);
    void sendMessage(QString string);
    void stopConnection();
    void stopListening();

  signals:
    void newMessage(const QString &from, const QString &message);
    void myServerConnected(const QString &from, quint16 port);
    void myServerDisconnected();

  private slots:
    void onConnected();
    void onDisconnected();
    void messageReady();

  private:
    QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;
    QByteArray array;
    QHostAddress clientAddr;
    quint16 clientPort;
};

#endif // MYTCPSERVER_H
