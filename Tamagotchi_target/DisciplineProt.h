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
        };
    protected:
        enum
        {
            rtiLast_DisciplineProt = rti_exit
        };
    public:
        inline RTInSignal initDiscipline( void );
        inline RTInSignal exit( void );
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

#endif /* DisciplineProt_h */
