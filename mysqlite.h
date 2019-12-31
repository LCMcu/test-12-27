#ifndef __MYSQLITE_H
#define __MYSQLITE_H

#include <sqlite3.h>
#include "proto.h"

int insert_data(sqlite3 *db, char *table, const DEVICE_DATA * device);

#endif 

