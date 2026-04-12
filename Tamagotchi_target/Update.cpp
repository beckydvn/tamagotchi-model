#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "Update.h"
#endif
#include <UnitName.h>
#include <Update.h>
#include <FeedProt.h>
#include <InputProt.h>

extern const RTActorClass Feed;

extern const RTActorClass InputLoop;

extern const RTActorClass TranslateInput;

static const char * const rtg_state_names[] =
{
    "<machine>"
    , "Hatch"
    , "Idle"
    , "RNGVal"
    , ""
    , ""
};

static const RTInterfaceDescriptor rtg_interfaces_input[] =
{
    {
        "statusPort"
        , 1
    }
    , {
        "inputPort"
        , 1
    }
};

static const RTBindingDescriptor rtg_bindings_input[] =
{
    {
        0
        , &StatusProt::Base::rt_class
    }
    , {
        1
        , &InputProt::Conjugate::rt_class
    }
};

static const RTInterfaceDescriptor rtg_interfaces_feed[] =
{
    {
        "feedPort"
        , 1
    }
    , {
        "updateValPort"
        , 1
    }
};

static const RTBindingDescriptor rtg_bindings_feed[] =
{
    {
        0
        , &FeedProt::Base::rt_class
    }
    , {
        1
        , &UpdateValProt::Conjugate::rt_class
    }
};

static const RTInterfaceDescriptor rtg_interfaces_translateInput[] =
{
    {
        "inputPort"
        , 1
    }
    , {
        "feedPort"
        , 1
    }
    , {
        "updateOptionsPort"
        , 1
    }
};

static const RTBindingDescriptor rtg_bindings_translateInput[] =
{
    {
        0
        , &InputProt::Base::rt_class
    }
    , {
        1
        , &FeedProt::Conjugate::rt_class
    }
    , {
        2
        , &UpdateOptionsProt::Conjugate::rt_class
    }
};

#define SUPER RTActor
Update_Actor::Update_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
    : RTActor( rtg_rts ,rtg_ref )
{
}

Update_Actor::~Update_Actor( void )
{
}

void Update_Actor::showStatus( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_mW9aQDRsEfGs993j7RVgLQ
std::cout<< "\n-----------------------------------------------------------------------" <<std::endl;
std::cout<< tama_name << " STATUS:\n" << "\nHUNGER: " << hunger << "\nHAPPINESS: " << happiness << "\nDISCIPLINE: " << discipline << "\nHEALTH: " << health <<std::endl;
std::cout<< "-----------------------------------------------------------------------" <<std::endl;
//}}}USR
}

INLINE_METHODS void Update_Actor::enter2_Hatch( void )
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
showStatus();
statusPort.hatch().send();
timingPort.informIn(RTTimespec(0.5,0));
//}}}USR
}

void Update_Actor::enterStateV( void )
{
    switch( getCurrentState() )
    {
    case 2:
        enter2_Hatch(  );
        break;
    case 3:
        enter3_Idle(  );
        break;
    default:
        RTActor::enterStateV(  );
        break;
    }
}

INLINE_METHODS void Update_Actor::enter3_Idle( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_7GC-sDX8EfGJaL0kWrhu3A
// here, we randomly generate the next event.
// discipline, happiness, and hunger all change over time (the first two decrease, the latter increases).
// every time we receive a "timeout," we randomly pick one of the 3 to decrease/increase by 1 point.
rng = (rand() % 100);

std::cout << "WHAT WILL " << owner_name << " DO?" << options << std::endl;
//}}}USR
}

INLINE_METHODS int Update_Actor::guard3_inc_hunger_50_chance( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_QnuoQDUdEfGJaL0kWrhu3A
return (rng <= 50);
//}}}USR
}

INLINE_METHODS void Update_Actor::transition3_inc_hunger_50_chance( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_nHuvwDX0EfGJaL0kWrhu3A
std::cout<< "\n" << tama_name << " IS GETTING HUNGRY..." <<std::endl;
hunger += 1;
//}}}USR
}

