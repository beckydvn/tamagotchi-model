#ifndef Status_h
#define Status_h

#ifdef PRAGMA
#pragma interface "Status.h"
#endif
#include <UnitName.h>
#include <StatusProt.h>
#define SUPER RTActor
class Status_Actor : public RTActor
{
public:
    Status_Actor( RTController * rtg_rts, RTActorRef * rtg_ref );
    virtual ~Status_Actor( void );
    Status_Actor( const Status_Actor & ) = delete;
    Status_Actor & operator=( Status_Actor & ) = delete;
protected:
    StatusProt::Base statusProt;
    std::string owner_name;
    std::string tama_name;
private:
    int hunger { 5 } ;
    int discipline { 5 } ;
    int happiness { 5 } ;
    int health { 5 } ;
public:
    void showStatus( void );
protected:
    INLINE_METHODS void enter3_Hatch( void );
    virtual void enterStateV( void ) override;
private:
    INLINE_CHAINS void chain1_Initial( void );
    INLINE_CHAINS void chain2_initiate_hatch( void );
public:
    virtual void rtsBehavior( int signalIndex, int portIndex ) override;
    static const RTStateId rtg_parent_state[];
    virtual const RTActor_class * getActorData( void ) const override;
protected:
    static const RTActor_class rtg_class;
private:
    static const RTPortDescriptor rtg_ports[];
public:
    static const RTFieldDescriptor rtg_Status_Actor_fields[];
    virtual int _followInV( RTBindingEnd & rtg_end, int rtg_portId, int rtg_repIndex ) override;
};
#undef SUPER
extern const RTActorClass Status;
#endif /* Status_h */
