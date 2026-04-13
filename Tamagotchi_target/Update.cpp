#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "Update.h"
#endif
#include <UnitName.h>
#include <Update.h>
#include <DisciplineProt.h>
#include <FeedProt.h>
#include <PlayProt.h>

extern const RTActorClass Discipline;

extern const RTActorClass Feed;

extern const RTActorClass InputLoop;

extern const RTActorClass Play;

extern const RTActorClass TranslateInput;

static const char * const rtg_state_names[] =
{
    "<machine>"
    , "Hatch :)"
    , "Idle"
    , "Sleep"
    , "Pause"
    , "Die :("
    , "RNGVal"
    , ""
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
    , {
        "triggerInputPort"
        , 5
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
    , {
        2
        , &InputProt::Base::rt_class
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
    , {
        "triggerInputPort"
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
    , {
        2
        , &InputProt::Conjugate::rt_class
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
    , {
        "playPort"
        , 1
    }
    , {
        "updateTamaPort"
        , 1
    }
    , {
        "disciplinePort"
        , 1
    }
    , {
        "triggerInputPort"
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
    , {
        3
        , &PlayProt::Conjugate::rt_class
    }
    , {
        4
        , &UpdateTamaProt::Conjugate::rt_class
    }
    , {
        5
        , &DisciplineProt::Conjugate::rt_class
    }
    , {
        6
        , &InputProt::Conjugate::rt_class
    }
};

static const RTInterfaceDescriptor rtg_interfaces_play[] =
{
    {
        "playPort"
        , 1
    }
    , {
        "updateValPort"
        , 1
    }
    , {
        "triggerInputPort"
        , 1
    }
    , {
        "resetPlayPort"
        , 1
    }
};

static const RTBindingDescriptor rtg_bindings_play[] =
{
    {
        0
        , &PlayProt::Base::rt_class
    }
    , {
        1
        , &UpdateValProt::Conjugate::rt_class
    }
    , {
        2
        , &InputProt::Conjugate::rt_class
    }
    , {
        3
        , &ResetPlayProt::Base::rt_class
    }
};

static const RTInterfaceDescriptor rtg_interfaces_discipline[] =
{
    {
        "triggerInputPort"
        , 1
    }
    , {
        "updateValPort"
        , 1
    }
    , {
        "disciplinePort"
        , 1
    }
};

static const RTBindingDescriptor rtg_bindings_discipline[] =
{
    {
        0
        , &InputProt::Conjugate::rt_class
    }
    , {
        1
        , &UpdateValProt::Conjugate::rt_class
    }
    , {
        2
        , &DisciplineProt::Base::rt_class
    }
};

static const RTLocalBindingDescriptor rtg_local_bindings[] =
{
    {
        1
        , 2
        , 6
    }
};

static const RTTypeModifier rtg_tm_Update_Actor_tama =
{
    RTNumberConstant
    , 1
    , 1
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
std::cout<< tama_name << " STATUS:\n" << "\nHUNGER: " << hunger << "\nHAPPINESS: " << happiness << "\nDISCIPLINE: " << disc << "\nHEALTH: " << health << "\n" << tama <<std::endl;
std::cout<< "-----------------------------------------------------------------------" <<std::endl;
std::cout << "\nWHAT WILL " << owner_name << " DO?" << options << std::endl;
triggerInputPort.triggerInput().send();
//}}}USR
}

int Update_Actor::determineChange( int var, int change )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_dgtjUDeCEfGJaL0kWrhu3A
if(var + change < 0 || (var + change >= 10)){
	return 0;
}
return change;
//}}}USR
}

INLINE_METHODS void Update_Actor::enter2_Hatch( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_NnvBADUoEfGJaL0kWrhu3A
SetConsoleOutputCP(65001);  // sets console to UTF-8

std::cout << "[Status] incarnating 'input' on logical thread 'InputLogical'" << std::endl;
RTTypedValue noData ( (const void *)0, (const RTObject_class *)0 );
RTActorId inputThread = frameP.incarnate(input, noData, InputLogical);
if (!inputThread.isValid())
	context()->perror("[Status] incarnation failed!");

std::cout<< "\nYOUR TAMAGOTCHI HAS HATCHED!" <<std::endl;

std::cout<< "\nPLEASE ENTER THE NAME YOU WOULD LIKE TO GIVE YOUR TAMAGOTCHI:" <<std::endl;

char tname[256];

fgets(tname, sizeof(tname), stdin);

// Remove trailing newline if present
tname[strcspn(tname, "\n")] = '\0';

for (int i = 0; tname[i]; i++) {
        tname[i] = toupper(tname[i]);
}

tama_name = tname;

std::cout<< "\nAND WHAT IS YOUR NAME?" <<std::endl;

char oname[256];

fgets(oname, sizeof(oname), stdin);

// Remove trailing newline if present
oname[strcspn(oname, "\n")] = '\0';

for (int i = 0; oname[i]; i++) {
        oname[i] = toupper(oname[i]);
}

owner_name = oname;

std::cout<< "\n" << tname << " LOOKS HAPPY TO MEET YOU, " << owner_name << "!" <<std::endl;
statusPort.hatch().send();
std::cout<< "\nINITIALIZING STATS..." <<std::endl;
showStatus();

//}}}USR
}

void Update_Actor::enterStateV( void )
{
    switch( getCurrentState() )
    {
    case 2:
        enter2_Hatch(  );
        break;
    case 4:
        enter4_Sleep(  );
        break;
    case 5:
        enter5_Pause(  );
        break;
    case 6:
        enter6_Die(  );
        break;
    default:
        RTActor::enterStateV(  );
        break;
    }
}

INLINE_METHODS void Update_Actor::enter4_Sleep( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_ET0MYDbaEfGJaL0kWrhu3A
generalTimer = timingGeneralPort.informIn(RTTimespec(3,0));
//}}}USR
}

INLINE_METHODS void Update_Actor::enter5_Pause( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_0DgQgDbiEfGJaL0kWrhu3A
generalTimer = timingGeneralPort.informIn(RTTimespec(3,0));
tama = tama_happy;
//}}}USR
}

INLINE_METHODS void Update_Actor::enter6_Die( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_rYryADd9EfGJaL0kWrhu3A
int score = 100;

if(hunger <= 0  || hunger >= 10){
	score -= 25;
}
if(disc <= 5){
	score -= 25;
}
if(health <= 5){
	score -= 25;
}
if(happiness <= 5){
	score -= 25;
}

std::cout<< tombstone << "\n" << tama_name << " HAS DIED!\nYOUR SCORE: " << score << "/100" << std::endl;
exit(0);
//if(generalTimer.isValid()){
//	timingGeneralPort.cancelTimer(generalTimer);
//}
//if(sleepTimer.isValid()){
//	timingSleepPort.cancelTimer(sleepTimer);
//}
//if(updateValTimer.isValid()){
//	timingUpdateValsPort.cancelTimer(updateValTimer);
//}
//}}}USR
}

INLINE_METHODS void Update_Actor::transition2_timeout_update_vals( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_JVtHADbcEfGJaL0kWrhu3A
std::cout << "\nGENERATING RANDOM VALUE" << std::endl;
rng = (rand() % 100);
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
tama = tama_hungry;
std::cout << "\n" << tama << std::endl;
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
std::cout<< "\n" << tama_name << " IS GETTING BORED..." << std::endl;
happiness -= 1;
tama = tama_bored;
std::cout << "\n" << tama << std::endl;
//}}}USR
}

INLINE_METHODS int Update_Actor::guard5_dec_discipline_20_chance( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_y1jHADUeEfGJaL0kWrhu3A
return (rng > 80 && rng <= 100);
//}}}USR
}

INLINE_METHODS void Update_Actor::transition5_dec_discipline_20_chance( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_8hdGYDX0EfGJaL0kWrhu3A
std::cout<< "\n" << tama_name << " IS GETTING ROWDY..." <<std::endl;
disc -= 1;
tama = tama_angry;
std::cout << "\n" << tama << std::endl;
//}}}USR
}

INLINE_METHODS void Update_Actor::transition6_hatch( const void * rtdata, StatusProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_710E8DaPEfGJaL0kWrhu3A
updateValTimer = timingUpdateValsPort.informEvery(RTTimespec(updateValTime,0));
sleepTimer = timingSleepPort.informEvery(RTTimespec(sleepTime,0));
timingDeathPort.informIn(RTTimespec(deathTime, 0));
//}}}USR
}

INLINE_METHODS void Update_Actor::transition7_updateHunger( const int * rtdata, UpdateValProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_0y1oIDXkEfGJaL0kWrhu3A
hunger += determineChange(hunger, *rtdata);
showStatus();
//}}}USR
}

INLINE_METHODS void Update_Actor::transition8_updateHealth( const int * rtdata, UpdateValProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_wL2YcDXwEfGJaL0kWrhu3A
health += determineChange(health, *rtdata);
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
std::cout<< tama_name << " IS FEELING OVERFED..." << std::endl;
health += determineChange(health, -1);
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

INLINE_METHODS void Update_Actor::transition12_else( const int * rtdata, UpdateValProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_UuQaADbkEfGJaL0kWrhu3A
std::cout<< tama_name << " IS FEELING HEALTHY..." << std::endl;
//}}}USR
}

INLINE_METHODS void Update_Actor::transition13_updateOptions( const void * rtdata, UpdateOptionsProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_4APKsDYEEfGJaL0kWrhu3A
options = (const char *)rtdata;

std::cout<< "\n-----------------------------------------------------------------------" <<std::endl;
std::cout<< "\n" << tama <<std::endl;
std::cout<< "-----------------------------------------------------------------------" <<std::endl;
std::cout << "\nWHAT WILL " << owner_name << " DO?" << options << std::endl;
triggerInputPort.triggerInput().send();
//}}}USR
}

INLINE_METHODS void Update_Actor::transition14_updateHappiness( const int * rtdata, UpdateValProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_AaW5gDYUEfGJaL0kWrhu3A
happiness += determineChange(happiness, *rtdata);
showStatus();
//}}}USR
}

INLINE_METHODS void Update_Actor::transition15_timeout_sleep( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_7MnrEDacEfGJaL0kWrhu3A
std::cout << "\n" << tama_name << " IS SLEEPING..." << std::endl;
tama = tama_sleep;
std::cout << "\n" << tama << std::endl;
//}}}USR
}

INLINE_METHODS void Update_Actor::transition16_updateTama( const void * rtdata, UpdateTamaProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_iSg3wDa5EfGJaL0kWrhu3A
tama = (const char *)rtdata;
//}}}USR
}

INLINE_METHODS void Update_Actor::transition18_timeout( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_OyX18DbaEfGJaL0kWrhu3A
std::cout << "\n" << tama_name << " WOKE UP AND IS FEELING ENERGIZED!" << std::endl;
tama = tama_happy;

health += determineChange(health, 1);
happiness += determineChange(happiness, 1);
hunger += determineChange(hunger, 1);
resetPlayPort.resetThrow().send();
if(generalTimer.isValid()){
	timingGeneralPort.cancelTimer(generalTimer);
}
showStatus();
//}}}USR
}

INLINE_METHODS void Update_Actor::transition19_timeout( const void * rtdata, Timing::Base * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_4kVh8DbjEfGJaL0kWrhu3A
if(generalTimer.isValid()){
	timingGeneralPort.cancelTimer(generalTimer);
}
showStatus();
//}}}USR
}

INLINE_METHODS void Update_Actor::transition20_updateDiscipline( const int * rtdata, UpdateValProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_bN6SsDdgEfGJaL0kWrhu3A
disc += determineChange(disc, *rtdata);
showStatus();
//}}}USR
}

INLINE_METHODS int Update_Actor::guard22_is_starving( const int * rtdata, UpdateValProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_MaA6YDd9EfGJaL0kWrhu3A
return (hunger >= 10);
//}}}USR
}

INLINE_METHODS void Update_Actor::transition22_is_starving( const int * rtdata, UpdateValProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_OYeyMDd9EfGJaL0kWrhu3A
std::cout<< tama_name << " IS STARVING..." << std::endl;
health += determineChange(health, -1);
//}}}USR
}

INLINE_CHAINS void Update_Actor::chain1_Initial( void )
{
    rtgChainBegin( 1, "Initial" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 2 );
}

INLINE_CHAINS void Update_Actor::chain2_timeout_update_vals( void )
{
    rtgChainBegin( 3, "timeout (update vals)" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition2_timeout_update_vals( msg->data, static_cast< Timing::Base * > ( msg->sap() ) );
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
    if( guard5_dec_discipline_20_chance( msg->data, static_cast< Timing::Base * > ( msg->sap() ) ) )
    {
        chain5_dec_discipline_20_chance(  );
        return ;
    }
}

INLINE_CHAINS void Update_Actor::chain3_inc_hunger_50_chance( void )
{
    rtgChainBegin( 7, "inc hunger (50% chance)" );
    rtgTransitionBegin(  );
    transition3_inc_hunger_50_chance( msg->data, static_cast< Timing::Base * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 5 );
}

INLINE_CHAINS void Update_Actor::chain4_dec_happiness_30_chance( void )
{
    rtgChainBegin( 7, "dec happiness (30% chance)" );
    rtgTransitionBegin(  );
    transition4_dec_happiness_30_chance( msg->data, static_cast< Timing::Base * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 5 );
}

INLINE_CHAINS void Update_Actor::chain5_dec_discipline_20_chance( void )
{
    rtgChainBegin( 7, "dec discipline (20% chance)" );
    rtgTransitionBegin(  );
    transition5_dec_discipline_20_chance( msg->data, static_cast< Timing::Base * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 5 );
}

INLINE_CHAINS void Update_Actor::chain6_hatch( void )
{
    rtgChainBegin( 2, "hatch" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition6_hatch( msg->data, static_cast< StatusProt::Conjugate * > ( msg->sap() ) );
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
    if( guard22_is_starving( static_cast< const int * > ( msg->data ), static_cast< UpdateValProt::Conjugate * > ( msg->sap() ) ) )
    {
        chain22_is_starving(  );
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
    rtgChainBegin( 8, "is full" );
    rtgTransitionBegin(  );
    transition9_is_full( static_cast< const int * > ( msg->data ), static_cast< UpdateValProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Update_Actor::chain10_else( void )
{
    rtgChainBegin( 8, "else" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Update_Actor::chain11_ill( void )
{
    rtgChainBegin( 9, "ill" );
    rtgTransitionBegin(  );
    transition11_ill( static_cast< const int * > ( msg->data ), static_cast< UpdateValProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Update_Actor::chain12_else( void )
{
    rtgChainBegin( 9, "else" );
    rtgTransitionBegin(  );
    transition12_else( static_cast< const int * > ( msg->data ), static_cast< UpdateValProt::Conjugate * > ( msg->sap() ) );
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

INLINE_CHAINS void Update_Actor::chain14_updateHappiness( void )
{
    rtgChainBegin( 3, "updateHappiness" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition14_updateHappiness( static_cast< const int * > ( msg->data ), static_cast< UpdateValProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Update_Actor::chain15_timeout_sleep( void )
{
    rtgChainBegin( 3, "timeout (sleep)" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition15_timeout_sleep( msg->data, static_cast< Timing::Base * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 4 );
}

INLINE_CHAINS void Update_Actor::chain16_updateTama( void )
{
    rtgChainBegin( 3, "updateTama" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition16_updateTama( msg->data, static_cast< UpdateTamaProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Update_Actor::chain17_ignore_timeout_update_vals( void )
{
    rtgChainBegin( 4, "ignore timeout (update vals)" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 4 );
}

INLINE_CHAINS void Update_Actor::chain18_timeout( void )
{
    rtgChainBegin( 4, "timeout" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition18_timeout( msg->data, static_cast< Timing::Base * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Update_Actor::chain19_timeout( void )
{
    rtgChainBegin( 5, "timeout" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition19_timeout( msg->data, static_cast< Timing::Base * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Update_Actor::chain20_updateDiscipline( void )
{
    rtgChainBegin( 3, "updateDiscipline" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition20_updateDiscipline( static_cast< const int * > ( msg->data ), static_cast< UpdateValProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Update_Actor::chain21_timeout_death( void )
{
    rtgChainBegin( 3, "timeout (death)" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 6 );
}

INLINE_CHAINS void Update_Actor::chain22_is_starving( void )
{
    rtgChainBegin( 8, "is starving" );
    rtgTransitionBegin(  );
    transition22_is_starving( static_cast< const int * > ( msg->data ), static_cast< UpdateValProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void Update_Actor::chain23_ignore_timeout_sleep( void )
{
    rtgChainBegin( 5, "ignore timeout (sleep)" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 5 );
}

INLINE_CHAINS void Update_Actor::chain24_timeout_death( void )
{
    rtgChainBegin( 4, "timeout (death)" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 6 );
}

INLINE_CHAINS void Update_Actor::chain25_timeout_death( void )
{
    rtgChainBegin( 5, "timeout (death)" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 6 );
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
            case 2 /* Hatch :) (State Machine::Hatch :)) */:
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
                case 7 /*statusProtR*/:
                    switch( signalIndex )
                    {
                    case StatusProt::Conjugate::rti_hatch:
                        chain6_hatch(  );
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
                case 2 /*timingUpdateValsPort*/:
                    switch( signalIndex )
                    {
                    case Timing::Base::rti_timeout:
                        chain2_timeout_update_vals(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                case 4 /*updateValPort*/:
                    switch( signalIndex )
                    {
                    case UpdateValProt::Conjugate::rti_updateDiscipline:
                        chain20_updateDiscipline(  );
                        return ;
                    case UpdateValProt::Conjugate::rti_updateHappiness:
                        chain14_updateHappiness(  );
                        return ;
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
                case 6 /*timingSleepPort*/:
                    switch( signalIndex )
                    {
                    case Timing::Base::rti_timeout:
                        chain15_timeout_sleep(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                case 10 /*updateTamaPort*/:
                    switch( signalIndex )
                    {
                    case UpdateTamaProt::Conjugate::rti_updateTama:
                        chain16_updateTama(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                case 12 /*timingDeathPort*/:
                    switch( signalIndex )
                    {
                    case Timing::Base::rti_timeout:
                        chain21_timeout_death(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 4 /* Sleep (State Machine::Sleep) */:
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
                case 2 /*timingUpdateValsPort*/:
                    switch( signalIndex )
                    {
                    case Timing::Base::rti_timeout:
                        chain17_ignore_timeout_update_vals(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                case 11 /*timingGeneralPort*/:
                    switch( signalIndex )
                    {
                    case Timing::Base::rti_timeout:
                        chain18_timeout(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                case 12 /*timingDeathPort*/:
                    switch( signalIndex )
                    {
                    case Timing::Base::rti_timeout:
                        chain24_timeout_death(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 5 /* Pause (State Machine::Pause) */:
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
                case 6 /*timingSleepPort*/:
                    switch( signalIndex )
                    {
                    case Timing::Base::rti_timeout:
                        chain23_ignore_timeout_sleep(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                case 11 /*timingGeneralPort*/:
                    switch( signalIndex )
                    {
                    case Timing::Base::rti_timeout:
                        chain19_timeout(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                case 12 /*timingDeathPort*/:
                    switch( signalIndex )
                    {
                    case Timing::Base::rti_timeout:
                        chain25_timeout_death(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 6 /* Die :( (State Machine::Die :() */:
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

const RTStateId Update_Actor::rtg_parent_state[] =
{
    0
    , 1
    , 1
    , 1
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
    , 6
    , Update_Actor::rtg_parent_state
    , &Update
    , 5
    , Update_Actor::rtg_capsule_roles
    , 12
    , Update_Actor::rtg_ports
    , 1
    , rtg_local_bindings
    , 12
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
        , 3
        , rtg_interfaces_input
        , 3
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
        , 3
        , rtg_interfaces_feed
        , 3
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
        , 7
        , rtg_interfaces_translateInput
        , 7
        , rtg_bindings_translateInput
    }
    , {
        "play"
        , &Play
        , RTOffsetOf( Update_Actor, play )
        , 4
        , RTComponentDescriptor::Fixed
        , 1
        , 1
        , 4
        , rtg_interfaces_play
        , 4
        , rtg_bindings_play
    }
    , {
        "discipline"
        , &Discipline
        , RTOffsetOf( Update_Actor, discipline )
        , 5
        , RTComponentDescriptor::Fixed
        , 1
        , 1
        , 3
        , rtg_interfaces_discipline
        , 3
        , rtg_bindings_discipline
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
        "timingUpdateValsPort"
        , nullptr
        , &Timing::Base::rt_class
        , RTOffsetOf( Update_Actor, timingUpdateValsPort )
        , 1
        , 2
        , RTPortDescriptor::KindSpecial + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "statusPort"
        , nullptr
        , &StatusProt::Base::rt_class
        , RTOffsetOf( Update_Actor, statusPort )
        , 2
        , 3
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "updateValPort"
        , nullptr
        , &UpdateValProt::Conjugate::rt_class
        , RTOffsetOf( Update_Actor, updateValPort )
        , 3
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
    , {
        "timingSleepPort"
        , nullptr
        , &Timing::Base::rt_class
        , RTOffsetOf( Update_Actor, timingSleepPort )
        , 1
        , 6
        , RTPortDescriptor::KindSpecial + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "statusProtR"
        , nullptr
        , &StatusProt::Conjugate::rt_class
        , RTOffsetOf( Update_Actor, statusProtR )
        , 1
        , 7
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "triggerInputPort"
        , nullptr
        , &InputProt::Base::rt_class
        , RTOffsetOf( Update_Actor, triggerInputPort )
        , 1
        , 8
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "resetPlayPort"
        , nullptr
        , &ResetPlayProt::Base::rt_class
        , RTOffsetOf( Update_Actor, resetPlayPort )
        , 1
        , 9
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "updateTamaPort"
        , nullptr
        , &UpdateTamaProt::Conjugate::rt_class
        , RTOffsetOf( Update_Actor, updateTamaPort )
        , 1
        , 10
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "timingGeneralPort"
        , nullptr
        , &Timing::Base::rt_class
        , RTOffsetOf( Update_Actor, timingGeneralPort )
        , 1
        , 11
        , RTPortDescriptor::KindSpecial + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "timingDeathPort"
        , nullptr
        , &Timing::Base::rt_class
        , RTOffsetOf( Update_Actor, timingDeathPort )
        , 1
        , 12
        , RTPortDescriptor::KindSpecial + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
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
        "disc"
        , RTOffsetOf( Update_Actor, disc )
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
    , {
        "sleepTime"
        , RTOffsetOf( Update_Actor, sleepTime )
        , &RTType_int
        , nullptr
    }
    , {
        "updateValTime"
        , RTOffsetOf( Update_Actor, updateValTime )
        , &RTType_int
        , nullptr
    }
    , {
        "sleepTimer"
        , RTOffsetOf( Update_Actor, sleepTimer )
        , &RTType_RTTimerId
        , nullptr
    }
    , {
        "updateValTimer"
        , RTOffsetOf( Update_Actor, updateValTimer )
        , &RTType_RTTimerId
        , nullptr
    }
    , {
        "tama"
        , RTOffsetOf( Update_Actor, tama )
        , &RTType_char
        , &rtg_tm_Update_Actor_tama
    }
    , {
        "generalTimer"
        , RTOffsetOf( Update_Actor, generalTimer )
        , &RTType_RTTimerId
        , nullptr
    }
    , {
        "deathTime"
        , RTOffsetOf( Update_Actor, deathTime )
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
                rtg_end.index = rtg_repIndex + 1;
                return 1;
            }
            break;
        case 1:
            if( rtg_repIndex < 1 )
                return translateInput._followIn( rtg_end, 0, rtg_repIndex );
            break;
        case 2:
            if( rtg_repIndex < 1 )
            {
                rtg_end.port = &triggerInputPort;
                rtg_end.index = rtg_repIndex;
                return 1;
            }
            if( rtg_repIndex < 2 )
                return feed._followIn( rtg_end, 2, rtg_repIndex - 1 );
            if( rtg_repIndex < 3 )
                return play._followIn( rtg_end, 2, rtg_repIndex - 2 );
            if( rtg_repIndex < 4 )
                return discipline._followIn( rtg_end, 0, rtg_repIndex - 3 );
            if( rtg_repIndex < 5 )
                return translateInput._followIn( rtg_end, 6, rtg_repIndex - 4 );
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
        case 2:
            if( rtg_repIndex < 1 )
                return input._followIn( rtg_end, 2, rtg_repIndex + 1 );
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
        case 3:
            if( rtg_repIndex < 1 )
                return play._followIn( rtg_end, 0, rtg_repIndex );
            break;
        case 4:
            if( rtg_repIndex < 1 )
            {
                rtg_end.port = &updateTamaPort;
                rtg_end.index = rtg_repIndex;
                return 1;
            }
            break;
        case 5:
            if( rtg_repIndex < 1 )
                return discipline._followIn( rtg_end, 2, rtg_repIndex );
            break;
        case 6:
            if( rtg_repIndex < 1 )
                return input._followIn( rtg_end, 2, rtg_repIndex + 4 );
            break;
        default:
            break;
        }
        break;
    case 4:
        switch( rtg_portId )
        {
        case 0:
            if( rtg_repIndex < 1 )
                return translateInput._followIn( rtg_end, 3, rtg_repIndex );
            break;
        case 1:
            if( rtg_repIndex < 1 )
            {
                rtg_end.port = &updateValPort;
                rtg_end.index = rtg_repIndex + 1;
                return 1;
            }
            break;
        case 2:
            if( rtg_repIndex < 1 )
                return input._followIn( rtg_end, 2, rtg_repIndex + 2 );
            break;
        case 3:
            if( rtg_repIndex < 1 )
            {
                rtg_end.port = &resetPlayPort;
                rtg_end.index = rtg_repIndex;
                return 1;
            }
            break;
        default:
            break;
        }
        break;
    case 5:
        switch( rtg_portId )
        {
        case 0:
            if( rtg_repIndex < 1 )
                return input._followIn( rtg_end, 2, rtg_repIndex + 3 );
            break;
        case 1:
            if( rtg_repIndex < 1 )
            {
                rtg_end.port = &updateValPort;
                rtg_end.index = rtg_repIndex + 2;
                return 1;
            }
            break;
        case 2:
            if( rtg_repIndex < 1 )
                return translateInput._followIn( rtg_end, 5, rtg_repIndex );
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

