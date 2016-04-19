#include "collision.hpp"
#include "../entity/entity.hpp"

bool clsn::hasCollided(entity *firstSprite, entity *secondSprite)
    {
        auto first = firstSprite->getSprite();
        auto second = secondSprite->getSprite();

        auto firstObjBound = first->getGlobalBounds();
        auto secondObjBound = second->getGlobalBounds();

        sf::Vector2f centerFirst(firstObjBound.left + (firstObjBound.width / 2),
                                 firstObjBound.top + (firstObjBound.height / 2));

        sf::Vector2f centerSecond(secondObjBound.left + (secondObjBound.width / 2),
                                  secondObjBound.top + (secondObjBound.height / 2));

        sf::Vector2f distance(centerFirst - centerSecond);
        sf::Vector2f minDistance((firstObjBound.width / 2) + (secondObjBound.width / 2),
                                 (firstObjBound.height / 2) + (secondObjBound.height / 2));

        return abs(distance.x) < minDistance.x && abs(distance.y) < minDistance.y;
    }

sf::Vector2f clsn::getOverlap(entity *firstSprite, entity *secondSprite)
    {
        auto first = firstSprite->getSprite();
        auto second = secondSprite->getSprite();

        auto firstObjBound = first->getGlobalBounds();
        auto secondObjBound = second->getGlobalBounds();

        sf::Vector2f centerFirst(firstObjBound.left + (firstObjBound.width / 2),
                                    firstObjBound.top + (firstObjBound.height / 2));

        sf::Vector2f centerSecond(secondObjBound.left + (secondObjBound.width / 2),
                                    secondObjBound.top + (secondObjBound.height / 2));

        sf::Vector2f distance(centerFirst - centerSecond);
        sf::Vector2f minDistance(((firstObjBound.width / 2) + (secondObjBound).width / 2),
                                 (firstObjBound.height / 2) + (secondObjBound.height / 2));

        return sf::Vector2f(distance.x > 0 ? minDistance.x - distance.x : -minDistance.x - distance.x,
                            distance.y > 0 ? minDistance.y - distance.y : -minDistance.y - distance.y);
    }