INLINE_METHODS int Update_Actor::guard4_dec_happiness_30_chance( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_UKgWADUeEfGJaL0kWrhu3A
return (rng > 50 && rng <= 80);
//}}}USR
}

INLINE_METHODS void Update_Actor::transition4_dec_happiness_30_chance( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_rfzjQDX0EfGJaL0kWrhu3A
std::cout<< "\n" << tama_name << " IS GETTING BORED..." <<std::endl;
happiness -= 1;
//}}}USR
}

INLINE_METHODS int Update_Actor::guard5_20_chance( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_y1jHADUeEfGJaL0kWrhu3A
return (rng > 80 && rng <= 100);
//}}}USR
}

INLINE_METHODS void Update_Actor::transition5_20_chance( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_8hdGYDX0EfGJaL0kWrhu3A
std::cout<< "\n" << tama_name << " IS GETTING ROWDY..." <<std::endl;
discipline -= 1;
//}}}USR
}

INLINE_METHODS void Update_Actor::transition6_timeout( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_3dEs4DX8EfGJaL0kWrhu3A
timingPort.informEvery(RTTimespec(10,0));
//}}}USR
}

INLINE_METHODS void Update_Actor::transition7_updateHunger( const int * rtdata, UpdateValProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_0y1oIDXkEfGJaL0kWrhu3A
hunger += *rtdata;
showStatus();
//}}}USR
}

INLINE_METHODS void Update_Actor::transition8_updateHealth( const int * rtdata, UpdateValProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_wL2YcDXwEfGJaL0kWrhu3A
health += *rtdata;
showStatus();
//}}}USR
}

INLINE_METHODS int Update_Actor::guard9_is_full( const int * rtdata, UpdateValProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_2mxsIDX-EfGJaL0kWrhu3A
return (hunger <= 0);
//}}}USR
}

INLINE_METHODS void Update_Actor::transition9_is_full( const int * rtdata, UpdateValProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_9EFGwDX-EfGJaL0kWrhu3A
std::cout<< tama_name << " IS FEELING FULL..." << std::endl;
//}}}USR
}

INLINE_METHODS int Update_Actor::guard11_ill( const int * rtdata, UpdateValProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_XP1pADX_EfGJaL0kWrhu3A
return (health <= 5);
//}}}USR
}

INLINE_METHODS void Update_Actor::transition11_ill( const int * rtdata, UpdateValProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_aBWuYDX_EfGJaL0kWrhu3A
std::cout<< tama_name << " IS FEELING ILL..." << std::endl;
//}}}USR
}

INLINE_METHODS void Update_Actor::transition13_updateOptions( const void * rtdata, UpdateOptionsProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_4APKsDYEEfGJaL0kWrhu3A
options = (const char *)rtdata;
//}}}USR
}

INLINE_CHAINS void Update_Actor::chain1_Initial( void )
{
    rtgChainBegin( 1, "Initial" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 2 );
}

