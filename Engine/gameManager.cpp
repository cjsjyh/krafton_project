#include "gameManager.h"
gameManager::gameManager()
{

}

gameManager::~gameManager()
{

}

void gameManager::RegisterObject(gameObject *item)
{
	gameobjects.push_back(item);
	cout << "manager size: " << gameobjects.size() << endl;
	return;
}

void gameManager::UnregisterObject(gameObject *item)
{
	int index = FindObjectIndex(item);
	gameobjects.erase(gameobjects.begin() + index);
	cout << "manager size: " << gameobjects.size() << endl;
	return;
}

int gameManager::FindObjectIndex(gameObject *item)
{
	vector<gameObject*>::iterator itr = find(gameobjects.begin(), gameobjects.end(), item);
	return distance(gameobjects.begin(), itr);
}

int gameManager::GetObjectCount()
{
	return gameobjects.size();
}

gameObject* gameManager::GetGameObject(int index)
{
	return gameobjects[index];
}

bool gameManager::CollisionManager(vector<gameObject*> &item1, vector<gameObject*> &item2)
{
	//check all objects if they collide and return true or false.
	//if there are objects colliding, add them to the vector
	int size = GetObjectCount();
	bool flag;

	for (int i = 0; i < size-1; i++) {
		gameObject::ColliderType srcType = gameobjects[i]->GetColliderType();

		if (gameobjects[i]->channel == gameObject::NO_COLLISION)
			continue;

		for (int j = i + 1; j < size; j++) {
			flag = false;
			gameObject::ColliderType destType = gameobjects[j]->GetColliderType();
			
			//collision 검사를 하지 않는 channel
			if (gameobjects[j]->channel == gameObject::NO_COLLISION)
				continue;
			//서로 다른 collision channel
			else if (gameobjects[j]->channel != gameobjects[i]->channel)
				continue;

			//서로 타입이 같은 2물체
			if (srcType == destType)
			{
				if (srcType == gameObject::COLLIDER_BOX)
				{
					if (SimpleBoxCollision(gameobjects[i], gameobjects[j]))
					{
						flag = true;
						cout << "2 Box Hit!" << endl;
						cout << gameobjects[i]->GetName() << gameobjects[j]->GetName() << endl;
					}
				}
				else if (srcType == gameObject::COLLIDER_COMPLEX)
				{
					if (ComplexCollision(gameobjects[i], gameobjects[j]))
						flag = true;
				}
			}
			//서로 타입이 다른 2물체
			else
			{
				if (srcType == gameObject::COLLIDER_BOX)
				{
					if (SimpleComplexCollision(gameobjects[i], gameobjects[j]))
						flag = true;
				}
				else
				{
					if (SimpleComplexCollision(gameobjects[j], gameobjects[i]))
						flag = true;
				}
			}
			if (flag) {
				item1.push_back(gameobjects[i]);
				item2.push_back(gameobjects[j]);
			}
		}
		
	}
	
	if (item1.size() == 0)
		return false;
	else
		return true;
}

bool gameManager::SimpleBoxCollision(gameObject* src, gameObject* dest)
{
	D3DXVECTOR3 pos, len;
	src->GetPosition(pos);
	src->GetSize(len);
	D3DXVECTOR3 pos2, len2;
	dest->GetPosition(pos2);
	dest->GetSize(len2);

	if ((pos2.x - len2.x <= pos.x + len.x && pos2.x + len2.x >= pos.x - len.x) &&
		(pos2.z - len2.z <= pos.z + len.z && pos2.z + len2.z >= pos.z - len.z))
		return true;
	return false;
}

bool gameManager::ComplexCollision(gameObject* objSrc, gameObject* objDest)
{
	vector<D3DXVECTOR3> SrcCollPts = ComplexCollisionInitialize(objSrc);
	vector<D3DXVECTOR3> DestCollPts = ComplexCollisionInitialize(objDest);
	float distance = objSrc->sphere_collSize + objDest->sphere_collSize;

	vector<D3DXVECTOR3>::iterator iter1, iter2;

	for (iter1 = SrcCollPts.begin(); iter1 < SrcCollPts.end(); iter1++)
	{
		for (iter2 = DestCollPts.begin(); iter2 < DestCollPts.end(); iter2++)
		{
			float result = pow(iter1->x - iter2->x,2) + pow(iter1->z - iter2->z,2);
			if (result <= pow(distance, 2)) {
				cout << "HIT!!" << endl;
				return true;
			}
			else if (result >= pow(distance * 2,2)) {
				return false;
			}
		}
	}
	return false;
}

bool gameManager::SimpleComplexCollision(gameObject* objSimple, gameObject* objComplex)
{
	float collider_size = objComplex->sphere_collSize;
	vector<D3DXVECTOR3> objComplexPts = ComplexCollisionInitialize(objComplex);

	vector<D3DXVECTOR3>::iterator iter1;
	for (iter1 = objComplexPts.begin(); iter1 < objComplexPts.end(); iter1++)
	{
		if (SimpleDetection(objSimple, iter1,collider_size))
			return true;
	}

}

bool gameManager::SimpleDetection(gameObject* simple, vector<D3DXVECTOR3>::iterator check,float colliderSize)
{
	D3DXVECTOR3 pos, len;
	simple->GetPosition(pos);
	simple->GetSize(len);
	if ((check->x - colliderSize <= pos.x + len.x && check->x + colliderSize >= pos.x - len.x) &&
		(check->z - colliderSize <= pos.z + len.z && check->z + colliderSize >= pos.z - len.z))
		return true;
	return false;
}



vector <D3DXVECTOR3> gameManager::ComplexCollisionInitialize(gameObject* obj)
{
	vector <D3DXVECTOR3> points;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 size;
	//from object
	float minVertex;
	float collider_size = obj->sphere_collSize;


	obj->GetPosition(pos);
	obj->GetScale(size);
	minVertex = min(min(size.x, size.y), size.z);
	minVertex -= collider_size;

	for (int i = 1; i < (size.x/collider_size)*2; i+=2) {
		for (int k = 1; k < (size.z / collider_size) * 2; k += 2) {
			D3DXVECTOR3 temp;
			float maxVertex;
			temp.x = pos.x - size.x + i * collider_size;
			temp.z = pos.z - size.z + k * collider_size;
			maxVertex = max(abs(temp.x), abs(temp.z));
			if (maxVertex < minVertex) {
				continue;
			}
			points.push_back(temp);
		}
	}

	return points;
}

