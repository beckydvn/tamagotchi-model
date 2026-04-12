#ifndef ResetPlayProt_h
#define ResetPlayProt_h

#ifdef PRAGMA
#pragma interface "ResetPlayProt.h"
#endif
#include <UnitName.h>
struct ResetPlayProt
{
    class Base : public RTRootProtocol
    {
    public:
        inline Base( void );
        inline ~Base( void );
    protected:
        enum
        {
            rtiLast_ResetPlayProt = rtiLast_RTRootProtocol
        };
    public:
        inline RTOutSignal resetThrow( void );
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
            rti_resetThrow = rtiLast_RTRootProtocol + 1
        };
    protected:
        enum
        {
            rtiLast_ResetPlayProt = rti_resetThrow
        };
    public:
        inline RTInSignal resetThrow( void );
        static const RTProtocolDescriptor rt_class;
    private:
        static const RTSignalDescriptor rt_signals[];
    };
};
inline ResetPlayProt::Base::Base( void )
    : RTRootProtocol(  )
{
}

inline ResetPlayProt::Base::~Base( void )
{
}

inline RTOutSignal ResetPlayProt::Base::resetThrow( void )
{
    return RTOutSignal( this, Conjugate::rti_resetThrow, nullptr, &RTType_void );
}

inline ResetPlayProt::Conjugate::Conjugate( void )
    : RTRootProtocol(  )
{
}

inline ResetPlayProt::Conjugate::~Conjugate( void )
{
}

inline RTInSignal ResetPlayProt::Conjugate::resetThrow( void )
{
    return RTInSignal( this, rti_resetThrow );
}

#endif /* ResetPlayProt_h */
