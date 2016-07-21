#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
        
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    register_all_packages();
    
    auto screenSize = glview->getFrameSize();
    auto fileUtils = FileUtils::getInstance();
    std::vector<std::string> searchPaths;
    
    if (screenSize.width >= 2208 || screenSize.height >= 2208)
    {
        director -> setContentScaleFactor( 2208.0f / screenSize.height );
        glview -> setDesignResolutionSize( screenSize.width, screenSize.height, ResolutionPolicy::NO_BORDER );
        searchPaths.push_back("iphone6plus");
        searchPaths.push_back("ipadhd");
        searchPaths.push_back("iphone6");
        searchPaths.push_back("ipadsd");
        searchPaths.push_back("iphone5");
        searchPaths.push_back("iphonehd");
        searchPaths.push_back("iphonesd");
    }
    //Ipad HD
    else if ( screenSize.width >= 2048 || screenSize.height >= 2048 )
    {
        director -> setContentScaleFactor( 2048.0f / screenSize.height );
        glview -> setDesignResolutionSize( screenSize.width, screenSize.height, ResolutionPolicy::NO_BORDER);
        searchPaths.push_back("ipadhd");
        searchPaths.push_back("iphone6");
        searchPaths.push_back("ipadsd");
        searchPaths.push_back("iphone5");
        searchPaths.push_back("iphonehd");
        searchPaths.push_back("iphonesd");
    }
    //Iphone 6
    else if ( screenSize.width >= 1334 || screenSize.height >= 1334 )
    {
        director -> setContentScaleFactor( 1334.0f / screenSize.height );
       
        glview -> setDesignResolutionSize( screenSize.width, screenSize.height, ResolutionPolicy::NO_BORDER);
        searchPaths.push_back("iphone6");
        searchPaths.push_back("ipadsd");
        searchPaths.push_back("iphone5");
        searchPaths.push_back("iphonehd");
        searchPaths.push_back("iphonesd");
    }
    else if (screenSize.width >= 1024 || screenSize.height >= 1024)
    {
        director -> setContentScaleFactor( 1024.0f / screenSize.height );
       
        glview -> setDesignResolutionSize( screenSize.width, screenSize.height, ResolutionPolicy::NO_BORDER );
        searchPaths.push_back("ipadsd");
        searchPaths.push_back("iphone5");
        searchPaths.push_back("iphonehd");
        searchPaths.push_back("iphonesd");
    }
    else if (screenSize.width >= 1136 || screenSize.height >= 1136)
    {
        director -> setContentScaleFactor( 1136.0f / screenSize.height );
       
        glview -> setDesignResolutionSize( screenSize.width, screenSize.height, ResolutionPolicy::NO_BORDER );
        searchPaths.push_back("iphone5");
        searchPaths.push_back("iphonehd");
        searchPaths.push_back("iphonesd");
    }
    else if (screenSize.width >= 960 || screenSize.height >= 960)
    {
        director -> setContentScaleFactor( 960.0f / screenSize.height );
               glview -> setDesignResolutionSize( screenSize.width, screenSize.height, ResolutionPolicy::NO_BORDER );
        searchPaths.push_back("iphonehd");
        searchPaths.push_back("iphonesd");
    }
    else
    {
        director -> setContentScaleFactor( 480.0f / screenSize.height );
        
        searchPaths.push_back("iphonesd");
        glview -> setDesignResolutionSize( screenSize.width, screenSize.height, ResolutionPolicy::NO_BORDER );
    }
    fileUtils->setSearchPaths(searchPaths);

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
