#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "InputProt.h"
#endif
#include <UnitName.h>
#include <InputProt.h>

const RTProtocolDescriptor InputProt::Base::rt_class =
{
    &RTRootProtocol::rt_class
    , &InputProt::Conjugate::rt_class
    , "InputProt"
    , 0
    , 2
    , InputProt::Base::rt_signals
};

const RTSignalDescriptor InputProt::Base::rt_signals[] =
{
    {
        "rtBound"
        , nullptr
        , InputProt::Base::rti_rtBound
    }
    , {
        "rtUnbound"
        , nullptr
        , InputProt::Base::rti_rtUnbound
    }
};

const RTProtocolDescriptor InputProt::Conjugate::rt_class =
{
    &RTRootProtocol::rt_class
    , &InputProt::Base::rt_class
    , "InputProt"
    , 0
    , 3
    , InputProt::Conjugate::rt_signals
};

const RTSignalDescriptor InputProt::Conjugate::rt_signals[] =
{
    {
        "gotInput"
        , nullptr
        , InputProt::Conjugate::rti_gotInput
    }
    , {
        "rtBound"
        , nullptr
        , InputProt::Conjugate::rti_rtBound
    }
    , {
        "rtUnbound"
        , nullptr
        , InputProt::Conjugate::rti_rtUnbound
    }
};

