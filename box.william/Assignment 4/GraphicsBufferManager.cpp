#include "GraphicsBufferManager.h"
GraphicsBufferManager::GraphicsBufferManager()
{

}
GraphicsBufferManager::~GraphicsBufferManager()
{
	clearManager();
}
void GraphicsBufferManager::addGraphicsBuffer(GraphicsBuffer* newGraphicsBuffer, MapKey graphicsBufferName)
{
	if (mGraphicsBufferMap.find(graphicsBufferName) == mGraphicsBufferMap.end())
	{
		mGraphicsBufferMap[graphicsBufferName] = newGraphicsBuffer;
	}
}
void GraphicsBufferManager::addGraphicsBuffer(std::string assetPath, std::string fileName, MapKey graphicsBufferName)
{
	if (mGraphicsBufferMap.find(graphicsBufferName) == mGraphicsBufferMap.end())
	{
		mGraphicsBufferMap[graphicsBufferName] = new GraphicsBuffer(assetPath, fileName);
	}
}
void GraphicsBufferManager::removeGraphicsBuffer(MapKey graphicsBufferName)
{
	auto graphicsBufferToDelete = mGraphicsBufferMap.find(graphicsBufferName);
	if (graphicsBufferToDelete != mGraphicsBufferMap.end())
	{
		delete graphicsBufferToDelete->second;
		mGraphicsBufferMap.erase(graphicsBufferName);
	}
}
GraphicsBuffer* GraphicsBufferManager::getGraphicsBuffer(MapKey graphicsBufferName)
{
	if (mGraphicsBufferMap.find(graphicsBufferName) != mGraphicsBufferMap.end())
	{
		return mGraphicsBufferMap.at(graphicsBufferName);
	}
	else
	{
		return NULL;
	}
}
void GraphicsBufferManager::clearManager()
{
	for (auto graphicsBufferToDelete : mGraphicsBufferMap)
	{
		delete graphicsBufferToDelete.second;
	}
	mGraphicsBufferMap.clear();
}