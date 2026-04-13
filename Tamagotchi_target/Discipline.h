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
    Timing::Base timing;
private:
    int sitCount { 0 } ;
    std::string input;
    int rng { 0 } ;
    RTTimerId generalTimer;
protected:
    INLINE_METHODS void enter3_Initiate_Discipline( void );
    virtual void enterStateV( void ) override;
    INLINE_METHODS void enter4_Sit( void );
    INLINE_METHODS void enter5_Untrained( void );
    INLINE_METHODS void enter6_Doesn_t_Sit( void );
    INLINE_METHODS int guard5_sitCount_4( const void * rtdata, DisciplineProt::Conjugate * rtport );
    INLINE_METHODS void transition7_reinforce( const void * rtdata, DisciplineProt::Conjugate * rtport );
    INLINE_METHODS int guard8_yes( const void * rtdata, DisciplineProt::Conjugate * rtport );
    INLINE_METHODS void transition8_yes( const void * rtdata, DisciplineProt::Conjugate * rtport );
    INLINE_METHODS int guard10_50_chance( const void * rtdata, DisciplineProt::Conjugate * rtport );
    INLINE_METHODS void transition12_reinforce( const void * rtdata, DisciplineProt::Conjugate * rtport );
    INLINE_METHODS int guard13_yes( const void * rtdata, DisciplineProt::Conjugate * rtport );
    INLINE_METHODS void transition13_yes( const void * rtdata, DisciplineProt::Conjugate * rtport );
    INLINE_METHODS int guard14_no( const void * rtdata, DisciplineProt::Conjugate * rtport );
    INLINE_METHODS void transition14_no( const void * rtdata, DisciplineProt::Conjugate * rtport );
    INLINE_METHODS int guard15_no( const void * rtdata, DisciplineProt::Conjugate * rtport );
    INLINE_METHODS void transition15_no( const void * rtdata, DisciplineProt::Conjugate * rtport );
private:
    INLINE_CHAINS void chain1_Initial( void );
    INLINE_CHAINS void chain2_discipline_activated( void );
    INLINE_CHAINS void chain3_exit( void );
    INLINE_CHAINS void chain4_sit( void );
    INLINE_CHAINS void chain5_sitCount_4( void );
    INLINE_CHAINS void chain6_else( void );
    INLINE_CHAINS void chain7_reinforce( void );
    INLINE_CHAINS void chain8_yes( void );
    INLINE_CHAINS void chain9_timeout( void );
    INLINE_CHAINS void chain10_50_chance( void );
    INLINE_CHAINS void chain11_else( void );
    INLINE_CHAINS void chain12_reinforce( void );
    INLINE_CHAINS void chain13_yes( void );
    INLINE_CHAINS void chain14_no( void );
    INLINE_CHAINS void chain15_no( void );
public:
    virtual void rtsBehavior( int signalIndex, int portIndex ) override;
    static const RTStateId rtg_parent_state[];
    virtual const RTActor_class * getActorData( void ) const override;
protected:
    static const RTActor_class rtg_class;
private:
    static const RTPortDescriptor rtg_ports[];
public:
    static const RTFieldDescriptor rtg_Discipline_Actor_fields[];
    virtual int _followInV( RTBindingEnd & rtg_end, int rtg_portId, int rtg_repIndex ) override;
};
#undef SUPER
extern const RTActorClass Discipline;
#endif /* Discipline_h */
