#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "UpdateTamaProt.h"
#endif
#include <UnitName.h>
#include <UpdateTamaProt.h>

const RTProtocolDescriptor UpdateTamaProt::Base::rt_class =
{
    &RTRootProtocol::rt_class
    , &UpdateTamaProt::Conjugate::rt_class
    , "UpdateTamaProt"
    , 0
    , 2
    , UpdateTamaProt::Base::rt_signals
};

const RTSignalDescriptor UpdateTamaProt::Base::rt_signals[] =
{
    {
        "rtBound"
        , nullptr
        , UpdateTamaProt::Base::rti_rtBound
    }
    , {
        "rtUnbound"
        , nullptr
        , UpdateTamaProt::Base::rti_rtUnbound
    }
};

const RTProtocolDescriptor UpdateTamaProt::Conjugate::rt_class =
{
    &RTRootProtocol::rt_class
    , &UpdateTamaProt::Base::rt_class
    , "UpdateTamaProt"
    , 0
    , 3
    , UpdateTamaProt::Conjugate::rt_signals
};

const RTSignalDescriptor UpdateTamaProt::Conjugate::rt_signals[] =
{
    {
        "rtBound"
        , nullptr
        , UpdateTamaProt::Conjugate::rti_rtBound
    }
    , {
        "rtUnbound"
        , nullptr
        , UpdateTamaProt::Conjugate::rti_rtUnbound
    }
    , {
        "updateTama"
        , nullptr
        , UpdateTamaProt::Conjugate::rti_updateTama
    }
};

