#ifndef InputProt_h
#define InputProt_h

#ifdef PRAGMA
#pragma interface "InputProt.h"
#endif
#include <UnitName.h>
struct InputProt
{
    class Base : public RTRootProtocol
    {
    public:
        inline Base( void );
        inline ~Base( void );
    protected:
        enum
        {
            rtiLast_InputProt = rtiLast_RTRootProtocol
        };
    public:
        inline RTOutSignal gotInput( void );
        inline RTOutSignal gotInput( const RTTypedValue & data );
        inline RTOutSignal triggerInput( void );
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
            rti_gotInput = rtiLast_RTRootProtocol + 1
            , rti_triggerInput
        };
    protected:
        enum
        {
            rtiLast_InputProt = rti_triggerInput
        };
    public:
        inline RTInSignal gotInput( void );
        inline RTInSignal triggerInput( void );
        static const RTProtocolDescriptor rt_class;
    private:
        static const RTSignalDescriptor rt_signals[];
    };
};
inline InputProt::Base::Base( void )
    : RTRootProtocol(  )
{
}

inline InputProt::Base::~Base( void )
{
}

inline RTOutSignal InputProt::Base::gotInput( void )
{
    return RTOutSignal( this, Conjugate::rti_gotInput, nullptr, &RTType_void );
}

inline RTOutSignal InputProt::Base::gotInput( const RTTypedValue & data )
{
    return RTOutSignal( this, Conjugate::rti_gotInput, data.data, data.type );
}

inline RTOutSignal InputProt::Base::triggerInput( void )
{
    return RTOutSignal( this, Conjugate::rti_triggerInput, nullptr, &RTType_void );
}

inline InputProt::Conjugate::Conjugate( void )
    : RTRootProtocol(  )
{
}

inline InputProt::Conjugate::~Conjugate( void )
{
}

inline RTInSignal InputProt::Conjugate::gotInput( void )
{
    return RTInSignal( this, rti_gotInput );
}

inline RTInSignal InputProt::Conjugate::triggerInput( void )
{
    return RTInSignal( this, rti_triggerInput );
}

#endif /* InputProt_h */
