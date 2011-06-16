#include "btselectornode.h"

#include "btcharacter.h"

btSelectorNode::btSelectorNode()
{
}

btNode::status btSelectorNode::run(btCharacter *self)
{
    /*for(int i = this->currentChildIndex(); i < this->childCount(); i++)
    {
        if(this->currentChildStatus() == btNode::Succeeded)
        {
            return btNode::Succeeded;
        }
		
		return runChild(i);
    }*/
	
	if(this->currentChildStatus() == btNode::Succeeded)
	{
		return Succeeded;
	}
	
	if(this->nextChildIndex() < this->childCount())
	{
		return runChild(this->currentChildIndex());
	}
	
    return Failed;
}

#include "btselectornode.moc"
