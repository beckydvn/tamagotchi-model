#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "UpdateValProt.h"
#endif
#include <UnitName.h>
#include <UpdateValProt.h>

const RTProtocolDescriptor UpdateValProt::Base::rt_class =
{
    &RTRootProtocol::rt_class
    , &UpdateValProt::Conjugate::rt_class
    , "UpdateValProt"
    , 0
    , 3
    , UpdateValProt::Base::rt_signals
};

const RTSignalDescriptor UpdateValProt::Base::rt_signals[] =
{
    {
        "resetThrow"
        , &RTType_void
        , UpdateValProt::Base::rti_resetThrow
    }
    , {
        "rtBound"
        , nullptr
        , UpdateValProt::Base::rti_rtBound
    }
    , {
        "rtUnbound"
        , nullptr
        , UpdateValProt::Base::rti_rtUnbound
    }
};

const RTProtocolDescriptor UpdateValProt::Conjugate::rt_class =
{
    &RTRootProtocol::rt_class
    , &UpdateValProt::Base::rt_class
    , "UpdateValProt"
    , 0
    , 5
    , UpdateValProt::Conjugate::rt_signals
};

const RTSignalDescriptor UpdateValProt::Conjugate::rt_signals[] =
{
    {
        "rtBound"
        , nullptr
        , UpdateValProt::Conjugate::rti_rtBound
    }
    , {
        "rtUnbound"
        , nullptr
        , UpdateValProt::Conjugate::rti_rtUnbound
    }
    , {
        "updateHappiness"
        , &RTType_int
        , UpdateValProt::Conjugate::rti_updateHappiness
    }
    , {
        "updateHealth"
        , &RTType_int
        , UpdateValProt::Conjugate::rti_updateHealth
    }
    , {
        "updateHunger"
        , &RTType_int
        , UpdateValProt::Conjugate::rti_updateHunger
    }
};

