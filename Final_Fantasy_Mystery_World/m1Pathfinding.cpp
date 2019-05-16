#include "p2Defs.h"
#include "p2Log.h"
#include "App.h"
#include "m1Pathfinding.h"
#include "m1Map.h"
#include "Brofiler/Brofiler.h"


m1PathFinding::m1PathFinding() : m1Module(), map(NULL), last_path(DEFAULT_PATH_LENGTH),width(0), height(0)
{
	name.assign("pathfinding");
}

// Destructor
m1PathFinding::~m1PathFinding()
{
	RELEASE_ARRAY(map);
}

// Called before quitting
bool m1PathFinding::CleanUp()
{
	LOG("Freeing pathfinding library");

	last_path.clear();
	RELEASE_ARRAY(map);
	return true;
}

// Sets up the walkability map
void m1PathFinding::SetMap(const uint& width, const uint& height, uchar* data)
{
	BROFILER_CATEGORY("PathFinding: SetMap", Profiler::Color::Brown);

	this->width = width;
	this->height = height;

	RELEASE_ARRAY(map);
	map = DBG_NEW uchar[width*height];
	memcpy(map, data, width*height);
	RELEASE(data);
	RELEASE_ARRAY(data);
}

// Utility: return true if pos is inside the map boundaries
bool m1PathFinding::CheckBoundaries(const iPoint& pos) const
{
	return (pos.x >= 0 && pos.x <= (int)width &&
			pos.y >= 0 && pos.y <= (int)height);
}

// Utility: returns true is the tile is walkable
bool m1PathFinding::IsWalkable(const iPoint& pos) const
{
	uchar t = GetTileAt(pos);
	return t != INVALID_WALK_CODE && t > 0;
}

// Utility: return the walkability value of a tile
uchar m1PathFinding::GetTileAt(const iPoint& pos) const
{
	if(CheckBoundaries(pos))
		return map[(pos.y*width) + pos.x];

	return INVALID_WALK_CODE;
}

// To request all tiles involved in the last generated path
iPoint m1PathFinding::GetLastPath() const
{
	if (!last_path.empty())
		return last_path[1];
	else
		return { 0,0 };
}

// PathList ------------------------------------------------------------------------
// Looks for a node in this list and returns it's list node or NULL
// ---------------------------------------------------------------------------------
const PathNode* PathList::Find(const iPoint& point) const
{
	std::list<PathNode>::const_iterator item = list.begin();
	while(item != list.end())
	{
		if ((*item).pos == point) {
			return &(*item);
		}
		
		++item;
	}
	return NULL;
}

// PathList ------------------------------------------------------------------------
// Returns the Pathnode with lowest score in this list or NULL if empty
// ---------------------------------------------------------------------------------
const PathNode* PathList::GetNodeLowestScore() const
{
	const PathNode* ret = NULL;
	int min = 65535;

	std::list<PathNode>::const_reverse_iterator item = list.rbegin();
	while(item != list.rend())
	{
		if((*item).Score() < min)
		{
			min = (*item).Score();
			ret = &(*item);
		}
		++item;
	}
	return ret;
}

// PathNode -------------------------------------------------------------------------
// Convenient constructors
// ----------------------------------------------------------------------------------
PathNode::PathNode() : g(-1), h(-1), pos(-1, -1), parent(NULL)
{}

PathNode::PathNode(int g, int h, const iPoint& pos, const PathNode* parent) : g(g), h(h), pos(pos), parent(parent)
{}

PathNode::PathNode(const PathNode& node) : g(node.g), h(node.h), pos(node.pos), parent(node.parent)
{}

// PathNode -------------------------------------------------------------------------
// Fills a list (PathList) of all valid adjacent pathnodes
// ----------------------------------------------------------------------------------
uint PathNode::FindWalkableAdjacents(PathList& list_to_fill) const
{
	iPoint cell;

	cell.create(pos.x - 1, pos.y - 1);
	if (App->map->IsWalkable(cell,false))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	// west
	cell.create(pos.x + 1, pos.y + 1);
	if (App->map->IsWalkable(cell, false))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	cell.create(pos.x - 1, pos.y + 1);
	if (App->map->IsWalkable(cell, false))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	cell.create(pos.x + 1, pos.y - 1);
	if (App->map->IsWalkable(cell, false))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	cell.create(pos.x - 1, pos.y);
	if (App->map->IsWalkable(cell, false))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	// west
	cell.create(pos.x + 1, pos.y);
	if (App->map->IsWalkable(cell, false))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	cell.create(pos.x, pos.y + 1);
	if (App->map->IsWalkable(cell, false))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	cell.create(pos.x, pos.y - 1);
	if (App->map->IsWalkable(cell, false))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	return list_to_fill.list.size();
}

