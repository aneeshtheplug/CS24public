#include "StarMap.h"
#include <sstream>
#include <string>
#include <cmath>

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
    starVec.push_back(newStar);
  }
}

StarMap::~StarMap()
{
  starVec.clear();
}

float StarMap::distanceHelp(Star str, float x1, float y1, float z1)
{
  float distance = sqrt(sqrt(pow(str.x - x1, 2)) + sqrt(pow(str.y - y1, 2)) + sqrt(pow(str.z - z1, 2)));
  return distance;
}

void StarMap::pushSpace(std::vector<Star> &close, Star add, float dist, float x, float y, float z)
{
  if (close.size() == 0)
  {
    close.push_back(add);
  }
  else
  {
    int insert = 0;
    for (int id = 0; id < int(close.size()); id++)
    {
      Star test = close[id];
      float starDist = distanceHelp(test, x, y, z);
      if (dist < starDist)
      {
        close.insert(close.begin() + id, add);
        insert++;
        break;
      }
    }
    if (insert == 0)
    {
      close.insert(close.begin() + int(close.size()), add);
    }
  }
}

void StarMap::pushFull(std::vector<Star> &close, Star add, float dist, float x, float y, float z)
{
  int insert = 0;
  if (dist < distanceHelp(close[0], x, y, z))
  {
    close.insert(close.begin() + 0, add);
    insert++;
  }
  else
  {
    for (int id = 0; id < int(close.size() - 1); id++)
    {
      Star test1 = close[id];
      Star test2 = close[id + 1];
      float starDist1 = distanceHelp(test1, x, y, z);
      float starDist2 = distanceHelp(test2, x, y, z);
      if (dist > starDist1 && dist <= starDist2)
      {
        close.insert(close.begin() + (id + 1), add);
        insert++;
        break;
      }
    }
  }
  if (insert == 0)
  {
    Star test = close[int(close.size() - 1)];
    float starDist = distanceHelp(test, x, y, z);
    if (dist < starDist)
    {
      close.insert(close.begin() + int(close.size() - 1), add);
      insert++;
      close.pop_back();
    }
  }
  else
  {
    close.pop_back();
  }
}

std::vector<Star> StarMap::find(size_t n, float x, float y, float z)
{
  vector<Star> closest;
  auto itr = starVec.begin();
  while (itr != starVec.end())
  {
    float distance;
    distance = sqrt(sqrt(pow(itr->x - x, 2)) + sqrt(pow(itr->y - y, 2)) + sqrt(pow(itr->z - z, 2)));
    if (closest.size() < n)
    {
      pushSpace(closest, *itr, distance, x, y, z);
    }
    else
    {
      pushFull(closest, *itr, distance, x, y, z);
    }
    itr++;
  }
  return closest;
}
