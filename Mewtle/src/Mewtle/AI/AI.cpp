#include <PrecompiledHeaders.h>

#include "AI.h"

#include "Mewtle/Utils/Utils.h"

namespace Mewtle{
	void AI::aStar(int startX, int startY, int endX, int endY, int xClearance, int yClearance, int* xMap, int* yMap, int width, int height, std::vector<MapNode*>* path, bool diagonalMovement){
		std::priority_queue<MapNode*, std::vector<MapNode*>, FValueComparator> openList;
		std::vector<MapNode*> openedListVector;
		std::vector<MapNode*> closedList;

		MapNode* startNode = new MapNode(startX, startY);
		MapNode* endNode = new MapNode(endX, endY);

		openList.push(startNode);
		openedListVector.push_back(startNode);

		while(!openList.empty()){
			MapNode* q = openList.top();
			openList.pop();
			openedListVector.erase(std::find(openedListVector.begin(), openedListVector.end(), q));

			std::vector<MapNode*> successors;
			generateNode(q->getX() - 1, q->getY(), xClearance, yClearance, xMap, yMap, width, height, &successors);
			generateNode(q->getX() + 1, q->getY(), xClearance, yClearance, xMap, yMap, width, height, &successors);
			generateNode(q->getX(), q->getY() - 1, xClearance, yClearance, xMap, yMap, width, height, &successors);
			generateNode(q->getX(), q->getY() + 1, xClearance, yClearance, xMap, yMap, width, height, &successors);
			if(diagonalMovement){
				generateNode(q->getX() - 1, q->getY() - 1, xClearance, yClearance, xMap, yMap, width, height, &successors);
				generateNode(q->getX() + 1, q->getY() - 1, xClearance, yClearance, xMap, yMap, width, height, &successors);
				generateNode(q->getX() - 1, q->getY() + 1, xClearance, yClearance, xMap, yMap, width, height, &successors);
				generateNode(q->getX() + 1, q->getY() + 1, xClearance, yClearance, xMap, yMap, width, height, &successors);
			}

			for(auto it = successors.begin(); it != successors.end(); it++){
				MapNode* node = *it;
				node->setParent(q);
				if(node->getX() == endNode->getX() && node->getY() == endNode->getY()){
					constructPath(node, path);
					return;
				}
				node->setGValue(q->getGValue() + (diagonalMovement ? Utils::distance((float) node->getX(), (float) node->getY(), (float) q->getX(), (float) q->getY()) : 1));
				node->setFValue(node->getGValue() + Utils::distance((float) node->getX(), (float) node->getY(), (float) endNode->getX(), (float) endNode->getY()));

				bool skipFlag = false;
				for(auto it2 = openedListVector.begin(); it2 != openedListVector.end(); it2++){
					MapNode* oldNode = *it2;
					if(node->getX() == oldNode->getX() && node->getY() == oldNode->getY()){
						if(oldNode->getFValue() <= node->getFValue()) skipFlag = true;
						break;
					}
				}
				if(skipFlag) continue;

				for(auto it2 = closedList.begin(); it2 != closedList.end(); it2++){
					MapNode* oldNode = *it2;
					if(node->getX() == oldNode->getX() && node->getY() == oldNode->getY()){
						if(oldNode->getFValue() <= node->getFValue()) skipFlag = true;
						break;
					}
				}
				if(!skipFlag){
					openList.push(node);
					openedListVector.push_back(node);
				}
				else{
					delete node;
				}
			}
			closedList.push_back(q);
		}
	}

	void AI::aStarTarget(int startX, int startY, int endX, int endY, int xClearance, int yClearance, int* xMap, int* yMap, int width, int height, std::vector<MapNode*>* path, bool diagonalMovement){
		std::priority_queue<MapNode*, std::vector<MapNode*>, FValueComparator> openList;
		std::vector<MapNode*> openedListVector;
		std::vector<MapNode*> closedList;

		MapNode* startNode = new MapNode(startX, startY);
		MapNode* endNode = new MapNode(endX, endY);

		openList.push(startNode);
		openedListVector.push_back(startNode);

		while(!openList.empty()){
			MapNode* q = openList.top();
			openList.pop();
			openedListVector.erase(std::find(openedListVector.begin(), openedListVector.end(), q));

			std::vector<MapNode*> successors;
			generateNode(q->getX() - 1, q->getY(), xClearance, yClearance, xMap, yMap, width, height, &successors, endX, endY);
			generateNode(q->getX() + 1, q->getY(), xClearance, yClearance, xMap, yMap, width, height, &successors, endX, endY);
			generateNode(q->getX(), q->getY() - 1, xClearance, yClearance, xMap, yMap, width, height, &successors, endX, endY);
			generateNode(q->getX(), q->getY() + 1, xClearance, yClearance, xMap, yMap, width, height, &successors, endX, endY);
			if(diagonalMovement){
				generateNode(q->getX() - 1, q->getY() - 1, xClearance, yClearance, xMap, yMap, width, height, &successors, endX, endY);
				generateNode(q->getX() + 1, q->getY() - 1, xClearance, yClearance, xMap, yMap, width, height, &successors, endX, endY);
				generateNode(q->getX() - 1, q->getY() + 1, xClearance, yClearance, xMap, yMap, width, height, &successors, endX, endY);
				generateNode(q->getX() + 1, q->getY() + 1, xClearance, yClearance, xMap, yMap, width, height, &successors, endX, endY);
			}

			for(auto it = successors.begin(); it != successors.end(); it++){
				MapNode* node = *it;
				node->setParent(q);
				if(node->getX() == endNode->getX() && node->getY() == endNode->getY()){
					constructPath(node->getParent(), path);
					return;
				}
				node->setGValue(q->getGValue() + (diagonalMovement ? Utils::distance((float) node->getX(), (float) node->getY(), (float) q->getX(), (float) q->getY()) : 1));
				node->setFValue(node->getGValue() + Utils::distance((float) node->getX(), (float) node->getY(), (float) endNode->getX(), (float) endNode->getY()));

				bool skipFlag = false;
				for(auto it2 = openedListVector.begin(); it2 != openedListVector.end(); it2++){
					MapNode* oldNode = *it2;
					if(node->getX() == oldNode->getX() && node->getY() == oldNode->getY()){
						if(oldNode->getFValue() <= node->getFValue()) skipFlag = true;
						break;
					}
				}
				if(skipFlag) continue;

				for(auto it2 = closedList.begin(); it2 != closedList.end(); it2++){
					MapNode* oldNode = *it2;
					if(node->getX() == oldNode->getX() && node->getY() == oldNode->getY()){
						if(oldNode->getFValue() <= node->getFValue()) skipFlag = true;
						break;
					}
				}
				if(!skipFlag){
					openList.push(node);
					openedListVector.push_back(node);
				}
				else{
					delete node;
				}
			}
			closedList.push_back(q);
		}
	}

