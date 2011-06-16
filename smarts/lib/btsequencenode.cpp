#include "btsequencenode.h"

#include "btnode.h"
#include "btcharacter.h"

btSequenceNode::btSequenceNode()
{
}

btNode::status btSequenceNode::run(btCharacter *self)
{    
	/*for(int i = this->currentChildIndex(); i < this->childCount(); i++)
    {       
		if(this->currentChildStatus() == btNode::Failed)
		{
			return btNode::Failed;
		}
		
		return this->runChild(i);
    }//*/
	
	
	if(this->currentChildStatus() == btNode::Failed)
	{
		return Failed;
	}
	
	if(this->nextChildIndex() < this->childCount())
	{
		return runChild(this->currentChildIndex());
	}
	
	
	
    return Succeeded;
}

#include "btsequencenode.moc"
