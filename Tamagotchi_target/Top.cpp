#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "Top.h"
#endif
#include <UnitName.h>
#include <Top.h>

extern const RTActorClass Status;

static const char * const rtg_state_names[] =
{
    "<machine>"
    , "Start"
};

static const RTInterfaceDescriptor rtg_interfaces_status[] =
{
    {
        "statusProt"
        , 1
    }
};

static const RTBindingDescriptor rtg_bindings_status[] =
{
    {
        0
        , &StatusProt::Conjugate::rt_class
    }
};

#define SUPER RTActor
Top_Actor::Top_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
    : RTActor( rtg_rts ,rtg_ref )
{
}

Top_Actor::~Top_Actor( void )
{
}

INLINE_METHODS void Top_Actor::transition1_Initial( const void * rtdata, RTProtocol * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_N3jGEDRhEfGs993j7RVgLQ
std::cout<< "\nSTARTING GAME...\n" <<std::endl;
statusProt.hatch().send();
//}}}USR
}

INLINE_CHAINS void Top_Actor::chain1_Initial( void )
{
    rtgChainBegin( 1, "Initial" );
    rtgTransitionBegin(  );
    transition1_Initial( msg->data, msg->sap() );
    rtgTransitionEnd(  );
    enterState( 2 );
}

void Top_Actor::rtsBehavior( int signalIndex, int portIndex )
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

const RTStateId Top_Actor::rtg_parent_state[] =
{
    0
    , 1
};

const RTActor_class * Top_Actor::getActorData( void ) const
{
    return &Top_Actor::rtg_class;
}

const RTActor_class Top_Actor::rtg_class =
{
    nullptr
    , rtg_state_names
    , 2
    , Top_Actor::rtg_parent_state
    , &Top
    , 1
    , Top_Actor::rtg_capsule_roles
    , 1
    , Top_Actor::rtg_ports
    , 0
    , nullptr
    , 0
    , nullptr
};

const RTComponentDescriptor Top_Actor::rtg_capsule_roles[] =
{
    {
        "status"
        , &Status
        , RTOffsetOf( Top_Actor, status )
        , 1
        , RTComponentDescriptor::Fixed
        , 1
        , 1
        , 1
        , rtg_interfaces_status
        , 1
        , rtg_bindings_status
    }
};

const RTPortDescriptor Top_Actor::rtg_ports[] =
{
    {
        "statusProt"
        , nullptr
        , &StatusProt::Conjugate::rt_class
        , RTOffsetOf( Top_Actor, statusProt )
        , 1
        , 1
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
};

int Top_Actor::_followOutV( RTBindingEnd & rtg_end, int rtg_compId, int rtg_portId, int rtg_repIndex )
{
    switch( rtg_compId )
    {
    case 1:
        switch( rtg_portId )
        {
        case 0:
            if( rtg_repIndex < 1 )
            {
                rtg_end.port = &statusProt;
                rtg_end.index = rtg_repIndex;
                return 1;
            }
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return RTActor::_followOutV( rtg_end, rtg_compId, rtg_portId, rtg_repIndex );
}

#undef SUPER
static RTActor * new_Top_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
{
    return new Top_Actor( rtg_rts, rtg_ref );
}

const RTActorClass Top =
{
    nullptr
    , "Top"
    , 0 /*RTVersionId*/
    , 0
    , nullptr
    , new_Top_Actor
};

