// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef _YARP2_REMOTEFRAMEGRABBER_
#define _YARP2_REMOTEFRAMEGRABBER_

#include <yarp/dev/ServerFrameGrabber.h>
#include <yarp/os/Network.h>


namespace yarp{
    namespace dev {
      class RemoteFrameGrabber;
    }
}

/**
 * @ingroup dev_impl_wrapper
 *
 * Connect to a ServerFrameGrabber.  See ServerFrameGrabber for
 * the network protocol used.
 */
class yarp::dev::RemoteFrameGrabber : public IFrameGrabberImage, 
            public IFrameGrabberControls,
            public DeviceDriver {

public:
    /**
     * Constructor.
     */
    RemoteFrameGrabber() {
        lastHeight = 0;
        lastWidth = 0;
    }

    virtual bool getImage(yarp::sig::ImageOf<yarp::sig::PixelRgb>& image) {
        
        if (reader.read(true)!=NULL) {
            image = *(reader.lastRead());
            lastHeight = image.height();
            lastWidth = image.width();
            return true;
        }
        return false;
    }

    virtual int height() const {
        return lastHeight;
    }

    virtual int width() const {
        return lastWidth;
    }

    /**
     * Configure with a set of options. These are:
     * <TABLE>
     * <TR><TD> local </TD><TD> Port name of this client. </TD></TR>
     * <TR><TD> remote </TD><TD> Port name of server to connect to. </TD></TR>
     * </TABLE>
     *
     * @param config The options to use
     * @return true iff the object could be configured.
     */
    virtual bool open(yarp::os::Searchable& config){
        remote = config.find("remote").asString().c_str();
        local = config.find("local").asString().c_str();
        if (local!="") {
            port.open(local.c_str());
        }
        if (remote!="") {
            yarp::os::Network::connect(remote.c_str(),local.c_str());

            // reverse connection for RPC
            // could choose to do this only on need
            yarp::os::Network::connect(local.c_str(),remote.c_str());
        }
        reader.attach(port);
        return true;
    }

    virtual bool close() {
        return true;;
    }

    virtual bool setBrightness(double v) {
        return setCommand(VOCAB_BRIGHTNESS,v);
    }

    virtual bool setShutter(double v) {
        return setCommand(VOCAB_SHUTTER,v);
    }

    virtual bool setGain(double v) {
        return setCommand(VOCAB_GAIN,v);
    }

    virtual double getBrightness() const {
        return getCommand(VOCAB_BRIGHTNESS);
    }

    virtual double getShutter() const {
        return getCommand(VOCAB_SHUTTER);
    }

    virtual double getGain() const {
        return getCommand(VOCAB_GAIN);
    }


private:
    yarp::os::Port port;
    yarp::os::PortReaderBuffer<yarp::sig::ImageOf<yarp::sig::PixelRgb> > reader;
    yarp::os::ConstString remote;
    yarp::os::ConstString local;
    int lastHeight;
    int lastWidth;

    bool setCommand(int code, double v) {
        yarp::os::Bottle cmd;
        cmd.addVocab(VOCAB_SET);
        cmd.addVocab(code);
        cmd.addDouble(v);
        port.write(cmd);
        return true;
    }

    double getCommand(int code) const {
        yarp::os::Bottle cmd, response;
        cmd.addVocab(VOCAB_GET);
        cmd.addVocab(code);
        port.write(cmd,response);
        // response should be [cmd] [name] value
        return response.get(2).asDouble();
    }

};


#endif
