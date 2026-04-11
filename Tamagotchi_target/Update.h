#ifndef Update_h
#define Update_h

#ifdef PRAGMA
#pragma interface "Update.h"
#endif
#include <UnitName.h>
#include <StatusProt.h>
#define SUPER RTActor
class Update_Actor : public RTActor
{
public:
    Update_Actor( RTController * rtg_rts, RTActorRef * rtg_ref );
    virtual ~Update_Actor( void );
    Update_Actor( const Update_Actor & ) = delete;
    Update_Actor & operator=( Update_Actor & ) = delete;
protected:
    RTActorRef input;
    RTActorRef feed;
    Frame::Base frameP;
    Timing::Base timingPort;
    StatusProt::Base statusPort;
    std::string owner_name;
    std::string tama_name;
private:
    int hunger { 5 } ;
    int discipline { 5 } ;
    int happiness { 5 } ;
    int health { 5 } ;
    int rng { 0 } ;
public:
    void showStatus( void );
protected:
    INLINE_METHODS void enter2_Hatch( void );
    virtual void enterStateV( void ) override;
    INLINE_METHODS void enter3_Idle( void );
    INLINE_METHODS void enter4_Inc_Hunger( void );
    INLINE_METHODS void enter5_Dec_Happiness( void );
    INLINE_METHODS void enter6_Dec_Discipline( void );
    INLINE_METHODS void enter7_Return_To_Idle( void );
    INLINE_METHODS int guard3_50_chance( const void * rtdata, Timing::Base * rtport );
    INLINE_METHODS int guard4_30_chance( const void * rtdata, Timing::Base * rtport );
    INLINE_METHODS int guard5_20_chance( const void * rtdata, Timing::Base * rtport );
private:
    INLINE_CHAINS void chain1_Initial( void );
    INLINE_CHAINS void chain2_timeout( void );
    INLINE_CHAINS void chain3_50_chance( void );
    INLINE_CHAINS void chain4_30_chance( void );
    INLINE_CHAINS void chain5_20_chance( void );
    INLINE_CHAINS void chain6_timeout( void );
    INLINE_CHAINS void chain7_timeout( void );
    INLINE_CHAINS void chain8_timeout( void );
    INLINE_CHAINS void chain9_timeout( void );
    INLINE_CHAINS void chain10_timeout( void );
public:
    virtual void rtsBehavior( int signalIndex, int portIndex ) override;
    static const RTStateId rtg_parent_state[];
    virtual const RTActor_class * getActorData( void ) const override;
protected:
    static const RTActor_class rtg_class;
private:
    static const RTComponentDescriptor rtg_capsule_roles[];
    static const RTPortDescriptor rtg_ports[];
public:
    static const RTFieldDescriptor rtg_Update_Actor_fields[];
    virtual int _followOutV( RTBindingEnd & rtg_end, int rtg_compId, int rtg_portId, int rtg_repIndex ) override;
};
#undef SUPER
extern const RTActorClass Update;
#endif /* Update_h */
