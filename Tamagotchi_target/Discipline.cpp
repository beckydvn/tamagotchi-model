#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "Discipline.h"
#endif
#include <UnitName.h>
#include <Discipline.h>

static const char * const rtg_state_names[] =
{
    "<machine>"
    , "Start"
    , "Initiate Discipline"
};

#define SUPER RTActor
Discipline_Actor::Discipline_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
    : RTActor( rtg_rts ,rtg_ref )
{
}

Discipline_Actor::~Discipline_Actor( void )
{
}

INLINE_METHODS void Discipline_Actor::enter3_Initiate_Discipline( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_CuE4cDbsEfGJaL0kWrhu3A
triggerInputPort.triggerInput().send();
//}}}USR
}

void Discipline_Actor::enterStateV( void )
{
    switch( getCurrentState() )
    {
    case 3:
        enter3_Initiate_Discipline(  );
        break;
    default:
        RTActor::enterStateV(  );
        break;
    }
}

INLINE_CHAINS void Discipline_Actor::chain1_Initial( void )
{
    rtgChainBegin( 1, "Initial" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 2 );
}

INLINE_CHAINS void Discipline_Actor::chain2_discipline_activated( void )
{
    rtgChainBegin( 2, "discipline activated" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Discipline_Actor::chain3_exit( void )
{
    rtgChainBegin( 3, "exit" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 2 );
}

void Discipline_Actor::rtsBehavior( int signalIndex, int portIndex )
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
                case 3 /*disciplinePort*/:
                    switch( signalIndex )
                    {
                    case DisciplineProt::Conjugate::rti_initDiscipline:
                        chain2_discipline_activated(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 3 /* Initiate Discipline (State Machine::Initiate Discipline) */:
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
                case 3 /*disciplinePort*/:
                    switch( signalIndex )
                    {
                    case DisciplineProt::Conjugate::rti_exit:
                        chain3_exit(  );
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

const RTStateId Discipline_Actor::rtg_parent_state[] =
{
    0
    , 1
    , 1
};

const RTActor_class * Discipline_Actor::getActorData( void ) const
{
    return &Discipline_Actor::rtg_class;
}

const RTActor_class Discipline_Actor::rtg_class =
{
    nullptr
    , rtg_state_names
    , 3
    , Discipline_Actor::rtg_parent_state
    , &Discipline
    , 0
    , nullptr
    , 3
    , Discipline_Actor::rtg_ports
    , 0
    , nullptr
    , 0
    , nullptr
};

const RTPortDescriptor Discipline_Actor::rtg_ports[] =
{
    {
        "triggerInputPort"
        , nullptr
        , &InputProt::Base::rt_class
        , RTOffsetOf( Discipline_Actor, triggerInputPort )
        , 1
        , 1
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "updateValPort"
        , nullptr
        , &UpdateValProt::Base::rt_class
        , RTOffsetOf( Discipline_Actor, updateValPort )
        , 1
        , 2
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "disciplinePort"
        , nullptr
        , &DisciplineProt::Conjugate::rt_class
        , RTOffsetOf( Discipline_Actor, disciplinePort )
        , 1
        , 3
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
};

int Discipline_Actor::_followInV( RTBindingEnd & rtg_end, int rtg_portId, int rtg_repIndex )
{
    switch( rtg_portId )
    {
    case 0:
        if( rtg_repIndex < 1 )
        {
            rtg_end.port = &triggerInputPort;
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
            rtg_end.port = &disciplinePort;
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
        "triggerInputPort"
        , &InputProt::Base::rt_class
        , 1
    }
    , {
        "updateValPort"
        , &UpdateValProt::Base::rt_class
        , 1
    }
    , {
        "disciplinePort"
        , &DisciplineProt::Conjugate::rt_class
        , 1
    }
};

static RTActor * new_Discipline_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
{
    return new Discipline_Actor( rtg_rts, rtg_ref );
}

const RTActorClass Discipline =
{
    nullptr
    , "Discipline"
    , 0 /*RTVersionId*/
    , 3
    , rtg_relays
    , new_Discipline_Actor
};

