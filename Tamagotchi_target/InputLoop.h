#ifndef InputLoop_h
#define InputLoop_h

#ifdef PRAGMA
#pragma interface "InputLoop.h"
#endif
#include <UnitName.h>
#include <InputProt.h>
#include <StatusProt.h>
#define SUPER RTActor
class InputLoop_Actor : public RTActor
{
public:
    InputLoop_Actor( RTController * rtg_rts, RTActorRef * rtg_ref );
    virtual ~InputLoop_Actor( void );
    InputLoop_Actor( const InputLoop_Actor & ) = delete;
    InputLoop_Actor & operator=( InputLoop_Actor & ) = delete;
protected:
    StatusProt::Conjugate statusPort;
    InputProt::Base inputPort;
    InputProt::Conjugate triggerInputPort;
    INLINE_METHODS void enter3_Take_Input( void );
    virtual void enterStateV( void ) override;
private:
    INLINE_CHAINS void chain1_Initial( void );
    INLINE_CHAINS void chain2_hatch( void );
    INLINE_CHAINS void chain3_input_requested( void );
public:
    virtual void rtsBehavior( int signalIndex, int portIndex ) override;
    static const RTStateId rtg_parent_state[];
    virtual const RTActor_class * getActorData( void ) const override;
protected:
    static const RTActor_class rtg_class;
private:
    static const RTPortDescriptor rtg_ports[];
public:
    virtual int _followInV( RTBindingEnd & rtg_end, int rtg_portId, int rtg_repIndex ) override;
};
#undef SUPER
extern const RTActorClass InputLoop;
#endif /* InputLoop_h */
