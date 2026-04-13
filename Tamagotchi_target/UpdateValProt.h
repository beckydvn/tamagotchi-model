#ifndef UpdateValProt_h
#define UpdateValProt_h

#ifdef PRAGMA
#pragma interface "UpdateValProt.h"
#endif
#include <UnitName.h>
struct UpdateValProt
{
    class Base : public RTRootProtocol
    {
    public:
        inline Base( void );
        inline ~Base( void );
    protected:
        enum
        {
            rtiLast_UpdateValProt = rtiLast_RTRootProtocol
        };
    public:
        inline RTOutSignal updateHunger( const int & data );
        inline RTOutSignal updateHealth( const int & data );
        inline RTOutSignal updateHappiness( const int & data );
        inline RTOutSignal updateDiscipline( const int & data );
        static const RTProtocolDescriptor rt_class;
    private:
        static const RTSignalDescriptor rt_signals[];
    };
    class Conjugate : public RTRootProtocol
    {
    public:
        inline Conjugate( void );
        inline ~Conjugate( void );
        enum RTOutEvents
        {
            rti_updateHunger = rtiLast_RTRootProtocol + 1
            , rti_updateHealth
            , rti_updateHappiness
            , rti_updateDiscipline
        };
    protected:
        enum
        {
            rtiLast_UpdateValProt = rti_updateDiscipline
        };
    public:
        inline RTInSignal updateHunger( void );
        inline RTInSignal updateHealth( void );
        inline RTInSignal updateHappiness( void );
        inline RTInSignal updateDiscipline( void );
        static const RTProtocolDescriptor rt_class;
    private:
        static const RTSignalDescriptor rt_signals[];
    };
};
inline UpdateValProt::Base::Base( void )
    : RTRootProtocol(  )
{
}

inline UpdateValProt::Base::~Base( void )
{
}

inline RTOutSignal UpdateValProt::Base::updateHunger( const int & data )
{
    return RTOutSignal( this, Conjugate::rti_updateHunger, &data, &RTType_int );
}

inline RTOutSignal UpdateValProt::Base::updateHealth( const int & data )
{
    return RTOutSignal( this, Conjugate::rti_updateHealth, &data, &RTType_int );
}

inline RTOutSignal UpdateValProt::Base::updateHappiness( const int & data )
{
    return RTOutSignal( this, Conjugate::rti_updateHappiness, &data, &RTType_int );
}

inline RTOutSignal UpdateValProt::Base::updateDiscipline( const int & data )
{
    return RTOutSignal( this, Conjugate::rti_updateDiscipline, &data, &RTType_int );
}

inline UpdateValProt::Conjugate::Conjugate( void )
    : RTRootProtocol(  )
{
}

inline UpdateValProt::Conjugate::~Conjugate( void )
{
}

inline RTInSignal UpdateValProt::Conjugate::updateHunger( void )
{
    return RTInSignal( this, rti_updateHunger );
}

inline RTInSignal UpdateValProt::Conjugate::updateHealth( void )
{
    return RTInSignal( this, rti_updateHealth );
}

inline RTInSignal UpdateValProt::Conjugate::updateHappiness( void )
{
    return RTInSignal( this, rti_updateHappiness );
}

inline RTInSignal UpdateValProt::Conjugate::updateDiscipline( void )
{
    return RTInSignal( this, rti_updateDiscipline );
}

#endif /* UpdateValProt_h */
