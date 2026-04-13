#ifndef Discipline_h
#define Discipline_h

#ifdef PRAGMA
#pragma interface "Discipline.h"
#endif
#include <UnitName.h>
#include <DisciplineProt.h>
#include <InputProt.h>
#include <UpdateValProt.h>
#define SUPER RTActor
class Discipline_Actor : public RTActor
{
public:
    Discipline_Actor( RTController * rtg_rts, RTActorRef * rtg_ref );
    virtual ~Discipline_Actor( void );
    Discipline_Actor( const Discipline_Actor & ) = delete;
    Discipline_Actor & operator=( Discipline_Actor & ) = delete;
protected:
    InputProt::Base triggerInputPort;
    UpdateValProt::Base updateValPort;
    DisciplineProt::Conjugate disciplinePort;
    INLINE_METHODS void enter3_Initiate_Discipline( void );
    virtual void enterStateV( void ) override;
private:
    INLINE_CHAINS void chain1_Initial( void );
    INLINE_CHAINS void chain2_discipline_activated( void );
    INLINE_CHAINS void chain3_exit( void );
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
extern const RTActorClass Discipline;
#endif /* Discipline_h */
