#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "StatusProt.h"
#endif
#include <UnitName.h>
#include <StatusProt.h>

const RTProtocolDescriptor StatusProt::Base::rt_class =
{
    &RTRootProtocol::rt_class
    , &StatusProt::Conjugate::rt_class
    , "StatusProt"
    , 0
    , 3
    , StatusProt::Base::rt_signals
};

const RTSignalDescriptor StatusProt::Base::rt_signals[] =
{
    {
        "hatch"
        , &RTType_void
        , StatusProt::Base::rti_hatch
    }
    , {
        "rtBound"
        , nullptr
        , StatusProt::Base::rti_rtBound
    }
    , {
        "rtUnbound"
        , nullptr
        , StatusProt::Base::rti_rtUnbound
    }
};

const RTProtocolDescriptor StatusProt::Conjugate::rt_class =
{
    &RTRootProtocol::rt_class
    , &StatusProt::Base::rt_class
    , "StatusProt"
    , 0
    , 2
    , StatusProt::Conjugate::rt_signals
};

const RTSignalDescriptor StatusProt::Conjugate::rt_signals[] =
{
    {
        "rtBound"
        , nullptr
        , StatusProt::Conjugate::rti_rtBound
    }
    , {
        "rtUnbound"
        , nullptr
        , StatusProt::Conjugate::rti_rtUnbound
    }
};

