#include "Person.h"
#include <string>
// Person Member Functions

using namespace std;
Person::Person(string identity, string sex, Person *mother, Person *father)
{
    strName = identity;
    if (sex == "male")
    {
        gen = Gender::MALE;
    }
    else
    {
        gen = Gender::FEMALE;
    }
    mom = mother;
    dad = father;
}

Person::~Person()
{
}

const string &Person::name() const
{
    return strName;
}

Gender Person::gender() const
{
    return gen;
}

Person *Person::mother()
{
    return mom;
}

Person *Person::father()
{
    return dad;
}

set<Person *> Person::children()
{
    return child;
}

set<Person *> Person::daughters()
{
    set<Person *> daughter;
    for (Person *ch : child)
    {
        if (ch->gender() == Gender::FEMALE)
        {
            daughter.insert(ch);
        }
    }
    return daughter;
}

set<Person *> Person::sons()
{
    set<Person *> son;
    for (Person *ch : child)
    {
        if (ch->gender() == Gender::MALE)
        {
            son.insert(ch);
        }
    }
    return son;
}

set<Person *> Person::grandchildren()
{
    set<Person *> grand;
    for (Person *ch : child)
    {
        for (Person *grandkid : ch->child)
        {
            grand.insert(grandkid);
        }
    }
    return grand;
}

set<Person *> Person::granddaughters()
{
    set<Person *> grandDaughter;
    for (Person *grand : grandchildren())
    {
        if (grand->gender() == Gender::FEMALE)
        {
            grandDaughter.insert(grand);
        }
    }
    return grandDaughter;
}

set<Person *> Person::grandsons()
{
    set<Person *> grandSon;
    for (Person *grand : grandchildren())
    {
        if (grand->gender() == Gender::MALE)
        {
            grandSon.insert(grand);
        }
    }
    return grandSon;
}

std::set<Person *> Person::parents(PMod pmod)
{
    set<Person *> parent;
    if (pmod == PMod::MATERNAL)
    {
        if (mom != nullptr)
        {
            parent.insert(mom);
        }
    }
    else if (pmod == PMod::PATERNAL)
    {
        if (dad != nullptr)
        {
            parent.insert(dad);
        }
    }
    else
    {
        if (mom != nullptr)
        {
            parent.insert(mom);
        }
        if (dad != nullptr)
        {
            parent.insert(dad);
        }
    }
    return parent;
}

std::set<Person *> Person::grandparents(PMod pmod)
{
    set<Person *> grandparent;
    set<Person *> iterate = parents(pmod);

    for (Person *old : iterate)
    {
        for (Person *ch : old->parents(PMod::ANY))
        {
            if (old != nullptr)
            {
                grandparent.insert(ch);
            }
        }
    }
    return grandparent;
}

std::set<Person *> Person::grandfathers(PMod pmod)
{
    set<Person *> grandfather;
    set<Person *> iterate = grandparents(pmod);

    for (Person *gp : iterate)
    {
        if (gp->gender() == Gender::MALE)
        {
            grandfather.insert(gp);
        }
    }
    return grandfather;
}

std::set<Person *> Person::grandmothers(PMod pmod)
{
    set<Person *> grandmother;
    set<Person *> iterate = grandparents(pmod);

    for (Person *gp : iterate)
    {
        if (gp->gender() == Gender::FEMALE)
        {
            grandmother.insert(gp);
        }
    }
    return grandmother;
}

std::set<Person *> Person::siblings(PMod pmod, SMod smod)
{
    set<Person *> sibling;
    set<Person *> iterate = parents(pmod);
    for (Person *par : iterate)
    {
        if (smod == SMod::FULL)
        {
            for (Person *per : par->child)
            {
                if (per->dad == dad && per->mom == mom && mom != nullptr && dad != nullptr)
                {
                    if (per->strName != strName)
                    {
                        sibling.insert(per);
                    }
                }
            }
        }
        else if (smod == SMod::HALF)
        {
            for (Person *per : par->child)
            {
                if (per->dad == dad && per->mom != mom)
                {
                    sibling.insert(per);
                }
                else if (per->dad != dad && per->mom == mom)
                {
                    sibling.insert(per);
                }
            }
        }
        else
        {
            for (Person *per : par->child)
            {
                if (per->strName != strName)
                {
                    sibling.insert(per);
                }
            }
        }
    }
    return sibling;
}

std::set<Person *> Person::brothers(PMod pmod, SMod smod)
{
    set<Person *> brother;
    set<Person *> iterate = siblings(pmod, smod);
    for (Person *per : iterate)
    {
        if (per->gender() == Gender::MALE)
        {
            brother.insert(per);
        }
    }
    return brother;
}

std::set<Person *> Person::sisters(PMod pmod, SMod smod)
{
    set<Person *> sister;
    set<Person *> iterate = siblings(pmod, smod);
    for (Person *per : iterate)
    {
        if (per->gender() == Gender::FEMALE)
        {
            sister.insert(per);
        }
    }
    return sister;
}

std::set<Person *> Person::nieces(PMod pmod, SMod smod)
{
    set<Person *> niece;
    set<Person *> iterate = siblings(pmod, smod);
    for (Person *per : iterate)
    {
        for (Person *ni : per->child)
        {
            if (ni->gender() == Gender::FEMALE)
            {
                niece.insert(ni);
            }
        }
    }
    return niece;
}

std::set<Person *> Person::nephews(PMod pmod, SMod smod)
{
    set<Person *> nephew;
    set<Person *> iterate = siblings(pmod, smod);
    for (Person *per : iterate)
    {
        for (Person *ni : per->child)
        {
            if (ni->gender() == Gender::MALE)
            {
                nephew.insert(ni);
            }
        }
    }
    return nephew;
}

std::set<Person *> Person::aunts(PMod pmod, SMod smod)
{
    set<Person *> aunt;
    set<Person *> iterate = parents(pmod);
    for (Person *per : iterate)
    {
        for (Person *au : per->sisters(PMod::ANY, smod))
        {
            aunt.insert(au);
        }
    }
    return aunt;
}

std::set<Person *> Person::uncles(PMod pmod, SMod smod)
{
    set<Person *> uncle;
    set<Person *> iterate = parents(pmod);
    for (Person *per : iterate)
    {
        for (Person *au : per->brothers(PMod::ANY, smod))
        {
            uncle.insert(au);
        }
    }
    return uncle;
}

std::set<Person *> Person::cousins(PMod pmod, SMod smod)
{
    set<Person *> cousin;
    set<Person *> iterate = parents(pmod);
    for (Person *per : iterate)
    {
        for (Person *sib : per->siblings(PMod::ANY, smod))
        {
            for (Person *cous : sib->child)
            {
                cousin.insert(cous);
            }
        }
    }
    return cousin;
}

std::set<Person *> ancestorHelp(Person *par)
{
    set<Person *> ancestor;
    if (par == nullptr)
    {
        return ancestor;
    }
    else
    {
        ancestor.insert(par);
    }
    return ancestor;
}
std::set<Person *> Person::ancestors(PMod pmod)
{
    set<Person *> ancestor;
    set<Person *> iterate = parents(pmod);
    for (Person *per : iterate)
    {
        ancestor.merge(per->ancestors());
    }
    ancestor.merge(iterate);
    return ancestor;
}

std::set<Person *> Person::descendants()
{
    set<Person *> descendant;
    set<Person *> iterate = child;
    for (Person *per : iterate)
    {
        descendant.merge(per->descendants());
    }
    descendant.merge(iterate);
    return descendant;
}
