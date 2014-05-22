#ifndef PGSQL_ID_TRACKER_HPP
#define PGSQL_ID_TRACKER_HPP

#include "osmtypes.hpp"
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

struct pgsql_id_tracker : public boost::noncopyable {
    pgsql_id_tracker(const char *conninfo, 
                     const char *prefix, 
                     const char *type,
                     bool owns_table);
    ~pgsql_id_tracker();

    void mark(osmid_t id);
    bool is_marked(osmid_t id);

    osmid_t pop_mark();

    void commit();
    void force_release(); // to avoid brain-damages with fork()

private:
    void unmark(osmid_t id);

    struct pimpl;
    boost::scoped_ptr<pimpl> impl;
};

#endif /* PGSQL_ID_TRACKER_HPP */
