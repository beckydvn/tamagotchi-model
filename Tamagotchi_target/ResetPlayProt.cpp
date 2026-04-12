#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "ResetPlayProt.h"
#endif
#include <UnitName.h>
#include <ResetPlayProt.h>

const RTProtocolDescriptor ResetPlayProt::Base::rt_class =
{
    &RTRootProtocol::rt_class
    , &ResetPlayProt::Conjugate::rt_class
    , "ResetPlayProt"
    , 0
    , 2
    , ResetPlayProt::Base::rt_signals
};

const RTSignalDescriptor ResetPlayProt::Base::rt_signals[] =
{
    {
        "rtBound"
        , nullptr
        , ResetPlayProt::Base::rti_rtBound
    }
    , {
        "rtUnbound"
        , nullptr
        , ResetPlayProt::Base::rti_rtUnbound
    }
};

const RTProtocolDescriptor ResetPlayProt::Conjugate::rt_class =
{
    &RTRootProtocol::rt_class
    , &ResetPlayProt::Base::rt_class
    , "ResetPlayProt"
    , 0
    , 3
    , ResetPlayProt::Conjugate::rt_signals
};

const RTSignalDescriptor ResetPlayProt::Conjugate::rt_signals[] =
{
    {
        "resetThrow"
        , &RTType_void
        , ResetPlayProt::Conjugate::rti_resetThrow
    }
    , {
        "rtBound"
        , nullptr
        , ResetPlayProt::Conjugate::rti_rtBound
    }
    , {
        "rtUnbound"
        , nullptr
        , ResetPlayProt::Conjugate::rti_rtUnbound
    }
};

