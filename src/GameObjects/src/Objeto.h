#ifndef HEADERS_OBJETO_H_
#define HEADERS_OBJETO_H_

enum NombreObjetos{

};




class Objeto {
public:

	Objeto(short id, float _i_x, float _i_y, float _i_z);
	virtual ~Objeto();

	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool usar() = 0;


	void setPosition(float _i_x, float _i_y, float _i_z);

	float getX();
	float getY();
	float get_widht();
	float get_height();

protected:
	short _id;
	float _objeto_x;
	float _objeto_y;
	float _objeto_z;
	float _objeto_ancho;
	float _objeto_alto;

};

#endif /* HEADERS_OBJETO_H_ */