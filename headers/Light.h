#ifndef PROJETO_LIGHT_H__
#define PROJETO_LIGHT_H__

class Light{

    int isPoint;
    Point* point;

	public:
		Light::Light(int, Point*);
        void Light::draw();
};

#endif
