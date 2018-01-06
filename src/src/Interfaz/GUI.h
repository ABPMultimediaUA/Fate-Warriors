#include "irrlicht/irrlicht.h"



using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class GUI{
public:
    
   GUI(IrrlichtDevice* _i_device);
   ~GUI();
   void set_text_vida(int _i_vida);
   void draw();

private:
      IGUIStaticText* _text;
      IGUIEnvironment* _guienv;
};

