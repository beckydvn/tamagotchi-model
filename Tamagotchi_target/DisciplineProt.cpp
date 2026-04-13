#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "DisciplineProt.h"
#endif
#include <UnitName.h>
#include <DisciplineProt.h>

const RTProtocolDescriptor DisciplineProt::Base::rt_class =
{
    &RTRootProtocol::rt_class
    , &DisciplineProt::Conjugate::rt_class
    , "DisciplineProt"
    , 0
    , 2
    , DisciplineProt::Base::rt_signals
};

const RTSignalDescriptor DisciplineProt::Base::rt_signals[] =
{
    {
        "rtBound"
        , nullptr
        , DisciplineProt::Base::rti_rtBound
    }
    , {
        "rtUnbound"
        , nullptr
        , DisciplineProt::Base::rti_rtUnbound
    }
};

const RTProtocolDescriptor DisciplineProt::Conjugate::rt_class =
{
    &RTRootProtocol::rt_class
    , &DisciplineProt::Base::rt_class
    , "DisciplineProt"
    , 0
    , 6
    , DisciplineProt::Conjugate::rt_signals
};

const RTSignalDescriptor DisciplineProt::Conjugate::rt_signals[] =
{
    {
        "exit"
        , &RTType_void
        , DisciplineProt::Conjugate::rti_exit
    }
    , {
        "initDiscipline"
        , &RTType_void
        , DisciplineProt::Conjugate::rti_initDiscipline
    }
    , {
        "reinforce"
        , nullptr
        , DisciplineProt::Conjugate::rti_reinforce
    }
    , {
        "rtBound"
        , nullptr
        , DisciplineProt::Conjugate::rti_rtBound
    }
    , {
        "rtUnbound"
        , nullptr
        , DisciplineProt::Conjugate::rti_rtUnbound
    }
    , {
        "sit"
        , &RTType_void
        , DisciplineProt::Conjugate::rti_sit
    }
};

