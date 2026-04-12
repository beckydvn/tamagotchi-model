#ifndef UpdateTamaProt_h
#define UpdateTamaProt_h

#ifdef PRAGMA
#pragma interface "UpdateTamaProt.h"
#endif
#include <UnitName.h>
struct UpdateTamaProt
{
    class Base : public RTRootProtocol
    {
    public:
        inline Base( void );
        inline ~Base( void );
    protected:
        enum
        {
            rtiLast_UpdateTamaProt = rtiLast_RTRootProtocol
        };
    public:
        inline RTOutSignal updateTama( void );
        inline RTOutSignal updateTama( const RTTypedValue & data );
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
            rti_updateTama = rtiLast_RTRootProtocol + 1
        };
    protected:
        enum
        {
            rtiLast_UpdateTamaProt = rti_updateTama
        };
    public:
        inline RTInSignal updateTama( void );
        static const RTProtocolDescriptor rt_class;
    private:
        static const RTSignalDescriptor rt_signals[];
    };
};
inline UpdateTamaProt::Base::Base( void )
    : RTRootProtocol(  )
{
}

inline UpdateTamaProt::Base::~Base( void )
{
}

inline RTOutSignal UpdateTamaProt::Base::updateTama( void )
{
    return RTOutSignal( this, Conjugate::rti_updateTama, nullptr, &RTType_void );
}

inline RTOutSignal UpdateTamaProt::Base::updateTama( const RTTypedValue & data )
{
    return RTOutSignal( this, Conjugate::rti_updateTama, data.data, data.type );
}

inline UpdateTamaProt::Conjugate::Conjugate( void )
    : RTRootProtocol(  )
{
}

inline UpdateTamaProt::Conjugate::~Conjugate( void )
{
}

inline RTInSignal UpdateTamaProt::Conjugate::updateTama( void )
{
    return RTInSignal( this, rti_updateTama );
}

#endif /* UpdateTamaProt_h */
