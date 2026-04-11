#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "Feed.h"
#endif
#include <UnitName.h>
#include <Feed.h>

static const char * const rtg_state_names[] =
{
    "<machine>"
    , "Start"
    , "Initialize Feed"
};

#define SUPER RTActor
Feed_Actor::Feed_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
    : RTActor( rtg_rts ,rtg_ref )
{
}

Feed_Actor::~Feed_Actor( void )
{
}

INLINE_METHODS void Feed_Actor::enter3_Initialize_Feed( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_TM_2ADVMEfGJaL0kWrhu3A
std::cout<< "\nWHAT WOULD YOU LIKE TO FEED YOUR PET?" <<std::endl;
//}}}USR
}

void Feed_Actor::enterStateV( void )
{
    switch( getCurrentState() )
    {
    case 3:
        enter3_Initialize_Feed(  );
        break;
    default:
        RTActor::enterStateV(  );
        break;
    }
}

INLINE_CHAINS void Feed_Actor::chain1_Initial( void )
{
    rtgChainBegin( 1, "Initial" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 2 );
}

INLINE_CHAINS void Feed_Actor::chain2_feed_activated( void )
{
    rtgChainBegin( 2, "feed activated" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 3 );
}

void Feed_Actor::rtsBehavior( int signalIndex, int portIndex )
{
    for (int stateIndex = getCurrentState() ; ;stateIndex = rtg_parent_state[ stateIndex - 1 ] )
        {
            switch( stateIndex )
            {
            case 1:
                switch( portIndex )
                {
                case 0:
                    switch( signalIndex )
                    {
                    case 1 /*RTInitSignal*/:
                        chain1_Initial(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                unhandledMessage(  );
                return ;
            case 2 /* Start (State Machine::Start) */:
                switch( portIndex )
                {
                case 0 /*RTControlPort*/:
                    switch( signalIndex )
                    {
                    case 1 /*RTInitSignal*/:
                        return ;
                    default:
                        break;
                    }
                    break;
                case 1 /*feedPort*/:
                    switch( signalIndex )
                    {
                    case FeedProt::Conjugate::rti_initFeed:
                        chain2_feed_activated(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 3 /* Initialize Feed (State Machine::Initialize Feed) */:
                switch( portIndex )
                {
                case 0 /*RTControlPort*/:
                    switch( signalIndex )
                    {
                    case 1 /*RTInitSignal*/:
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            default:
                unexpectedState(  );
                return ;
            }
        }
}

const RTStateId Feed_Actor::rtg_parent_state[] =
{
    0
    , 1
    , 1
};

const RTActor_class * Feed_Actor::getActorData( void ) const
{
    return &Feed_Actor::rtg_class;
}

const RTActor_class Feed_Actor::rtg_class =
{
    nullptr
    , rtg_state_names
    , 3
    , Feed_Actor::rtg_parent_state
    , &Feed
    , 0
    , nullptr
    , 1
    , Feed_Actor::rtg_ports
    , 0
    , nullptr
    , 0
    , nullptr
};

const RTPortDescriptor Feed_Actor::rtg_ports[] =
{
    {
        "feedPort"
        , nullptr
        , &FeedProt::Conjugate::rt_class
        , RTOffsetOf( Feed_Actor, feedPort )
        , 1
        , 1
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
};

int Feed_Actor::_followInV( RTBindingEnd & rtg_end, int rtg_portId, int rtg_repIndex )
{
    switch( rtg_portId )
    {
    case 0:
        if( rtg_repIndex < 1 )
        {
            rtg_end.port = &feedPort;
            rtg_end.index = rtg_repIndex;
            return 1;
        }
        break;
    default:
        break;
    }
    return RTActor::_followInV( rtg_end, rtg_portId, rtg_repIndex );
}

#undef SUPER
static const RTRelayDescriptor rtg_relays[] =
{
    {
        "feedPort"
        , &FeedProt::Conjugate::rt_class
        , 1
    }
};

static RTActor * new_Feed_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
{
    return new Feed_Actor( rtg_rts, rtg_ref );
}

const RTActorClass Feed =
{
    nullptr
    , "Feed"
    , 0 /*RTVersionId*/
    , 1
    , rtg_relays
    , new_Feed_Actor
};

