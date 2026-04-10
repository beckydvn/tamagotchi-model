#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "Status.h"
#endif
#include <UnitName.h>
#include <Status.h>

static const char * const rtg_state_names[] =
{
    "<machine>"
    , "Start"
    , "Hatch"
    , "Idle"
    , "Inc Hunger"
    , "Dec Happiness"
    , "Dec Discipline"
    , "RNGVal"
    , ""
};

#define SUPER RTActor
Status_Actor::Status_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
    : RTActor( rtg_rts ,rtg_ref )
{
}

Status_Actor::~Status_Actor( void )
{
}

void Status_Actor::showStatus( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_mW9aQDRsEfGs993j7RVgLQ
std::cout<< "\n-----------------------------------------------------------------------" <<std::endl;
std::cout<< tama_name << " STATUS:\n" << "\nHUNGER: " << hunger << "\nHAPPINESS: " << happiness << "\nDISCIPLINE: " << discipline << "\nHEALTH: " << health <<std::endl;
std::cout<< "-----------------------------------------------------------------------" <<std::endl;
//}}}USR
}

INLINE_METHODS void Status_Actor::enter3_Hatch( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_rydaoDRhEfGs993j7RVgLQ
std::cout<< "YOUR TAMAGOTCHI HAS HATCHED!" <<std::endl;

std::cout<< "PLEASE ENTER THE NAME YOU WOULD LIKE TO GIVE YOUR TAMAGOTCHI:" <<std::endl;

char tname[256];

fgets(tname, sizeof(tname), stdin);

// Remove trailing newline if present
tname[strcspn(tname, "\n")] = '\0';

for (int i = 0; tname[i]; i++) {
        tname[i] = toupper(tname[i]);
}

tama_name = tname;

std::cout<< "AND WHAT IS YOUR NAME?" <<std::endl;

char oname[256];

fgets(oname, sizeof(oname), stdin);

// Remove trailing newline if present
oname[strcspn(oname, "\n")] = '\0';

for (int i = 0; oname[i]; i++) {
        oname[i] = toupper(oname[i]);
}

owner_name = oname;

std::cout<< "\n" << tname << " LOOKS HAPPY TO MEET YOU, " << owner_name << "!" <<std::endl;

std::cout<< "\nINITIALIZING METERS..." <<std::endl;

showStatus();

timingPort.informIn(RTTimespec(1,0));
//}}}USR
}

void Status_Actor::enterStateV( void )
{
    switch( getCurrentState() )
    {
    case 3:
        enter3_Hatch(  );
        break;
    case 4:
        enter4_Idle(  );
        break;
    case 5:
        enter5_Inc_Hunger(  );
        break;
    case 6:
        enter6_Dec_Happiness(  );
        break;
    case 7:
        enter7_Dec_Discipline(  );
        break;
    default:
        RTActor::enterStateV(  );
        break;
    }
}

INLINE_METHODS void Status_Actor::enter4_Idle( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#__QRG0DUUEfGPsvtei6AytQ
std::cout<< "\n" << tama_name << " IS IDLING..." <<std::endl;
showStatus();

// here, we randomly generate the next event.
// discipline, happiness, and hunger all change over time (the first two decrease, the latter increases).
// every 5 seconds, we randomly pick one of the 3 to decrease/increase by 1 point.

rng = (rand() % 100);
timingPort.informIn(RTTimespec(5,0));
//}}}USR
}

INLINE_METHODS void Status_Actor::enter5_Inc_Hunger( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_LWNdkDUYEfGJaL0kWrhu3A
std::cout<< "\n" << tama_name << " IS GETTING HUNGRY..." <<std::endl;
hunger += 1;
timingPort.informIn(RTTimespec(0.2,0));

//}}}USR
}

INLINE_METHODS void Status_Actor::enter6_Dec_Happiness( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_IrkNgDUeEfGJaL0kWrhu3A
std::cout<< "\n" << tama_name << " IS GETTING BORED..." <<std::endl;
happiness -= 1;
timingPort.informIn(RTTimespec(0.2,0));

//}}}USR
}

INLINE_METHODS void Status_Actor::enter7_Dec_Discipline( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_8_H_EDUeEfGJaL0kWrhu3A
std::cout<< "\n" << tama_name << " IS GETTING ROWDY..." <<std::endl;
discipline -= 1;
timingPort.informIn(RTTimespec(0.2,0));

//}}}USR
}

INLINE_METHODS int Status_Actor::guard5_50_chance( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_QnuoQDUdEfGJaL0kWrhu3A
return (rng <= 50);
//}}}USR
}

INLINE_METHODS int Status_Actor::guard6_30_chance( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_UKgWADUeEfGJaL0kWrhu3A
return (rng > 50 && rng <= 80);
//}}}USR
}

INLINE_METHODS int Status_Actor::guard7_20_chance( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_y1jHADUeEfGJaL0kWrhu3A
return (rng > 80 && rng <= 100);
//}}}USR
}

INLINE_CHAINS void Status_Actor::chain1_Initial( void )
{
    rtgChainBegin( 1, "Initial" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 2 );
}

