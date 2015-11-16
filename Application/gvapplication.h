#ifndef GVAPPLICATION_H
#define GVAPPLICATION_H

#include <QList>

#include "CommonComponent/gvcomponent.h"

#include "CommonControlChannel/controlchannelmaster.h"

#include "partnerdevice.h"

#include "ApplicationCommand/discoverycommand.h"
#include "ApplicationCommand/readregistercommand.h"
#include "ApplicationCommand/writeregistercommand.h"

#include "Device/deviceregisters.h"

/**
 * @brief The GVApplication class provide methods for application in GigE vision network.
 * It manage discovery for GigE device and send command to it
 */
class GVApplication : public GVComponent
{
public:
    /**
     * @brief GVApplication constructor
     * @param primaryChannelport local port for send broadcast message or common message on GigE vision network
     */
    GVApplication(int primaryChannelport=5000);
    /**
     * @brief ~GVApplication object deconstructor
     */
    virtual ~GVApplication();

    /**
     * @brief clearDevices method destory all the discoreved devices
     */
    void clearDevices();

    /**
     * @brief addDevice method add a new device to discovered device list
     * @param aDevice new device
     */
    void addDevice(PartnerDevice aDevice);

    /**
     * @brief getDiscoveredDevice method
     * @return list of discovered devices
     */
    QList<PartnerDevice> getDiscoveredDevice();

    /**
     * @brief discoverDevice send a broadcast message for device discover
     * @return 0 if command success
     */
    int discoverDevice();

    /**
     * @brief getStreamingChannelNumber
     * @param device
     * @return
     */
    int getStreamingChannelNumber(PartnerDevice device);

    /**
     * @brief setControlAccessKey
     * @param device
     * @param key
     */
    void setControlAccessKey(PartnerDevice device, int key);

private:

    /**
     * @brief devices store discovered devices list
     */
    QList<PartnerDevice> devices;

    /**
     * @brief masterChannel is broadcast control channel
     */
    ControlChannelMaster* masterChannel;

};

#endif // GVAPPLICATION_H
