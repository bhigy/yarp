// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-
#ifndef _YARP2_SOUND_
#define _YARP2_SOUND_

#include <yarp/os/Portable.h>

namespace yarp {
  namespace sig {
    class Sound;
  }
}

/**
 * \ingroup sig_class
 *
 * Class for storing sounds
 */
class yarp::sig::Sound : public yarp::os::Portable {
public:
    Sound(int bytesPerSample = 1);

    /**
     * Copy constructor.  
     * Clones the content of another sound.
     * @param alt the image to sound
     */
    Sound(const Sound& alt);

    virtual ~Sound();

    /**
     * Assignment operator.
     * Clones the content of another sound.
     * @param alt the image to sound
     */
    const Sound& operator=(const Sound& alt);

    void resize(int samples, int channels = 1);

    int get(int sample, int channel = 0);
    void set(int value, int sample, int channel = 0);

    int getSafe(int sample, int channel = 0) {
        if (isSample(sample,channel)) {
            return get(sample,channel);
        }
        return 0;
    }

    void setSafe(int value, int sample, int channel = 0) {
        if (isSample(sample,channel)) {
            set(value,sample,channel);
        }
    }

    /**
     * Check whether a sample lies within the sound
     * @param sample the sample to choose
     * @param channel the channel to choose
     * @return true iff there is a sample at the given coordinate
     */
    inline bool isSample(int sample, int channel=0) const {
        return (sample>=0 && channel>=0 && sample<samples && channel<channels);
    }

    //int getFrequency() const;
    //void setFrequency(int freq);

    int getBytesPerSample() const { return bytesPerSample; }

    int getSamples() const { return samples; }

    int getChannels() const { return channels; }

    virtual bool read(ConnectionReader& connection);

    virtual bool write(ConnectionWriter& connection);

private:
    void init(int bytesPerSample);

    void *implementation;
    int samples;
    int channels;
    int bytesPerSample;
    int frequency;
};

#endif
