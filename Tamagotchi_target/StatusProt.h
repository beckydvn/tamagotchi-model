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
        enum RTInEvents
        {
            rti_hatch = rtiLast_RTRootProtocol + 1
        };
    protected:
        enum
        {
            rtiLast_StatusProt = rti_hatch
        };
    public:
        inline RTInSignal hatch( void );
        static const RTProtocolDescriptor rt_class;
    private:
        static const RTSignalDescriptor rt_signals[];
    };
    class Conjugate : public RTRootProtocol
    {
    public:
        inline Conjugate( void );
        inline ~Conjugate( void );
    protected:
        enum
        {
            rtiLast_StatusProt = rtiLast_RTRootProtocol
        };
    public:
        inline RTOutSignal hatch( void );
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

inline RTInSignal StatusProt::Base::hatch( void )
{
    return RTInSignal( this, rti_hatch );
}

inline StatusProt::Conjugate::Conjugate( void )
    : RTRootProtocol(  )
{
}

inline StatusProt::Conjugate::~Conjugate( void )
{
}

inline RTOutSignal StatusProt::Conjugate::hatch( void )
{
    return RTOutSignal( this, Base::rti_hatch, nullptr, &RTType_void );
}

#endif /* StatusProt_h */
