#ifndef Input_h
#define Input_h

#ifdef PRAGMA
#pragma interface "Input.h"
#endif
#include <UnitName.h>
#include <StatusProt.h>
#define SUPER RTActor
class Input_Actor : public RTActor
{
public:
    Input_Actor( RTController * rtg_rts, RTActorRef * rtg_ref );
    virtual ~Input_Actor( void );
    Input_Actor( const Input_Actor & ) = delete;
    Input_Actor & operator=( Input_Actor & ) = delete;
protected:
    StatusProt::Conjugate statusProt;
private:
    std::string input;
protected:
    INLINE_METHODS void enter3_Take_Input( void );
    virtual void enterStateV( void ) override;
private:
    INLINE_CHAINS void chain1_Initial( void );
    INLINE_CHAINS void chain2_hatch( void );
    INLINE_CHAINS void chain3_returnToIdle( void );
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
extern const RTActorClass Input;
#endif /* Input_h */
