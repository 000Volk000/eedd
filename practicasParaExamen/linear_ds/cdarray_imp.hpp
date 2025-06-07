/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <cassert>
#include <cdarray.hpp>
#include <cstddef>
#include <memory>
#include <sstream>
#include <stdexcept>

size_t cInc(size_t v, size_t size);

template <class T> size_t CDArray<T>::capacity() const {
  // TODO: recode with respect to your representation.
  return cap_;
  //
}

template <class T> size_t CDArray<T>::size() const {
  // TODO: recode with respect to your representation.
  return size_;
  //
}

template <class T> bool CDArray<T>::is_empty() const {
  // TODO: recode with respect to your representation.
  if (size_ == 0) {
    return true;
  }
  return false;
  //
}

template <class T> bool CDArray<T>::is_full() const {
  bool ret_v = false;
  // TODO
  if (size_ == cap_) {
    ret_v = true;
  }
  //
  assert(!ret_v || size() == capacity());
  return ret_v;
}

template <class T> CDArray<T>::CDArray(size_t cap) {
  assert(cap > 0);
  // TODO
  cap_ = cap;
  size_ = 0;
  front_ = 0;
  back_ = 0;
  v_ = std::shared_ptr<T[]>(new T[cap_]);
  //
  assert(capacity() == cap);
  assert(is_empty());
  assert(size() == 0);
}

template <class T> CDArray<T>::~CDArray() {
  // TODO
  // Remember: depending on your representation, it is possible that nothing
  // must be done.

  //
}

template <class T>
CDArray<T>::CDArray(std::istream &in) noexcept(false) : CDArray(1) {
  std::string token;
  in >> token;

  // TODO
  // Hint: use std::istringstream to convert from "string" to template
  //  parameter T type.
  // Remember: throw std::runtime_error("Wrong input format.") exception when an
  // input
  //  format error was found.
  if (token != "[") {
    throw std::runtime_error("Wrong input format.");
  }

  while ((in >> token) && (token != "]")) {
    T temp;
    std::istringstream val(token);

    if (!(val >> temp)) {
      throw std::runtime_error("Wrong input format.");
    }

    push_back(temp);
  }

  if (token != "]") {
    throw std::runtime_error("Wrong input format.");
  }
  //
}

template <class T> std::ostream &CDArray<T>::fold(std::ostream &out) const {
  // TODO
  out << "[";
  for (size_t i = front_; i != back_; i = cInc(i, cap_)) {
    out << get(i);
  }
  out << get(back_);
  out << "]";
  //
  return out;
}

template <class T> T const &CDArray<T>::get(size_t pos) const {
  // TODO: recode with respect to your representation.
  size_t actualPos = front_;
  for (size_t i = 0; i < pos; i++) {
    actualPos = cInc(actualPos, cap_);
  }
  return v_[actualPos];
  //
}

template <class T> void CDArray<T>::set(size_t pos, T const &new_v) {
  // TODO
  size_t actualPos = front_;
  for (size_t i = 0; i < pos; i++) {
    actualPos = cInc(actualPos, cap_);
  }

  v_[actualPos] = new_v;
  //
  assert(new_v == get(pos));
}

size_t cInc(size_t v, size_t size) {
  size_t ret_v;
  // TODO
  ret_v = (v + 1) % size;
  //
  return ret_v;
}

size_t cDec(size_t v, size_t size) {
#ifndef NDEBUG
  size_t old_v = v;
#endif
  size_t ret_v;
  // TODO
  // Remember: v is a unsigned value, so you must cast to signed before
  // decrementing
  ret_v = ((int)v - 1) % size;
  //
  assert(old_v == cInc(ret_v, size));
  return ret_v;
}

template <class T> void CDArray<T>::push_front(T const &new_it) {
#ifndef NDEBUG
  size_t old_size = size();
  bool old_is_empty = is_empty();
  T old_front = is_empty() ? T() : get(0);
#endif
  // TODO
  if (size_ == cap_) {
    grow();
  }

  if (!is_empty()) {
    front_ = cDec(front_, cap_);
  }
  v_[front_] = new_it;
  size_++;
  //
  assert(size() == old_size + 1);
  assert(get(0) == new_it);
  assert(old_is_empty || (get(1) == old_front));
}

