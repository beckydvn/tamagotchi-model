#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "PlayProt.h"
#endif
#include <UnitName.h>
#include <PlayProt.h>

const RTProtocolDescriptor PlayProt::Base::rt_class =
{
    &RTRootProtocol::rt_class
    , &PlayProt::Conjugate::rt_class
    , "PlayProt"
    , 0
    , 2
    , PlayProt::Base::rt_signals
};

const RTSignalDescriptor PlayProt::Base::rt_signals[] =
{
    {
        "rtBound"
        , nullptr
        , PlayProt::Base::rti_rtBound
    }
    , {
        "rtUnbound"
        , nullptr
        , PlayProt::Base::rti_rtUnbound
    }
};

const RTProtocolDescriptor PlayProt::Conjugate::rt_class =
{
    &RTRootProtocol::rt_class
    , &PlayProt::Base::rt_class
    , "PlayProt"
    , 0
    , 5
    , PlayProt::Conjugate::rt_signals
};

const RTSignalDescriptor PlayProt::Conjugate::rt_signals[] =
{
    {
        "exit"
        , &RTType_void
        , PlayProt::Conjugate::rti_exit
    }
    , {
        "initPlay"
        , &RTType_void
        , PlayProt::Conjugate::rti_initPlay
    }
    , {
        "rtBound"
        , nullptr
        , PlayProt::Conjugate::rti_rtBound
    }
    , {
        "rtUnbound"
        , nullptr
        , PlayProt::Conjugate::rti_rtUnbound
    }
    , {
        "throwBall"
        , &RTType_void
        , PlayProt::Conjugate::rti_throwBall
    }
};

