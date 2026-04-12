#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "TranslateInput.h"
#endif
#include <UnitName.h>
#include <TranslateInput.h>

static const char * const rtg_state_names[] =
{
    "<machine>"
    , "Start"
    , "Send Signals"
};

static const RTTypeModifier rtg_tm_TranslateInput_Actor_feedOptions =
{
    RTNumberConstant
    , 1
    , 1
};

static const RTTypeModifier rtg_tm_TranslateInput_Actor_idleOptions =
{
    RTNumberConstant
    , 1
    , 1
};

static const RTTypeModifier rtg_tm_TranslateInput_Actor_playOptions =
{
    RTNumberConstant
    , 1
    , 1
};

#define SUPER RTActor
TranslateInput_Actor::TranslateInput_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
    : RTActor( rtg_rts ,rtg_ref )
{
}

TranslateInput_Actor::~TranslateInput_Actor( void )
{
}

INLINE_METHODS void TranslateInput_Actor::enter3_Send_Signals( void )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_doD84DXfEfGJaL0kWrhu3A
if(mode == "IDLE"){
	 if(input == "FEED"){
		updateOptionsPort.updateOptions(feedOptions).send();
		feedPort.initFeed().send();
		mode = "FEED";
	}
	else if(input == "PLAY"){
		updateOptionsPort.updateOptions(playOptions).send();
		playPort.initPlay().send();
		mode = "PLAY";
	}
}
else if(mode == "FEED"){
	if(input == "SNACK"){
		feedPort.feedSnack().send();
	}
	else if(input == "MEAL"){
		feedPort.feedMeal().send();
	}
	else if(input == "EXIT"){
		updateOptionsPort.updateOptions(idleOptions).send();
		feedPort.exit().send();
		mode = "IDLE";
	}
}
else if(mode == "PLAY"){
	if(input == "FETCH"){
		playPort.throwBall().send();
	}
	else if(input == "EXIT"){
		updateOptionsPort.updateOptions(idleOptions).send();
		playPort.exit().send();
		mode = "IDLE";
	}
}
//}}}USR
}

void TranslateInput_Actor::enterStateV( void )
{
    switch( getCurrentState() )
    {
    case 3:
        enter3_Send_Signals(  );
        break;
    default:
        RTActor::enterStateV(  );
        break;
    }
}

INLINE_METHODS void TranslateInput_Actor::transition2_gotInput( const void * rtdata, InputProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_Kiq10DXeEfGJaL0kWrhu3A
input = (const char *)rtdata;

//}}}USR
}

INLINE_METHODS void TranslateInput_Actor::transition3_gotInput( const void * rtdata, InputProt::Conjugate * rtport )
{
//{{{USR platform:/resource/Tamagotchi/CPPModel.emx#_Nd20kDXeEfGJaL0kWrhu3A
input = (const char *)rtdata;

//}}}USR
}

INLINE_CHAINS void TranslateInput_Actor::chain1_Initial( void )
{
    rtgChainBegin( 1, "Initial" );
    rtgTransitionBegin(  );
    rtgTransitionEnd(  );
    enterState( 2 );
}

