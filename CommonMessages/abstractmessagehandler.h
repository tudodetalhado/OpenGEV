#ifndef ABSTRACTMESSAGEHANDLER_H
#define ABSTRACTMESSAGEHANDLER_H

#include <QString>
#include <QHostAddress>

#include "CommonComponent/gvcomponent.h"
#include "CommonMessages/privilege.h"

/**
 * \brief The AbstractMessageHandler class is generic handler
 * for incoming message on slave channel
 */
class AbstractMessageHandler
{
public:
    /**
     * @brief AbstractMessageHandler
     * @param target component where the new message should be applied
     * @param ackCode acknoledgment code
     * @param datagram datagram received
     * @param senderAddress who send the datagram
     * @param senderPort destination port of the datagram
     */
    AbstractMessageHandler(GVComponent* target,
                           quint16 ackCode,
                           QByteArray datagram,
                           QHostAddress senderAddress,
                           quint16 senderPort);


    /**
     * @brief ~AbstractMessageHandler decostructor
     */
    virtual ~AbstractMessageHandler();

    /**
     * @brief getTarget
     * @return target for this command
     */
    GVComponent* getTarget();

    /**
     * @brief getDatagram
     * @return datagram received
     */
    QByteArray* getDatagram();

    /**
     * @brief getSenderAddress
     * @return sender address
     */
    QHostAddress getSenderAddress();


    quint16 getSenderPort();

    /**
     * @brief isAllowed
     * @return true if this command is allowed on the target
     */
    virtual bool isAllowed(Privilege ctrlChannelPrivilege) = 0;

    /**
     * @brief execute a command on the target
     * @param datagram data received
     * @param sender of datagram
     * @param port
     * @return error code
     */
    virtual int execute(Privilege ctrlChannelPrivilege) = 0;

    /**
     * @brief isAckAllowed check if the command is allowed on the target
     * @return true if it's allowed
     */
    bool isAckAllowed();

    /**
     * @brief readRequestCommandCode extract command code from a datagram
     * @param datagram
     * @return command code
     */
    static quint16 readRequestCommandCode(QByteArray* datagram);

    /**
     * @brief readRequestRequestLength extract length from a datagram
     * @param datagram
     * @return length
     */
    static quint16 readRequestRequestLength(QByteArray* datagram);

    /**
     * @brief readRequestRequestId extract request id from a datagram
     * @param datagram
     * @return request id
     */
    static quint16 readRequestRequestId(QByteArray* datagram);

    /**
     * @brief getRequestCommandCode
     * @return request command code
     */
    quint16 getRequestCommandCode();

    /**
     * @brief getRequestLength
     * @return request length
     */
    quint16 getRequestLength();

    /**
     * @brief getRequestId
     * @return request id
     */
    quint16 getRequestId();

    /**
     * @brief getResultStatus
     * @return result of execution
     */
    quint16 getResultStatus();

    /**
     * @brief getAck
     * @return message for acknowledgement
     */
    virtual QByteArray* getAckDatagram() final;

    /**
     * @brief toString
     * @return handler major info as string
     */
    std::string toString();

protected:
    /*!
     * \brief target component
     */
    GVComponent* target;

    QByteArray datagram;

    QHostAddress sender;

    quint16 port;

    quint16 ackCode;

    quint16 resultStatus;

    quint16 requestCommandCode;

    quint16 requestLength;

    quint16 reqId;

    bool ackNotAllowed = false;

    /**
     * @brief getAckHeader
     * @return header for ack message
     */
    virtual char* getAckHeader() final;

    /**
     * @brief checkHeader check received datagram
     * @return true if header is good
     */
    virtual bool checkHeader() final;

    /*!
     * \brief getAck
     * \return message for acknowledgement without header
     */
    virtual char* getAckDatagramWithoutHeader() = 0;

    /*!
     * \brief getAck message without length
     * \return message for acknowledgement
     */
    virtual quint16 getAckDatagramLengthWithoutHeader() = 0;

};

#endif // ABSTRACTMESSAGEHANDLER_H
