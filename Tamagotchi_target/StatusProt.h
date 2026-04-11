#ifndef StatusProt_h
#define StatusProt_h

#ifdef PRAGMA
#pragma interface "StatusProt.h"
#endif
#include <UnitName.h>
struct StatusProt
{
    class Base : public RTRootProtocol
    {
    public:
        inline Base( void );
        inline ~Base( void );
    protected:
        enum
        {
            rtiLast_StatusProt = rtiLast_RTRootProtocol
        };
    public:
        inline RTOutSignal hatch( void );
        inline RTOutSignal returnToIdle( void );
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
            rti_hatch = rtiLast_RTRootProtocol + 1
            , rti_returnToIdle
        };
    protected:
        enum
        {
            rtiLast_StatusProt = rti_returnToIdle
        };
    public:
        inline RTInSignal hatch( void );
        inline RTInSignal returnToIdle( void );
        static const RTProtocolDescriptor rt_class;
    private:
        static const RTSignalDescriptor rt_signals[];
    };
};
inline StatusProt::Base::Base( void )
    : RTRootProtocol(  )
{
}

inline StatusProt::Base::~Base( void )
{
}

inline RTOutSignal StatusProt::Base::hatch( void )
{
    return RTOutSignal( this, Conjugate::rti_hatch, nullptr, &RTType_void );
}

inline RTOutSignal StatusProt::Base::returnToIdle( void )
{
    return RTOutSignal( this, Conjugate::rti_returnToIdle, nullptr, &RTType_void );
}

inline StatusProt::Conjugate::Conjugate( void )
    : RTRootProtocol(  )
{
}

inline StatusProt::Conjugate::~Conjugate( void )
{
}

inline RTInSignal StatusProt::Conjugate::hatch( void )
{
    return RTInSignal( this, rti_hatch );
}

inline RTInSignal StatusProt::Conjugate::returnToIdle( void )
{
    return RTInSignal( this, rti_returnToIdle );
}

#endif /* StatusProt_h */
