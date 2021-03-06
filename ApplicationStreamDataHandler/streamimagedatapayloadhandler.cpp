#include "streamimagedatapayloadhandler.h"

StreamImageDataPayloadHandler::StreamImageDataPayloadHandler(GVComponent *target, const QByteArray &receivedDatagram,
                                                             QHostAddress senderAddress, quint16 senderPort)
    : AbstractStreamDataHandler(target, PacketFormat::DATA_PAYLOAD_GENIRIC_FORMAT, receivedDatagram, senderAddress, senderPort)
{
}

int StreamImageDataPayloadHandler::execute()
{
    int resultStatus;

    if(!checkHeader())
        resultStatus = GEV_STATUS_INVALID_HEADER;
    else {

        StreamDataReceiver* receiver = (StreamDataReceiver*) target;

        QByteArray datagramWithoutHeader = receivedDatagram.mid(20);

        const char* origin = datagramWithoutHeader.data();
        if(!receiver->addData(getRequestBlockId(), getRequestPacketId(), origin, datagramWithoutHeader.size()))
            return GEV_STATUS_ERROR;

        resultStatus = GEV_STATUS_SUCCESS;
    }

    return resultStatus;
}

