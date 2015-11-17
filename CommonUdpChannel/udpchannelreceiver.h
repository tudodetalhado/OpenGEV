#ifndef DEVICECONTROLCHANNEL_H
#define DEVICECONTROLCHANNEL_H

#include "CommonUdpChannel/udpchannel.h"

#include "CommonMessages/conversionutils.h"

/**
 * @brief The ControlChannelSlave class provide a control channel that wait for new command
 * from a master control channel. It will automatically generate new message handler
 * for manage incoming command
 */
class UdpChannelReceiver : public UDPChannel
{
public:
    /**
     * @brief ControlChannelSlave constructor
     * @param sourceAddr
     * @param sourcePort
     * @param messageHandlerFactory factory used to generate a new message handler
     */
    UdpChannelReceiver(QHostAddress sourceAddr,
                         quint16 sourcePort,
                         AbstractMessageHandlerFactory *messageHandlerFactory);

    /**
     * @brief ~ControlChannelSlave deconstructor
     */
    virtual ~UdpChannelReceiver();

    /* HIHERIT DOCS */
    void processTheDatagram(QByteArray datagram, QHostAddress sender, quint16 senderPort);

private:
    /**
     * @brief messageHandlerFactory store factory reference used to generate a new message handler
     */
    AbstractMessageHandlerFactory* messageHandlerFactory;
};

#endif // DEVICECONTROLCHANNEL_H