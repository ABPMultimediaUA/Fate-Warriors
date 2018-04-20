
#ifndef GUI_H_
#define GUI_H_


class GUI{
public:
    
   GUI(/*IrrlichtDevice* _i_device*/);
   ~GUI();
   void set_text_vida(int _i_vida);
   void draw();

private:
/*
      IGUIStaticText* _text;
      IGUIEnvironment* _guienv;
      IGUISkin* _skin;
      IGUIFont* _font;
      */
};

#endif /* GUI_H_ */
