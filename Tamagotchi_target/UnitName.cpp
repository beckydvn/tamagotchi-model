#if defined( PRAGMA ) && ! defined( PRAGMA_IMPLEMENTED )
#pragma implementation "UnitName.h"
#endif
#include <UnitName.h>

extern const RTActorClass Top;

#if USE_THREADS
static void _rtg_createThreads( RTDebugger * debugger )
{
}

static void _rtg_deleteThreads( void )
{
}

static void _rtg_mapLogicalThreads( RTController * )
{
}

#else 
static void _rtg_mapLogicalThreads( RTController * controller )
{
}

#endif
static const RTSystemDescriptor _rtg_system =
{
    &Top
#if USE_THREADS
    , DEFAULT_MAIN_PRIORITY
    , 20000
    , DEFAULT_TIMER_PRIORITY
    , 20000
    , _rtg_createThreads
    , _rtg_deleteThreads
#endif
    , _rtg_mapLogicalThreads
};

const char * const default_argv[] =
{
    "Top"
};

int RTMain::entryPoint( int argc, const char * const * argv )
{
    if( argc <= 0 )
    {
        argc = 1;
        argv = default_argv;
    }
    _argc = argc;
    _argv = argv;
    _system = &_rtg_system;
    return execute(  );
}

