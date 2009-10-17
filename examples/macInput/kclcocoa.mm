#import "kclcocoa.h"
#import "kclmain.h"

#include <iostream>
#include <IOKit/IOKitLib.h>
#include <IOKit/hid/IOHIDKeys.h>
#include <IOKit/hid/IOHIDLib.h>
#include <CoreFoundation/CoreFoundation.h>


/////////
/*static void Handle_IOHIDDeviceInputValueCallback( 
                                                 void *          inContext,      // context from IOHIDDeviceRegisterInputValueCallback
                                                 IOReturn        inResult,       // completion result for the input value operation
                                                 void *          inSender,       // IOHIDDeviceRef of the device this element is from
                                                 IOHIDValueRef   inIOHIDValueRef // the new element value
                                                 ) 
{
    IOHIDDeviceRef deviceRef = (IOHIDDeviceRef) inSender;
    if(inResult == kIOReturnSuccess && CFGetTypeID(deviceRef) == IOHIDDeviceGetTypeID())
    {
        CFArrayRef elements = IOHIDDeviceCopyMatchingElements(deviceRef, NULL, kIOHIDOptionsTypeNone);
        
        if(elements)
        {
            
            for(int i = 0; i < CFArrayGetCount(elements); i++)
            {
                IOHIDElementRef elementRef = (IOHIDElementRef)CFArrayGetValueAtIndex(elements,(CFIndex)i);
                if(CFGetTypeID(elementRef) == IOHIDElementGetTypeID())
                {
                    uint32_t usagePage = IOHIDElementGetUsagePage( elementRef );
                    uint32_t usage = IOHIDElementGetUsage( elementRef );
                    
                    /*IOHIDValueRef bla = NULL;
                    IOHIDDeviceGetValue(deviceRef, elementRef, &bla);*/                    
                    
                    /*if ( bla != NULL ) 
                    {
                        CFIndex mdmd = IOHIDValueGetIntegerValue( inIOHIDValueRef );
                        
                        if(mdmd > 0)
                        {
                            printf("usagepage: %d usage: %d newvalue: %d\n", usagePage, usage, mdmd);
                        }
                    //}
                }
            }
        }
    }    
}*/
//////////
static void Handle_IOHIDDeviceIOHIDReportCallback(void * inContext, IOReturn inResult, void * inSender, IOHIDReportType inType, uint32_t inReportID, uint8_t * inReport, CFIndex inReportLength )
{
    IOHIDDeviceRef deviceRef = (IOHIDDeviceRef) inSender;
    if(inResult == kIOReturnSuccess && CFGetTypeID(deviceRef) == IOHIDDeviceGetTypeID())
    {
        CFArrayRef elements = IOHIDDeviceCopyMatchingElements(deviceRef, NULL, kIOHIDOptionsTypeNone);
        
        if(elements)
        {
            
            for(int i = 0; i < CFArrayGetCount(elements); i++)
            {
                IOHIDElementRef elementRef = (IOHIDElementRef)CFArrayGetValueAtIndex(elements,(CFIndex)i);
                if(CFGetTypeID(elementRef) == IOHIDElementGetTypeID())
                {
                    uint32_t usagePage = IOHIDElementGetUsagePage( elementRef );
                    uint32_t usage = IOHIDElementGetUsage( elementRef );
                    
                    IOHIDValueRef bla = NULL;
                    IOHIDDeviceGetValue(deviceRef, elementRef, &bla);                    
                    
                    if ( bla != NULL ) 
                    {
                        CFTypeRef dsd = IOHIDElementGetName(elementRef);
                        iohiddevi
                        CFIndex mdmd = IOHIDValueGetIntegerValue( bla );
                        
                        if(mdmd > 0)
                        {
                            printf("usagepage: %d usage: %d \n", usagePage, usage);
                        }
                    }
                }
            }
        }
    }
}

static void MyCallBack (const void *value, void *context)
{
    IOHIDDeviceRef device = (IOHIDDeviceRef) value;
    
    if ( CFGetTypeID( device ) == IOHIDDeviceGetTypeID( ) ) 
    {
        IOHIDDeviceOpen(device,kIOHIDOptionsTypeNone);
        
        
        CFStringRef propRef = (CFStringRef) IOHIDDeviceGetProperty( device, CFSTR( kIOHIDManufacturerKey ) );
        const char * str = NULL;
        if(propRef)
        {
            str = CFStringGetCStringPtr(propRef, kCFStringEncodingMacRoman);
            std::cout << str;
            std::cout << "\n";
            
            IOHIDDeviceScheduleWithRunLoop( device, CFRunLoopGetCurrent( ), kCFRunLoopDefaultMode );
            //IOHIDDeviceRegisterInputValueCallback(device, Handle_IOHIDDeviceInputValueCallback, NULL);
            CFIndex reportSize = (CFIndex) IOHIDDeviceGetProperty(device,CFSTR( kIOHIDMaxInputReportSizeKey));
            uint8_t *report = (uint8_t*)malloc( reportSize );
            IOHIDDeviceRegisterInputReportCallback( device, report, reportSize, Handle_IOHIDDeviceIOHIDReportCallback, context );
            
        }
    }
}

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

    ///using iohidmanager
    IOHIDManagerRef miw = IOHIDManagerCreate( kCFAllocatorDefault, kIOHIDOptionsTypeNone);
    
    
    if ( CFGetTypeID( miw ) == IOHIDManagerGetTypeID( ) ) 
    {
        IOHIDManagerSetDeviceMatching(miw, NULL);
        
        IOReturn success = IOHIDManagerOpen(miw, kIOHIDOptionsTypeNone);
        
        if(success == kIOReturnSuccess)
        {
            CFSetRef devicesSet = IOHIDManagerCopyDevices(miw);
            
            if(CFSetGetCount(devicesSet) > 0)
            {               
                CFSetApplyFunction(devicesSet, MyCallBack, NULL);
            }
            // CFRelease(devicesSet);
        }        
    }
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