	MapNode::MapNode(int x, int y){
		this->x = x;
		this->y = y;
	}

	void AI::generateNode(int x, int y, int xClearance, int yClearance, int* xMap, int* yMap, int width, int height, std::vector<MapNode*>* successors){
		if(x >= 0 && y >= 0 && x < width && y < height){
			int clearance[2];
			clearance[0] = *(xMap + x * height + y);
			clearance[1] = *(yMap + x * height + y);
			if(clearance[0] >= xClearance && clearance[1] >= yClearance) successors->push_back(new MapNode(x, y));
		}
	}

	void AI::generateNode(int x, int y, int xClearance, int yClearance, int* xMap, int* yMap, int width, int height, std::vector<MapNode*>* successors, int endX, int endY){
		if(x >= 0 && y >= 0 && x < width && y < height){
			int clearance[2];
			clearance[0] = *(xMap + x * height + y);
			clearance[1] = *(yMap + x * height + y);
			if(clearance[0] >= xClearance && clearance[1] >= yClearance || (x == endX && y == endY)) successors->push_back(new MapNode(x, y));
		}
	}

	void AI::updateMap(int x, int y, int newValue, int* xClearance, int* yClearance, int* rawMap, int width, int height){
		int oldValue = *(rawMap + x * height + y);
		if(isSolid(oldValue) != isSolid(newValue)){
			if(isSolid(newValue)){
				*(xClearance + x * height + y) = 0;
				*(yClearance + x * height + y) = 0;
			}else{
				*(xClearance + x * height + y) = (y == height - 1) ? 1 : *(xClearance + x * height + y + 1) + 1;
				*(yClearance + x * height + y) = (x == width - 1) ? 1 : *(yClearance + (x + 1) * height + y) + 1;
			}
			for(int i = y - 1; i >= 0; i--){
				*(xClearance + x * height + i) = (isSolid(*(rawMap + x * height + i))) ? 0 : *(xClearance + x * height + i + 1) + 1;
			}
			for(int i = x - 1; i >= 0; i--){
				*(yClearance + i * height + y) = (isSolid(*(rawMap + i * height + y))) ? 0 : *(yClearance + (i + 1) * height + y) + 1;
			}
		}
		*(rawMap + x * height + y) = newValue;
	}

	bool AI::isSolid(int value){
		switch(value){
		case 0:
			return false;

		default:
			return true;
		}
	}

	void AI::initializeClearanceValues(int* map, int width, int height, int* xClearance, int* yClearance){
		for(int i = 0; i < width; i++){
			*(xClearance + i * height + height - 1) = (*(map + i * height + height - 1) == 0) ? 1 : 0;
			for(int j = height - 2; j >= 0; j--){
				if(*(map + i * height + j) == 0){
					*(xClearance + i * height + j) = *(xClearance + i * height + j + 1) + 1;
				}else{
					*(xClearance + i * height + j) = 0;
				}
			}
		}

		for(int j = 0; j < height; j++){
			*(yClearance + (width - 1) * height + j) = (*(map + (width - 1) * height + j) == 0) ? 1 : 0;
			for(int i = width - 2; i >= 0; i--){
				if(*(map + i * height + j) == 0){
					*(yClearance + i * height + j) = *(yClearance + (i + 1) * height + j) + 1;
				}else{
					*(yClearance + i * height + j) = 0;
				}
			}
		}
	}

	void AI::constructPath(MapNode* head, std::vector<MapNode*>* path){
		if(head == nullptr) return;
		constructPath(head->getParent(), path);
		path->push_back(head);
	}

	int MapNode::getX(){
		return x;
	}

	int MapNode::getY(){
		return y;
	}

	float MapNode::getFValue(){
		return fValue;
	}

	float MapNode::getGValue(){
		return gValue;
	}

	MapNode* MapNode::getParent(){
		return parent;
	}

	void MapNode::setFValue(float value){
		fValue = value;
	}

	void MapNode::setGValue(float value){
		gValue = value;
	}

	void MapNode::setParent(MapNode* parent){
		this->parent = parent;
	}
}