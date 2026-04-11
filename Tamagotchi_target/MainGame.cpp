#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "MainGame.h"
#endif
#include <UnitName.h>
#include <MainGame.h>

extern const RTActorClass Input;

static const char * const rtg_state_names[] =
{
    "<machine>"
    , "Hatch"
    , "Idle"
    , "Inc Hunger"
    , "Dec Happiness"
    , "Dec Discipline"
    , "Return To Idle"
    , "RNGVal"
};

static const RTInterfaceDescriptor rtg_interfaces_input[] =
{
    {
        "statusProt"
        , 1
    }
};

static const RTBindingDescriptor rtg_bindings_input[] =
{
    {
        0
        , &StatusProt::Base::rt_class
    }
};

#define SUPER RTActor
MainGame_Actor::MainGame_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
    : RTActor( rtg_rts ,rtg_ref )
{
}

MainGame_Actor::~MainGame_Actor( void )
{
}

void MainGame_Actor::showStatus( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_mW9aQDRsEfGs993j7RVgLQ
std::cout<< "\n-----------------------------------------------------------------------" <<std::endl;
std::cout<< tama_name << " STATUS:\n" << "\nHUNGER: " << hunger << "\nHAPPINESS: " << happiness << "\nDISCIPLINE: " << discipline << "\nHEALTH: " << health <<std::endl;
std::cout<< "-----------------------------------------------------------------------" <<std::endl;
//}}}USR
}

INLINE_METHODS void MainGame_Actor::enter2_Hatch( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_NnvBADUoEfGJaL0kWrhu3A
std::cout << "[Status] incarnating 'input' on logical thread 'InputLogical'" << std::endl;
RTTypedValue noData ( (const void *)0, (const RTObject_class *)0 );
RTActorId inputThread = frameP.incarnate(input, noData, InputLogical);
if (!inputThread.isValid())
	context()->perror("[Status] incarnation failed!");

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

std::cout<< "\nINITIALIZING STATS..." <<std::endl;

statusProt.hatch().send();
timingPort.informIn(RTTimespec(0.5,0));
//}}}USR
}

void MainGame_Actor::enterStateV( void )
{
    switch( getCurrentState() )
    {
    case 2:
        enter2_Hatch(  );
        break;
    case 3:
        enter3_Idle(  );
        break;
    case 4:
        enter4_Inc_Hunger(  );
        break;
    case 5:
        enter5_Dec_Happiness(  );
        break;
    case 6:
        enter6_Dec_Discipline(  );
        break;
    case 7:
        enter7_Return_To_Idle(  );
        break;
    default:
        RTActor::enterStateV(  );
        break;
    }
}

INLINE_METHODS void MainGame_Actor::enter3_Idle( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#__QRG0DUUEfGPsvtei6AytQ
std::cout<< "\nWHAT WOULD YOU LIKE TO DO NEXT?" <<std::endl;

// here, we randomly generate the next event.
// discipline, happiness, and hunger all change over time (the first two decrease, the latter increases).
// every 5 seconds, we randomly pick one of the 3 to decrease/increase by 1 point.

rng = (rand() % 100);
timingPort.informIn(RTTimespec(5,0));
//}}}USR
}

INLINE_METHODS void MainGame_Actor::enter4_Inc_Hunger( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_LWNdkDUYEfGJaL0kWrhu3A
std::cout<< "\n" << tama_name << " IS GETTING HUNGRY..." <<std::endl;
hunger += 1;
timingPort.informIn(RTTimespec(0.2,0));

//}}}USR
}

INLINE_METHODS void MainGame_Actor::enter5_Dec_Happiness( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_IrkNgDUeEfGJaL0kWrhu3A
std::cout<< "\n" << tama_name << " IS GETTING BORED..." <<std::endl;
happiness -= 1;
timingPort.informIn(RTTimespec(0.2,0));

//}}}USR
}

INLINE_METHODS void MainGame_Actor::enter6_Dec_Discipline( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_8_H_EDUeEfGJaL0kWrhu3A
std::cout<< "\n" << tama_name << " IS GETTING ROWDY..." <<std::endl;
discipline -= 1;
timingPort.informIn(RTTimespec(0.2,0));

//}}}USR
}

INLINE_METHODS void MainGame_Actor::enter7_Return_To_Idle( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_6tDGYDUsEfGJaL0kWrhu3A
statusProt.returnToIdle().send();
timingPort.informIn(RTTimespec(0.2,0));

//}}}USR
}

INLINE_METHODS int MainGame_Actor::guard3_50_chance( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_QnuoQDUdEfGJaL0kWrhu3A
return (rng <= 50);
//}}}USR
}

INLINE_METHODS int MainGame_Actor::guard4_30_chance( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_UKgWADUeEfGJaL0kWrhu3A
return (rng > 50 && rng <= 80);
//}}}USR
}

INLINE_METHODS int MainGame_Actor::guard5_20_chance( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_y1jHADUeEfGJaL0kWrhu3A
return (rng > 80 && rng <= 100);
//}}}USR
}

INLINE_CHAINS void MainGame_Actor::chain1_Initial( void )
{
    rtgChainBegin( 1, "Initial" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 2 );
}

