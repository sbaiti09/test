#include "emailsender.h"
#include <QDebug>

EmailSender::EmailSender(const QString &from, const QString &to, const QString &subject, const QString &body, const QString &smtpServer, int port)
    : from(from), to(to), subject(subject), body(body), smtpServer(smtpServer), port(port) {

    appPassword = "kazz rxmu vmgz vhxt"; // Replace with a Google app password
    socket = new QSslSocket(this);
    connect(socket, &QSslSocket::encrypted, this, &EmailSender::onConnected);
    connect(socket, &QSslSocket::readyRead, this, &EmailSender::onReadyRead);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &EmailSender::onError);
}

void EmailSender::sendMail() {
    socket->connectToHostEncrypted(smtpServer, port);
}

void EmailSender::onConnected() {
    stream.setDevice(socket);
    sendCommand("EHLO " + smtpServer);
}

void EmailSender::onReadyRead() {
    QString response = socket->readAll();
    qDebug() << "Server response:" << response;

    if (response.startsWith("250")) {
        if (!authenticated) {
            sendCommand("AUTH LOGIN");
        } else {
            sendCommand("MAIL FROM:<" + from + ">");
            sendCommand("RCPT TO:<" + to + ">");
            sendCommand("DATA");
            sendCommand("Subject: " + subject + "\r\n\r\n" + body + "\r\n.");
        }
    } else if (response.startsWith("334")) {
        sendCommand(authenticated ? appPassword.toUtf8().toBase64() : from.toUtf8().toBase64());
        authenticated = true;
    }
}

void EmailSender::sendCommand(const QString &cmd) {
    stream << cmd << "\r\n";
    stream.flush();
}

void EmailSender::onError(QAbstractSocket::SocketError socketError) {
    qDebug() << "Error:" << socketError << socket->errorString();
}
