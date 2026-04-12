#ifndef UpdateOptionsProt_h
#define UpdateOptionsProt_h

#ifdef PRAGMA
#pragma interface "UpdateOptionsProt.h"
#endif
#include <UnitName.h>
struct UpdateOptionsProt
{
    class Base : public RTRootProtocol
    {
    public:
        inline Base( void );
        inline ~Base( void );
    protected:
        enum
        {
            rtiLast_UpdateOptionsProt = rtiLast_RTRootProtocol
        };
    public:
        inline RTOutSignal updateOptions( void );
        inline RTOutSignal updateOptions( const RTTypedValue & data );
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
            rti_updateOptions = rtiLast_RTRootProtocol + 1
        };
    protected:
        enum
        {
            rtiLast_UpdateOptionsProt = rti_updateOptions
        };
    public:
        inline RTInSignal updateOptions( void );
        static const RTProtocolDescriptor rt_class;
    private:
        static const RTSignalDescriptor rt_signals[];
    };
};
inline UpdateOptionsProt::Base::Base( void )
    : RTRootProtocol(  )
{
}

inline UpdateOptionsProt::Base::~Base( void )
{
}

inline RTOutSignal UpdateOptionsProt::Base::updateOptions( void )
{
    return RTOutSignal( this, Conjugate::rti_updateOptions, nullptr, &RTType_void );
}

inline RTOutSignal UpdateOptionsProt::Base::updateOptions( const RTTypedValue & data )
{
    return RTOutSignal( this, Conjugate::rti_updateOptions, data.data, data.type );
}

inline UpdateOptionsProt::Conjugate::Conjugate( void )
    : RTRootProtocol(  )
{
}

inline UpdateOptionsProt::Conjugate::~Conjugate( void )
{
}

inline RTInSignal UpdateOptionsProt::Conjugate::updateOptions( void )
{
    return RTInSignal( this, rti_updateOptions );
}

#endif /* UpdateOptionsProt_h */