INLINE_CHAINS void MainGame_Actor::chain2_timeout( void )
{
    rtgChainBegin( 3, "timeout" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    if( guard3_50_chance( msg->data, static_cast< Timing::Base * > ( msg->sap() ) ) )
    {
        chain3_50_chance(  );
        return ;
    }
    if( guard4_30_chance( msg->data, static_cast< Timing::Base * > ( msg->sap() ) ) )
    {
        chain4_30_chance(  );
        return ;
    }
    if( guard5_20_chance( msg->data, static_cast< Timing::Base * > ( msg->sap() ) ) )
    {
        chain5_20_chance(  );
        return ;
    }
}

INLINE_CHAINS void MainGame_Actor::chain3_50_chance( void )
{
    rtgChainBegin( 8, "50% chance" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 4 );
}

INLINE_CHAINS void MainGame_Actor::chain4_30_chance( void )
{
    rtgChainBegin( 8, "30% chance" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 5 );
}

INLINE_CHAINS void MainGame_Actor::chain5_20_chance( void )
{
    rtgChainBegin( 8, "20% chance" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 6 );
}

INLINE_CHAINS void MainGame_Actor::chain6_timeout( void )
{
    rtgChainBegin( 6, "timeout" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 7 );
}

INLINE_CHAINS void MainGame_Actor::chain7_timeout( void )
{
    rtgChainBegin( 5, "timeout" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 7 );
}

INLINE_CHAINS void MainGame_Actor::chain8_timeout( void )
{
    rtgChainBegin( 4, "timeout" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 7 );
}

INLINE_CHAINS void MainGame_Actor::chain9_timeout( void )
{
    rtgChainBegin( 7, "timeout" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void MainGame_Actor::chain10_timeout( void )
{
    rtgChainBegin( 2, "timeout" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 3 );
}

void MainGame_Actor::rtsBehavior( int signalIndex, int portIndex )
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
            case 2 /* Hatch (State Machine::Hatch) */:
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
                        chain10_timeout(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 3 /* Idle (State Machine::Idle) */:
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
                        chain2_timeout(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 4 /* Inc Hunger (State Machine::Inc Hunger) */:
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
                        chain8_timeout(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 5 /* Dec Happiness (State Machine::Dec Happiness) */:
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
                        chain7_timeout(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 6 /* Dec Discipline (State Machine::Dec Discipline) */:
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
                        chain6_timeout(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 7 /* Return To Idle (State Machine::Return To Idle) */:
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
            default:
                unexpectedState(  );
                return ;
            }
        }
}

const RTStateId MainGame_Actor::rtg_parent_state[] =
{
    0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
};

const RTActor_class * MainGame_Actor::getActorData( void ) const
{
    return &MainGame_Actor::rtg_class;
}

const RTActor_class MainGame_Actor::rtg_class =
{
    nullptr
    , rtg_state_names
    , 7
    , MainGame_Actor::rtg_parent_state
    , &MainGame
    , 1
    , MainGame_Actor::rtg_capsule_roles
    , 3
    , MainGame_Actor::rtg_ports
    , 0
    , nullptr
    , 5
    , MainGame_Actor::rtg_MainGame_Actor_fields
};

const RTComponentDescriptor MainGame_Actor::rtg_capsule_roles[] =
{
    {
        "input"
        , &Input
        , RTOffsetOf( MainGame_Actor, input )
        , 1
        , RTComponentDescriptor::Optional
        , 1
        , 1
        , 1
        , rtg_interfaces_input
        , 1
        , rtg_bindings_input
    }
};

const RTPortDescriptor MainGame_Actor::rtg_ports[] =
{
    {
        "frameP"
        , nullptr
        , &Frame::Base::rt_class
        , RTOffsetOf( MainGame_Actor, frameP )
        , 1
        , 1
        , RTPortDescriptor::KindSpecial + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "timingPort"
        , nullptr
        , &Timing::Base::rt_class
        , RTOffsetOf( MainGame_Actor, timingPort )
        , 1
        , 2
        , RTPortDescriptor::KindSpecial + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "statusProt"
        , nullptr
        , &StatusProt::Base::rt_class
        , RTOffsetOf( MainGame_Actor, statusProt )
        , 1
        , 3
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
};

const RTFieldDescriptor MainGame_Actor::rtg_MainGame_Actor_fields[] =
{
    {
        "hunger"
        , RTOffsetOf( MainGame_Actor, hunger )
        , &RTType_int
        , nullptr
    }
    , {
        "discipline"
        , RTOffsetOf( MainGame_Actor, discipline )
        , &RTType_int
        , nullptr
    }
    , {
        "happiness"
        , RTOffsetOf( MainGame_Actor, happiness )
        , &RTType_int
        , nullptr
    }
    , {
        "health"
        , RTOffsetOf( MainGame_Actor, health )
        , &RTType_int
        , nullptr
    }
    , {
        "rng"
        , RTOffsetOf( MainGame_Actor, rng )
        , &RTType_int
        , nullptr
    }
};

int MainGame_Actor::_followOutV( RTBindingEnd & rtg_end, int rtg_compId, int rtg_portId, int rtg_repIndex )
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
static RTActor * new_MainGame_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
{
    return new MainGame_Actor( rtg_rts, rtg_ref );
}

const RTActorClass MainGame =
{
    nullptr
    , "MainGame"
    , 0 /*RTVersionId*/
    , 0
    , nullptr
    , new_MainGame_Actor
};

