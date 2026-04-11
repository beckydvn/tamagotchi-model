#ifndef Top_h
#define Top_h

#ifdef PRAGMA
#pragma interface "Top.h"
#endif
#include <UnitName.h>
#define SUPER RTActor
class Top_Actor : public RTActor
{
public:
    Top_Actor( RTController * rtg_rts, RTActorRef * rtg_ref );
    virtual ~Top_Actor( void );
    Top_Actor( const Top_Actor & ) = delete;
    Top_Actor & operator=( Top_Actor & ) = delete;
protected:
    RTActorRef status;
    INLINE_METHODS void transition1_Initial( const void * rtdata, RTProtocol * rtport );
private:
    INLINE_CHAINS void chain1_Initial( void );
public:
    virtual void rtsBehavior( int signalIndex, int portIndex ) override;
    static const RTStateId rtg_parent_state[];
    virtual const RTActor_class * getActorData( void ) const override;
protected:
    static const RTActor_class rtg_class;
private:
    static const RTComponentDescriptor rtg_capsule_roles[];
};
#undef SUPER
extern const RTActorClass Top;
#endif /* Top_h */