INLINE_CHAINS void Update_Actor::chain2_timeout( void )
{
    rtgChainBegin( 3, "timeout" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    if( guard3_inc_hunger_50_chance( msg->data, static_cast< Timing::Base * > ( msg->sap() ) ) )
    {
        chain3_inc_hunger_50_chance(  );
        return ;
    }
    if( guard4_dec_happiness_30_chance( msg->data, static_cast< Timing::Base * > ( msg->sap() ) ) )
    {
        chain4_dec_happiness_30_chance(  );
        return ;
    }
    if( guard5_20_chance( msg->data, static_cast< Timing::Base * > ( msg->sap() ) ) )
    {
        chain5_20_chance(  );
        return ;
    }
}

INLINE_CHAINS void Update_Actor::chain3_inc_hunger_50_chance( void )
{
    rtgChainBegin( 4, "inc hunger (50% chance)" );
    rtgTransitionBegin(  );
    transition3_inc_hunger_50_chance( msg->data, static_cast< Timing::Base * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Update_Actor::chain4_dec_happiness_30_chance( void )
{
    rtgChainBegin( 4, "dec happiness (30% chance)" );
    rtgTransitionBegin(  );
    transition4_dec_happiness_30_chance( msg->data, static_cast< Timing::Base * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Update_Actor::chain5_20_chance( void )
{
    rtgChainBegin( 4, "20% chance" );
    rtgTransitionBegin(  );
    transition5_20_chance( msg->data, static_cast< Timing::Base * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Update_Actor::chain6_timeout( void )
{
    rtgChainBegin( 2, "timeout" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition6_timeout( msg->data, static_cast< Timing::Base * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Update_Actor::chain7_updateHunger( void )
{
    rtgChainBegin( 3, "updateHunger" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition7_updateHunger( static_cast< const int * > ( msg->data ), static_cast< UpdateValProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    if( guard9_is_full( static_cast< const int * > ( msg->data ), static_cast< UpdateValProt::Conjugate * > ( msg->sap() ) ) )
    {
        chain9_is_full(  );
        return ;
    }
    chain10_else(  );
}

INLINE_CHAINS void Update_Actor::chain8_updateHealth( void )
{
    rtgChainBegin( 3, "updateHealth" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition8_updateHealth( static_cast< const int * > ( msg->data ), static_cast< UpdateValProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    if( guard11_ill( static_cast< const int * > ( msg->data ), static_cast< UpdateValProt::Conjugate * > ( msg->sap() ) ) )
    {
        chain11_ill(  );
        return ;
    }
    chain12_else(  );
}

INLINE_CHAINS void Update_Actor::chain9_is_full( void )
{
    rtgChainBegin( 5, "is full" );
    rtgTransitionBegin(  );
    transition9_is_full( static_cast< const int * > ( msg->data ), static_cast< UpdateValProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Update_Actor::chain10_else( void )
{
    rtgChainBegin( 5, "else" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Update_Actor::chain11_ill( void )
{
    rtgChainBegin( 6, "ill" );
    rtgTransitionBegin(  );
    transition11_ill( static_cast< const int * > ( msg->data ), static_cast< UpdateValProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Update_Actor::chain12_else( void )
{
    rtgChainBegin( 6, "else" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Update_Actor::chain13_updateOptions( void )
{
    rtgChainBegin( 3, "updateOptions" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition13_updateOptions( msg->data, static_cast< UpdateOptionsProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

void Update_Actor::rtsBehavior( int signalIndex, int portIndex )
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
                case 4 /*updateValPort*/:
                    switch( signalIndex )
                    {
                    case UpdateValProt::Conjugate::rti_updateHealth:
                        chain8_updateHealth(  );
                        return ;
                    case UpdateValProt::Conjugate::rti_updateHunger:
                        chain7_updateHunger(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                case 5 /*updateOptionsPort*/:
                    switch( signalIndex )
                    {
                    case UpdateOptionsProt::Conjugate::rti_updateOptions:
                        chain13_updateOptions(  );
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

const RTStateId Update_Actor::rtg_parent_state[] =
{
    0
    , 1
    , 1
};

const RTActor_class * Update_Actor::getActorData( void ) const
{
    return &Update_Actor::rtg_class;
}

const RTActor_class Update_Actor::rtg_class =
{
    nullptr
    , rtg_state_names
    , 3
    , Update_Actor::rtg_parent_state
    , &Update
    , 3
    , Update_Actor::rtg_capsule_roles
    , 5
    , Update_Actor::rtg_ports
    , 0
    , nullptr
    , 5
    , Update_Actor::rtg_Update_Actor_fields
};

const RTComponentDescriptor Update_Actor::rtg_capsule_roles[] =
{
    {
        "input"
        , &InputLoop
        , RTOffsetOf( Update_Actor, input )
        , 1
        , RTComponentDescriptor::Optional
        , 1
        , 1
        , 2
        , rtg_interfaces_input
        , 2
        , rtg_bindings_input
    }
    , {
        "feed"
        , &Feed
        , RTOffsetOf( Update_Actor, feed )
        , 2
        , RTComponentDescriptor::Fixed
        , 1
        , 1
        , 2
        , rtg_interfaces_feed
        , 2
        , rtg_bindings_feed
    }
    , {
        "translateInput"
        , &TranslateInput
        , RTOffsetOf( Update_Actor, translateInput )
        , 3
        , RTComponentDescriptor::Fixed
        , 1
        , 1
        , 3
        , rtg_interfaces_translateInput
        , 3
        , rtg_bindings_translateInput
    }
};

const RTPortDescriptor Update_Actor::rtg_ports[] =
{
    {
        "frameP"
        , nullptr
        , &Frame::Base::rt_class
        , RTOffsetOf( Update_Actor, frameP )
        , 1
        , 1
        , RTPortDescriptor::KindSpecial + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "timingPort"
        , nullptr
        , &Timing::Base::rt_class
        , RTOffsetOf( Update_Actor, timingPort )
        , 1
        , 2
        , RTPortDescriptor::KindSpecial + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "statusPort"
        , nullptr
        , &StatusProt::Base::rt_class
        , RTOffsetOf( Update_Actor, statusPort )
        , 1
        , 3
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "updateValPort"
        , nullptr
        , &UpdateValProt::Conjugate::rt_class
        , RTOffsetOf( Update_Actor, updateValPort )
        , 1
        , 4
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "updateOptionsPort"
        , nullptr
        , &UpdateOptionsProt::Conjugate::rt_class
        , RTOffsetOf( Update_Actor, updateOptionsPort )
        , 1
        , 5
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
};

const RTFieldDescriptor Update_Actor::rtg_Update_Actor_fields[] =
{
    {
        "hunger"
        , RTOffsetOf( Update_Actor, hunger )
        , &RTType_int
        , nullptr
    }
    , {
        "discipline"
        , RTOffsetOf( Update_Actor, discipline )
        , &RTType_int
        , nullptr
    }
    , {
        "happiness"
        , RTOffsetOf( Update_Actor, happiness )
        , &RTType_int
        , nullptr
    }
    , {
        "health"
        , RTOffsetOf( Update_Actor, health )
        , &RTType_int
        , nullptr
    }
    , {
        "rng"
        , RTOffsetOf( Update_Actor, rng )
        , &RTType_int
        , nullptr
    }
};

int Update_Actor::_followOutV( RTBindingEnd & rtg_end, int rtg_compId, int rtg_portId, int rtg_repIndex )
{
    switch( rtg_compId )
    {
    case 1:
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
                return translateInput._followIn( rtg_end, 0, rtg_repIndex );
            break;
        default:
            break;
        }
        break;
    case 2:
        switch( rtg_portId )
        {
        case 0:
            if( rtg_repIndex < 1 )
                return translateInput._followIn( rtg_end, 1, rtg_repIndex );
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
        break;
    case 3:
        switch( rtg_portId )
        {
        case 0:
            if( rtg_repIndex < 1 )
                return input._followIn( rtg_end, 1, rtg_repIndex );
            break;
        case 1:
            if( rtg_repIndex < 1 )
                return feed._followIn( rtg_end, 0, rtg_repIndex );
            break;
        case 2:
            if( rtg_repIndex < 1 )
            {
                rtg_end.port = &updateOptionsPort;
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
static RTActor * new_Update_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
{
    return new Update_Actor( rtg_rts, rtg_ref );
}

const RTActorClass Update =
{
    nullptr
    , "Update"
    , 0 /*RTVersionId*/
    , 0
    , nullptr
    , new_Update_Actor
};

