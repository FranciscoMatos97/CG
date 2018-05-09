#ifndef PROJETO_MATERIAL_H__
#define PROJETO_MATERIAL_H__

class Material{

    Float diffuse[4], ambient[4], diffuseANDambient[4], specular[4], emission[4], shininess;

	public:
		Material::Material(Float*, Float*, Float*, Float*, Float*, float);
		void Material::draw();
};

#endif
