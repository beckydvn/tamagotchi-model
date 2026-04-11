#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "Input.h"
#endif
#include <UnitName.h>
#include <Input.h>

static const char * const rtg_state_names[] =
{
    "<machine>"
    , "Start"
    , "Take Input"
};

#define SUPER RTActor
Input_Actor::Input_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
    : RTActor( rtg_rts ,rtg_ref )
{
}

Input_Actor::~Input_Actor( void )
{
}

INLINE_METHODS void Input_Actor::enter3_Take_Input( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_Z0mKADUpEfGJaL0kWrhu3A
char user_input[256];

fgets(user_input, sizeof(user_input), stdin);

// Remove trailing newline if present
input[strcspn(user_input, "\n")] = '\0';

for (int i = 0; user_input[i]; i++) {
        user_input[i] = toupper(user_input[i]);
}

input = user_input;

std::cout<< "\nGOT INPUT " << input <<std::endl;
//}}}USR
}

void Input_Actor::enterStateV( void )
{
    switch( getCurrentState() )
    {
    case 3:
        enter3_Take_Input(  );
        break;
    default:
        RTActor::enterStateV(  );
        break;
    }
}

INLINE_CHAINS void Input_Actor::chain1_Initial( void )
{
    rtgChainBegin( 1, "Initial" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 2 );
}

INLINE_CHAINS void Input_Actor::chain2_hatch( void )
{
    rtgChainBegin( 2, "hatch" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Input_Actor::chain3_returnToIdle( void )
{
    rtgChainBegin( 3, "returnToIdle" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 3 );
}

void Input_Actor::rtsBehavior( int signalIndex, int portIndex )
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
                case 1 /*statusProt*/:
                    switch( signalIndex )
                    {
                    case StatusProt::Conjugate::rti_hatch:
                        chain2_hatch(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 3 /* Take Input (State Machine::Take Input) */:
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
                case 1 /*statusProt*/:
                    switch( signalIndex )
                    {
                    case StatusProt::Conjugate::rti_returnToIdle:
                        chain3_returnToIdle(  );
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

const RTStateId Input_Actor::rtg_parent_state[] =
{
    0
    , 1
    , 1
};

const RTActor_class * Input_Actor::getActorData( void ) const
{
    return &Input_Actor::rtg_class;
}

const RTActor_class Input_Actor::rtg_class =
{
    nullptr
    , rtg_state_names
    , 3
    , Input_Actor::rtg_parent_state
    , &Input
    , 0
    , nullptr
    , 1
    , Input_Actor::rtg_ports
    , 0
    , nullptr
    , 0
    , nullptr
};

const RTPortDescriptor Input_Actor::rtg_ports[] =
{
    {
        "statusProt"
        , nullptr
        , &StatusProt::Conjugate::rt_class
        , RTOffsetOf( Input_Actor, statusProt )
        , 1
        , 1
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
};

int Input_Actor::_followInV( RTBindingEnd & rtg_end, int rtg_portId, int rtg_repIndex )
{
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
    return RTActor::_followInV( rtg_end, rtg_portId, rtg_repIndex );
}

#undef SUPER
static const RTRelayDescriptor rtg_relays[] =
{
    {
        "statusProt"
        , &StatusProt::Conjugate::rt_class
        , 1
    }
};

static RTActor * new_Input_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
{
    return new Input_Actor( rtg_rts, rtg_ref );
}

const RTActorClass Input =
{
    nullptr
    , "Input"
    , 0 /*RTVersionId*/
    , 1
    , rtg_relays
    , new_Input_Actor
};

