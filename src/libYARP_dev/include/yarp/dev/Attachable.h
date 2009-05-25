// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
* Copyright (C) 2008 RobotCub Consortium
* Authors: Lorenzo Natale
* CopyPolicy: Released under the terms of the GNU GPL v2.0.
*/

#ifndef __YARPATTACHABLEINTERFACE__
#define __YARPATTACHABLEINTERFACE__

#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/PolyDriverList.h>

/*! \file Attachable.h define the interface for an attachable object*/

namespace yarp {
    namespace dev {
        class IAttachable;
        class IMultipleAttachable;
    }
}

/**
 * @ingroup dev_iattachable
 *
 * Interface for an object that can "attach" to another. This is useful
 * for example when an object refers internally to another device, but
 * you want to decouple the creation of the two objects. In this case
 * you first creates the two objects separately then you can attach one 
 * to the other.
 */
class yarp::dev::IAttachable
{
public:
    /**
     * Destructor.
     */
    virtual ~IAttachable() {}

    /*
    * Attach to another object.
    * @param poly: the polydriver that you want to attach to.
    * @return true/false on success failure.
    */
    virtual bool attach(PolyDriver *poly)=0;

    /*
    * Detach the object (you must have first called attach).
    * @return true/false on success failure.
    */
    virtual bool detach()=0;
};

/**
 * @ingroup dev_imultipleattachable
 *
 * Interface for an object that can "attach" to another. This is useful
 * for example when an object refers internally to another device, but
 * you want to decouple the creation of the two objects. In this case
 * you first creates the two objects separately then you can attach one 
 * to the other. This class is similar to IAttachable, but allows attaching
 * to more than one object by subsequent calls to attach.
 */
class yarp::dev::IMultipleAttachable
{
public:
    /**
     * Destructor.
     */
    virtual ~IMultipleAttachable() {}

    /*
    * Attach to another object.
    * @param poly: the polydriver that you want to attach to.
    * @key: specify the key which identifies the driver to attach to.
    * @return true/false on success failure.
    */
    virtual bool attachAll(const PolyDriverList &p)=0;

    /*
    * Detach the object (you must have first called attach).
    * @return true/false on success failure.
    */
    virtual bool detachAll()=0;
};

#endif

