#include "TestGluonCore.h"

#include <QMetaProperty>

#include <cassert>
#include <cstddef>

using namespace GluonCore;

#define SANITY_CHECK_POINTERS(a, b) if((a) == NULL || (b) == NULL) return (a) == NULL && (b) == NULL

static bool compare_metaproperties(const QMetaObject* a, const QObject* a_parent, const QMetaObject* b, const QObject* b_parent)
{
    SANITY_CHECK_POINTERS(a, b);

    if(a->className() != b->className())
        return false;

    int a_propcount = a->propertyCount(),
        b_propcount = b->propertyCount();

    if(a_propcount != b_propcount)
        return false;

    for(int i = 0; i < a_propcount; ++i)
    {
        QMetaProperty am = a->property(i),
                      bm = b->property(i);

        if(am.type() != bm.type())
            return false;

        if(am.name() != bm.name())
            return false;

        if(am.read(a_parent).toString() != bm.read(b_parent).toString())
            return false;
    }

    return true;
}

static bool compare_dynproperties(const GluonObject* a, const GluonObject* b)
{
    typedef QList<QByteArray> PropNameList;

    SANITY_CHECK_POINTERS(a, b);

    const PropNameList a_names = a->dynamicPropertyNames(),
                       b_names = b->dynamicPropertyNames();

    if(a_names.size() != b_names.size())
        return false;

    for(PropNameList::const_iterator p1 = a_names.begin(), p2 = b_names.begin(), e = a_names.end(); p1 != e; ++p1, ++p2)
    {
        if(QString(*p1) != QString(*p2))
            return false;

        if(a->property(*p1).toString() != b->property(*p2).toString())
            return false;
    }
    
    return true;
}

static bool compare_objects(const GluonObject* a, const GluonObject* b)
{
    SANITY_CHECK_POINTERS(a, b);

    if(compare_metaproperties(a->metaObject(), a, b->metaObject(), b) == false)
        return false;

    if(compare_dynproperties(a, b) == false)
        return false;

    return true;
}

typedef QList<GluonObject*> OTree;

bool TestGluonCore::compare_trees(const QList<GluonObject*>& t1, const QList<GluonObject*>& t2)
{
    if(t1.size() != t2.size())
        return false;

    OTree::const_iterator p1 = t1.begin(),
                          p2 = t2.begin(),
                          end = t1.end();
    
    for(; p1 != end; ++p1, ++p2)
    {
        assert(p2 != t2.end());

        if(compare_objects(*p1, *p2) == false)
            return false;
    }

    return true;
}

