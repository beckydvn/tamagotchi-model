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
    , "Sit"
    , "Untrained"
    , "Doesn't Sit"
    , ""
    , ""
    , ""
    , ""
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
    case 4:
        enter4_Sit(  );
        break;
    case 5:
        enter5_Untrained(  );
        break;
    case 6:
        enter6_Doesn_t_Sit(  );
        break;
    default:
        RTActor::enterStateV(  );
        break;
    }
}

INLINE_METHODS void Discipline_Actor::enter4_Sit( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_DadGkDdKEfGJaL0kWrhu3A
std::cout<< "\nSITS!" <<std::endl;
//}}}USR
}

INLINE_METHODS void Discipline_Actor::enter5_Untrained( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_bHVyoDdKEfGJaL0kWrhu3A
std::cout<< "\nPET IS THINKING..." <<std::endl;
rng = (rand() % 2);
generalTimer = timing.informIn(RTTimespec(3,0));
//}}}USR
}

INLINE_METHODS void Discipline_Actor::enter6_Doesn_t_Sit( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_lgzUQDdfEfGJaL0kWrhu3A
std::cout<< "\nDOESN'T SIT..." <<std::endl;

//}}}USR
}

INLINE_METHODS int Discipline_Actor::guard5_sitCount_4( const void * rtdata, DisciplineProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_B5_rUDdIEfGJaL0kWrhu3A
return (sitCount <= 4);
//}}}USR
}

INLINE_METHODS void Discipline_Actor::transition7_reinforce( const void * rtdata, DisciplineProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_0LGVkDdLEfGJaL0kWrhu3A
input = (const char *)rtdata;
//}}}USR
}

INLINE_METHODS int Discipline_Actor::guard8_yes( const void * rtdata, DisciplineProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_HVwzoDdMEfGJaL0kWrhu3A
return (input == "YES");
//}}}USR
}

INLINE_METHODS void Discipline_Actor::transition8_yes( const void * rtdata, DisciplineProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_AxsIADdfEfGJaL0kWrhu3A
std::cout<< "\nGAVE A TREAT!" <<std::endl;
updateValPort.updateDiscipline(2).send();
//}}}USR
}

INLINE_METHODS int Discipline_Actor::guard10_50_chance( const void * rtdata, DisciplineProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_qOxvADdOEfGJaL0kWrhu3A
return (rng == 0);
//}}}USR
}

INLINE_METHODS void Discipline_Actor::transition12_reinforce( const void * rtdata, DisciplineProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_SsYocDdeEfGJaL0kWrhu3A
input = (const char *)rtdata;
//}}}USR
}

INLINE_METHODS int Discipline_Actor::guard13_yes( const void * rtdata, DisciplineProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_jNRA0DdeEfGJaL0kWrhu3A
return (input == "YES");
//}}}USR
}

INLINE_METHODS void Discipline_Actor::transition13_yes( const void * rtdata, DisciplineProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_MJftwDdfEfGJaL0kWrhu3A
std::cout<< "\nGAVE A TREAT!" <<std::endl;
updateValPort.updateDiscipline(-2).send();
//}}}USR
}

INLINE_METHODS int Discipline_Actor::guard14_no( const void * rtdata, DisciplineProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_lsSA8DdeEfGJaL0kWrhu3A
return (input == "NO");
//}}}USR
}

INLINE_METHODS void Discipline_Actor::transition14_no( const void * rtdata, DisciplineProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_BM0k0DdfEfGJaL0kWrhu3A
std::cout<< "\nYOU DIDN'T GIVE A TREAT." <<std::endl;
updateValPort.updateDiscipline(-1).send();
//}}}USR
}

INLINE_METHODS int Discipline_Actor::guard15_no( const void * rtdata, DisciplineProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_oeXuEDdeEfGJaL0kWrhu3A
return (input == "NO");
//}}}USR
}

