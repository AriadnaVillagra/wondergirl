#include "Application.h"

int main()
{
    Application WonderGirl = Application();
    if (!WonderGirl.Init())
        return 1;
    
    WonderGirl.Run();    
    return WonderGirl.Shutdown();
}
