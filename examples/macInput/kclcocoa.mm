#import "kclcocoa.h"
#import "kclmain.h"

@interface GameThread : NSObject
{
}
- (void)startGameThread;
@end


@implementation GameThread

-(void)startGameThread
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    char *argv[] = {0};
    kclMain(0, argv);
    [pool release];
}

@end


@implementation kclCocoa

- (void) applicationDidFinishLaunching: (NSNotification *) note
{    
    GameThread * gameThread = [[GameThread alloc] init];
    [gameThread performSelectorInBackground:@selector(startGameThread) withObject:gameThread];
}

-(void)sendEvent:(NSEvent *)theEvent
{    
    switch ([theEvent type]) {
        case NSKeyDown:
        case NSKeyUp:
            break;
        case NSLeftMouseDown:
        case NSLeftMouseUp:
        case NSRightMouseDown:
        case NSRightMouseUp:
        case NSMouseMoved:
        case NSMouseEntered:
        case NSMouseExited:
        case NSScrollWheel:
        case NSOtherMouseDown:
        case NSOtherMouseUp:
            break;
        default:
            [super sendEvent:theEvent];
            break;
    }
}

-(BOOL)acceptsFirstResponder
{
    return true;
}

@end

static void GameApplicationMain (int argc, char *argv[])
{
    NSAutoreleasePool	*pool = [[NSAutoreleasePool alloc] init];
    [kclCocoa sharedApplication];
    [NSApp setDelegate:NSApp];
    [NSApp run];
    [NSApp release];
    [pool release];
}

#ifdef main
#  undef main
#endif

int main (int argc, char *argv[])
{
    GameApplicationMain(argc,argv);
    return 0;
}
