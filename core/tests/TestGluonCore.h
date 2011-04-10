#ifndef GLUON_CORE_TEST_H
#define GLUON_CORE_TEST_H

#include <QtTest/QTest>

#include "../core/gluonobject.h"
#include "../core/gdlhandler.h"

class TestGluonCore : public QObject
{
    Q_OBJECT

private:
    // Compares two non-serialized GDL trees. True if they're equal, false if not.
    static bool compare_trees(const QList<GluonCore::GluonObject*>& t1, const QList<GluonCore::GluonObject*>& t2);

    template <typename T>
    static QList<const T*> const_list_from_nonconst(const QList<T*>& x)
    {
        QList<const T*> r;

        foreach(T* e, x)
            r.push_back(e);

        return r;
    }

    // Returns true if the passed GDL has (parsed -> serialized -> parsed) == parsed
    static bool ensure_reversible(const QString& gdl)
    {
        GluonCore::GDLHandler* gh = GluonCore::GDLHandler::instance();

        QList<GluonCore::GluonObject*> parsed = gh->parseGDL(gdl, NULL);

        return compare_trees(
            parsed, gh->parseGDL(gh->serializeGDL(const_list_from_nonconst(parsed)), NULL)
        );
    }

    private slots:
    void doxygenSample();
    void invadersSample();
};

#endif
