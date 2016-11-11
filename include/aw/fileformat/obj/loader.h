/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_fileformat_obj_loader_h
#define aw_fileformat_obj_loader_h
#include <aw/io/input_stream.h>
#include <string>
#include <vector>
namespace aw {
namespace obj {

struct vert {
	double points[3];
	double& operator[](unsigned index)
	{
		return points[index];
	}
};

struct face_vert {
	unsigned index;
	unsigned normal  = 0;
	unsigned texuv   = 0;
};

struct face {
	face_vert verts[3];
	unsigned smooth  = 0;
};

struct submesh {
	std::string name;
	std::string material;
	std::vector<face> faces;
};

struct mesh {
	static mesh parse( io::input_stream& is );
	std::vector<std::string> matlibs;
	std::vector<vert> verts;
	std::vector<vert> normals;
	std::vector<vert> texverts;
	std::vector<submesh> meshes;
};


} // namespace obj
} // namespace aw
#endif//aw_fileformat_obj_loader_h
