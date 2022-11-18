#include "StarMap.h"
#include <sstream>
#include <string>
#include <cmath>
#include "Helpers.h"

using namespace std;

StarMap *StarMap::create(std::istream &stream)
{
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new StarMap(stream);
}

StarMap::StarMap(std::istream &stream)
{
  double starId = 0;
  std::string line;
  while (std::getline(stream, line))
  {
    string coord;
    istringstream myExp(line);
    getline(myExp, coord, '\t');
    xCord = stof(coord);
    getline(myExp, coord, '\t');
    yCord = stof(coord);
    getline(myExp, coord, '\t');
    zCord = stof(coord);
    starId++;
    Star newStar;
    newStar.x = xCord;
    newStar.y = yCord;
    newStar.z = zCord;
    newStar.id = starId;
    tree.root = tree.insert(newStar);
  }
}

StarMap::~StarMap()
{
  starVec.clear();
}

std::vector<Star> StarMap::find(size_t n, float x, float y, float z)
{
  findHelp(x, y, z, tree.root, 0, n);
  while (heap.size() > 0)
  {
    starVec.push_back(heap.top()->star);
    heap.pop();
  }
  return starVec;
}

void StarMap::findHelp(float x1, float y1, float z1, KD_tree::Node *kdRoot, int depth, size_t size)
{
  if (kdRoot == nullptr)
  {
    return;
  }
  kdRoot->dist = sqrt(sqrt(pow(kdRoot->star.x - x1, 2)) + sqrt(pow(kdRoot->star.y - y1, 2)) + sqrt(pow(kdRoot->star.z - z1, 2)));
  if (heap.size() < size)
  {
    heap.push(kdRoot);
  }
  else
  {
    heap.pop();
    heap.push(kdRoot);
  }
  int cd = depth % 3;
  float comp;
  float target;
  if (cd == 0)
  {
    comp = kdRoot->star.x;
    target = x1;
  }
  else if (cd == 1)
  {
    comp = kdRoot->star.y;
    target = y1;
  }
  else
  {
    comp = kdRoot->star.z;
    target = z1;
  }
  if (target < comp)
  {
    findHelp(x1, y1, z1, kdRoot->left, depth + 1, size);
  }
  else
  {
    findHelp(x1, y1, z1, kdRoot->right, depth + 1, size);
  }
  if (depth == 0)
  {
    if (abs(kdRoot->star.x - x1) < heap.top()->dist)
    {
      if (x1 < kdRoot->star.x)
      {
        findHelp(x1, y1, z1, kdRoot->right, depth + 1, size);
      }
      else
      {
        findHelp(x1, y1, z1, kdRoot->left, depth + 1, size);
      }
    }
  }
  else if (depth == 1)
  {
    if (abs(kdRoot->star.y - y1) < heap.top()->dist)
    {
      if (y1 < kdRoot->star.y)
      {
        findHelp(x1, y1, z1, kdRoot->right, depth + 1, size);
      }
      else
      {
        findHelp(x1, y1, z1, kdRoot->left, depth + 1, size);
      }
    }
  }
  else
  {
    if (abs(kdRoot->star.z - z1) < heap.top()->dist)
    {
      if (z1 < kdRoot->star.z)
      {
        findHelp(x1, y1, z1, kdRoot->right, depth + 1, size);
      }
      else
      {
        findHelp(x1, y1, z1, kdRoot->left, depth + 1, size);
      }
    }
  }
}