//
// Created by mac on 1/04/17.
//

#include "Path.h"

Path::Path(Node* node, ActionType action) {
    pathNode = node;
    pathAction = action;
}

Path::Path(Node* node) {
    pathNode = node;
}

Path::Path() {

}

