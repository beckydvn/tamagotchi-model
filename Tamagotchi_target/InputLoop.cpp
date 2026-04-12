#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "InputLoop.h"
#endif
#include <UnitName.h>
#include <InputLoop.h>

static const char * const rtg_state_names[] =
{
    "<machine>"
    , "Start"
    , "Take Input"
};

#define SUPER RTActor
InputLoop_Actor::InputLoop_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
    : RTActor( rtg_rts ,rtg_ref )
{
}

InputLoop_Actor::~InputLoop_Actor( void )
{
}

INLINE_METHODS void InputLoop_Actor::enter3_Take_Input( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_Z0mKADUpEfGJaL0kWrhu3A
char userInput[256];
fgets(userInput, sizeof(userInput), stdin);

userInput[strcspn(userInput, "\n")] = '\0';

for (int i = 0; userInput[i]; i++) {
		userInput[i] = toupper(userInput[i]);
}

inputPort.gotInput(userInput).send();
//}}}USR
}

void InputLoop_Actor::enterStateV( void )
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

INLINE_CHAINS void InputLoop_Actor::chain1_Initial( void )
{
    rtgChainBegin( 1, "Initial" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 2 );
}

INLINE_CHAINS void InputLoop_Actor::chain2_hatch( void )
{
    rtgChainBegin( 2, "hatch" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void InputLoop_Actor::chain3_input_requested( void )
{
    rtgChainBegin( 3, "input requested" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 3 );
}

void InputLoop_Actor::rtsBehavior( int signalIndex, int portIndex )
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
                case 1 /*statusPort*/:
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
                case 3 /*triggerInputPort*/:
                    switch( signalIndex )
                    {
                    case InputProt::Conjugate::rti_triggerInput:
                        chain3_input_requested(  );
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

const RTStateId InputLoop_Actor::rtg_parent_state[] =
{
    0
    , 1
    , 1
};

const RTActor_class * InputLoop_Actor::getActorData( void ) const
{
    return &InputLoop_Actor::rtg_class;
}

const RTActor_class InputLoop_Actor::rtg_class =
{
    nullptr
    , rtg_state_names
    , 3
    , InputLoop_Actor::rtg_parent_state
    , &InputLoop
    , 0
    , nullptr
    , 3
    , InputLoop_Actor::rtg_ports
    , 0
    , nullptr
    , 0
    , nullptr
};

const RTPortDescriptor InputLoop_Actor::rtg_ports[] =
{
    {
        "statusPort"
        , nullptr
        , &StatusProt::Conjugate::rt_class
        , RTOffsetOf( InputLoop_Actor, statusPort )
        , 1
        , 1
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "inputPort"
        , nullptr
        , &InputProt::Base::rt_class
        , RTOffsetOf( InputLoop_Actor, inputPort )
        , 1
        , 2
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "triggerInputPort"
        , nullptr
        , &InputProt::Conjugate::rt_class
        , RTOffsetOf( InputLoop_Actor, triggerInputPort )
        , 3
        , 3
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
};

int InputLoop_Actor::_followInV( RTBindingEnd & rtg_end, int rtg_portId, int rtg_repIndex )
{
    switch( rtg_portId )
    {
    case 0:
        if( rtg_repIndex < 1 )
        {
            rtg_end.port = &statusPort;
            rtg_end.index = rtg_repIndex;
            return 1;
        }
        break;
    case 1:
        if( rtg_repIndex < 1 )
        {
            rtg_end.port = &inputPort;
            rtg_end.index = rtg_repIndex;
            return 1;
        }
        break;
    case 2:
        if( rtg_repIndex < 3 )
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
        "statusPort"
        , &StatusProt::Conjugate::rt_class
        , 1
    }
    , {
        "inputPort"
        , &InputProt::Base::rt_class
        , 1
    }
    , {
        "triggerInputPort"
        , &InputProt::Conjugate::rt_class
        , 3
    }
};

static RTActor * new_InputLoop_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
{
    return new InputLoop_Actor( rtg_rts, rtg_ref );
}

const RTActorClass InputLoop =
{
    nullptr
    , "InputLoop"
    , 0 /*RTVersionId*/
    , 3
    , rtg_relays
    , new_InputLoop_Actor
};

