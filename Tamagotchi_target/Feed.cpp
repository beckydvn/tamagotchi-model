#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "Feed.h"
#endif
#include <UnitName.h>
#include <Feed.h>

static const char * const rtg_state_names[] =
{
    "<machine>"
    , "Start"
    , "Initiate Feed"
    , ""
};

#define SUPER RTActor
Feed_Actor::Feed_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
    : RTActor( rtg_rts ,rtg_ref )
{
}

Feed_Actor::~Feed_Actor( void )
{
}

INLINE_METHODS void Feed_Actor::enter3_Initiate_Feed( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_659mEDaiEfGJaL0kWrhu3A
triggerInputPort.triggerInput().send();
//}}}USR
}

void Feed_Actor::enterStateV( void )
{
    switch( getCurrentState() )
    {
    case 3:
        enter3_Initiate_Feed(  );
        break;
    default:
        RTActor::enterStateV(  );
        break;
    }
}

INLINE_METHODS void Feed_Actor::transition3_getSnack( const void * rtdata, FeedProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_UGBWMDXwEfGJaL0kWrhu3A
snackCount += 1;
//}}}USR
}

INLINE_METHODS int Feed_Actor::guard4_snackCount_3( const void * rtdata, FeedProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_6LJIkDXvEfGJaL0kWrhu3A
return (snackCount < 3);
//}}}USR
}

INLINE_METHODS void Feed_Actor::transition4_snackCount_3( const void * rtdata, FeedProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_AJn4MDX7EfGJaL0kWrhu3A
updateValPort.updateHunger(-2).send();
updateValPort.updateHappiness(2).send();
std::cout<< "\nATE THE SNACK..." <<std::endl;
//}}}USR
}

INLINE_METHODS int Feed_Actor::guard5_else( const void * rtdata, FeedProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_B6KpwDXwEfGJaL0kWrhu3A
return (snackCount >= 3);
//}}}USR
}

INLINE_METHODS void Feed_Actor::transition5_else( const void * rtdata, FeedProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_EMqP0DX7EfGJaL0kWrhu3A
updateValPort.updateHunger(-1).send();
updateValPort.updateHealth(-3).send();
std::cout<< "\nSO...MANY...SNACKS..." <<std::endl;

//}}}USR
}

INLINE_METHODS void Feed_Actor::transition6_getMeal( const void * rtdata, FeedProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_wAme0DX9EfGJaL0kWrhu3A
updateValPort.updateHunger(3).send();
updateValPort.updateHealth(1).send();
std::cout<< "\nATE THE MEAL..." <<std::endl;

//}}}USR
}

INLINE_METHODS void Feed_Actor::transition7_exit( const void * rtdata, FeedProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_sLdXQDYTEfGJaL0kWrhu3A
snackCount = 0;
//}}}USR
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

INLINE_CHAINS void Feed_Actor::chain3_getSnack( void )
{
    rtgChainBegin( 3, "getSnack" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition3_getSnack( msg->data, static_cast< FeedProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    if( guard4_snackCount_3( msg->data, static_cast< FeedProt::Conjugate * > ( msg->sap() ) ) )
    {
        chain4_snackCount_3(  );
        return ;
    }
    if( guard5_else( msg->data, static_cast< FeedProt::Conjugate * > ( msg->sap() ) ) )
    {
        chain5_else(  );
        return ;
    }
}

INLINE_CHAINS void Feed_Actor::chain4_snackCount_3( void )
{
    rtgChainBegin( 4, "snackCount < 3" );
    rtgTransitionBegin(  );
    transition4_snackCount_3( msg->data, static_cast< FeedProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Feed_Actor::chain5_else( void )
{
    rtgChainBegin( 4, "else" );
    rtgTransitionBegin(  );
    transition5_else( msg->data, static_cast< FeedProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Feed_Actor::chain6_getMeal( void )
{
    rtgChainBegin( 3, "getMeal" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition6_getMeal( msg->data, static_cast< FeedProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Feed_Actor::chain7_exit( void )
{
    rtgChainBegin( 3, "exit" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition7_exit( msg->data, static_cast< FeedProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 2 );
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
            case 3 /* Initiate Feed (State Machine::Initiate Feed) */:
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
                    case FeedProt::Conjugate::rti_exit:
                        chain7_exit(  );
                        return ;
                    case FeedProt::Conjugate::rti_feedMeal:
                        chain6_getMeal(  );
                        return ;
                    case FeedProt::Conjugate::rti_feedSnack:
                        chain3_getSnack(  );
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
    , 3
    , Feed_Actor::rtg_ports
    , 0
    , nullptr
    , 1
    , Feed_Actor::rtg_Feed_Actor_fields
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
    , {
        "updateValPort"
        , nullptr
        , &UpdateValProt::Base::rt_class
        , RTOffsetOf( Feed_Actor, updateValPort )
        , 1
        , 2
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "triggerInputPort"
        , nullptr
        , &InputProt::Base::rt_class
        , RTOffsetOf( Feed_Actor, triggerInputPort )
        , 1
        , 3
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
};

const RTFieldDescriptor Feed_Actor::rtg_Feed_Actor_fields[] =
{
    {
        "snackCount"
        , RTOffsetOf( Feed_Actor, snackCount )
        , &RTType_int
        , nullptr
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
    case 1:
        if( rtg_repIndex < 1 )
        {
            rtg_end.port = &updateValPort;
            rtg_end.index = rtg_repIndex;
            return 1;
        }
        break;
    case 2:
        if( rtg_repIndex < 1 )
        {
            rtg_end.port = &triggerInputPort;
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
    , {
        "updateValPort"
        , &UpdateValProt::Base::rt_class
        , 1
    }
    , {
        "triggerInputPort"
        , &InputProt::Base::rt_class
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
    , 3
    , rtg_relays
    , new_Feed_Actor
};

