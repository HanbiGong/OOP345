#ifndef SENECA_ORDEREDCOLLECTION_H
#define SENECA_ORDEREDCOLLECTION_H

#include "Book.h"
#include "Collection.h"

namespace seneca {
	// Collection클래스를 상속받음
	// 오름차순으로 아이템들을 저장함
	// Always have a capacity of 72 items.Your design of OrderedCollection is to have only one template parameter T.
	template<typename T>
	class OrderedCollection : public seneca::Collection<T, 72> {
	public:
        bool operator+=(const T& item) override {
            if (this->size() < this->capacity()) {
                // Find the position where the item should be inserted
                unsigned int pos = 0;
                while (pos < this->size() && this->operator[](pos) < item) {
                    ++pos;
                }
                // Shift elements to the right
                for (unsigned int i = this->size(); i > pos; --i) {
                    this->operator[](i) = this->operator[](i - 1);
                }
                // Insert the item
                this->operator[](pos) = item;
                this->incrSize();
                this -> setLargestItem(item);
                this-> setSmallestItem(item);
                return true;
            }
            return false;
        };

	};

}

#endif