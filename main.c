#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include <mach/mach_port.h>
#include <mach/mach_interface.h>
#include <mach/mach_init.h>

#include <IOKit/pwr_mgt/IOPMLib.h>
#include <IOKit/IOMessage.h>

io_connect_t  root_port;

void
sleepCb(void * refCon, io_service_t service, natural_t messageType, void * messageArgument)
{
    switch (messageType)
    {
            
        case kIOMessageCanSystemSleep:
        case kIOMessageSystemWillSleep:
            system("osascript -e \"set Volume 0\"\n");
            IOAllowPowerChange(root_port, (long)messageArgument);
        default:
            break;
    }
}


int main(int argc, char **argv)
{
    IONotificationPortRef  notifyPortRef;
    io_object_t            notifierObject;
    void*                  refCon;
    
    root_port = IORegisterForSystemPower(refCon, &notifyPortRef, sleepCb, &notifierObject);
    if (root_port == 0)
    {
        printf("IORegisterForSystemPower failed\n");
        return 1;
    }
    
    CFRunLoopAddSource(CFRunLoopGetCurrent(),
                       IONotificationPortGetRunLoopSource(notifyPortRef), kCFRunLoopCommonModes);
    
    CFRunLoopRun();
    
    return (0);
}
