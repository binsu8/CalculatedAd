#ifndef SCHEMA_TREE_
#define SCHEMA_TREE_

#include <string>
#include <map>
using namespace std;

class SchemaTreeServer {

  public:
    SchemaTree* BuildSchemaTree (SchemaTree root, Queue<string> formula);
    
}


#endif
