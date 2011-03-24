/* eos - A reimplementation of BioWare's Aurora engine
 * Copyright (c) 2010-2011 Sven Hesse (DrMcCoy), Matthew Hoops (clone2727)
 *
 * The Infinity, Aurora, Odyssey and Eclipse engines, Copyright (c) BioWare corp.
 * The Electron engine, Copyright (c) Obsidian Entertainment and BioWare corp.
 *
 * This file is part of eos and is distributed under the terms of
 * the GNU General Public Licence. See COPYING for more informations.
 */

/** @file graphics/aurora/modelnode.h
 *  A node within a 3D model.
 */

#ifndef GRAPHICS_AURORA_MODELNODE_H
#define GRAPHICS_AURORA_MODELNODE_H

#include "common/ustring.h"
#include "common/transmatrix.h"
#include "common/boundingbox.h"

#include "graphics/types.h"
#include "graphics/listcontainer.h"

#include "graphics/aurora/types.h"
#include "graphics/aurora/textureman.h"

namespace Graphics {

namespace Aurora {

class Model;

class ModelNode : public ListContainer {
public:
	ModelNode(Model &model);
	~ModelNode();

	/** Get the node's name. */
	const Common::UString &getName() const;

	float getWidth () const; ///< Get the width of the node's bounding box.
	float getHeight() const; ///< Get the height of the node's bounding box.
	float getDepth () const; ///< Get the depth of the node's bounding box.

	/** Should the node never be rendered at all? */
	void setInvisible(bool invisible);


	// Positioning

	/** Get the position of the node. */
	void getPosition(float &x, float &y, float &z) const;
	/** Get the rotation of the node. */
	void getRotation(float &x, float &y, float &z) const;
	/** Get the orientation of the node. */
	void getOrientation(float &x, float &y, float &z, float &a) const;

	/** Get the position of the node after translate/rotate. */
	void getAbsolutePosition(float &x, float &y, float &z) const;

	/** Set the position of the node. */
	void setPosition(float x, float y, float z);
	/** Set the rotation of the node. */
	void setRotation(float x, float y, float z);

	/** Move the node, relative to its current position. */
	void move  (float x, float y, float z);
	/** Rotate the node, relative to its current rotation. */
	void rotate(float x, float y, float z);


	// Renderable
	void render(RenderPass pass);

	// ListContainer
	void doRebuild();
	void doDestroy();


protected:
	Model *_model; ///< The model this node belongs to.

	ModelNode *_parent;               ///< The node's parent.
	std::list<ModelNode *> _children; ///< The node's children.

	uint32 _level;

	Common::UString _name; ///< The node's name.

	uint32 _faceCount; ///< Number of faces

	float *_coords; ///< Coordinates pool.

	// Vertex coordinates
	float *_vX; ///< Vertex coordinates, X.
	float *_vY; ///< Vertex coordinates, Y.
	float *_vZ; ///< Vertex coordinates, Z.

	// Texture cordinates
	float *_tX; ///< Texture cordinates, X.
	float *_tY; ///< Texture cordinates, Y.

	uint32 *_smoothGroups; ///< Face smooth groups.
	uint32 *_material;     ///< Face materials.

	float _center     [3]; ///< The node's center.
	float _position   [3]; ///< Position of the node.
	float _rotation   [3]; ///< Node rotation.
	float _orientation[4]; ///< Orientation of the node.

	/** Position of the node after translate/rotate. */
	Common::TransformationMatrix _absolutePosition;

	float _wirecolor[3]; ///< Color of the wireframe.
	float _ambient  [3]; ///< Ambient color.
	float _diffuse  [3]; ///< Diffuse color.
	float _specular [3]; ///< Specular color.
	float _selfIllum[3]; ///< Self illumination color.
	float _shininess;    ///< Shiny?

	std::vector<TextureHandle> _textures; ///< Textures.

	bool _isTransparent;

	bool _dangly; ///< Is the node mesh's dangly?

	float _period;
	float _tightness;
	float _displacement;

	bool _showdispl;
	int  _displtype;

	float *_constraints;

	int _tilefade;

	float _scale;

	bool _render; ///< Render the node?
	bool _shadow; ///< Does the node have a shadow?

	bool _beaming;
	bool _inheritcolor;
	bool _rotatetexture;

	float _alpha;

	bool _hasTransparencyHint;
	bool _transparencyHint;

	Common::BoundingBox _boundBox;
	Common::BoundingBox _absoluteBoundBox;

	ListID _list; ///< OpenGL display list for the node.


	// Loading helpers
	void loadTextures(const std::vector<Common::UString> &textures);
	bool createFaces(uint32 count);
	void createBound();
	void createCenter();


private:
	const Common::BoundingBox &getAbsoluteBound() const;

	void createAbsoluteBound(Common::BoundingBox parentPosition);

	void orderChildren();


public:
	// General helpers

	ModelNode *getParent();             ///< Get the node's parent.
	const ModelNode *getParent() const; ///< Get the node's parent.

	void setParent(ModelNode *parent); ///< Set the node's parent.

	/** Is this node in front of that other node? */
	bool isInFrontOf(const ModelNode &node) const;

	void inheritPosition(ModelNode &node) const;
	void inheritOrientation(ModelNode &node) const;
	void inheritGeometry(ModelNode &node) const;


	friend class Model;
};

} // End of namespace Aurora

} // End of namespace Graphics

#endif // GRAPHICS_AURORA_MODELNODE_H
