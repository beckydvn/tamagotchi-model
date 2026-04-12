#ifndef PlayProt_h
#define PlayProt_h

#ifdef PRAGMA
#pragma interface "PlayProt.h"
#endif
#include <UnitName.h>
struct PlayProt
{
    class Base : public RTRootProtocol
    {
    public:
        inline Base( void );
        inline ~Base( void );
    protected:
        enum
        {
            rtiLast_PlayProt = rtiLast_RTRootProtocol
        };
    public:
        inline RTOutSignal initPlay( void );
        inline RTOutSignal exit( void );
        inline RTOutSignal throwBall( void );
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
            rti_initPlay = rtiLast_RTRootProtocol + 1
            , rti_exit
            , rti_throwBall
        };
    protected:
        enum
        {
            rtiLast_PlayProt = rti_throwBall
        };
    public:
        inline RTInSignal initPlay( void );
        inline RTInSignal exit( void );
        inline RTInSignal throwBall( void );
        static const RTProtocolDescriptor rt_class;
    private:
        static const RTSignalDescriptor rt_signals[];
    };
};
inline PlayProt::Base::Base( void )
    : RTRootProtocol(  )
{
}

inline PlayProt::Base::~Base( void )
{
}

inline RTOutSignal PlayProt::Base::initPlay( void )
{
    return RTOutSignal( this, Conjugate::rti_initPlay, nullptr, &RTType_void );
}

inline RTOutSignal PlayProt::Base::exit( void )
{
    return RTOutSignal( this, Conjugate::rti_exit, nullptr, &RTType_void );
}

inline RTOutSignal PlayProt::Base::throwBall( void )
{
    return RTOutSignal( this, Conjugate::rti_throwBall, nullptr, &RTType_void );
}

inline PlayProt::Conjugate::Conjugate( void )
    : RTRootProtocol(  )
{
}

inline PlayProt::Conjugate::~Conjugate( void )
{
}

inline RTInSignal PlayProt::Conjugate::initPlay( void )
{
    return RTInSignal( this, rti_initPlay );
}

inline RTInSignal PlayProt::Conjugate::exit( void )
{
    return RTInSignal( this, rti_exit );
}

inline RTInSignal PlayProt::Conjugate::throwBall( void )
{
    return RTInSignal( this, rti_throwBall );
}

#endif /* PlayProt_h */
