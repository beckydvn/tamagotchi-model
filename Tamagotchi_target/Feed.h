#ifndef Feed_h
#define Feed_h

#ifdef PRAGMA
#pragma interface "Feed.h"
#endif
#include <UnitName.h>
#include <FeedProt.h>
#include <UpdateValProt.h>
#define SUPER RTActor
class Feed_Actor : public RTActor
{
public:
    Feed_Actor( RTController * rtg_rts, RTActorRef * rtg_ref );
    virtual ~Feed_Actor( void );
    Feed_Actor( const Feed_Actor & ) = delete;
    Feed_Actor & operator=( Feed_Actor & ) = delete;
protected:
    FeedProt::Conjugate feedPort;
    UpdateValProt::Base updateValPort;
    Timing::Base timingPort;
private:
    int snackCount { 0 } ;
protected:
    INLINE_METHODS void enter3_Initialize_Feed( void );
    virtual void enterStateV( void ) override;
    INLINE_METHODS void transition3_getSnack( const void * rtdata, FeedProt::Conjugate * rtport );
    INLINE_METHODS int guard4_snackCount_3( const void * rtdata, FeedProt::Conjugate * rtport );
    INLINE_METHODS void transition4_snackCount_3( const void * rtdata, FeedProt::Conjugate * rtport );
    INLINE_METHODS int guard5_else( const void * rtdata, FeedProt::Conjugate * rtport );
    INLINE_METHODS void transition5_else( const void * rtdata, FeedProt::Conjugate * rtport );
private:
    INLINE_CHAINS void chain1_Initial( void );
    INLINE_CHAINS void chain2_feed_activated( void );
    INLINE_CHAINS void chain3_getSnack( void );
    INLINE_CHAINS void chain4_snackCount_3( void );
    INLINE_CHAINS void chain5_else( void );
public:
    virtual void rtsBehavior( int signalIndex, int portIndex ) override;
    static const RTStateId rtg_parent_state[];
    virtual const RTActor_class * getActorData( void ) const override;
protected:
    static const RTActor_class rtg_class;
private:
    static const RTPortDescriptor rtg_ports[];
public:
    static const RTFieldDescriptor rtg_Feed_Actor_fields[];
    virtual int _followInV( RTBindingEnd & rtg_end, int rtg_portId, int rtg_repIndex ) override;
};
#undef SUPER
extern const RTActorClass Feed;
#endif /* Feed_h */
