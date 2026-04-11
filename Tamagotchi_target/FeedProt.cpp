#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "FeedProt.h"
#endif
#include <UnitName.h>
#include <FeedProt.h>

const RTProtocolDescriptor FeedProt::Base::rt_class =
{
    &RTRootProtocol::rt_class
    , &FeedProt::Conjugate::rt_class
    , "FeedProt"
    , 0
    , 2
    , FeedProt::Base::rt_signals
};

const RTSignalDescriptor FeedProt::Base::rt_signals[] =
{
    {
        "rtBound"
        , nullptr
        , FeedProt::Base::rti_rtBound
    }
    , {
        "rtUnbound"
        , nullptr
        , FeedProt::Base::rti_rtUnbound
    }
};

const RTProtocolDescriptor FeedProt::Conjugate::rt_class =
{
    &RTRootProtocol::rt_class
    , &FeedProt::Base::rt_class
    , "FeedProt"
    , 0
    , 4
    , FeedProt::Conjugate::rt_signals
};

const RTSignalDescriptor FeedProt::Conjugate::rt_signals[] =
{
    {
        "feedSnack"
        , &RTType_void
        , FeedProt::Conjugate::rti_feedSnack
    }
    , {
        "initFeed"
        , &RTType_void
        , FeedProt::Conjugate::rti_initFeed
    }
    , {
        "rtBound"
        , nullptr
        , FeedProt::Conjugate::rti_rtBound
    }
    , {
        "rtUnbound"
        , nullptr
        , FeedProt::Conjugate::rti_rtUnbound
    }
};

