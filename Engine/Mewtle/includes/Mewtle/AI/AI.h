#pragma once

namespace Mewtle{
	class MapNode{
	private :
		int x = 0, y = 0;
		float fValue = 0;
		float gValue = 0;
		MapNode* parent = nullptr;

	public :
		MapNode(int x, int y);
		int getX();
		int getY();
		float getFValue();
		float getGValue();
		MapNode* getParent();
		void setFValue(float value);
		void setGValue(float value);
		void setParent(MapNode* parent);
	};

	class FValueComparator{
	public :
		int operator() (MapNode* p1, MapNode* p2){
			return p1->getFValue() > p2->getFValue();
		}
	};

	class AI{
	private :
		static void constructPath(MapNode* head, std::vector<MapNode*>* path);

	public :
		static void aStar(int startX, int startY, int endX, int endY, int xClearance, int yClearance, int* xMap, int* yMap, int width, int height, std::vector<MapNode*>* path, bool diagonalMovement);
		static void aStarTarget(int startX, int startY, int endX, int endY, int xClearance, int yClearance, int* xMap, int* yMap, int width, int height, std::vector<MapNode*>* path, bool diagonalMovement);
		static void generateNode(int x, int y, int xClearance, int yClearance, int* xMap, int* yMap, int width, int height, std::vector<MapNode*>* successors);
		static void generateNode(int x, int y, int xClearance, int yClearance, int* xMap, int* yMap, int width, int height, std::vector<MapNode*>* successors, int endX, int endY);
		static void initializeClearanceValues(int* map, int width, int height, int* xClearance, int* yClearance);
		static void updateMap(int x, int y, int newValue, int* xClearance, int* yClearance, int* map, int width, int height);
		static bool isSolid(int value);
	};
}