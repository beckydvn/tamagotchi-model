#ifndef TranslateInput_h
#define TranslateInput_h

#ifdef PRAGMA
#pragma interface "TranslateInput.h"
#endif
#include <UnitName.h>
#include <FeedProt.h>
#include <InputProt.h>
#define SUPER RTActor
class TranslateInput_Actor : public RTActor
{
public:
    TranslateInput_Actor( RTController * rtg_rts, RTActorRef * rtg_ref );
    virtual ~TranslateInput_Actor( void );
    TranslateInput_Actor( const TranslateInput_Actor & ) = delete;
    TranslateInput_Actor & operator=( TranslateInput_Actor & ) = delete;
protected:
    InputProt::Conjugate inputPort;
    FeedProt::Base feedPort;
private:
    std::string input;
    std::string mode { "IDLE" } ;
protected:
    INLINE_METHODS void enter3_Send_Signals( void );
    virtual void enterStateV( void ) override;
    INLINE_METHODS void transition2_gotInput( const void * rtdata, InputProt::Conjugate * rtport );
    INLINE_METHODS void transition3_gotInput( const void * rtdata, InputProt::Conjugate * rtport );
private:
    INLINE_CHAINS void chain1_Initial( void );
    INLINE_CHAINS void chain2_gotInput( void );
    INLINE_CHAINS void chain3_gotInput( void );
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
extern const RTActorClass TranslateInput;
#endif /* TranslateInput_h */
