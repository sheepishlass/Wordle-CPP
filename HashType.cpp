#include "HashType.hpp"
#include <string>

using std::cout;
using std::endl;
using std::string;

template <class ItemType> HashType<ItemType>::HashType() {
  a = 33;
  numItems = 0;
  size = MAX_ITEMS;
  info = new string[size];
  for (int i = 0; i < size; i++)
    info[i] = emptyItem;
  numCollisions = 0;
}

template <class ItemType> HashType<ItemType>::HashType(int s, int factor) {
  a = factor;
  numItems = 0;
  size = s;
  info = new string[size];
  for (int i = 0; i < size; i++)
    info[i] = emptyItem;
  numCollisions = 0;
}

template <class ItemType> void HashType<ItemType>::MakeEmpty() {
  numItems = 0;
  for (int i = 0; i < size; i++)
    info[i] = emptyItem;
}

template <class ItemType> bool HashType<ItemType>::IsFull() const {
  return (numItems == size);
}

template <class ItemType> int HashType<ItemType>::GetNumItems() const {
  return numItems;
}

template <class ItemType>
void HashType<ItemType>::RetrieveItem(ItemType &item, bool &found, int type) {
  int location;
  int startLoc;
  bool moreToSearch = true;

  startLoc = Hash(item);
  location = startLoc;

  double quadraticValue;
  int i = 1;

  do {
    if (info[location] == item || info[location] == emptyItem)
      moreToSearch = false;
    else if (type == 1)
      location = (location + 1) % size;
    else {
      quadraticValue = pow(-1.0, static_cast<double>(i - 1)) *
                       pow(static_cast<double>((i + 1) / 2), 2.0);
      location = (startLoc + static_cast<int>(quadraticValue)) % size;
      if (location < 0)
        location = location + size;
      i++;
    }
  } while (location != startLoc && moreToSearch);
  found = (info[location] == item);
  if (found)
    item = info[location];
}

template <class ItemType>
void HashType<ItemType>::InsertItemLinear(ItemType item) {
  int location;
  location = Hash(item);

  while (info[location] != emptyItem) {
    location = (location + 1) % size; // linear probing
    numCollisions++;
  }

  info[location] = item;
  numItems++;
}

template <class ItemType>
void HashType<ItemType>::InsertItemQuadratic(ItemType item) {
  int location;
  int HashValue;
  double quadraticValue;
  HashValue = Hash(item);
  location = HashValue;
  int i = 1;

  while (info[location] != emptyItem) {
    quadraticValue = pow(-1.0, static_cast<double>(i - 1)) *
                     pow(static_cast<double>((i + 1) / 2), 2.0);
    location = (HashValue + static_cast<int>(quadraticValue)) %
               size; // quadratic probing
    if (location < 0)
      location = location + size;
    numCollisions++;
    i++;
  }

  info[location] = item;
  numItems++;
}

template <class ItemType> void HashType<ItemType>::DeleteItem(ItemType item) {
  int location = 0;
  int startLoc;

  startLoc = Hash(item);
  location = startLoc;
  do {
    if (info[location] == item) {
      info[location] = deletedItem;
      numItems--;
      return;
    } else
      location = (location + 1) % size;
  } while (location != startLoc);
  if (location == startLoc) {
    cout << "Item to delete not found." << endl;
  }
}

template <class ItemType> 
int HashType<ItemType>::Hash(string item) const {
  unsigned long long hash = 0;
  unsigned long long m = 1e9 + 9;
  int n = item.length();
  for (int i = 0; i < n; i++) {
    hash = (a * hash + item.at(i)) % m;
  }
  return static_cast<int>(hash % size);
}

template <class ItemType>
unsigned long long HashType<ItemType>::GetCollisions() const {
  return numCollisions;
}

template <class ItemHash>
ostream &operator<<(ostream &out, const HashType<ItemHash> &items) {
  out << "[ ";
  for (int i = 0; i < items.size; i++) {
    if (items.info[i] == items.emptyItem)
      out << "";
    else if (i == items.size - 1)
      out << items.info[i];
    else
      out << items.info[i] << ", ";
  }
  out << " ]" << endl;
  return out;
}

template class HashType<string>;