#include "Concepts.h"

#include <algorithm>
#include <array>
#include <bitset>
#include <list>
#include <string>
#include <vector>


// Структуры для теста концепта наличия конструктора по умолчанию.
struct StructWithDefaultConstructor {
  StructWithDefaultConstructor() = default;
};

struct StructWithoutDefaultConstructor {
  StructWithoutDefaultConstructor() = delete;
};


// Структуры для теста концепта наличия копирующего конструктора.
struct StructWithCopyConstructor {
  StructWithCopyConstructor(const StructWithCopyConstructor&) = default;
};

struct StructWithoutCopyConstructor {
  StructWithoutCopyConstructor(const StructWithoutCopyConstructor&) = delete;
};

struct StructWithoutAddressOfOperator {
  operator&() = delete;
};


// Структуры для теста концепта наличия деструктора.
struct StructWithDestructor {
  ~StructWithDestructor() = default;
};

struct StructWithoutDestructor {
  ~StructWithoutDestructor() = delete;
};


// Шаблоны итераторов для теста концепта итератора произвольного доступа.
template<typename T>
struct IteratorWithoutCopyConstructor : std::vector<T>::iterator {
  IteratorWithoutCopyConstructor(IteratorWithoutCopyConstructor&) = delete;
};

template<typename T>
struct IteratorWithoutIncrementOperator : std::vector<T>::iterator {
  T operator++() = delete;
};

template<typename T>
struct IteratorWithoutDecrementOperator : std::vector<T>::iterator {
  T operator--() = delete;
};

template<typename T>
struct IteratorWithoutDereferenceOperator : std::vector<T>::iterator {
  T operator*() = delete;
};

template<typename T>
struct IteratorWithoutElementAcessOperator : std::vector<T>::iterator {
  T operator[](size_t) = delete;
};

template<typename T>
struct IteratorWithoutEqualOperator : std::vector<T>::iterator {
  bool operator==(IteratorWithoutEqualOperator&) = delete;
};


int main(int argc, char * argv[]) {

  // Проверка концепта DefaultConstructible.
  // Не нарушен.
  BOOST_CONCEPT_ASSERT((my_concepts::DefaultConstructible<int>));
  BOOST_CONCEPT_ASSERT((my_concepts::DefaultConstructible<StructWithDefaultConstructor>));
  // Нарушен.
//  BOOST_CONCEPT_ASSERT((my_concepts::DefaultConstructible<StructWithoutDefaultConstructor>));


  // Проверка концепта CopyConstructible.
  // Не нарушен.
  BOOST_CONCEPT_ASSERT((my_concepts::CopyConstructible<int>));
  BOOST_CONCEPT_ASSERT((my_concepts::CopyConstructible<StructWithCopyConstructor>));
  // Нарушен.
//  BOOST_CONCEPT_ASSERT((my_concepts::CopyConstructible<StructWithoutCopyConstructor>));
//  BOOST_CONCEPT_ASSERT((my_concepts::CopyConstructible<StructWithoutAddressOfOperator>));


  // Проверка концепта Destructible.
  // Не нарушен.
  BOOST_CONCEPT_ASSERT((my_concepts::Destructible<int>));
  BOOST_CONCEPT_ASSERT((my_concepts::Destructible<StructWithDestructor>));
  // Нарушен.
//  BOOST_CONCEPT_ASSERT((my_concepts::Destructible<StructWithoutDestructor>));


  // Проверка концепта Assignable.
  // Не нарушен.
  BOOST_CONCEPT_ASSERT((my_concepts::Assignable<int>));
  // Нарушен.
//  BOOST_CONCEPT_ASSERT((my_concepts::Assignable<const int>));


  // Проверка концепта Swappable.
  // Не нарушен.
  BOOST_CONCEPT_ASSERT((my_concepts::Swappable<int>));
  // Нарушен.
//  BOOST_CONCEPT_ASSERT((my_concepts::Swappable<const int>));


  // Проверка концепта Convertible.
  // Не нарушен.
  BOOST_CONCEPT_ASSERT((my_concepts::Convertible<int, float>));
  // Нарушен.
//  BOOST_CONCEPT_ASSERT((my_concepts::Convertible<int, int*>));
//  BOOST_CONCEPT_ASSERT((my_concepts::Convertible<std::array<int, 5>, std::array<int, 4>>));

  // Проверка концепта Container.
  // Не нарушен.
  BOOST_CONCEPT_ASSERT((my_concepts::Container<std::vector<int>>));
  BOOST_CONCEPT_ASSERT((my_concepts::Container<std::string>));
  BOOST_CONCEPT_ASSERT((my_concepts::Container<std::array<int, 5>>));
  BOOST_CONCEPT_ASSERT((my_concepts::Container<std::list<int>>));
  // Нарушен.
//  BOOST_CONCEPT_ASSERT((my_concepts::Container<int>));
//  BOOST_CONCEPT_ASSERT((my_concepts::Container<std::bitset<5>>));


  // Проверка концепта RandomAccessIterator.
  // Не нарушен.
  BOOST_CONCEPT_ASSERT((my_concepts::RandomAccessIterator<std::vector<int>::iterator>));
  BOOST_CONCEPT_ASSERT((my_concepts::RandomAccessIterator<std::array<int, 5>::iterator>));
  BOOST_CONCEPT_ASSERT((my_concepts::RandomAccessIterator<std::string::iterator>));
  // Нарушен.
//  BOOST_CONCEPT_ASSERT((my_concepts::RandomAccessIterator<int>));
//  BOOST_CONCEPT_ASSERT((my_concepts::RandomAccessIterator<std::list<int>::iterator>));
//  BOOST_CONCEPT_ASSERT((my_concepts::RandomAccessIterator<IteratorWithoutCopyConstructor<int>>));
//  BOOST_CONCEPT_ASSERT((my_concepts::RandomAccessIterator<IteratorWithoutIncrementOperator<int>>));
//  BOOST_CONCEPT_ASSERT((my_concepts::RandomAccessIterator<IteratorWithoutDecrementOperator<int>>));
//  BOOST_CONCEPT_ASSERT((my_concepts::RandomAccessIterator<IteratorWithoutDereferenceOperator<int>>));
//  BOOST_CONCEPT_ASSERT((my_concepts::RandomAccessIterator<IteratorWithoutElementAcessOperator<int>>));
//  BOOST_CONCEPT_ASSERT((my_concepts::RandomAccessIterator<IteratorWithoutEqualOperator<int>>));
}
