

#include "WINGsP.h"

#include <proplist.h>


_WINGsConfiguration WINGsConfiguration;



#define SYSTEM_FONT "-*-helvetica-medium-r-normal-*-%d-*-*-*-*-*-*-*,-*-*-medium-r-*-*-%d-*-*-*-*-*-*-*"

#define BOLD_SYSTEM_FONT "-*-helvetica-bold-r-normal-*-%d-*-*-*-*-*-*-*,-*-*-bold-r-*-*-%d-*-*-*-*-*-*-*"


static unsigned
getButtonWithName(const char *name, unsigned defaultButton)
{
    if (strncmp(name, "Button", 6)==0 && strlen(name)==7) {
        switch (name[6]) {
        case '1':
            return Button1;
        case '2':
            return Button2;
        case '3':
            return Button3;
        case '4':
            return Button4;
        case '5':
            return Button5;
        default:
            break;
        }
    }

    return defaultButton;
}


void
W_ReadConfigurations(void)
{
    WMUserDefaults *defaults;

    memset(&WINGsConfiguration, 0, sizeof(_WINGsConfiguration));

    defaults = WMGetStandardUserDefaults();

    if (defaults) {
        char *buttonName;
        unsigned button;

	WINGsConfiguration.systemFont = 
	    WMGetUDStringForKey(defaults, "SystemFont");

	WINGsConfiguration.boldSystemFont = 
	    WMGetUDStringForKey(defaults, "BoldSystemFont");

	WINGsConfiguration.useMultiByte =
	    WMGetUDBoolForKey(defaults, "MultiByteText");

	WINGsConfiguration.doubleClickDelay = 
	    WMGetUDIntegerForKey(defaults, "DoubleClickTime");	

        buttonName = WMGetUDStringForKey(defaults, "MouseWheelUp");
        if (buttonName) {
            button = getButtonWithName(buttonName, Button4);
            free(buttonName);
        } else {
            button = Button4;
        }
        WINGsConfiguration.mouseWheelUp = button;

        buttonName = WMGetUDStringForKey(defaults, "MouseWheelDown");
        if (buttonName) {
            button = getButtonWithName(buttonName, Button5);
            free(buttonName);
        } else {
            button = Button5;
        }
        WINGsConfiguration.mouseWheelDown = button;

        if (WINGsConfiguration.mouseWheelDown==WINGsConfiguration.mouseWheelUp) {
            WINGsConfiguration.mouseWheelUp = Button4;
            WINGsConfiguration.mouseWheelDown = Button5;
        }

	WINGsConfiguration.defaultFontSize = 
            WMGetUDIntegerForKey(defaults, "DefaultFontSize");
    }


    if (!WINGsConfiguration.systemFont) {
	WINGsConfiguration.systemFont = SYSTEM_FONT;
    }
    if (!WINGsConfiguration.boldSystemFont) {
	WINGsConfiguration.boldSystemFont = BOLD_SYSTEM_FONT;
    }
    if (WINGsConfiguration.doubleClickDelay == 0) {
	WINGsConfiguration.doubleClickDelay = 250;
    }
    if (WINGsConfiguration.mouseWheelUp == 0) {
	WINGsConfiguration.mouseWheelUp = Button4;
    }
    if (WINGsConfiguration.mouseWheelDown == 0) {
	WINGsConfiguration.mouseWheelDown = Button5;
    }
    if (WINGsConfiguration.defaultFontSize == 0) {
	WINGsConfiguration.defaultFontSize = 12;
    }

}

