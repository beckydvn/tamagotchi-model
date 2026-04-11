#ifndef FeedProt_h
#define FeedProt_h

#ifdef PRAGMA
#pragma interface "FeedProt.h"
#endif
#include <UnitName.h>
struct FeedProt
{
    class Base : public RTRootProtocol
    {
    public:
        inline Base( void );
        inline ~Base( void );
    protected:
        enum
        {
            rtiLast_FeedProt = rtiLast_RTRootProtocol
        };
    public:
        inline RTOutSignal initFeed( void );
        inline RTOutSignal feedSnack( void );
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
            rti_initFeed = rtiLast_RTRootProtocol + 1
            , rti_feedSnack
        };
    protected:
        enum
        {
            rtiLast_FeedProt = rti_feedSnack
        };
    public:
        inline RTInSignal initFeed( void );
        inline RTInSignal feedSnack( void );
        static const RTProtocolDescriptor rt_class;
    private:
        static const RTSignalDescriptor rt_signals[];
    };
};
inline FeedProt::Base::Base( void )
    : RTRootProtocol(  )
{
}

inline FeedProt::Base::~Base( void )
{
}

inline RTOutSignal FeedProt::Base::initFeed( void )
{
    return RTOutSignal( this, Conjugate::rti_initFeed, nullptr, &RTType_void );
}

inline RTOutSignal FeedProt::Base::feedSnack( void )
{
    return RTOutSignal( this, Conjugate::rti_feedSnack, nullptr, &RTType_void );
}

inline FeedProt::Conjugate::Conjugate( void )
    : RTRootProtocol(  )
{
}

inline FeedProt::Conjugate::~Conjugate( void )
{
}

inline RTInSignal FeedProt::Conjugate::initFeed( void )
{
    return RTInSignal( this, rti_initFeed );
}

inline RTInSignal FeedProt::Conjugate::feedSnack( void )
{
    return RTInSignal( this, rti_feedSnack );
}

#endif /* FeedProt_h */