INLINE_CHAINS void Status_Actor::chain2_initiate_hatch( void )
{
    rtgChainBegin( 2, "initiate hatch" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Status_Actor::chain3_start( void )
{
    rtgChainBegin( 3, "start" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 4 );
}

INLINE_CHAINS void Status_Actor::chain4_timeout( void )
{
    rtgChainBegin( 4, "timeout" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    if( guard5_50_chance( msg->data, static_cast< Timing::Base * > ( msg->sap() ) ) )
    {
        chain5_50_chance(  );
        return ;
    }
    if( guard6_30_chance( msg->data, static_cast< Timing::Base * > ( msg->sap() ) ) )
    {
        chain6_30_chance(  );
        return ;
    }
    if( guard7_20_chance( msg->data, static_cast< Timing::Base * > ( msg->sap() ) ) )
    {
        chain7_20_chance(  );
        return ;
    }
}

INLINE_CHAINS void Status_Actor::chain5_50_chance( void )
{
    rtgChainBegin( 8, "50% chance" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 5 );
}

INLINE_CHAINS void Status_Actor::chain6_30_chance( void )
{
    rtgChainBegin( 8, "30% chance" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 6 );
}

INLINE_CHAINS void Status_Actor::chain7_20_chance( void )
{
    rtgChainBegin( 8, "20% chance" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 7 );
}

INLINE_CHAINS void Status_Actor::chain8_timeout_11( void )
{
    rtgChainBegin( 7, "timeout" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    rtgChainBegin( 9, "reset" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 4 );
}

INLINE_CHAINS void Status_Actor::chain9_timeout_11( void )
{
    rtgChainBegin( 6, "timeout" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    rtgChainBegin( 9, "reset" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 4 );
}

INLINE_CHAINS void Status_Actor::chain10_timeout_11( void )
{
    rtgChainBegin( 5, "timeout" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    rtgChainBegin( 9, "reset" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 4 );
}

void Status_Actor::rtsBehavior( int signalIndex, int portIndex )
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
                    case StatusProt::Base::rti_hatch:
                        chain2_initiate_hatch(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 3 /* Hatch (State Machine::Hatch) */:
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
                case 2 /*timingPort*/:
                    switch( signalIndex )
                    {
                    case Timing::Base::rti_timeout:
                        chain3_start(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 4 /* Idle (State Machine::Idle) */:
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
                case 2 /*timingPort*/:
                    switch( signalIndex )
                    {
                    case Timing::Base::rti_timeout:
                        chain4_timeout(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 5 /* Inc Hunger (State Machine::Inc Hunger) */:
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
                case 2 /*timingPort*/:
                    switch( signalIndex )
                    {
                    case Timing::Base::rti_timeout:
                        chain10_timeout_11(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 6 /* Dec Happiness (State Machine::Dec Happiness) */:
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
                case 2 /*timingPort*/:
                    switch( signalIndex )
                    {
                    case Timing::Base::rti_timeout:
                        chain9_timeout_11(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 7 /* Dec Discipline (State Machine::Dec Discipline) */:
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
                case 2 /*timingPort*/:
                    switch( signalIndex )
                    {
                    case Timing::Base::rti_timeout:
                        chain8_timeout_11(  );
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

const RTStateId Status_Actor::rtg_parent_state[] =
{
    0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
};

const RTActor_class * Status_Actor::getActorData( void ) const
{
    return &Status_Actor::rtg_class;
}

const RTActor_class Status_Actor::rtg_class =
{
    nullptr
    , rtg_state_names
    , 7
    , Status_Actor::rtg_parent_state
    , &Status
    , 0
    , nullptr
    , 2
    , Status_Actor::rtg_ports
    , 0
    , nullptr
    , 5
    , Status_Actor::rtg_Status_Actor_fields
};

const RTPortDescriptor Status_Actor::rtg_ports[] =
{
    {
        "statusProt"
        , nullptr
        , &StatusProt::Base::rt_class
        , RTOffsetOf( Status_Actor, statusProt )
        , 1
        , 1
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "timingPort"
        , nullptr
        , &Timing::Base::rt_class
        , RTOffsetOf( Status_Actor, timingPort )
        , 1
        , 2
        , RTPortDescriptor::KindSpecial + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
};

const RTFieldDescriptor Status_Actor::rtg_Status_Actor_fields[] =
{
    {
        "hunger"
        , RTOffsetOf( Status_Actor, hunger )
        , &RTType_int
        , nullptr
    }
    , {
        "discipline"
        , RTOffsetOf( Status_Actor, discipline )
        , &RTType_int
        , nullptr
    }
    , {
        "happiness"
        , RTOffsetOf( Status_Actor, happiness )
        , &RTType_int
        , nullptr
    }
    , {
        "health"
        , RTOffsetOf( Status_Actor, health )
        , &RTType_int
        , nullptr
    }
    , {
        "rng"
        , RTOffsetOf( Status_Actor, rng )
        , &RTType_int
        , nullptr
    }
};

int Status_Actor::_followInV( RTBindingEnd & rtg_end, int rtg_portId, int rtg_repIndex )
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
        , &StatusProt::Base::rt_class
        , 1
    }
};

static RTActor * new_Status_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
{
    return new Status_Actor( rtg_rts, rtg_ref );
}

const RTActorClass Status =
{
    nullptr
    , "Status"
    , 0 /*RTVersionId*/
    , 1
    , rtg_relays
    , new_Status_Actor
};

