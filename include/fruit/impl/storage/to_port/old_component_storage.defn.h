/*
 * Copyright 2014 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FRUIT_COMPONENT_STORAGE_DEFN_H
#define FRUIT_COMPONENT_STORAGE_DEFN_H

#include <fruit/impl/util/demangle_type_name.h>
#include <fruit/impl/util/type_info.h>
#include <fruit/impl/fruit_assert.h>
#include <fruit/impl/meta/vector.h>
#include <fruit/impl/util/lambda_invoker.h>
#include <fruit/component.h>
#include <fruit/impl/bindings/lazy_component_with_no_args.h>
#include <fruit/impl/generic_lazy_component.h>

// Not necessary, just to make KDevelop happy.
#include <fruit/impl/storage/to_port/old_component_storage.h>

namespace fruit {
namespace impl {

inline OldComponentStorage::OldComponentStorage(const OldComponentStorage& other) {
  *this = other;
}

inline std::size_t OldComponentStorage::numBindings() const {
  return bindings.size();
}

inline std::size_t OldComponentStorage::numCompressedBindings() const {
  return compressed_bindings.size();
}

inline std::size_t OldComponentStorage::numMultibindings() const {
  return multibindings.size();
}

inline void OldComponentStorage::expectBindings(std::size_t n) {
  bindings.reserve(n);
}

inline void OldComponentStorage::expectCompressedBindings(std::size_t n) {
  compressed_bindings.reserve(n);
}

inline void OldComponentStorage::expectMultibindings(std::size_t n) {
  multibindings.reserve(n);
}

inline void OldComponentStorage::addBinding(std::tuple<TypeId, BindingData> t) throw() {
  bindings.push_back(std::make_pair(std::get<0>(t), std::get<1>(t)));
}

inline void OldComponentStorage::addCompressedBinding(std::tuple<TypeId, TypeId, BindingData> t) throw() {
  compressed_bindings.push_back(OldCompressedBinding{std::get<0>(t), std::get<1>(t), std::get<2>(t)});
}

inline void OldComponentStorage::addMultibinding(std::tuple<TypeId, MultibindingData> t) throw() {
  multibindings.emplace_back(std::get<0>(t), std::get<1>(t));
}

inline void OldComponentStorage::install(LazyComponent* lazy_component) throw() {
  lazy_components.push_back(OwningGenericLazyComponent::create(lazy_component));
}

inline void OldComponentStorage::install(LazyComponentWithNoArgs lazy_component) throw() {
  lazy_components.push_back(OwningGenericLazyComponent::create(lazy_component));
}


} // namespace fruit
} // namespace impl


#endif // FRUIT_COMPONENT_STORAGE_DEFN_H