template <class T> void CDArray<T>::push_back(T const &new_it) {
#ifndef NDEBUG
  size_t old_size = size();
  bool old_is_empty = is_empty();
  T old_back = is_empty() ? T() : get(size() - 1);
#endif
  // TODO
  if (size_ == cap_) {
    grow();
  }

  if (!is_empty()) {
    back_ = cInc(back_, cap_);
  }
  v_[back_] = new_it;
  size_++;
  //
  assert(size() == old_size + 1);
  assert(get(size() - 1) == new_it);
  assert(old_is_empty || (get(size() - 2) == old_back));
}

template <class T> void CDArray<T>::pop_front() {
#ifndef NDEBUG
  size_t old_size = size();
  T old_next_front = size() > 1 ? get(1) : T();
#endif
  // TODO
  front_ = cInc(front_, cap_);
  size_--;
  //
  assert(size() == old_size - 1);
  assert(is_empty() || get(0) == old_next_front);
}

template <class T> void CDArray<T>::pop_back() {
#ifndef NDEBUG
  size_t old_size = size();
  T old_prev_back = size() > 1 ? get(size() - 2) : T();
#endif
  // TODO
  back_ = cDec(back_, cap_);
  size_--;
  //
  assert(size() == old_size - 1);
  assert(is_empty() || get(size() - 1) == old_prev_back);
}

template <class T> void CDArray<T>::insert(size_t pos, T const &v) {
  assert(pos >= 0 && pos < size());
#ifndef NDEBUG
  size_t old_size = size();
  T old_back = get(size() - 1);
  T old_pos_v = get(pos);
#endif
  // TODO
  // Hint: if pos==0, delegate in push_front.
  // Remember: back_ needs to be updated too.
  if (size_ == cap_) {
    grow();
  }

  if (pos == 0) {
    push_front(v);
  } else {
    std::shared_ptr<T[]> aux = std::shared_ptr<T[]>(new T[cap_]);

    size_t contaux = 0;
    size_t contv = front_;
    while (contv != back_) {
      if (contaux == pos) {
        aux[contaux] = v;
      } else {
        aux[contaux] = v_[contv];
        contv = cInc(contv, cap_);
      }

      contaux++;
    }
    aux[contaux] = v_[back_];

    size_++;
    front_ = 0;
    back_ = size_ - 1;
    v_ = aux;
  }
  //
  assert(size() == old_size + 1);
  assert(get(pos) == v);
  assert(get(pos + 1) == old_pos_v);
  assert(get(size() - 1) == old_back);
}

template <class T> void CDArray<T>::remove(size_t pos) {
  assert(pos >= 0 && pos < size());
#ifndef NDEBUG
  size_t old_size = size();
  T old_next_pos_v = (pos <= (size() - 2)) ? get(pos + 1) : T();
#endif
  // TODO
  // Remember: back_ needs to be updated.
  if (pos == size_) {
    pop_back();
  } else {
    std::shared_ptr<T[]> aux = std::shared_ptr<T[]>(new T[cap_]);

    size_t contaux = 0;
    size_t contv = front_;
    pos = (pos + front_) % cap_;

    while (contv != back_) {
      if (contv != pos) {
        aux[contaux] = v_[contv];
        contaux++;
      }

      contv = cInc(contv, cap_);
    }
    if (contaux != pos) {
      aux[contaux] = v_[back_];
    }

    size_--;
    front_ = 0;
    back_ = size_ - 1;
    v_ = aux;
  }
  //
  assert(size() == old_size - 1);
  assert(pos == size() || get(pos) == old_next_pos_v);
}

template <class T> void CDArray<T>::grow() {
#ifndef NDEBUG
  size_t old_capacity = capacity();
  T old_front = get(0);
  T old_back = get(size() - 1);
#endif
  // TODO
  std::shared_ptr<T[]> aux = std::shared_ptr<T[]>(new T[cap_ * 2]);
  int cont = 0;
  for (size_t i = front_; i != back_; i = cInc(i, cap_)) {
    aux[cont] = v_[i];
    cont++;
  }
  aux[cont] = v_[back_];

  v_ = aux;
  front_ = 0;
  back_ = size_ - 1;
  cap_ = cap_ * 2;
  //
  assert(capacity() == 2 * old_capacity);
  assert(get(0) == old_front);
  assert(get(size() - 1) == old_back);
}
