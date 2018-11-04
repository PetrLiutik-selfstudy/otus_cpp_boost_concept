#include <boost/concept_check.hpp>

//#include <algorithm>
#include <iterator>

namespace my_concepts {

template <typename T>
void ignore_unused_var_warning(T const&) {}

/**
 * @brief Концепт проверки возможности копирующего конструирования.
 */
template<typename T>
struct CopyConstructible {
  BOOST_CONCEPT_USAGE(CopyConstructible) {
    T t1(t2);
    T* p = &t1;

    const_constraints(t1);
    ignore_unused_var_warning(p);
  }
private:
  void const_constraints(const T& tt) {
    T t(tt);
    const T* p = &tt;

    ignore_unused_var_warning(t);
    ignore_unused_var_warning(p);
  }
  T t2;
};

/**
 * @brief Концепт проверки возможности конструирования по умолчанию.
 */
template<typename T>
struct DefaultConstructible {
  BOOST_CONCEPT_USAGE(DefaultConstructible) {
    T t1;
    T t2{};

    ignore_unused_var_warning(T());
    ignore_unused_var_warning(T{});
  }
};

/**
 * @brief Концепт проверки возможности разрушения.
 */
template<typename T>
struct Destructible {
  BOOST_CONCEPT_USAGE(Destructible) {
    t.~T();
  }
private:
  T t;
};

/**
 * @brief Концепт проверки возможности присваивания.
 */
template<typename T>
struct Assignable {
  BOOST_CONCEPT_USAGE(Assignable) {
    t1 = t2;
    const_constraints(t2);
  }

private:
  void const_constraints(const T& t) {
    t1 = t;
    ignore_unused_var_warning(t1);
    ignore_unused_var_warning(t);
  }
  T t1, t2;
};

/**
 * @brief Концепт проверки возможности свопа.
 */
template <typename T>
struct Swappable {
  BOOST_CONCEPT_ASSERT((Assignable<T>));
  BOOST_CONCEPT_USAGE(Swappable){
    std::swap(t1, t2);
  }
private:
  T t1, t2;
};

/**
 * @brief Концепт проверки возможности преобразования.
 */
template <typename T, typename U>
struct Convertible {
  BOOST_CONCEPT_USAGE(Convertible) {
    U u = t;
    ignore_unused_var_warning(u);
  }
 private:
  T t;
};

/**
 * @brief Концепт проверки контейнера.
 */
template <typename T>
struct Container : Assignable<T> {
  typedef typename T::value_type value_type;
  typedef typename T::difference_type difference_type;
  typedef typename T::size_type size_type;
  typedef typename T::const_reference const_reference;
  typedef typename T::const_pointer const_pointer;
  typedef typename T::const_iterator const_iterator;

  BOOST_CONCEPT_USAGE(Container) {
    const_constraints(t);
  }

private:
  void const_constraints(const T& tt) {
    i = tt.begin();
    i = tt.end();
    n = tt.size();
    n = tt.max_size();
    b = tt.empty();
  }
  T t;
  bool b;
  const_iterator i;
  size_type n;
};

/**
 * @brief Концепт проверки итератора произвольного доступа.
 */
template<typename T>
struct RandomAccessIterator : Swappable<T>, Assignable<T> {
  BOOST_CONCEPT_USAGE(RandomAccessIterator){
    // Требования к InputIterator.
    T j(i);
    ++j;        // require preincrement operator
    i++;        // require postincrement operator

    // Требования к ForwardIterator.
    r = *i;     // require dereference operator
    ignore_unused_var_warning(r);

    // Требования к Mutable_ForwardIterator.
    *i++ = *j;  // require postincrement and assignment

    // Требования к BidirectionalIterator.
    --i;        // require predecrement operator
    i--;        // require postdecrement operator

    // Требования к RandomAccessIterator.
    i += n;     // require assignment addition operator
    i = i + n;  // require addition with difference type
    i = n + i;
    i -= n;     // require assignment subtraction operator
    i = i - n;  // require subtraction with difference type
    n = i - j;  // require difference operator
    ignore_unused_var_warning(i[n]); // require element access operator

    // Требования к Comparable.
    ignore_unused_var_warning(a < b);
    ignore_unused_var_warning(a > b);
    ignore_unused_var_warning(a <= b);
    ignore_unused_var_warning(a >= b);

    // Требования к EqualityComparable.
    ignore_unused_var_warning(a == b);
    ignore_unused_var_warning(a != b);
  }

private:
  T a, b;
  T i, j;
  typename std::iterator_traits<T>::difference_type n;
  typename std::iterator_traits<T>::reference r;
};

/**
 * @brief Концепт проверки наличия оператора меньше.
 */
template <typename T>
struct LessThenComparable {
  BOOST_CONCEPT_USAGE(LessThenComparable) {
    ignore_unused_var_warning(t1 < t2);
  }
  private:
    T t1, t2;
};

} // namespace my_concepts.
