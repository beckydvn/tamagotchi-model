#ifndef DisciplineProt_h
#define DisciplineProt_h

#ifdef PRAGMA
#pragma interface "DisciplineProt.h"
#endif
#include <UnitName.h>
struct DisciplineProt
{
    class Base : public RTRootProtocol
    {
    public:
        inline Base( void );
        inline ~Base( void );
    protected:
        enum
        {
            rtiLast_DisciplineProt = rtiLast_RTRootProtocol
        };
    public:
        inline RTOutSignal initDiscipline( void );
        inline RTOutSignal exit( void );
        inline RTOutSignal sit( void );
        inline RTOutSignal reinforce( void );
        inline RTOutSignal reinforce( const RTTypedValue & data );
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
            rti_initDiscipline = rtiLast_RTRootProtocol + 1
            , rti_exit
            , rti_sit
            , rti_reinforce
        };
    protected:
        enum
        {
            rtiLast_DisciplineProt = rti_reinforce
        };
    public:
        inline RTInSignal initDiscipline( void );
        inline RTInSignal exit( void );
        inline RTInSignal sit( void );
        inline RTInSignal reinforce( void );
        static const RTProtocolDescriptor rt_class;
    private:
        static const RTSignalDescriptor rt_signals[];
    };
};
inline DisciplineProt::Base::Base( void )
    : RTRootProtocol(  )
{
}

inline DisciplineProt::Base::~Base( void )
{
}

inline RTOutSignal DisciplineProt::Base::initDiscipline( void )
{
    return RTOutSignal( this, Conjugate::rti_initDiscipline, nullptr, &RTType_void );
}

inline RTOutSignal DisciplineProt::Base::exit( void )
{
    return RTOutSignal( this, Conjugate::rti_exit, nullptr, &RTType_void );
}

inline RTOutSignal DisciplineProt::Base::sit( void )
{
    return RTOutSignal( this, Conjugate::rti_sit, nullptr, &RTType_void );
}

inline RTOutSignal DisciplineProt::Base::reinforce( void )
{
    return RTOutSignal( this, Conjugate::rti_reinforce, nullptr, &RTType_void );
}

inline RTOutSignal DisciplineProt::Base::reinforce( const RTTypedValue & data )
{
    return RTOutSignal( this, Conjugate::rti_reinforce, data.data, data.type );
}

inline DisciplineProt::Conjugate::Conjugate( void )
    : RTRootProtocol(  )
{
}

inline DisciplineProt::Conjugate::~Conjugate( void )
{
}

inline RTInSignal DisciplineProt::Conjugate::initDiscipline( void )
{
    return RTInSignal( this, rti_initDiscipline );
}

inline RTInSignal DisciplineProt::Conjugate::exit( void )
{
    return RTInSignal( this, rti_exit );
}

inline RTInSignal DisciplineProt::Conjugate::sit( void )
{
    return RTInSignal( this, rti_sit );
}

inline RTInSignal DisciplineProt::Conjugate::reinforce( void )
{
    return RTInSignal( this, rti_reinforce );
}

#endif /* DisciplineProt_h */
