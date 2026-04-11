#ifndef Feed_h
#define Feed_h

#ifdef PRAGMA
#pragma interface "Feed.h"
#endif
#include <UnitName.h>
#include <FeedProt.h>
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
    INLINE_METHODS void enter3_Initialize_Feed( void );
    virtual void enterStateV( void ) override;
private:
    INLINE_CHAINS void chain1_Initial( void );
    INLINE_CHAINS void chain2_feed_activated( void );
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
extern const RTActorClass Feed;
#endif /* Feed_h */