uint PathNode::FindWalkableAdjacents(PathList & list_to_fill, const std::vector<iPoint>& no_walkables) const
{
	iPoint cell;

	cell.create(pos.x - 1, pos.y - 1);
	if (App->map->IsWalkable(cell, false) && (std::find(no_walkables.begin(), no_walkables.end(), cell) == no_walkables.end()))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	// west
	cell.create(pos.x + 1, pos.y + 1);
	if (App->map->IsWalkable(cell, false) && (std::find(no_walkables.begin(), no_walkables.end(), cell) == no_walkables.end()))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	cell.create(pos.x - 1, pos.y + 1);
	if (App->map->IsWalkable(cell, false) && (std::find(no_walkables.begin(), no_walkables.end(), cell) == no_walkables.end()))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	cell.create(pos.x + 1, pos.y - 1);
	if (App->map->IsWalkable(cell, false) && (std::find(no_walkables.begin(), no_walkables.end(), cell) == no_walkables.end()))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	cell.create(pos.x - 1, pos.y);
	if (App->map->IsWalkable(cell, false) && (std::find(no_walkables.begin(), no_walkables.end(), cell) == no_walkables.end()))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	// west
	cell.create(pos.x + 1, pos.y);
	if (App->map->IsWalkable(cell, false) && (std::find(no_walkables.begin(), no_walkables.end(), cell) == no_walkables.end()))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	cell.create(pos.x, pos.y + 1);
	if (App->map->IsWalkable(cell, false) && (std::find(no_walkables.begin(), no_walkables.end(), cell) == no_walkables.end()))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	cell.create(pos.x, pos.y - 1);
	if (App->map->IsWalkable(cell, false) && (std::find(no_walkables.begin(), no_walkables.end(), cell) == no_walkables.end()))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	return list_to_fill.list.size();
}

// PathNode -------------------------------------------------------------------------
// Calculates this tile score
// ----------------------------------------------------------------------------------
int PathNode::Score() const
{
	return g + h;
}

// PathNode -------------------------------------------------------------------------
// Calculate the F for a specific destination tile
// ----------------------------------------------------------------------------------
int PathNode::CalculateF(const iPoint& destination)
{
	g = parent->g + 1;
	h = pos.DistanceTo(destination);

	return g + h;
}

// ----------------------------------------------------------------------------------
// Actual A* algorithm: return number of steps in the creation of the path or -1 ----
// ----------------------------------------------------------------------------------
int m1PathFinding::CreatePath(const iPoint& origin, const iPoint& destination)
{
	BROFILER_CATEGORY("PathFinding", Profiler::Color::Brown);

	last_path.clear();

	if (!App->map->IsWalkable(origin,false) || !App->map->IsWalkable(destination,false))
		return -1;


	PathList open, close;
	PathNode ori(0, origin.DistanceNoSqrt(destination), origin, nullptr);
	open.list.push_back(ori);
	
	while (open.list.size() > 0) {

		PathNode* current_node = (PathNode*)open.GetNodeLowestScore();
		close.list.push_back(*current_node);

		std::list<PathNode>::iterator item = open.list.begin();
		while (item != open.list.end()) {

			if (&(*item) == &(*current_node))
				break;
			item++;
		}
		open.list.erase(item);

		if (close.list.back().pos == destination) {

			for (PathNode node = close.list.back(); node.parent != nullptr; node = *close.Find(node.parent->pos)) {

				last_path.push_back(node.pos);
			}

			last_path.push_back(close.list.front().pos);

			std::reverse(last_path.begin(), last_path.end());
			return 1;
		}
		else if (close.list.back().pos != destination) {

			PathList adjacents_nodes;
			close.list.back().FindWalkableAdjacents(adjacents_nodes);

			std::list<PathNode>::iterator item = adjacents_nodes.list.begin();

			while (item != adjacents_nodes.list.end()) {
				
				if (close.Find((*item).pos) != nullptr) {
					++item;
					continue;
				}
				(*item).CalculateF(destination);
				if (open.Find((*item).pos) != nullptr) {

					PathNode n = *open.Find((*item).pos);
					if ((*item).g < n.g)
						n.parent = (*item).parent;
				}
				else {
					open.list.push_back(*item);
				}
				++item;
			}
		}
	}

	last_path.clear();
	return -1;
}

int m1PathFinding::RecalculatePath(const iPoint & origin, const iPoint & destination, const std::vector<iPoint>& no_walkables)
{
	BROFILER_CATEGORY("RecalculatePathFinding", Profiler::Color::Brown);

	last_path.clear();

	if (!App->map->IsWalkable(origin, false) || !App->map->IsWalkable(destination, false))
		return -1;

	PathList open, close;
	PathNode ori(0, origin.DistanceNoSqrt(destination), origin, nullptr);
	open.list.push_back(ori);

	while (open.list.size() > 0) {

		PathNode* current_node = (PathNode*)open.GetNodeLowestScore();
		close.list.push_back(*current_node);

		std::list<PathNode>::iterator item = open.list.begin();
		while (item != open.list.end()) {

			if (&(*item) == &(*current_node))
				break;
			item++;
		}
		open.list.erase(item);

		if (close.list.back().pos == destination) {

			for (PathNode node = close.list.back(); node.parent != nullptr; node = *close.Find(node.parent->pos)) {

				last_path.push_back(node.pos);
			}

			last_path.push_back(close.list.front().pos);

			std::reverse(last_path.begin(), last_path.end());
			return 1;
		}
		else if (close.list.back().pos != destination) {

			PathList adjacents_nodes;
			close.list.back().FindWalkableAdjacents(adjacents_nodes, no_walkables);

			std::list<PathNode>::iterator item = adjacents_nodes.list.begin();

			while (item != adjacents_nodes.list.end()) {

				if (close.Find((*item).pos) != nullptr) {
					++item;
					continue;
				}
				(*item).CalculateF(destination);
				if (open.Find((*item).pos) != nullptr) {

					PathNode n = *open.Find((*item).pos);
					if ((*item).g < n.g)
						n.parent = (*item).parent;
				}
				else {
					open.list.push_back(*item);
				}
				++item;
			}
		}
	}
	last_path.clear();
	return -1;
}
