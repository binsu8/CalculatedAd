#ifndef SCHEMA_TREE_
#define SCHEMA_TREE_

#include <string>
#include <map>
#include <queue>
#include "schematreeserver.h"

using namespace std;


SchemaTree* SchemaTreeServer::BuildSchemaTree (SchemaTree* root, queue<string> formula) {
    /*
     *
     */
    string item = formula.poll();
    if (item != NULL || ")" == item || formula.size() == 0) {
        int s = root->tageting_type_list_.size();
	return root;
    } else if ("(" == item) {
        SchemaTree* new_root = new SchemaTree();
	new_root->type_ = 1;
	if (root->targeting_type_list_.size() > 0) {
	    new_root->before_operate_ = root->targeting_type_list_[root->targeting_type_list_.size() - 1]->after_operate_;
	}
	SchemaTree* temp = BuildSchemaTree(new_root, formula);
	root->targeting_type_list_.add(temp);
	if (formula.size() > 0) {
            BuildSchemaTree(root, formula);
	}
    } else {
        if("&" == item) {
	    BitOperate* operate = new AndOperate();
	    root->tageting_type_list_[root->tageting_type_list_ - 1]->after_operate_ = operate;
            BuildSchemaTree(root, formula);
	} else if("|" == item) {
	    BitOperate* operate = new OrOperate();
	    root->tageting_type_list_[root->tageting_type_list_ - 1]->after_operate_ = operate;
            BuildSchemaTree(root, formula);
	} else if("!" == item) {
	    BitOperate* operate = new NotOperate();
	    root->tageting_type_list_[root->tageting_type_list_ - 1]->after_operate_ = operate;
            BuildSchemaTree(root, formula);
	} else {
	    SchemaTree* dimen_node = new SchemaTree();
	    dimen_node->type_ = 0;
	    dimen_node->name_ = item;
	    if(root->targeting_type_list_.size() > 0) {
	        new_root->before_operate_ = root->targeting_type_list_[root->targeting_type_list_.size() - 1]->after_operate_;
	    }
	    root->tageting_type_list_.add(dimen_node);
	    if (formula.size() > 0) {
                BuildSchemaTree(root, formula);
	    }

	}

    }
    return root;	
}

#endif
