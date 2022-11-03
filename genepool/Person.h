#ifndef PERSON_H
#define PERSON_H

#include "Enums.h"

#include <set>
#include <string>

using namespace std;

// This is the Person class you need to implement.
// It has many member functions that perform relationship queries.
// Add any member variables you need to support this.
// Implement the member functions in Person.cpp.

class Person
{
  string strName;
  Gender gen;
  Person *mom;
  Person *dad;

  // Helper Functions

public:
  Person(string identity, string sex, Person *mother, Person *father);
  ~Person();
  set<Person *> child;

  // Required Getter Functions
  const std::string &name() const;
  Gender gender() const;
  Person *mother();
  Person *father();

  // Required Relationship Functions
  std::set<Person *> ancestors(PMod pmod = PMod::ANY);
  std::set<Person *> aunts(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person *> brothers(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person *> children();
  std::set<Person *> cousins(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person *> daughters();
  std::set<Person *> descendants();
  std::set<Person *> grandchildren();
  std::set<Person *> granddaughters();
  std::set<Person *> grandfathers(PMod pmod = PMod::ANY);
  std::set<Person *> grandmothers(PMod pmod = PMod::ANY);
  std::set<Person *> grandparents(PMod pmod = PMod::ANY);
  std::set<Person *> grandsons();
  std::set<Person *> nephews(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person *> nieces(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person *> parents(PMod pmod = PMod::ANY);
  std::set<Person *> siblings(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person *> sisters(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person *> sons();
  std::set<Person *> uncles(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);

  // Other Member Functions
};

#endif
