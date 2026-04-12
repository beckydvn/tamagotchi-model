#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "UpdateOptionsProt.h"
#endif
#include <UnitName.h>
#include <UpdateOptionsProt.h>

const RTProtocolDescriptor UpdateOptionsProt::Base::rt_class =
{
    &RTRootProtocol::rt_class
    , &UpdateOptionsProt::Conjugate::rt_class
    , "UpdateOptionsProt"
    , 0
    , 2
    , UpdateOptionsProt::Base::rt_signals
};

const RTSignalDescriptor UpdateOptionsProt::Base::rt_signals[] =
{
    {
        "rtBound"
        , nullptr
        , UpdateOptionsProt::Base::rti_rtBound
    }
    , {
        "rtUnbound"
        , nullptr
        , UpdateOptionsProt::Base::rti_rtUnbound
    }
};

const RTProtocolDescriptor UpdateOptionsProt::Conjugate::rt_class =
{
    &RTRootProtocol::rt_class
    , &UpdateOptionsProt::Base::rt_class
    , "UpdateOptionsProt"
    , 0
    , 3
    , UpdateOptionsProt::Conjugate::rt_signals
};

const RTSignalDescriptor UpdateOptionsProt::Conjugate::rt_signals[] =
{
    {
        "rtBound"
        , nullptr
        , UpdateOptionsProt::Conjugate::rti_rtBound
    }
    , {
        "rtUnbound"
        , nullptr
        , UpdateOptionsProt::Conjugate::rti_rtUnbound
    }
    , {
        "updateOptions"
        , nullptr
        , UpdateOptionsProt::Conjugate::rti_updateOptions
    }
};