INLINE_METHODS void Discipline_Actor::transition15_no( const void * rtdata, DisciplineProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_OLyVoDdfEfGJaL0kWrhu3A
std::cout<< "\nYOU DIDN'T GIVE A TREAT." <<std::endl;
updateValPort.updateDiscipline(1).send();
//}}}USR
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

INLINE_CHAINS void Discipline_Actor::chain4_sit( void )
{
    rtgChainBegin( 3, "sit" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    if( guard5_sitCount_4( msg->data, static_cast< DisciplineProt::Conjugate * > ( msg->sap() ) ) )
    {
        chain5_sitCount_4(  );
        return ;
    }
    chain6_else(  );
}

INLINE_CHAINS void Discipline_Actor::chain5_sitCount_4( void )
{
    rtgChainBegin( 7, "sitCount <= 4" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    if( guard10_50_chance( msg->data, static_cast< DisciplineProt::Conjugate * > ( msg->sap() ) ) )
    {
        chain10_50_chance(  );
        return ;
    }
    chain11_else(  );
}

INLINE_CHAINS void Discipline_Actor::chain6_else( void )
{
    rtgChainBegin( 7, "else" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 4 );
}

INLINE_CHAINS void Discipline_Actor::chain7_reinforce( void )
{
    rtgChainBegin( 4, "reinforce" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition7_reinforce( msg->data, static_cast< DisciplineProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    if( guard8_yes( msg->data, static_cast< DisciplineProt::Conjugate * > ( msg->sap() ) ) )
    {
        chain8_yes(  );
        return ;
    }
    if( guard14_no( msg->data, static_cast< DisciplineProt::Conjugate * > ( msg->sap() ) ) )
    {
        chain14_no(  );
        return ;
    }
}

INLINE_CHAINS void Discipline_Actor::chain8_yes( void )
{
    rtgChainBegin( 8, "yes" );
    rtgTransitionBegin(  );
    transition8_yes( msg->data, static_cast< DisciplineProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Discipline_Actor::chain9_timeout( void )
{
    rtgChainBegin( 5, "timeout" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 5 );
}

INLINE_CHAINS void Discipline_Actor::chain10_50_chance( void )
{
    rtgChainBegin( 9, "50% chance" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 4 );
}

INLINE_CHAINS void Discipline_Actor::chain11_else( void )
{
    rtgChainBegin( 9, "else" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 6 );
}

INLINE_CHAINS void Discipline_Actor::chain12_reinforce( void )
{
    rtgChainBegin( 6, "reinforce" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition12_reinforce( msg->data, static_cast< DisciplineProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    if( guard13_yes( msg->data, static_cast< DisciplineProt::Conjugate * > ( msg->sap() ) ) )
    {
        chain13_yes(  );
        return ;
    }
    if( guard15_no( msg->data, static_cast< DisciplineProt::Conjugate * > ( msg->sap() ) ) )
    {
        chain15_no(  );
        return ;
    }
}

INLINE_CHAINS void Discipline_Actor::chain13_yes( void )
{
    rtgChainBegin( 10, "yes" );
    rtgTransitionBegin(  );
    transition13_yes( msg->data, static_cast< DisciplineProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Discipline_Actor::chain14_no( void )
{
    rtgChainBegin( 8, "no" );
    rtgTransitionBegin(  );
    transition14_no( msg->data, static_cast< DisciplineProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Discipline_Actor::chain15_no( void )
{
    rtgChainBegin( 10, "no" );
    rtgTransitionBegin(  );
    transition15_no( msg->data, static_cast< DisciplineProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
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
                    case DisciplineProt::Conjugate::rti_sit:
                        chain4_sit(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 4 /* Sit (State Machine::Sit) */:
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
                    case DisciplineProt::Conjugate::rti_reinforce:
                        chain7_reinforce(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 5 /* Untrained (State Machine::Untrained) */:
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
                case 4 /*timing*/:
                    switch( signalIndex )
                    {
                    case Timing::Base::rti_timeout:
                        chain9_timeout(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 6 /* Doesn't Sit (State Machine::Doesn't Sit) */:
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
                    case DisciplineProt::Conjugate::rti_reinforce:
                        chain12_reinforce(  );
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
    , 1
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
    , 6
    , Discipline_Actor::rtg_parent_state
    , &Discipline
    , 0
    , nullptr
    , 4
    , Discipline_Actor::rtg_ports
    , 0
    , nullptr
    , 3
    , Discipline_Actor::rtg_Discipline_Actor_fields
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
    , {
        "timing"
        , nullptr
        , &Timing::Base::rt_class
        , RTOffsetOf( Discipline_Actor, timing )
        , 1
        , 4
        , RTPortDescriptor::KindSpecial + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
};

const RTFieldDescriptor Discipline_Actor::rtg_Discipline_Actor_fields[] =
{
    {
        "sitCount"
        , RTOffsetOf( Discipline_Actor, sitCount )
        , &RTType_int
        , nullptr
    }
    , {
        "rng"
        , RTOffsetOf( Discipline_Actor, rng )
        , &RTType_int
        , nullptr
    }
    , {
        "generalTimer"
        , RTOffsetOf( Discipline_Actor, generalTimer )
        , &RTType_RTTimerId
        , nullptr
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

