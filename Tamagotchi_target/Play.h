#ifndef Play_h
#define Play_h

#ifdef PRAGMA
#pragma interface "Play.h"
#endif
#include <UnitName.h>
#include <InputProt.h>
#include <PlayProt.h>
#include <ResetPlayProt.h>
#include <UpdateValProt.h>
#define SUPER RTActor
class Play_Actor : public RTActor
{
public:
    Play_Actor( RTController * rtg_rts, RTActorRef * rtg_ref );
    virtual ~Play_Actor( void );
    Play_Actor( const Play_Actor & ) = delete;
    Play_Actor & operator=( Play_Actor & ) = delete;
protected:
    PlayProt::Conjugate playPort;
    UpdateValProt::Base updateValPort;
    InputProt::Base triggerInputPort;
    ResetPlayProt::Conjugate resetPlayPort;
private:
    int throwCount { 0 } ;
protected:
    INLINE_METHODS void enter3_Initiate_Play( void );
    virtual void enterStateV( void ) override;
    INLINE_METHODS void transition3_throwBall( const void * rtdata, PlayProt::Conjugate * rtport );
    INLINE_METHODS int guard4_throws_5( const void * rtdata, PlayProt::Conjugate * rtport );
    INLINE_METHODS void transition4_throws_5( const void * rtdata, PlayProt::Conjugate * rtport );
    INLINE_METHODS void transition5_caught_last( const void * rtdata, PlayProt::Conjugate * rtport );
    INLINE_METHODS void transition7_sleep( const void * rtdata, ResetPlayProt::Conjugate * rtport );
    INLINE_METHODS void transition8_sleep( const void * rtdata, ResetPlayProt::Conjugate * rtport );
private:
    INLINE_CHAINS void chain1_Initial( void );
    INLINE_CHAINS void chain2_play_activated( void );
    INLINE_CHAINS void chain3_throwBall( void );
    INLINE_CHAINS void chain4_throws_5( void );
    INLINE_CHAINS void chain5_caught_last( void );
    INLINE_CHAINS void chain6_exit( void );
    INLINE_CHAINS void chain7_sleep( void );
    INLINE_CHAINS void chain8_sleep( void );
public:
    virtual void rtsBehavior( int signalIndex, int portIndex ) override;
    static const RTStateId rtg_parent_state[];
    virtual const RTActor_class * getActorData( void ) const override;
protected:
    static const RTActor_class rtg_class;
private:
    static const RTPortDescriptor rtg_ports[];
public:
    static const RTFieldDescriptor rtg_Play_Actor_fields[];
    virtual int _followInV( RTBindingEnd & rtg_end, int rtg_portId, int rtg_repIndex ) override;
};
#undef SUPER
extern const RTActorClass Play;
#endif /* Play_h */
