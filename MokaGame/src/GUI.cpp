#include "GUI.h"

GUI::GUI()
{
    myRenderer = &CEGUI::OpenGLRenderer::create();
    CEGUI::System::create( *myRenderer );
    CEGUI::GUIContext(*myRenderer);

        // initialise the required dirs for the DefaultResourceProvider
    rp = static_cast<CEGUI::DefaultResourceProvider*>
        (CEGUI::System::getSingleton().getResourceProvider());
    rp->setResourceGroupDirectory("schemes", "data/gui/schemes/");
    rp->setResourceGroupDirectory("imagesets", "data/gui/imagesets/");
    rp->setResourceGroupDirectory("fonts", "data/gui/fonts/");
    rp->setResourceGroupDirectory("layouts", "data/gui/layouts/");
    rp->setResourceGroupDirectory("looknfeels", "data/gui/looknfeel/");
    rp->setResourceGroupDirectory("lua_scripts", "data/gui/lua_scripts/");
    // This is only really needed if you are using Xerces and need to
    // specify the schemas location
    rp->setResourceGroupDirectory("schemas", "data/gui/xml_schemas/");

    CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
    CEGUI::Font::setDefaultResourceGroup("fonts");
    CEGUI::Scheme::setDefaultResourceGroup("schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
    CEGUI::WindowManager::setDefaultResourceGroup("layouts");
    CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

    CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
    if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
        parser->setProperty("SchemaDefaultResourceGroup", "schemas");

        CEGUI::SchemeManager::getSingleton().createFromFile( "TaharezLook.scheme" );
        CEGUI::System::getSingleton().getDefaultGUIContext().
        setDefaultTooltipType( "TaharezLook/Tooltip" );

}

GUI::~GUI()
{}

int GUI::init()
{

}

int GUI::createTest()
{
   using namespace CEGUI;
    WindowManager& wmgr = WindowManager::getSingleton();
    Window* myRoot = wmgr.createWindow( "DefaultWindow", "root" );
    System::getSingleton().getDefaultGUIContext().setRootWindow( myRoot );
    FrameWindow* fWnd = static_cast<FrameWindow*>(
    wmgr.createWindow( "TaharezLook/FrameWindow", "testWindow" ));
    myRoot->addChild( fWnd );

    // position a quarter of the way in from the top-left of parent.
    fWnd->setPosition( UVector2( UDim( 0.6f, 0.0f ), UDim( 0.6f, 0.0f ) ) );
    // set size to be half the size of the parent
    fWnd->setSize( USize( UDim( 0.3f, 0.0f ), UDim( 0.2f, 0.0f ) ) );
    fWnd->setText( "Panel Zajebistosci " );
  //  fWnd->setProperty("Image","full_image");

}

void GUI::renderTest()
{

}
    //dtor

