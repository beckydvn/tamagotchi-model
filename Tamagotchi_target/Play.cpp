#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "Play.h"
#endif
#include <UnitName.h>
#include <Play.h>

static const char * const rtg_state_names[] =
{
    "<machine>"
    , "Start"
    , "Initiate Play"
    , ""
};

#define SUPER RTActor
Play_Actor::Play_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
    : RTActor( rtg_rts ,rtg_ref )
{
}

Play_Actor::~Play_Actor( void )
{
}

INLINE_METHODS void Play_Actor::transition3_throwBall( const void * rtdata, PlayProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_UrMnYDYSEfGJaL0kWrhu3A
std::cout << "THREW THE BALL!" << std::endl;
throwCount += 1;
//}}}USR
}

INLINE_METHODS int Play_Actor::guard4_throws_5( const void * rtdata, PlayProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_jydhcDYSEfGJaL0kWrhu3A
return (throwCount <= 5);
//}}}USR
}

INLINE_METHODS void Play_Actor::transition4_throws_5( const void * rtdata, PlayProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_8kw9cDYSEfGJaL0kWrhu3A
std::cout << "PET CAUGHT THE BALL!" << std::endl;
updateValPort.updateHappiness(2).send();
//}}}USR
}

INLINE_METHODS void Play_Actor::transition5_caught_last( const void * rtdata, PlayProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_Q_kNsDYTEfGJaL0kWrhu3A
std::cout << "PET IS TIRED..." << std::endl;
//}}}USR
}

INLINE_METHODS void Play_Actor::transition6_exit( const void * rtdata, PlayProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_zTYcMDYTEfGJaL0kWrhu3A
throwCount = 0;
//}}}USR
}

INLINE_CHAINS void Play_Actor::chain1_Initial( void )
{
    rtgChainBegin( 1, "Initial" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 2 );
}

INLINE_CHAINS void Play_Actor::chain2_play_activated( void )
{
    rtgChainBegin( 2, "play activated" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Play_Actor::chain3_throwBall( void )
{
    rtgChainBegin( 3, "throwBall" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition3_throwBall( msg->data, static_cast< PlayProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    if( guard4_throws_5( msg->data, static_cast< PlayProt::Conjugate * > ( msg->sap() ) ) )
    {
        chain4_throws_5(  );
        return ;
    }
    chain5_caught_last(  );
}

INLINE_CHAINS void Play_Actor::chain4_throws_5( void )
{
    rtgChainBegin( 4, "throws <= 5" );
    rtgTransitionBegin(  );
    transition4_throws_5( msg->data, static_cast< PlayProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Play_Actor::chain5_caught_last( void )
{
    rtgChainBegin( 4, "caught last" );
    rtgTransitionBegin(  );
    transition5_caught_last( msg->data, static_cast< PlayProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Play_Actor::chain6_exit( void )
{
    rtgChainBegin( 3, "exit" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition6_exit( msg->data, static_cast< PlayProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 2 );
}

void Play_Actor::rtsBehavior( int signalIndex, int portIndex )
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
                case 1 /*playPort*/:
                    switch( signalIndex )
                    {
                    case PlayProt::Conjugate::rti_initPlay:
                        chain2_play_activated(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 3 /* Initiate Play (State Machine::Initiate Play) */:
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
                case 1 /*playPort*/:
                    switch( signalIndex )
                    {
                    case PlayProt::Conjugate::rti_exit:
                        chain6_exit(  );
                        return ;
                    case PlayProt::Conjugate::rti_throwBall:
                        chain3_throwBall(  );
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

const RTStateId Play_Actor::rtg_parent_state[] =
{
    0
    , 1
    , 1
};

const RTActor_class * Play_Actor::getActorData( void ) const
{
    return &Play_Actor::rtg_class;
}

const RTActor_class Play_Actor::rtg_class =
{
    nullptr
    , rtg_state_names
    , 3
    , Play_Actor::rtg_parent_state
    , &Play
    , 0
    , nullptr
    , 2
    , Play_Actor::rtg_ports
    , 0
    , nullptr
    , 1
    , Play_Actor::rtg_Play_Actor_fields
};

const RTPortDescriptor Play_Actor::rtg_ports[] =
{
    {
        "playPort"
        , nullptr
        , &PlayProt::Conjugate::rt_class
        , RTOffsetOf( Play_Actor, playPort )
        , 1
        , 1
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "updateValPort"
        , nullptr
        , &UpdateValProt::Base::rt_class
        , RTOffsetOf( Play_Actor, updateValPort )
        , 1
        , 2
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
};

const RTFieldDescriptor Play_Actor::rtg_Play_Actor_fields[] =
{
    {
        "throwCount"
        , RTOffsetOf( Play_Actor, throwCount )
        , &RTType_int
        , nullptr
    }
};

int Play_Actor::_followInV( RTBindingEnd & rtg_end, int rtg_portId, int rtg_repIndex )
{
    switch( rtg_portId )
    {
    case 0:
        if( rtg_repIndex < 1 )
        {
            rtg_end.port = &playPort;
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
    default:
        break;
    }
    return RTActor::_followInV( rtg_end, rtg_portId, rtg_repIndex );
}

#undef SUPER
static const RTRelayDescriptor rtg_relays[] =
{
    {
        "playPort"
        , &PlayProt::Conjugate::rt_class
        , 1
    }
    , {
        "updateValPort"
        , &UpdateValProt::Base::rt_class
        , 1
    }
};

static RTActor * new_Play_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
{
    return new Play_Actor( rtg_rts, rtg_ref );
}

const RTActorClass Play =
{
    nullptr
    , "Play"
    , 0 /*RTVersionId*/
    , 2
    , rtg_relays
    , new_Play_Actor
};

