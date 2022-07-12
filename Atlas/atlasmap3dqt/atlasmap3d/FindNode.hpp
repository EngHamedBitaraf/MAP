#ifndef FINDNODE_H
#define FINDNODE_H

#include <string>

#include <osg/Node>
#include <osg/Group>

static osg::Node* findNodeInNode(const std::string &searchName, osg::Node *currNode)
{
    osg::Group *currGroup = nullptr;
    osg::Node  *foundNode = nullptr;

    if (!currNode)
    {
        return nullptr;
    }

    if (currNode->getName() == searchName)
    {
        return currNode;
    }

    currGroup = currNode->asGroup();

    if (currGroup)
    {
        for (unsigned int i = 0; i < currGroup->getNumChildren(); i++)
        {
            foundNode = findNodeInNode(searchName, currGroup->getChild(i));

            if (foundNode)
            {
                return foundNode;
            }
        }

        return nullptr;
    }
    else
    {
        return nullptr;
    }
}

#endif // FINDNODE_H