INLINE_CHAINS void TranslateInput_Actor::chain2_gotInput( void )
{
    rtgChainBegin( 2, "gotInput" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition2_gotInput( msg->data, static_cast< InputProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

INLINE_CHAINS void TranslateInput_Actor::chain3_gotInput( void )
{
    rtgChainBegin( 3, "gotInput" );
    exitState( rtg_parent_state );
    rtgTransitionBegin(  );
    transition3_gotInput( msg->data, static_cast< InputProt::Conjugate * > ( msg->sap() ) );
    rtgTransitionEnd(  );
    enterState( 3 );
}

void TranslateInput_Actor::rtsBehavior( int signalIndex, int portIndex )
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
                case 1 /*inputPort*/:
                    switch( signalIndex )
                    {
                    case InputProt::Conjugate::rti_gotInput:
                        chain2_gotInput(  );
                        return ;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 3 /* Send Signals (State Machine::Send Signals) */:
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
                case 1 /*inputPort*/:
                    switch( signalIndex )
                    {
                    case InputProt::Conjugate::rti_gotInput:
                        chain3_gotInput(  );
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

const RTStateId TranslateInput_Actor::rtg_parent_state[] =
{
    0
    , 1
    , 1
};

const RTActor_class * TranslateInput_Actor::getActorData( void ) const
{
    return &TranslateInput_Actor::rtg_class;
}

const RTActor_class TranslateInput_Actor::rtg_class =
{
    nullptr
    , rtg_state_names
    , 3
    , TranslateInput_Actor::rtg_parent_state
    , &TranslateInput
    , 0
    , nullptr
    , 4
    , TranslateInput_Actor::rtg_ports
    , 0
    , nullptr
    , 3
    , TranslateInput_Actor::rtg_TranslateInput_Actor_fields
};

const RTPortDescriptor TranslateInput_Actor::rtg_ports[] =
{
    {
        "inputPort"
        , nullptr
        , &InputProt::Conjugate::rt_class
        , RTOffsetOf( TranslateInput_Actor, inputPort )
        , 1
        , 1
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "feedPort"
        , nullptr
        , &FeedProt::Base::rt_class
        , RTOffsetOf( TranslateInput_Actor, feedPort )
        , 1
        , 2
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "updateOptionsPort"
        , nullptr
        , &UpdateOptionsProt::Base::rt_class
        , RTOffsetOf( TranslateInput_Actor, updateOptionsPort )
        , 1
        , 3
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
    , {
        "playPort"
        , nullptr
        , &PlayProt::Base::rt_class
        , RTOffsetOf( TranslateInput_Actor, playPort )
        , 1
        , 4
        , RTPortDescriptor::KindWired + RTPortDescriptor::NotificationDisabled + RTPortDescriptor::RegisterNotPermitted + RTPortDescriptor::VisibilityPublic
    }
};

const RTFieldDescriptor TranslateInput_Actor::rtg_TranslateInput_Actor_fields[] =
{
    {
        "feedOptions"
        , RTOffsetOf( TranslateInput_Actor, feedOptions )
        , &RTType_char
        , &rtg_tm_TranslateInput_Actor_feedOptions
    }
    , {
        "idleOptions"
        , RTOffsetOf( TranslateInput_Actor, idleOptions )
        , &RTType_char
        , &rtg_tm_TranslateInput_Actor_idleOptions
    }
    , {
        "playOptions"
        , RTOffsetOf( TranslateInput_Actor, playOptions )
        , &RTType_char
        , &rtg_tm_TranslateInput_Actor_playOptions
    }
};

int TranslateInput_Actor::_followInV( RTBindingEnd & rtg_end, int rtg_portId, int rtg_repIndex )
{
    switch( rtg_portId )
    {
    case 0:
        if( rtg_repIndex < 1 )
        {
            rtg_end.port = &inputPort;
            rtg_end.index = rtg_repIndex;
            return 1;
        }
        break;
    case 1:
        if( rtg_repIndex < 1 )
        {
            rtg_end.port = &feedPort;
            rtg_end.index = rtg_repIndex;
            return 1;
        }
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
        {
            rtg_end.port = &playPort;
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
        "inputPort"
        , &InputProt::Conjugate::rt_class
        , 1
    }
    , {
        "feedPort"
        , &FeedProt::Base::rt_class
        , 1
    }
    , {
        "updateOptionsPort"
        , &UpdateOptionsProt::Base::rt_class
        , 1
    }
    , {
        "playPort"
        , &PlayProt::Base::rt_class
        , 1
    }
};

static RTActor * new_TranslateInput_Actor( RTController * rtg_rts, RTActorRef * rtg_ref )
{
    return new TranslateInput_Actor( rtg_rts, rtg_ref );
}

const RTActorClass TranslateInput =
{
    nullptr
    , "TranslateInput"
    , 0 /*RTVersionId*/
    , 4
    , rtg_relays
    , new_TranslateInput_Actor
};

