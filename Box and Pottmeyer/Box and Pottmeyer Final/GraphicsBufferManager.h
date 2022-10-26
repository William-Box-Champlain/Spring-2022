#pragma once
#include <Trackable.h>
#include <unordered_map>
#include <string>
#include "GraphicsBuffer.h"

class GraphicsBuffer;

typedef std::string MapKey;

class GraphicsBufferManager:public Trackable
{
public:
	GraphicsBufferManager();
	~GraphicsBufferManager();

	void addGraphicsBuffer(GraphicsBuffer* newGraphicsBuffer, MapKey graphicsBufferName);
	void addGraphicsBuffer(std::string assetPath, std::string fileName, MapKey graphicsBufferName);
	void removeGraphicsBuffer(MapKey graphicsBufferName);
	GraphicsBuffer* getGraphicsBuffer(MapKey graphicsBufferName);

	void clearManager();
private:
	std::unordered_map<MapKey, GraphicsBuffer*> mGraphicsBufferMap;
};