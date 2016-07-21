#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);
    //FileUtils对象获得 --单列
    FileUtils *fUtils = FileUtils::getInstance();
    
    
    //--------------添加搜索路径
    //创建vector
    
    std::vector<std::string> _searchPath;
    //创建文件名字 string
    std::string dirString = "test";
    _searchPath.push_back(dirString);
    //添加到搜索路径
    fUtils->setSearchPaths(_searchPath);
    
    
    //---------------写入文件
    //获得可写路径
    std::string writePath = fUtils->getWritablePath();
    //文件名称
    std::string fileName = writePath+"text.txt";
    //存储写入字符
    char buf[100] = "Cocos2D-x";
    //创建FILE
    FILE *file = fopen(fileName.c_str(), "wb");
    if (file) {
        //如果创建成功
        //写入文件
        size_t st = fwrite(buf, 1, strlen(buf), file);//写入的字符，开始位置，长度
        
        if (st != 0) {
            //写入成功
            log("successful");
        }else{
            //失败
            log("faild");
        }
        //关闭文件
        fclose(file);
        
    }
    //---------------文件是否存在
    bool isExist = fUtils->isFileExist("res/HelloWorld.png");
    
    if (isExist) {
        log("file is exist");
    }else{
        log("file is not exist");
    }
    
    //-------文件夹是否存在
    
    
    isExist = fUtils->isDirectoryExist(fUtils->fullPathForFilename("res"));
    
    if (isExist) {
        log("diretory is exist");
    }else{
        log("diretory is not exist");
    }
    
    //---------创建文件夹
    //文件夹路径
    std::string dirPath = writePath +"_test";
    bool success = fUtils->createDirectory(dirPath);
    
    if (success) {
        log("创建成功");
    }else{
        log("创建失败");
    }
    
    return true;
}
