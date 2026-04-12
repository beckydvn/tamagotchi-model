#ifndef Update_h
#define Update_h

#ifdef PRAGMA
#pragma interface "Update.h"
#endif
#include <UnitName.h>
#include <StatusProt.h>
#include <UpdateOptionsProt.h>
#include <UpdateValProt.h>
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
    RTActorRef translateInput;
    Frame::Base frameP;
    Timing::Base timingPort;
    StatusProt::Base statusPort;
    UpdateValProt::Conjugate updateValPort;
    UpdateOptionsProt::Conjugate updateOptionsPort;
    std::string owner_name;
public:
    std::string tama_name;
private:
    int hunger { 5 } ;
    int discipline { 5 } ;
    int happiness { 5 } ;
    int health { 5 } ;
    int rng { 0 } ;
    std::string options { "\nACTIVITY OPTIONS: (FEED)" } ;
public:
    void showStatus( void );
protected:
    INLINE_METHODS void enter2_Hatch( void );
    virtual void enterStateV( void ) override;
    INLINE_METHODS void enter3_Idle( void );
    INLINE_METHODS int guard3_inc_hunger_50_chance( const void * rtdata, Timing::Base * rtport );
    INLINE_METHODS void transition3_inc_hunger_50_chance( const void * rtdata, Timing::Base * rtport );
    INLINE_METHODS int guard4_dec_happiness_30_chance( const void * rtdata, Timing::Base * rtport );
    INLINE_METHODS void transition4_dec_happiness_30_chance( const void * rtdata, Timing::Base * rtport );
    INLINE_METHODS int guard5_20_chance( const void * rtdata, Timing::Base * rtport );
    INLINE_METHODS void transition5_20_chance( const void * rtdata, Timing::Base * rtport );
    INLINE_METHODS void transition6_timeout( const void * rtdata, Timing::Base * rtport );
    INLINE_METHODS void transition7_updateHunger( const int * rtdata, UpdateValProt::Conjugate * rtport );
    INLINE_METHODS void transition8_updateHealth( const int * rtdata, UpdateValProt::Conjugate * rtport );
    INLINE_METHODS int guard9_is_full( const int * rtdata, UpdateValProt::Conjugate * rtport );
    INLINE_METHODS void transition9_is_full( const int * rtdata, UpdateValProt::Conjugate * rtport );
    INLINE_METHODS int guard11_ill( const int * rtdata, UpdateValProt::Conjugate * rtport );
    INLINE_METHODS void transition11_ill( const int * rtdata, UpdateValProt::Conjugate * rtport );
    INLINE_METHODS void transition13_updateOptions( const void * rtdata, UpdateOptionsProt::Conjugate * rtport );
private:
    INLINE_CHAINS void chain1_Initial( void );
    INLINE_CHAINS void chain2_timeout( void );
    INLINE_CHAINS void chain3_inc_hunger_50_chance( void );
    INLINE_CHAINS void chain4_dec_happiness_30_chance( void );
    INLINE_CHAINS void chain5_20_chance( void );
    INLINE_CHAINS void chain6_timeout( void );
    INLINE_CHAINS void chain7_updateHunger( void );
    INLINE_CHAINS void chain8_updateHealth( void );
    INLINE_CHAINS void chain9_is_full( void );
    INLINE_CHAINS void chain10_else( void );
    INLINE_CHAINS void chain11_ill( void );
    INLINE_CHAINS void chain12_else( void );
    INLINE_CHAINS void chain13_updateOptions( void );
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
