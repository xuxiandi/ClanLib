/*
**  ClanLib SDK
**  Copyright (c) 1997-2013 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
*/

#include "Scene3D/precomp.h"
#include "oct_tree.h"

namespace clan
{


OctTree::OctTree()
: aabb(Vec3f(-300.0f), Vec3f(300.0f)), root(new OctTreeNode()), frame(0)
{
}

OctTree::OctTree(const AxisAlignedBoundingBox &aabb)
: aabb(aabb), root(new OctTreeNode()), frame(0)
{
}

OctTree::~OctTree()
{
	delete root;
}

SceneCullProxy *OctTree::create_proxy(SceneItem *object, const AxisAlignedBoundingBox &box)
{
	OctTreeObject *tree_object = new OctTreeObject(object, box);
	root->insert(tree_object, aabb);
	return tree_object;
}

void OctTree::delete_proxy(SceneCullProxy *proxy)
{
	OctTreeObject *tree_object = static_cast<OctTreeObject*>(proxy);
	root->remove(tree_object, aabb);
	tree_object->release();
}

void OctTree::set_aabb(SceneCullProxy *proxy, const AxisAlignedBoundingBox &box)
{
	OctTreeObject *tree_object = static_cast<OctTreeObject*>(proxy);
	root->remove(tree_object, aabb);
	tree_object->box = box;
	root->insert(tree_object, aabb);
}

AxisAlignedBoundingBox OctTree::get_aabb(SceneCullProxy *proxy)
{
	OctTreeObject *tree_object = static_cast<OctTreeObject*>(proxy);
	return tree_object->box;
}

std::vector<SceneItem *> OctTree::cull(const FrustumPlanes &frustum)
{
	std::vector<SceneItem *> pvs;
	root->cull(frame++, frustum, aabb, pvs);
	return pvs;
}

std::vector<SceneItem *> OctTree::cull(const Vec3f &point)
{
	std::vector<SceneItem *> pvs;
	root->cull(frame++, point, aabb, pvs);
	return pvs;
}

}

