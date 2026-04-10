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
//}}}USR
}

void Status_Actor::enterStateV( void )
{
    switch( getCurrentState() )
    {
    case 3:
        enter3_Hatch(  );
        break;
    default:
        RTActor::enterStateV(  );
        break;
    }
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
};

const RTActor_class * Status_Actor::getActorData( void ) const
{
    return &Status_Actor::rtg_class;
}

const RTActor_class Status_Actor::rtg_class =
{
    nullptr
    , rtg_state_names
    , 3
    , Status_Actor::rtg_parent_state
    , &Status
    , 0
    , nullptr
    , 1
    , Status_Actor::rtg_ports
    , 0
    , nullptr
    , 4
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

